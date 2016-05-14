#include <string>
#include "MemoryAddress.h"
#include "utils.h"

MemoryAddress::MemoryAddress() {
  memoryAddress = 0;
  offset = 0;
  registerPair = RegisterPair::unknown;
  rgstr = Rgstr::unknown;
}

MemoryAddress::MemoryAddress(const std::uint16_t memoryAddress) : MemoryAddress() {
  this->memoryAddress = memoryAddress;
}

MemoryAddress::MemoryAddress(const Rgstr rgstr) : MemoryAddress() { this->rgstr = rgstr; }

MemoryAddress::MemoryAddress(const RegisterPair rgstrPair) : MemoryAddress() { this->registerPair = rgstrPair; }

MemoryAddress::MemoryAddress(const RegisterPair rgstrPair, const std::uint8_t offset) : MemoryAddress() {
  this->registerPair = rgstrPair;
  this->offset = offset;
}

std::uint16_t MemoryAddress::getMemoryAddress() const { return memoryAddress; }

std::uint8_t MemoryAddress::getOffset() const { return offset; }

Rgstr MemoryAddress::getRegister() const { return rgstr; }

RegisterPair MemoryAddress::getRegisterPair() const { return registerPair; }

std::string MemoryAddress::toString() const {
  string address = "";
  if (getRegister() != Rgstr::unknown) {
    address = registers::toString(getRegister());
    if (getOffset() != 0) {
      address = address + "+" + utils::int_to_hex(getOffset());
    }
  } else if (getRegisterPair() != RegisterPair::unknown) {
    address = registers::toString(getRegisterPair());
    if (getOffset() != 0) {
      address = address + "+" + utils::int_to_hex(getOffset());
    }
  } else { // if (getMemoryAddress() != 0) {
    address = utils::int_to_hex(getMemoryAddress());
  }
  return "(" + address + ")";
}
