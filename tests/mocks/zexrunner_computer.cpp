#include "zexrunner_computer.h"
#include "../computer/cpm/console_serial_io.h"

ZexRunnerComputer::ZexRunnerComputer() {
  io = new ConsoleSerialIO();
  memory = new BadgerMemory();
  processor = new Processor(memory, io);
}

ZexRunnerComputer::~ZexRunnerComputer() {
  delete io;
  delete memory;
  delete processor;
}

BadgerMemory *ZexRunnerComputer::getMemory() { return memory; }

IO *ZexRunnerComputer::getIO() { return io; }

Processor *ZexRunnerComputer::getProcessor() { return processor; }
