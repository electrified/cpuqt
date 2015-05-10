#pragma once
#include<map>
#include<fstream>
#include <cstdint>

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
