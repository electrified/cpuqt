#include "qtbadgermemory.h"

QtBadgerMemory::QtBadgerMemory(QObject *parent) : QObject(parent)
{

}

void QtBadgerMemory::write(const std::uint16_t address, const std::uint8_t value) {
    BadgerMemory::write(address, value);
    emit memoryUpdated(address);
}
