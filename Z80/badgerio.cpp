#include "badgerio.h"

BadgerIO::BadgerIO()
{

}

std::uint8_t BadgerIO::read(std::uint16_t address){
    return memory[address];
}

void BadgerIO::write(std::uint16_t address, std::uint8_t value){
    memory[address] = value;
}
