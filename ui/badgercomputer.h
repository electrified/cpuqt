#pragma once

#include <cstdint>
#include <QTimer>
#include <set>

#include "Z80/processor.h"
#include "ui/qtbadgermemory.h"
#include "ui/qtbadgerio.h"
#include "Z80/alu.h"
#include "computer/spectrum/spectrumio.h"


class BadgerComputer : public QObject {
  Q_OBJECT
public:
  BadgerComputer();
  ~BadgerComputer();
  void reset();
  Processor *processor;
  QtBadgerMemory *memory;
  SpectrumIO *io;
  bool skipBreakpoint = false;

  void process(const std::uint8_t count);
  void step();
  void addBreakpoint(const std::uint16_t pc);
  void removeBreakpoint(const std::uint16_t pc);
  void listBreakpoints();
  void run();
  void stop();
private slots:
  void doOneScreenRefreshesWorth();
signals:
  void hitbreakpoint();
  void gfxUpdated();
private:
  set<uint16_t> breakpoints;
  QTimer timer;
};
