#include "BadgerMemory.h"
#include <iostream>

BadgerMemory::BadgerMemory(): memory{} {
     std::cout << "Initialising badgermemory" << std::endl;
}

BadgerMemory::~BadgerMemory() {
     std::cout << "destroying badgermemory" << std::endl;
}

std::uint8_t BadgerMemory::read(const std::uint16_t address){
    return this->memory[address];
}

void BadgerMemory::write(const std::uint16_t address,const std::uint8_t value){
    memory[address] = value;
}

std::uint16_t BadgerMemory::size() {
    return 0xffff;
}

