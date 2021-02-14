#pragma once

#include "Register.hpp"
#include "RegisterPair.hpp"
#include <cstdint>
#include <string>

using namespace std;
using namespace registers;

class MemoryAddress {
  std::uint16_t memoryAddress;
  std::uint8_t offset;
  Rgstr rgstr;
  RegisterPair registerPair;

public:
  MemoryAddress();
  explicit MemoryAddress(std::uint16_t i);
  explicit MemoryAddress(Rgstr r);
  explicit MemoryAddress(RegisterPair rp);
  MemoryAddress(RegisterPair rp, std::uint8_t offset);
  std::uint16_t getMemoryAddress() const;
  std::uint8_t getOffset() const;
  Rgstr getRegister() const;
  RegisterPair getRegisterPair() const;
  std::string toString() const;
};
