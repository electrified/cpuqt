#include "console_serial_io.h"
#include <iostream>

void ConsoleSerialIO::outputCharacter(std::uint8_t value) { std::cout << value << std::flush; }

ConsoleSerialIO::ConsoleSerialIO() {}

ConsoleSerialIO::~ConsoleSerialIO() {}
