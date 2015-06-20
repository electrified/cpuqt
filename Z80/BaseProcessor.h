#ifndef BASEPROCESSOR_H
#define BASEPROCESSOR_H

#include <cstdint>

#include "Z80/Memory.h"
#include "Z80/IO.h"
#include "Z80/Processor.h"
#include "Logger.h"

class BaseProcessor : public Processor
{
protected:
    Logger logger;
    Memory& memory;
    IO& io;
    std::uint16_t addressBus;

    /*
 * Program Counter (PC) The program counter holds the 16-bit address of the
 * current instruction being fetched from memory. The PC is automatically
 * incremented after its contents have been transferred to the address
 * lines. When a program jump occurs, the new value is automatically placed
 * in the PC, overriding the incrementer.
 */
    std::uint16_t PC;
public:
    BaseProcessor(Memory& memory, IO& io);
    ~BaseProcessor();
    void placeProgramCounterOnAddressBus();
    std::uint16_t getPC();
    void setPC(std::uint16_t pc);
    Memory& getMemory();
    IO& getIO();
    std::uint8_t fetchInstruction();
    std::uint8_t instructionByteCount = 0;
    std::uint8_t getNextByte();
};

#endif // BASEPROCESSOR_H
