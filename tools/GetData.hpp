// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/GetData.java

#pragma once
#include<fstream>
#include<cstdint>
#include <tools/FinalNode.hpp>

class GetData : FinalNode
{
public:
    uint8_t level;

public:
    void write(std::ofstream* writer) override;
    GetData(uint8_t level);
};
