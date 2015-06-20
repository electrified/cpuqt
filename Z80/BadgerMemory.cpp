#include "BadgerMemory.h"
#include <iostream>

BadgerMemory::BadgerMemory() {
     std::cout << "Initialising badgermemory" << std::endl;
}

BadgerMemory::~BadgerMemory() {
     std::cout << "destroying badgermemory" << std::endl;
}

std::uint8_t BadgerMemory::read(std::uint16_t address){
    return memory[address];
}

void BadgerMemory::write(std::uint16_t address, std::uint8_t value){
    memory[address] = value;
}

std::uint16_t BadgerMemory::size() {
    return 0xffff;
}

