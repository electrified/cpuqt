#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>
#include <QMessageBox>

#include "spdlog/spdlog.h"

#include "about_box.h"
#include "computer/utils.h"
#include "keypresseater.h"
#include "qdebugstream.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  computer = new BadgerComputer();

  disassemblyModel = new DisassemblyModel(computer->memory, this);

  scriptHost = new ScriptHost(computer);

  //   QDebugStream qout(std::cout, this->ui->scriptOutput);

  settings = new Settings();

  // Attach the model to the view
  ui->disassemblyView->setModel(disassemblyModel);
  ui->disassemblyView->setColumnWidth(0, 50);

  QHeaderView *verticalHeader = ui->disassemblyView->verticalHeader();
  verticalHeader->sectionResizeMode(QHeaderView::Fixed);
  verticalHeader->setDefaultSectionSize(15);

  connect(&recentRomsSignalMapper, SIGNAL(mapped(QString)), this, SLOT(loadRom(QString)));
  connect(&recentScriptsSignalMapper, SIGNAL(mapped(QString)), this, SLOT(loadScript(QString)));
  connect(computer, SIGNAL(gfxUpdated()), this, SLOT(update()));
  connect(computer->memory, SIGNAL(spectrumGfxUpdated(std::uint16_t)), this, SLOT(gfxUpdated(std::uint16_t)));
  connect(computer, SIGNAL(hitbreakpoint()), this, SLOT(haltOnBreakpoint()));

  connect(computer->memory, SIGNAL(memoryUpdated(std::uint16_t)), disassemblyModel, SLOT(memoryUpdated(std::uint16_t)));
  connect(this, SIGNAL(programCounterUpdated(std::uint16_t)), disassemblyModel,
          SLOT(programCounterUpdated(std::uint16_t)));
  connect(this, SIGNAL(programCounterUpdated(std::uint16_t)), this, SLOT(moveDebuggerToPC(std::uint16_t)));
  connect(disassemblyModel, SIGNAL(programManuallySet(std::uint16_t)), this, SLOT(setPC(std::uint16_t)));

  initialRecentMenuPopulation(settings->recent_roms, ui->menuRecent, &recentRomsSignalMapper);
  initialRecentMenuPopulation(settings->recent_scripts, ui->recentScriptMenu, &recentScriptsSignalMapper);

  KeyPressEater *keyPressEater = new KeyPressEater(computer->io);

  ui->spectrumInput->installEventFilter(keyPressEater);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::gfxUpdated(std::uint16_t memoryAddress) {

  spdlog::get("general")->trace("gfxUpdated(std::uint16_t memoryAddress)");
  /*
   * Y Coordinate bit layout (MSB to LSB):
      zzxxxnnn

      Register pair bit layout (R are the bits for the x-axis offset, 010 provides the base address $4000):
      010z znnn xxxR RRRR
  */
  std::uint8_t data = computer->memory->read(memoryAddress);

  if (memoryAddress < 0x5800) {
    std::uint16_t x = memoryAddress & 0x1f; // get bottom 5 bits
    std::uint16_t y = ((memoryAddress & 0x700) >> 8) | ((memoryAddress & 0xe0) >> 2) | ((memoryAddress & 0x1800) >> 5);

    for (std::uint8_t j = 0; j < 8; ++j) {
      std::uint8_t xCoord = (x * 8) + j;
      bool on = (data << j) & 0x80;
      drawPixel(xCoord, y, on);
      // std::cout << "GFX UPDATE: x:" << (int)xCoord << " y:" <<  (int)y << " j:" <<  (int)j << " i: " << i <<
      // std::endl;
    }
  } else {
    // colour stuff
    bool flash = data & 0x80;
    bool bright = data & 0x40;
    uint8_t paper_colour = data & 0x38;
    uint8_t ink_colour = data & 0x7;
  }
}

void MainWindow::drawPixel(std::uint16_t x, std::uint16_t y, bool on) { image.setPixel(x, y, on ? valueOn : valueOff); }

void MainWindow::initialRecentMenuPopulation(QString list_name, QMenu *menu, QSignalMapper *signal_mapper) {
  std::list<QString> recentFiles = settings->get_recents_list(list_name);

  for (std::list<QString>::const_iterator iterator = recentFiles.begin(), end = recentFiles.end(); iterator != end;
       ++iterator) {
    addRecentMenuItem(*iterator, menu, signal_mapper);
  }
}

void MainWindow::addRecentMenuItem(QString file_path, QMenu *menu, QSignalMapper *signal_mapper) {
  std::cout << "adding to menu " << file_path.toStdString() << std::endl;
  QAction *recent_menu_item_action = new QAction(this);
  recent_menu_item_action->setObjectName(file_path);
  recent_menu_item_action->setText(file_path);
  menu->addAction(recent_menu_item_action);
  signal_mapper->setMapping(recent_menu_item_action, file_path);
  QObject::connect(recent_menu_item_action, SIGNAL(triggered()), signal_mapper, SLOT(map()));
}

void MainWindow::loadRom() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open ROM"), QDir::homePath(), tr("ROM Files (*.rom *.bin)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    settings->update_recents_list(settings->recent_roms, fileName);
    loadRom(fileName);
  }
}

void MainWindow::loadRom(QString file_path) {
  scriptHost->loadRom(file_path.toUtf8().constData());
  disassemblyModel->forceDisassembly();
}

void MainWindow::loadSnapshot() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Snapshot"), QDir::homePath(),
                                                  tr("Snapshot Files (*.z80)"), 0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    loadSnapshot(fileName);
  }
}

void MainWindow::loadSnapshot(QString file_path) { scriptHost->loadSnapshot(file_path.toUtf8().constData()); }

void MainWindow::run() { computer->run(); }

void MainWindow::stop() {
  computer->stop();
  updateRegisterValues();
  emit programCounterUpdated(computer->processor->getRegisters()->getPC());
}

void MainWindow::update() { updateScreen(); }

void MainWindow::updateScreen() { ui->gfxLabel->setPixmap(QPixmap::fromImage(image).scaled(512, 384)); }

void MainWindow::showAboutBox() {
  Dialog *mw = new Dialog();
  mw->show();
}

void MainWindow::quit() { QCoreApplication::exit(); }

void MainWindow::updateRegisterValues() {
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
  updateRegisterValues();
  emit programCounterUpdated(computer->processor->getRegisters()->getPC());
  //   moveDebuggerToPC(computer->processor->getRegisters()->getPC());
  updateScreen();
}

void MainWindow::reset() {
  computer->reset();
  updateRegisterValues();
}

void MainWindow::print_debug_stats() {
  //    this->ui->statusbar->showMessage(QString("Refresh count:
  //    %1").arg(QString::number(emulationProcessor->refreshes)), 1000);
  updateRegisterValues();
}

void MainWindow::moveDebuggerToPC(std::uint16_t address) {
  if (this->scrollMemory) {
    this->ui->disassemblyView->scrollTo(disassemblyModel->index(address, 0));
  }
}

void MainWindow::setPC(std::uint16_t address) {
  computer->processor->getRegisters()->setPC(address);
  updateRegisterValues();
  emit programCounterUpdated(computer->processor->getRegisters()->getPC());
}

void MainWindow::haltOnBreakpoint() {
  stop();
  disassemblyModel->forceDisassembly();
}

void MainWindow::toggleScrollMemory(bool scroll) { this->scrollMemory = scroll; }

void MainWindow::executeScript() {
  QString script = this->ui->scriptEdit->toPlainText();
  scriptHost->runCommand(script.toStdString());
}

void MainWindow::loadScript() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open script"), QDir::homePath(), tr("Lua scripts (*.lua)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    settings->update_recents_list(settings->recent_scripts, fileName);
    loadScript(fileName);
  }
}

void MainWindow::loadScript(QString file_name) {
  std::string script_contents = utils::get_file_contents(file_name.toLocal8Bit());
  ui->scriptEdit->clear();
  ui->scriptEdit->appendPlainText(QString::fromStdString(script_contents));
}

void MainWindow::saveScript() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save script"), QDir::homePath(), tr("Lua scripts (*.lua)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  if (fileName != NULL) {
    utils::save_file(fileName.toLocal8Bit(), ui->scriptEdit->toPlainText().toStdString());
  }
}
