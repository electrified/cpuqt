#include "Register.hpp"

std::string registers::toString(Rgstr c) {
  switch (c) {
  case Rgstr::unknown:
    return "unknown";
  case Rgstr::A:
    return "A";
  case Rgstr::B:
    return "B";
  case Rgstr::C:
    return "C";
  case Rgstr::D:
    return "D";
  case Rgstr::E:
    return "E";
  case Rgstr::H:
    return "H";
  case Rgstr::I:
    return "I";
  case Rgstr::IXH:
    return "IXH";
  case Rgstr::IXL:
    return "IXL";
  case Rgstr::IYH:
    return "IYH";
  case Rgstr::IYL:
    return "IYL";
  case Rgstr::L:
    return "L";
  case Rgstr::R:
    return "R";
  default:
    return "UNKNOWN";
  }
}
