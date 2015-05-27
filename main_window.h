#pragma once
#include <QMainWindow>
#include "Z80/Processor.h"
#include "Z80/EmulationProcessor.h"
#include "ui/DisassemblyModel.h"
#include <QStandardItemModel>
#include <QTimer>
#include "Logger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static std::vector<char> ReadAllBytes(char const* filename);
private:
    Ui::MainWindow *ui;
    EmulationProcessor *emulationProcessor;
    // QStandardItemModel provides a classic 
    // item-based approach to working with the model.
//     QStandardItemModel *model;
    DisassemblyModel *model2;
    QTimer timer;
    Logger l;
    void initial_recent_menu_population();
    void add_recent_menu_item(QString rom_path);
private slots:
    void loadRom();
    void loadRom(QString file_path);
    void showAboutBox();
    void quit();
    void run();
    void stop();
    void update();
    void update_recents_list(QString rom_path);
};

