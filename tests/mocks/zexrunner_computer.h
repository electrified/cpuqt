#pragma once

#include "../Z80/processor.h"
#include "../Z80/BadgerMemory.h"
#include "../Z80/IO.h"

class ZexRunnerComputer {
  IO *io;
  BadgerMemory *memory;
  Processor *processor;

public:
  ZexRunnerComputer();
  ~ZexRunnerComputer();
  BadgerMemory *getMemory();
  IO *getIO();
  Processor *getProcessor();
};
