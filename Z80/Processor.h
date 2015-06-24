#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>

#include "Z80/RegisterPair.hpp"
#include "Z80/Register.hpp"
#include "Z80/Condition.hpp"
#include "Z80/MemoryAddress.h"
#include "Z80/Memory.h"
#include "Z80/IO.h"
#include "Z80/alu.h"
#include "Z80/registers.h"

class Processor
{
    Memory& memory;
    IO& io;
    Alu& alu;
    Registers& registers;
public:
    Processor(Memory& memory, IO& io, Alu& alu, Registers& registers);
    Processor(Memory& memory, IO& io);
    ~Processor();

    void process();
    void process(std::uint8_t count);

    void doOneScreenRefreshesWorth();
    Memory& getMemory();
    IO& getIO();
    Registers& getRegisters();
//    virtual std::uint8_t fetchInstruction() = 0;
//    virtual Memory& getMemory() = 0;
//    virtual IO& getIO() = 0;
//    virtual std::uint16_t getRegisterPairValue(const RegisterPair register) = 0;
//    virtual std::uint8_t getRegisterValue(const Rgstr register) = 0;
//    virtual void placeProgramCounterOnAddressBus() = 0;
    void placeProgramCounterOnAddressBus();
//    std::uint8_t fetchInstruction();
//    std::uint8_t instructionByteCount = 0;
//    std::uint8_t getNextByte();
    std::uint64_t refreshes;

    void reset();

};

#endif // PROCESSOR_H
