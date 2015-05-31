#include "main_window.h"
#include "ui_main_window.h"

#include <iostream>
#include <fstream>

#include <vector>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets/QTableView>
#include <QSettings>

#include "ui/badgerio.h"
#include "Z80/BadgerMemory.h"
#include "utils.h"
#include "ui/cpm_io.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BadgerMemory* bm = new BadgerMemory();
    BadgerIO* bo = new BadgerIO();

    emulationProcessor = new cpm_io(*bm, *bo);

    model2 = new DisassemblyModel(*bm, this);

    // Attach the model to the view
    ui->disassemblyView->setModel(model2);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(bo, &BadgerIO::consoleTextOutput, this, &MainWindow::outputCharacterToConsole);
    
    connect((cpm_io*)emulationProcessor, SIGNAL(consoleTextOutput(char)), this, SLOT(outputCharacterToConsole(char)));
    
    connect(&recentItemsSignalMapper, SIGNAL(mapped(QString)), this, SLOT(loadRom(QString)));
    
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
//         actionLoad_ROM.setData(rom_path);
    ui->menuRecent->addAction(actionLoad_ROM);
    recentItemsSignalMapper.setMapping(actionLoad_ROM, rom_path);
    QObject::connect(actionLoad_ROM, SIGNAL(triggered()), &recentItemsSignalMapper, SLOT(map()));
}

void MainWindow::loadRom() {
    Logger l;
    l.debug("Loadrom called");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open ROM"), QDir::homePath(), tr("ROM Files (*.rom *.bin)"),0, QFileDialog::DontUseNativeDialog);

    if (fileName != NULL ) {
        update_recents_list(fileName);
        loadRom(fileName);
    }
}

void MainWindow::loadRom(QString file_path) {
    QMessageBox::information(this, tr("filename"), file_path);
    auto data = MainWindow::ReadAllBytes(file_path.toUtf8().constData());

    for (int i = 0; i < data.size(); ++i) {
        emulationProcessor->getMemory().write(i + 0x100, data.at(i));
    }
    
    // HAX
    emulationProcessor->getMemory().write(0,0xd3);       /* OUT N, A */
    emulationProcessor->getMemory().write(1,0x00);

    emulationProcessor->getMemory().write(5,0xdb);       /* IN A, N */
    emulationProcessor->getMemory().write(6,0x00);
    emulationProcessor->getMemory().write(7,0xc9);
    emulationProcessor->setPC(0x100);
}

void MainWindow::run()
{
    timer.start(20); //50 times per second 1000/50 = 20
}

void MainWindow::stop()
{
    l.debug("Stopping!");
    timer.stop();
}

void MainWindow::update()
{
    l.debug("update!");
    emulationProcessor->doOneScreenRefreshesWorth();
    update_register_values();
}

void MainWindow::showAboutBox() {
    QMessageBox::about(this,"Badgersoft","Z80 Emulator (c) 2015 Badgersoft");
}

void MainWindow::quit() {
    QCoreApplication::exit();
}

std::vector<char> MainWindow::ReadAllBytes(char const* filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

void MainWindow::update_register_values() {
    this->ui->pc_value->setText(utils::int_to_hex(emulationProcessor->getPC()));
    this->ui->sp_value->setText(utils::int_to_hex(emulationProcessor->getSP()));
    this->ui->ix_value->setText(utils::int_to_hex(emulationProcessor->getIX()));
    this->ui->iy_value->setText(utils::int_to_hex(emulationProcessor->getIY()));
    this->ui->hl_value->setText(utils::int_to_hex(emulationProcessor->getHL()));
    this->ui->a_value->setText(utils::int_to_hex(emulationProcessor->getA()));
    this->ui->b_value->setText(utils::int_to_hex(emulationProcessor->getB()));
    this->ui->c_value->setText(utils::int_to_hex(emulationProcessor->getC()));
    this->ui->d_value->setText(utils::int_to_hex(emulationProcessor->getD()));
    this->ui->e_value->setText(utils::int_to_hex(emulationProcessor->getE()));
    this->ui->f_value->setText(utils::int_to_hex(emulationProcessor->getF()));
    std::cout << "updating display " << std::endl;
}

void MainWindow::step()
{
    emulationProcessor->process();
    update_register_values();
}

void MainWindow::reset()
{
    emulationProcessor->reset();
    update_register_values();
}

void MainWindow::outputCharacterToConsole(char value)
{
    this->ui->plainTextEdit->insertPlainText(QString(value));
}
