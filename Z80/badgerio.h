#ifndef BADGERIO_H
#define BADGERIO_H

#include <cstdint>
#include "Z80/IO.h"

class BadgerIO : public IO
{
private:
    std::uint8_t memory[0xffff];
public:
    BadgerIO();
    std::uint8_t read(std::uint16_t address);
    void write(std::uint16_t address, std::uint8_t value);
};

#endif // BADGERIO_H
