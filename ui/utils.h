#pragma once

#include <QString>
#include <iostream>
#include <iomanip>
#include <sstream>
// for loading script
#include <fstream>

namespace utils {
  template <typename T> QString int_to_hex(T i) {
    std::stringstream stream;
    stream << std::hex << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
          << +i; // http://stackoverflow.com/questions/23575381/behavior-of-cout-hex-with-uint8-and-uint16
    return QString::fromStdString(stream.str());
  }

  std::string get_file_contents(const char *filename) {
    std::ifstream in(filename, std::ios::in);
    if (in) {
      std::ostringstream contents;
      contents << in.rdbuf();
      in.close();
      return (contents.str());
    }
    throw(errno);
  }

  void save_file(const char *filename, std::string contents) {
    std::ofstream out(filename, std::ios::trunc);
    if (out) {
      out << contents;
      out.close();
    }
  }
}
