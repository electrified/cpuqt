#pragma once

#include "../Z80/IO.h"

#include <list>
#include <map>
#include <cstdint>

struct spec_key {
  std::uint8_t row;
  std::uint8_t mask;
  bool caps;

public:
  spec_key() {
    this->row = 0;
    this->mask = 0;
    this->caps = false;
  }

  spec_key(std::uint8_t row, std::uint8_t mask) {
    this->row = row;
    this->mask = mask;
    this->caps = false;
  }

  spec_key(std::uint8_t row, std::uint8_t mask, bool caps) {
    this->row = row;
    this->mask = mask;
    this->caps = caps;
  }
};

class SpectrumIO : public IO {
  uint8_t keystates[8];
  std::map<int, spec_key> keyCodes;

public:
  SpectrumIO();
  ~SpectrumIO() override;
  std::uint8_t read(std::uint16_t address) override;
  void write(std::uint16_t address, std::uint8_t value) override;
  void keydown(int key);
  void keyup(int key);
  spec_key findKey(int key);
};
