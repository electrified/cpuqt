#pragma once

#include <cstdint>
class IO {
public:
  virtual std::uint8_t read(std::uint16_t address) = 0;
  virtual void write(std::uint16_t address, std::uint8_t value) = 0;
  virtual ~IO(){

  };
};
