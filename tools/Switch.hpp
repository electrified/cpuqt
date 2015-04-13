// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/Switch.java

#pragma once
#include<map>
#include<fstream>
#include <cstdint>

#include"tools/FinalNode.hpp"

class Switch
{
public:
    int32_t* level;
    std::map<int, FinalNode>* nodes;
public:
    virtual void write(std::ofstream* writer);

public:
    Switch(int32_t* level);
};
