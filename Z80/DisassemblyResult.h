#pragma once

#include <cstdint>
#include <string>

class DisassemblyResult {
private:
  std::uint16_t address;
  std::string mnemonic;

public:
  DisassemblyResult(std::uint16_t address, std::string mnemonic);
  uint16_t getAddress() const;
  const std::string &getMnemonic() const;
};
