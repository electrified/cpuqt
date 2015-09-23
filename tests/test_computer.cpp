#include "test_computer.h"
#include "computer/consolebadgerio.h"

TestComputer::TestComputer()
{
//     io = new TestIO();
    io = new ConsoleBadgerIO();
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

IO* TestComputer::getIO() {
    return io;
}

Processor* TestComputer::getProcessor() {
    return processor;
}

void TestComputer::setIO(IO* io) {
    io = io;
}
