#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>

#include "Z80/RegisterPair.hpp"
#include "Z80/Register.hpp"
#include "Z80/Condition.hpp"
#include "Z80/MemoryAddress.h"
#include "Z80/Memory.h"
#include "Z80/IO.h"

class Processor
{
    virtual std::uint8_t fetchInstruction() = 0;
    virtual Memory& getMemory() = 0;
    virtual IO& getIO() = 0;
    virtual std::uint16_t getRegisterPairValue(const RegisterPair register) = 0;
    virtual std::uint8_t getRegisterValue(const Rgstr register) = 0;
    virtual void placeProgramCounterOnAddressBus() = 0;
};

#endif // PROCESSOR_H
