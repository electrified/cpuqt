#ifndef TESTCOMPUTER_H
#define TESTCOMPUTER_H
#include "Z80/processor.h"
#include "Z80/emu_alu.h"
#include "Z80/BadgerMemory.h"
#include "Z80/TestIO.h"


class TestComputer
{
    TestIO& io = *new TestIO();
    BadgerMemory& memory = *new BadgerMemory();
    Processor& processor = *new Processor(memory, io);
public:
    TestComputer();
    Memory& getMemory();
    IO& getIO();
    Processor& getProcessor();
};

#endif // TESTCOMPUTER_H
