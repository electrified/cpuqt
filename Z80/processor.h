#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>

#include "RegisterPair.hpp"
#include "Register.hpp"
#include "Condition.hpp"
#include "MemoryAddress.h"
#include "Memory.h"
#include "IO.h"
#include "alu.h"
#include "registers.h"
#include "decoder.h"

class Processor
{
    Memory* memory;
    IO* io;
    Alu* alu;
    Registers* registers;
    Decoder* decoder;
public:
    Processor(Memory* memory, IO* io, Alu* alu, Registers* registers);
    Processor(Memory* memory, IO* io);
    ~Processor();

    void process();
    void process(std::uint8_t count);
    Memory* getMemory();
    IO* getIO();
    Registers* getRegisters();
    void placeProgramCounterOnAddressBus();
    void reset();
};

#endif // PROCESSOR_H
