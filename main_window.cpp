#include "main_window.h"
#include "ui_main_window.h"

#include <fstream>
#include <vector>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QtWidgets/QTableView>
#include <QSettings>

#include "Z80/badgerio.h"
#include "Z80/BadgerMemory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BadgerMemory* bm = new BadgerMemory();
    BadgerIO* bo = new BadgerIO();

    emulationProcessor = new EmulationProcessor(*bm, *bo);
    
    model2 = new DisassemblyModel(*bm, this);

        Logger l;
    l.debug("MainWindow::MainWindow");

    // Attach the model to the view
    ui->disassemblyView->setModel(model2);
    
//     timer = new QTimer(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    
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
        settings.beginReadArray("recentroms");
        settings.setArrayIndex(size);
        settings.setValue("path",rom_path);
        settings.endArray();
        settings.sync();
        

    }
}

void MainWindow::initial_recent_menu_population() {
 QSettings settings;     
    int size = settings.beginReadArray("recentroms");
    
    for (int i = 0; i < size; i++) 
    {
        settings.setArrayIndex(i);
        QString existing_path = settings.value("path").toString();
        add_recent_menu_item(existing_path);
    }
    settings.endArray();
}

void MainWindow::add_recent_menu_item(QString rom_path) {
    QAction* actionLoad_ROM = new QAction(this);
    actionLoad_ROM->setObjectName(rom_path);
//         actionLoad_ROM.setData(rom_path);
    ui->menuRecent->addAction(actionLoad_ROM);
    QObject::connect(actionLoad_ROM, SIGNAL(triggered()), this, SLOT(loadRom(rom_path)));
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
        emulationProcessor->getMemory().write(i, data.at(i));
    }
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
}

void MainWindow::showAboutBox() {
    
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