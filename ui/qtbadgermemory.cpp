#include "qtbadgermemory.h"
#include "Z80/utils.h"
#include <iostream>

QtBadgerMemory::QtBadgerMemory(QObject *parent) : QObject(parent) {}

void QtBadgerMemory::write(const std::uint16_t address, const std::uint8_t value) {
  BadgerMemory::write(address, value);

  emit memoryUpdated(address);

  if (address >= 0x4000 && address <= 0x5AFF) {

    //     std::cout << "RAM UPDATE: " << utils::int_to_hex(address) << " " <<  utils::int_to_hex<>(value) << std::endl;
    emit spectrumGfxUpdated(address);
  }
}
