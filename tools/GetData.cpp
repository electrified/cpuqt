#include<fstream>
#include<cstdint>

#include <tools/GetData.hpp>
// #include <tools/FinalNode.hpp>

GetData::GetData(uint8_t level)
{
   this->level = level;
}

void GetData::write(std::ofstream* writer)
{
   *writer << "currentInstruction[%d] = getNextByte();\n" << this->level;
}
