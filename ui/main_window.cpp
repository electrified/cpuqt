#include "main_window.h"
#include "ui_main_window.h"

#include <iostream>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets/QTableView>
#include <QSettings>
#include <QImage>

#include "ui/qtbadgerio.h"
#include "ui/qtbadgermemory.h"
#include "utils.h"
#include "ui/cpm_io.h"
#include "about_box.h"
#include "computer/utils.h"


void MainWindow::gfxUpdated() {
    QImage image(256, 192, QImage::Format_RGB32);
    QRgb valueOn = qRgb(189, 149, 39);// 0xffbd9527
    QRgb valueOff = qRgb(122, 163, 39); // 0xff7aa327
    
    for (std::uint16_t i = 0x4000; i < 0x57FF; i++) {
        //determine pixel location of byte i
        std::uint8_t x = i & 0x1f; //get bottom 5 bits
        std::uint8_t y = ((i >> 8) & 0x7) | (((i >> 5) & 0x7) << 3) | (((i >> 11) & 0x3) << 6);
        std::uint8_t data = computer->memory->read(i);
        for (std::uint8_t j = 0; j < 8; ++j) {
            std::uint8_t xCoord = (x * 8) + j;
            bool on = (data & (1 << j) >> j);
            image.setPixel(xCoord, y, on ? valueOn : valueOff);
//             std::cout << "GFX UPDATE: x:" << (int)xCoord << " y:" <<  (int)y << " j:" <<  (int)j << std::endl;
        }
    }
    /*
    value 
    image.setPixel(1, 1, value);

    value = qRgb(122, 163, 39); // 0xff7aa327
    image.setPixel(0, 1, value);
    image.setPixel(1, 0, value);

    value = qRgb(237, 187, 51); // 0xffedba31
    image.setPixel(2, 1, value);*/
    ui->gfxLabel->setPixmap(QPixmap::fromImage(image));
//     ui->gfxLabel->setText(QString("hello"));
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    computer = new BadgerComputer();

    disassemblyModel = new DisassemblyModel(computer->memory, this);

    // Attach the model to the view
    ui->disassemblyView->setModel(disassemblyModel);
    ui->disassemblyView->setColumnWidth(0, 50);

    QHeaderView *verticalHeader = ui->disassemblyView->verticalHeader();
    verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(15);

    connect(&recentItemsSignalMapper, SIGNAL(mapped(QString)), this, SLOT(loadRom(QString)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    connect((QtBadgerIO*)computer->io, &QtBadgerIO::consoleTextOutput, this, &MainWindow::outputCharacterToConsole);
    
    connect(computer->memory, SIGNAL(spectrumGfxUpdated(std::uint16_t)), this, SLOT(gfxUpdated()));

    //this is ther text output for cp/m
//     connect((cpm_io*)computer->alu, SIGNAL(consoleTextOutput(char)), this, SLOT(outputCharacterToConsole(char)));

//     connect(computer->memory, SIGNAL(memoryUpdated(std::uint16_t)), disassemblyModel, SLOT(memoryUpdated(std::uint16_t)));
//     connect(this, SIGNAL(programCounterUpdated(std::uint16_t)), disassemblyModel, SLOT(programCounterUpdated(std::uint16_t)));
//     connect(this, SIGNAL(programCounterUpdated(std::uint16_t)), this, SLOT(moveDebuggerToPC(std::uint16_t)));
//     connect(disassemblyModel, SIGNAL(programManuallySet(std::uint16_t)), this, SLOT(setPC(std::uint16_t)));


    connect(computer, SIGNAL(hitbreakpoint()), this, SLOT(haltOnBreakpoint()));
    initial_recent_menu_population();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_recents_list(QString rom_path)
{
    QSettings settings;
    int size = settings.beginReadArray("recentroms");

    bool found = false;

    for (int i = 0; i < size; i++)
    {
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
        settings.setValue("path",rom_path);
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
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        QString existing_path = settings.value("path").toString();
        add_recent_menu_item(existing_path);
    }
    settings.endArray();
}

void MainWindow::add_recent_menu_item(QString rom_path) {
    std::cout << "adding to menu " << rom_path.toStdString() << std::endl;
    QAction* actionLoad_ROM = new QAction(this);
    actionLoad_ROM->setObjectName(rom_path);
    actionLoad_ROM->setText(rom_path);
    ui->menuRecent->addAction(actionLoad_ROM);
    recentItemsSignalMapper.setMapping(actionLoad_ROM, rom_path);
    QObject::connect(actionLoad_ROM, SIGNAL(triggered()), &recentItemsSignalMapper, SLOT(map()));
}

void MainWindow::loadRom() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open ROM"), QDir::homePath(), tr("ROM Files (*.rom *.bin)"),0, QFileDialog::DontUseNativeDialog);

    if (fileName != NULL ) {
        update_recents_list(fileName);
        loadRom(fileName);
    }
}

void MainWindow::loadRom(QString file_path) {
//     QMessageBox::information(this, tr("filename"), file_path);

    auto data = ReadAllBytes(file_path.toUtf8().constData());

    bool tests = false;
    if (file_path.endsWith(QString("zexdoc.bin"))) {
        tests = true;
    }

    std::uint16_t offset = (tests ? 0x100 : 0);

    loadIntoMemory(data, computer->memory, offset);

    // HAX
//     if (tests) {
//         l.debug("patching zexdoc");
//         computer->memory->write(0,0xd3);       /* OUT N, A */
//         computer->memory->write(1,0x00);
// 
//         computer->memory->write(5,0xdb);       /* IN A, N */
//         computer->memory->write(6,0x00); //this val gets used for the stack location
//         computer->memory->write(7,0xc9);
//         computer->processor->getRegisters()->setPC(0x100);
//     }

    disassemblyModel->forceDisassembly();
}

void MainWindow::run()
{
    timer.start(20); //50 times per second 1000/50 = 20
}

void MainWindow::stop()
{
    l.debug("Stopping!");
    timer.stop();
    update_register_values();
    emit programCounterUpdated(computer->processor->getRegisters()->getPC());
}

void MainWindow::update()
{
    computer->doOneScreenRefreshesWorth();
}

void MainWindow::showAboutBox() {
    Dialog * mw = new Dialog();
    mw->show();
}

void MainWindow::quit() {
    QCoreApplication::exit();
}

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
    this->ui->iff1_value->setText(utils::int_to_hex(computer->processor->getRegisters()->isIFF1()));
    this->ui->iff2_value->setText(utils::int_to_hex(computer->processor->getRegisters()->isIFF2()));
}

void MainWindow::step()
{
    computer->step();
    update_register_values();
    emit programCounterUpdated(computer->processor->getRegisters()->getPC());
}

void MainWindow::reset()
{
    computer->reset();
    update_register_values();
}

void MainWindow::outputCharacterToConsole(char value)
{
    this->ui->plainTextEdit->insertPlainText(QString(value));
}

void MainWindow::print_debug_stats()
{
//    this->ui->statusbar->showMessage(QString("Refresh count: %1").arg(QString::number(emulationProcessor->refreshes)), 1000);
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

void MainWindow::haltOnBreakpoint() {
    stop();
}

void MainWindow::resume() {
}

void MainWindow::toggleScrollMemory(bool scroll) {
    this->scrollMemory = scroll;
}
