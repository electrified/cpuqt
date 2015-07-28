#pragma once
#include <QMainWindow>
#include "Z80/processor.h"
#include "Z80/emu_alu.h"
#include "ui/DisassemblyModel.h"
#include <QStandardItemModel>
#include <QTimer>
#include <QSignalMapper>

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
    Processor *emulationProcessor;
    DisassemblyModel *disassemblyModel;
    QTimer timer;
    QSignalMapper recentItemsSignalMapper;
    Logger l;
    void initial_recent_menu_population();
    void add_recent_menu_item(QString rom_path);
    void update_register_values();
private slots:
    void loadRom();
    void loadRom(QString file_path);
    void showAboutBox();
    void quit();
    void run();
    void stop();
    void update();
    void update_recents_list(QString rom_path);
    void step();
    void reset();
    void outputCharacterToConsole(char value);
    void print_debug_stats();
    void moveDebuggerToPC(std::uint16_t address);
    void setPC(std::uint16_t address);
signals:
    void programCounterUpdated(std::uint16_t address);
};

