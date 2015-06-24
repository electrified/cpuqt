#pragma once

#include <tools/FinalNode.hpp>
#include <cstdint>

class Case : public FinalNode {
public:
    int opcode;
    void write(std::ofstream* writer) override;
    Case(int opcode);
    Case();
};
