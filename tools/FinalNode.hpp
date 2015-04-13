// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/FinalNode.java

#pragma once
#include <cstdint>
#include <map>
#include <fstream>

#include "tools/Switch.hpp"
#include "tools/Instruction.hpp"
#include "tools/GetData.hpp"

class FinalNode
{

public:
    Switch* theSwitch;
    Instruction* instruction;
    std::map<uint8_t,GetData> getDatas;
    virtual void write(std::ofstream* writer);
    FinalNode();
};
