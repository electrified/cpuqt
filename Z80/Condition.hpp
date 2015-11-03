#pragma once

#include <string>

enum class Condition {
  C,
  M,
  NC,
  NZ,
  P,
  PE,
  PO,
  Z,
};

namespace registers {
std::string toString(Condition c);
}