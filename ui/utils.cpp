#include "utils.h"

#include <QString>
#include <iomanip>
#include <iostream>
#include <sstream>
// for loading script
#include <fstream>

namespace utils {

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
} // namespace utils
