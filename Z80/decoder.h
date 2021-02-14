#pragma once

#include "Memory.h"
#include "alu.h"
#include "spdlog/spdlog.h"

class Decoder {
public:
  void decode(Memory &memory, Alu &alu, std::uint16_t &pc);

private:
  static std::uint8_t next(Memory &memory, std::uint16_t &pc) { return memory.read(pc++); }
};
