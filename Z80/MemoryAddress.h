#ifndef MEMORYADDRESS_H
#define MEMORYADDRESS_H
#include <cstdint>
#include <string>
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"

using namespace std;
using namespace registers;

class MemoryAddress {
  std::uint16_t memoryAddress;
  std::uint8_t offset;
  Rgstr rgstr;
  RegisterPair registerPair;

public:
  MemoryAddress();
  MemoryAddress(const std::uint16_t i);
  MemoryAddress(const Rgstr r);
  MemoryAddress(const RegisterPair rp);
  MemoryAddress(const RegisterPair rp, const std::uint8_t offset);
  std::uint16_t getMemoryAddress() const;
  std::uint8_t getOffset() const;
  Rgstr getRegister() const;
  RegisterPair getRegisterPair() const;
  std::string toString() const;
};

#endif // MEMORYADDRESS_H
