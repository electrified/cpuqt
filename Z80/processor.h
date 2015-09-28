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
    
    static inline std::uint8_t next(Memory* memory, std::uint16_t& pc) {
        return memory->read(pc++);
    }
public:
    Processor(Memory* memory, IO* io);
    ~Processor();

    //Memory& memory, Alu& alu, 
    void decode(std::uint16_t& pc);
    void process();
    void process(std::uint8_t count);
    Memory* getMemory();
    IO* getIO();
    Registers* getRegisters();
    Alu* getAlu();
    void placeProgramCounterOnAddressBus();
    void reset();
};

#endif // PROCESSOR_H
