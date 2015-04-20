#pragma once
// class FinalNode;
#include <cstdint>

#include "tools/FinalNode.hpp"

class GetData : public FinalNode
{
public:
   uint8_t level;
   void write(std::ofstream* writer);
   GetData(uint8_t level);
};
