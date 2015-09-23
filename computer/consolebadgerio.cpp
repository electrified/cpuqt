#include "consolebadgerio.h"
#include <iostream>

void ConsoleBadgerIO::outputCharacter(std::uint8_t value) {
    std::cout << value << std::flush;
}

ConsoleBadgerIO::ConsoleBadgerIO() {
}

ConsoleBadgerIO::~ConsoleBadgerIO() {
}