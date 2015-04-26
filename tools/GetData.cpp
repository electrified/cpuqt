#include<fstream>
#include<cstdint>
#include<boost/format.hpp>

#include "tools/GetData.hpp"
//#include <tools/FinalNode.hpp>

GetData::GetData(uint8_t level)
{
   this->level = level;
}

void GetData::write(std::ofstream* writer)
{
   *writer << boost::format("currentInstruction[%d] = getNextByte();") % this->level << endl;
}
