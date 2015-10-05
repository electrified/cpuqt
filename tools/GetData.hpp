#pragma once
#include <cstdint>

#include "FinalNode.hpp"

class GetData : public FinalNode
{
public:
   uint8_t level;
   void write(std::ofstream* writer);
   GetData(uint8_t level);
};
