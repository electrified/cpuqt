#include <fstream>
#include <boost/format.hpp>

#include "GetData.hpp"

GetData::GetData(uint8_t level) { this->level = level; }

void GetData::write(std::ofstream *writer) {
  *writer << boost::format("currentInstruction[%1%] = memory.read(++pc);") % int(this->level) << std::endl;
}
