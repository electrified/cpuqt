//
// Created by ed on 30/04/15.
//
#include <cstdint>
#include "BadgerMemory.h"

//BadgerMemory::BadgerMemory(std::uint8_t memory[]) {
//    this->memory = memory;
//}

std::uint8_t BadgerMemory::read(std::uint16_t address){
    return memory[address];
}

void BadgerMemory::write(std::uint16_t address, std::uint8_t value){
    memory[address] = value;
}
