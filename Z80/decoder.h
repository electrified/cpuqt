#ifndef DECODER
#define DECODER
#include "spdlog/spdlog.h"
#include "Memory.h"
#include "alu.h"

class Decoder {
public:
  void decode(Memory &memory, Alu &alu, std::uint16_t &pc);

private:
  static std::uint8_t next(Memory &memory, std::uint16_t &pc) { return memory.read(pc++); }
};
#endif
