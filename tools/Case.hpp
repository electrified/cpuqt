#pragma once

#include <tools/FinalNode.hpp>
#include <cstdint>

class Case : public FinalNode {
private:
    uint8_t opcode;
    std::map<int, FinalNode*> nodes;
public:
    void write(std::ofstream* writer) override;
    Case(uint8_t opcode);
};
