#include "test_computer.h"
#include "../computer/consolebadgerio.h"

TestComputer::TestComputer() {
  io = new ConsoleBadgerIO();
  memory = new BadgerMemory();
  processor = new Processor(memory, io);
}

TestComputer::~TestComputer() {
  delete io;
  delete memory;
  delete processor;
}

BadgerMemory *TestComputer::getMemory() { return memory; }

IO *TestComputer::getIO() { return io; }

Processor *TestComputer::getProcessor() { return processor; }
