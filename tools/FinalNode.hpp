#pragma once
#include <cstdint>
#include <map>
#include <fstream>

#include "tools/Switch.hpp"
// #include "tools/GetData.hpp"
#include "tools/Instruction.hpp"

//class Switch;
//class Instruction;
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
