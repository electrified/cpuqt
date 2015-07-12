#include "TestIO.h"
#include <iostream>

TestIO::TestIO() {
//     std::cout << "Initialising TestIO" << std::endl;
}

TestIO::~TestIO() {
//     std::cout << "Destroying TestIO" << std::endl;
}

std::uint8_t TestIO::read(std::uint16_t address)
{
        return memory[address];
}

void TestIO::write(std::uint16_t address, std::uint8_t value)
{
        memory[address] = value;
}