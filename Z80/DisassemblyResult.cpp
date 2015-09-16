#include "DisassemblyResult.h"

DisassemblyResult::DisassemblyResult(const std::uint16_t address, const std::string mnemonic) {
    this->address = address;
    this->mnemonic = mnemonic;
}

const std::string &DisassemblyResult::getMnemonic() const {
    return mnemonic;
}

uint16_t DisassemblyResult::getAddress() const {
    return address;
}