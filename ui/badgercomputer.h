#ifndef BADGERCOMPUTER_H
#define BADGERCOMPUTER_H

#include <cstdint>
#include "Z80/processor.h"
#include "ui/qtbadgermemory.h"
#include "ui/qtbadgerio.h"
#include "Z80/alu.h"
#include "computer/spectrum/spectrumio.h"
#include <set>

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
  void doOneScreenRefreshesWorth();
  void step();
  void addBreakpoint(const std::uint16_t pc);
  void removeBreakpoint(const std::uint16_t pc);
  void listBreakpoints();
signals:
  void hitbreakpoint();

private:
  set<uint16_t> breakpoints;
};

#endif // BADGERCOMPUTER_H
