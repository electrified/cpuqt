#ifndef TESTPROJECT_DISASSEMBLYRESULT_H
#define TESTPROJECT_DISASSEMBLYRESULT_H

#include <string>
#include <cstdint>

class DisassemblyResult {
private:
    std::uint16_t address;
    std::string mnemonic;
public:
    DisassemblyResult(std::uint16_t address, std::string mnemonic);
    uint16_t getAddress() const;
    const std::string & getMnemonic() const;
};

#endif //TESTPROJECT_DISASSEMBLYRESULT_H
