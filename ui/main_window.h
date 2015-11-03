 #pragma once
#include <QMainWindow>
#include "Z80/processor.h"
#include "Z80/emu_alu.h"
#include "ui/DisassemblyModel.h"
#include <QStandardItemModel>
#include <QTimer>
#include <QSignalMapper>

#include <QImage>

#include "Logger.h"
#include "badgercomputer.h"
#include "ui/scripting/script_host.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    BadgerComputer* computer;
    ScriptHost* scriptHost;
    QImage image = QImage(256, 192, QImage::Format_RGB32);
    QRgb valueOn = qRgb(0x0, 0x0, 0x0);
    QRgb valueOff = qRgb(0xCD, 0xCD, 0xCD);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    DisassemblyModel *disassemblyModel;
    QTimer timer;
    QSignalMapper recentItemsSignalMapper;
    Logger l;
    bool scrollMemory = true;
    void initial_recent_menu_population();
    void add_recent_menu_item(QString rom_path);
    void update_register_values();
    void drawPixel(std::uint16_t x, std::uint16_t y, bool on);
    void updateScreen();
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
    void haltOnBreakpoint();
    void resume();
    void toggleScrollMemory(bool scroll);
    void gfxUpdated(std::uint16_t i);
    void executeScript();
signals:
    void programCounterUpdated(std::uint16_t address);
};

