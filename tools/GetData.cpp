#include<fstream>
//#include<cstdint>
#include<boost/format.hpp>

#include "tools/GetData.hpp"

GetData::GetData(uint8_t level)
{
   this->level = level;
}

void GetData::write(std::ofstream* writer)
{
    *writer << "//GetData" <<std::endl;
   *writer << boost::format("currentInstruction[%1%] = getNextByte();") % int(this->level) <<std::endl;
}
