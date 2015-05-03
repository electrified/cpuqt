//
// Created by ed on 30/04/15.
//

#ifndef TESTPROJECT_BADGERMEMORY_H
#define TESTPROJECT_BADGERMEMORY_H

#include <cstdint>
#include "Memory.h"

class BadgerMemory : public Memory {
private:
    std::uint8_t memory[0xffff];
public:
    BadgerMemory();
    std::uint8_t read(std::uint16_t  address);
    void write(std::uint16_t address, std::uint8_t value);
};


#endif //TESTPROJECT_BADGERMEMORY_H
