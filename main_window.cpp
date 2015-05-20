#include "main_window.h"
#include "ui_main_window.h"
#include <QFileDialog>
#include "Logger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadRom() {
    Logger l;
    l.debug("Loadrom called");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open ROM"), "~", tr("ROM Files (*.rom *.bin)"));
}