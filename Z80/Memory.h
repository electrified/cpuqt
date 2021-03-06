#pragma once

#include <cstdint>

class Memory {
public:
  virtual std::uint8_t read(const std::uint16_t address) = 0;
  virtual void write(const std::uint16_t address, const std::uint8_t value) = 0;
  virtual std::uint16_t size() = 0;
};
