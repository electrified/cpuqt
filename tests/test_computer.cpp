#include "test_computer.h"

TestComputer::TestComputer()
{
    io = new TestIO();
    memory = new BadgerMemory();
    registers = new Registers();
    alu = new EmuAlu(memory, io, registers);
    processor = new Processor(memory, io);
}

TestComputer::~TestComputer()
{
    delete io;
    delete memory;
    delete registers;
    delete alu;
    delete processor;
}

BadgerMemory* TestComputer::getMemory() {
    return memory;
}

TestIO* TestComputer::getIO() {
    return io;
}

Processor* TestComputer::getProcessor() {
    return processor;
}
