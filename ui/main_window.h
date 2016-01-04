#pragma once
#include <QMainWindow>
#include "Z80/processor.h"
#include "Z80/emu_alu.h"
#include "ui/DisassemblyModel.h"
#include <QStandardItemModel>
#include <QTimer>
#include <QSignalMapper>

#include <QImage>

#include <QSystemTrayIcon>

#include "spdlog/spdlog.h"
#include "badgercomputer.h"
#include "scripting/script_host.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
  BadgerComputer *computer;
  ScriptHost *scriptHost;
  QImage image = QImage(256, 192, QImage::Format_RGB32);
  QRgb valueOn = qRgb(0x0, 0x0, 0x0);
  QRgb valueOff = qRgb(0xCD, 0xCD, 0xCD);

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

//     void setVisible(bool visible) Q_DECL_OVERRIDE;

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
private:
  Ui::MainWindow *ui;

  DisassemblyModel *disassemblyModel;
  QTimer timer;
  QSignalMapper recentItemsSignalMapper;
  
  QSystemTrayIcon *trayIcon;
  QMenu *trayIconMenu;
  QAction *minimizeAction;
  QAction *maximizeAction;
  QAction *restoreAction;
  QAction *quitAction;
    
    
  bool scrollMemory = true;
  void initial_recent_menu_population();
  void add_recent_menu_item(QString rom_path);
  void update_register_values();
  void drawPixel(std::uint16_t x, std::uint16_t y, bool on);
  void updateScreen();
  std::string get_file_contents(const char *filename);
  void save_file(const char *filename, std::string contents);
  void createActions();
  void createTrayIcon();
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
  void print_debug_stats();
  void moveDebuggerToPC(std::uint16_t address);
  void setPC(std::uint16_t address);
  void haltOnBreakpoint();
  void resume();
  void toggleScrollMemory(bool scroll);
  void gfxUpdated(std::uint16_t i);
  void executeScript();
  void saveScript();
  void loadScript();
  void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void showMessage();
  void messageClicked();
  
signals:
  void programCounterUpdated(std::uint16_t address);
};
