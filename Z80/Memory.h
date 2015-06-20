#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>
class Memory
{
public:
    virtual std::uint8_t read(std::uint16_t address) = 0;
    virtual void write(std::uint16_t address, std::uint8_t value) = 0;
    virtual std::uint16_t size() = 0;
};

#endif // MEMORY_H
