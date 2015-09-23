#ifndef TESTCOMPUTER_H
#define TESTCOMPUTER_H
#include "Z80/processor.h"
#include "Z80/emu_alu.h"
#include "Z80/BadgerMemory.h"
#include "Z80/TestIO.h"


class TestComputer
{
    TestIO* io;
    BadgerMemory* memory;
    Registers* registers;
    EmuAlu* alu;
    Processor* processor;
public:
    TestComputer();
    ~TestComputer();
    BadgerMemory* getMemory();
    TestIO* getIO();
    void setIO(IO* io);
    Processor* getProcessor();
};

#endif // TESTCOMPUTER_H
