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

    void doOneScreenRefreshesWorth();
    Memory* getMemory();
    IO* getIO();
    Registers* getRegisters();
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
