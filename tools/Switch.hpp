#pragma once
#include<map>
#include<fstream>
#include <cstdint>

//#include "tools/FinalNode.hpp"

class Case;

class Switch
{
public:
    int level;
    std::map<int, Case*> cases;
public:
    virtual void write(std::ofstream* writer);
    Switch(int level);
    Switch();
};
