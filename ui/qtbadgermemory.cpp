#include "qtbadgermemory.h"
#include <iostream>
#include "Z80/utils.h"

QtBadgerMemory::QtBadgerMemory(QObject *parent) : QObject(parent)
{

}

void QtBadgerMemory::write(const std::uint16_t address, const std::uint8_t value) {
    BadgerMemory::write(address, value);
    
//     std::cout << "RAM UPDATE: " << utils::int_to_hex(address) << " " <<  utils::int_to_hex<>(value) << std::endl;
    
    emit memoryUpdated(address);
    
    if (address >= 0x4000 && address <= 0x5AFF) {
        emit spectrumGfxUpdated(address);
    }
}
