#ifndef DECODER
#define DECODER
#include "Logger.h"
#include "Z80/Memory.h"
#include "Z80/alu.h"

class Decoder {
    Logger logger;
public:
    void decode(Memory& memory, Alu& alu,std::uint8_t& pc);
};
#endif
