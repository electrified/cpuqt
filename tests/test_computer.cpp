#include "test_computer.h"

TestComputer::TestComputer()
{
    io = new TestIO();
    memory = new BadgerMemory();
    registers = new Registers();
    alu = new EmuAlu(memory, io, registers);
    processor = new Processor(memory, io, alu, registers);
}

TestComputer::~TestComputer()
{
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
