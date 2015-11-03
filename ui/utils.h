#pragma once
#include <QString>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace utils {
template <typename T> QString int_to_hex(T i) {
  std::stringstream stream;
  stream << std::hex << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
         << +i; // http://stackoverflow.com/questions/23575381/behavior-of-cout-hex-with-uint8-and-uint16
  return QString::fromStdString(stream.str());
}
}
