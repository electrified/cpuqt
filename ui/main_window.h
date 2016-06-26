#pragma once
#include <QMainWindow>
#include "Z80/processor.h"
#include "ui/DisassemblyModel.h"
#include <QStandardItemModel>
#include <QSignalMapper>
#include <QImage>

#include "spdlog/spdlog.h"
#include "badgercomputer.h"
#include "scripting/script_host.h"
#include "settings.h"

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
  Settings *settings;
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private:
  Ui::MainWindow *ui;

  DisassemblyModel *disassemblyModel;

  QSignalMapper recentRomsSignalMapper;
  QSignalMapper recentScriptsSignalMapper;
  
  bool scrollMemory = true;
  void initialRecentMenuPopulation(QString list_name, QMenu* menu, QSignalMapper* signal_mapper);
  void addRecentMenuItem(QString file_path, QMenu* menu, QSignalMapper* signal_mapper);
  void updateRegisterValues();
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
  void loadScript(QString file_path);
  void loadSnapshot();
  void loadSnapshot(QString file_path);
signals:
  void programCounterUpdated(std::uint16_t address);
};
