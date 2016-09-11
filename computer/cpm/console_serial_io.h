#pragma once

#include "serial_io.h"

class ConsoleSerialIO : public SerialIO {
public:
  ConsoleSerialIO();
  ~ConsoleSerialIO();
  void outputCharacter(std::uint8_t value);
};
