#ifndef TESTPROJECT_BADGERMEMORY_H
#define TESTPROJECT_BADGERMEMORY_H

#include <cstdint>
#include "Memory.h"

class BadgerMemory : public Memory {
private:
    std::uint8_t memory[0xffff] = {};
public:
    BadgerMemory();
    std::uint8_t read(const std::uint16_t address);
    void write(const std::uint16_t address, const std::uint8_t value);
    std::uint16_t size();
    virtual ~BadgerMemory();
};

#endif //TESTPROJECT_BADGERMEMORY_H
