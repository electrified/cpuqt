#include "main_window.h"
#include "ui_main_window.h"

#include <iostream>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets/QTableView>
#include <QSettings>
#include <QImage>

// for loading script
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>

#include "ui/qtbadgerio.h"
#include "ui/qtbadgermemory.h"
#include "utils.h"
#include "ui/cpm_io.h"
#include "about_box.h"
#include "computer/utils.h"
#include "qdebugstream.h"
#include "spdlog/spdlog.h"
#include "keypresseater.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  computer = new BadgerComputer();

  disassemblyModel = new DisassemblyModel(computer->memory, this);

  scriptHost = new ScriptHost(computer);

  QDebugStream qout(std::cout, this->ui->scriptOutput);

  // Attach the model to the view
  ui->disassemblyView->setModel(disassemblyModel);
  ui->disassemblyView->setColumnWidth(0, 50);

  QHeaderView *verticalHeader = ui->disassemblyView->verticalHeader();
  verticalHeader->sectionResizeMode(QHeaderView::Fixed);
  verticalHeader->setDefaultSectionSize(15);

  connect(&recentItemsSignalMapper, SIGNAL(mapped(QString)), this, SLOT(loadRom(QString)));
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  connect(computer->memory, SIGNAL(spectrumGfxUpdated(std::uint16_t)), this, SLOT(gfxUpdated(std::uint16_t)));
  connect(computer, SIGNAL(hitbreakpoint()), this, SLOT(haltOnBreakpoint()));

  connect(computer->memory, SIGNAL(memoryUpdated(std::uint16_t)), disassemblyModel, SLOT(memoryUpdated(std::uint16_t)));
  connect(this, SIGNAL(programCounterUpdated(std::uint16_t)), disassemblyModel,
          SLOT(programCounterUpdated(std::uint16_t)));
  connect(this, SIGNAL(programCounterUpdated(std::uint16_t)), this, SLOT(moveDebuggerToPC(std::uint16_t)));
  connect(disassemblyModel, SIGNAL(programManuallySet(std::uint16_t)), this, SLOT(setPC(std::uint16_t)));

  initial_recent_menu_population();

  KeyPressEater *keyPressEater = new KeyPressEater(computer->io);

  ui->spectrumInput->installEventFilter(keyPressEater);
  
  createActions();
  createTrayIcon();
  trayIcon->setIcon(QIcon(":/toolbar/badger.jpg"));
  trayIcon->show();
  
  connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::gfxUpdated(std::uint16_t i) {
  /*
   * Y Coordinate bit layout (MSB to LSB):
      zzxxxnnn

      Register pair bit layout (R are the bits for the x-axis offset, 010 provides the base address $4000):
      010z znnn xxxR RRRR
  */
  if (i < 0x5800) {
    std::uint16_t x = i & 0x1f; // get bottom 5 bits
    std::uint16_t y = ((i & 0x700) >> 8) | ((i & 0xe0) >> 2) | ((i & 0x1800) >> 5);

    std::uint8_t data = computer->memory->read(i);
    for (std::uint8_t j = 0; j < 8; ++j) {
      std::uint8_t xCoord = (x * 8) + j;
      bool on = (data << j) & 0x80;
      drawPixel(xCoord, y, on);
      // std::cout << "GFX UPDATE: x:" << (int)xCoord << " y:" <<  (int)y << " j:" <<  (int)j << " i: " << i <<
      // std::endl;
    }
  } else {
    // colour stuff
  }
}

void MainWindow::drawPixel(std::uint16_t x, std::uint16_t y, bool on) { image.setPixel(x, y, on ? valueOn : valueOff); }

void MainWindow::update_recents_list(QString rom_path) {
  QSettings settings;
  int size = settings.beginReadArray("recentroms");

  bool found = false;

  for (int i = 0; i < size; i++) {
    settings.setArrayIndex(i);
    QString existing_path = settings.value("path").toString();
    if (existing_path == rom_path) {
      found = true;
    }
  }
  settings.endArray();

  if (!found) {
    settings.beginWriteArray("recentroms");
    settings.setArrayIndex(size);
    settings.setValue("path", rom_path);
    settings.endArray();
    settings.sync();
    add_recent_menu_item(rom_path);
  }
}

void MainWindow::initial_recent_menu_population() {
  QSettings settings;
  std::cout << settings.fileName().toStdString() << std::endl;
  int size = settings.beginReadArray("recentroms");
  std::cout << "reading vals from config file " << size << std::endl;
  for (int i = 0; i < size; ++i) {
    settings.setArrayIndex(i);
    QString existing_path = settings.value("path").toString();
    add_recent_menu_item(existing_path);
  }
  settings.endArray();
}

void MainWindow::add_recent_menu_item(QString rom_path) {
  std::cout << "adding to menu " << rom_path.toStdString() << std::endl;
  QAction *actionLoad_ROM = new QAction(this);
  actionLoad_ROM->setObjectName(rom_path);
  actionLoad_ROM->setText(rom_path);
  ui->menuRecent->addAction(actionLoad_ROM);
  recentItemsSignalMapper.setMapping(actionLoad_ROM, rom_path);
  QObject::connect(actionLoad_ROM, SIGNAL(triggered()), &recentItemsSignalMapper, SLOT(map()));
}

void MainWindow::loadRom() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open ROM"), QDir::homePath(), tr("ROM Files (*.rom *.bin)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    update_recents_list(fileName);
    loadRom(fileName);
  }
}

void MainWindow::loadRom(QString file_path) {
  auto data = ReadAllBytes(file_path.toUtf8().constData());

  loadIntoMemory(data, computer->memory, 0);
  disassemblyModel->forceDisassembly();
}

void MainWindow::loadSnapshot() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Snapshot"), QDir::homePath(), tr("Snapshot Files (*.z80)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    loadSnapshot(fileName);
  }
}

void MainWindow::loadSnapshot(QString file_path) {
  auto data = ReadAllBytes(file_path.toUtf8().constData());

  loadZ80Snapshot(data, computer->memory, computer->processor->getRegisters());
//   disassemblyModel->forceDisassembly();
}

void MainWindow::run() {
  timer.start(20); // 50 times per second 1000/50 = 20
}

void MainWindow::stop() {
  spdlog::get("console")->debug("Stopping!");
  timer.stop();
  update_register_values();
  emit programCounterUpdated(computer->processor->getRegisters()->getPC());
}

void MainWindow::update() {
  computer->doOneScreenRefreshesWorth();
  updateScreen();
}

void MainWindow::updateScreen() { ui->gfxLabel->setPixmap(QPixmap::fromImage(image).scaled(512, 384)); }

void MainWindow::showAboutBox() {
  Dialog *mw = new Dialog();
  mw->show();
}

void MainWindow::quit() { QCoreApplication::exit(); }

void MainWindow::update_register_values() {
  this->ui->pc_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getPC()));
  this->ui->sp_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getSP()));
  this->ui->ix_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getIX()));
  this->ui->iy_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getIY()));
  this->ui->hl_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getHL()));
  this->ui->af_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getAF()));
  this->ui->bc_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getBC()));
  this->ui->de_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getDE()));
  this->ui->afalt_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getAF_alt()));
  this->ui->bcalt_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getBC_alt()));
  this->ui->dealt_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getDE_alt()));
  this->ui->hlalt_value->setText(utils::int_to_hex(computer->processor->getRegisters()->getHL_alt()));
  this->ui->iff1_value->setText(utils::int_to_hex(computer->processor->getRegisters()->isIFF1()));
  this->ui->iff2_value->setText(utils::int_to_hex(computer->processor->getRegisters()->isIFF2()));
}

void MainWindow::step() {
  computer->step();
  update_register_values();
  emit programCounterUpdated(computer->processor->getRegisters()->getPC());
  //   moveDebuggerToPC(computer->processor->getRegisters()->getPC());
  updateScreen();
  showMessage();
}

void MainWindow::reset() {
  computer->reset();
  update_register_values();
}

// void MainWindow::outputCharacterToConsole(char value) { this->ui->plainTextEdit->insertPlainText(QString(value)); }

void MainWindow::print_debug_stats() {
  //    this->ui->statusbar->showMessage(QString("Refresh count:
  //    %1").arg(QString::number(emulationProcessor->refreshes)), 1000);
  update_register_values();
}

void MainWindow::moveDebuggerToPC(std::uint16_t address) {
  if (this->scrollMemory) {
    this->ui->disassemblyView->scrollTo(disassemblyModel->index(address, 0));
  }
}

void MainWindow::setPC(std::uint16_t address) {
  computer->processor->getRegisters()->setPC(address);
  update_register_values();
  emit programCounterUpdated(computer->processor->getRegisters()->getPC());
}

void MainWindow::haltOnBreakpoint() { stop(); }

void MainWindow::resume() {}

void MainWindow::toggleScrollMemory(bool scroll) { this->scrollMemory = scroll; }

void MainWindow::executeScript() {
  QString script = this->ui->scriptEdit->toPlainText();
  scriptHost->runCommand(script.toStdString());
}

void MainWindow::loadScript() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open script"), QDir::homePath(), tr("Lua scripts (*.lua)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    std::string script_contents = get_file_contents(fileName.toLocal8Bit());
    ui->scriptEdit->clear();
    ui->scriptEdit->appendPlainText(QString::fromStdString(script_contents));
  }
}

std::string MainWindow::get_file_contents(const char *filename) {
  std::ifstream in(filename, std::ios::in);
  if (in) {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return (contents.str());
  }
  throw(errno);
}

void MainWindow::save_file(const char *filename, std::string contents) {
  std::ofstream out(filename, std::ios::trunc);
  if (out) {
    out << contents;
    out.close();
  }
}

void MainWindow::saveScript() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save script"), QDir::homePath(), tr("Lua scripts (*.lua)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    this->save_file(fileName.toLocal8Bit(), ui->scriptEdit->toPlainText().toStdString());
  }
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}


void MainWindow::showMessage()
{
//     showIconCheckBox->setChecked(true);
//     QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon();
    trayIcon->showMessage("test", "test", QSystemTrayIcon::Critical, 5000);
}

void MainWindow::messageClicked()
{
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

// void MainWindow::setVisible(bool visible)
// {
//     minimizeAction->setEnabled(visible);
//     maximizeAction->setEnabled(!isMaximized());
//     restoreAction->setEnabled(isMaximized() || !visible);
// //     QDialog::setVisible(visible);
// }


void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showMessage();
        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}
