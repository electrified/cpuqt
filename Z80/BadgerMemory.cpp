#include "BadgerMemory.h"
#include <iostream>
#include "utils.h"

BadgerMemory::BadgerMemory(): memory{} {
//      std::cout << "Initialising badgermemory" << std::endl;
}

BadgerMemory::~BadgerMemory() {
//      std::cout << "destroying badgermemory" << std::endl;
}

std::uint8_t BadgerMemory::read(const std::uint16_t address){
    return memory[address];
}

void BadgerMemory::write(const std::uint16_t address,const std::uint8_t value){
    if (address < 0x4000) {
    
//         std::cout << "rom write!" << utils::int_to_hex(address) << std::endl;
//         return;
    }
    memory[address] = value;
}

std::uint16_t BadgerMemory::size() {
    return 0xffff;
}

