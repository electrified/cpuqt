#pragma once
#include <cstdint>
#include <map>
#include <fstream>

#include "Switch.hpp"
#include "Instruction.hpp"

class GetData;

class FinalNode
{
public:
    Switch theSwitch;
    Instruction instruction;
    std::map<uint8_t,GetData*> getDatas;
    virtual void write(std::ofstream* writer) = 0;
    FinalNode();
};
