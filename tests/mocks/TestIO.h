#ifndef TESTIO_H
#define TESTIO_H

#include "IO.h"
#include <cstdint>

class TestIO : public IO {
private:
  std::uint8_t memory[0xffff];

public:
  TestIO();
  ~TestIO();
  std::uint8_t read(std::uint16_t address);
  void write(std::uint16_t address, std::uint8_t value);
};

#endif // TESTIO_H
