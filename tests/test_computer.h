#ifndef TESTCOMPUTER_H
#define TESTCOMPUTER_H
#include "../Z80/processor.h"
#include "../Z80/BadgerMemory.h"
#include "../Z80/IO.h"

class TestComputer {
  IO *io;
  BadgerMemory *memory;
  Processor *processor;

public:
  TestComputer();
  ~TestComputer();
  BadgerMemory *getMemory();
  IO *getIO();
  Processor *getProcessor();
};

#endif // TESTCOMPUTER_H
