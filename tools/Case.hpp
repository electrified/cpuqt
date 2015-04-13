// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/Case.java

#pragma once

#include <tools/FinalNode.hpp>
#include <cstdint>

class Case : FinalNode {
private:
    uint8_t opcode;
public:
    void write(std::ofstream* writer) override;
    Case(uint8_t opcode);
};
