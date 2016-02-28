#pragma once

#include "badgerio.h"

class ConsoleBadgerIO : public BadgerIO {
public:
  ConsoleBadgerIO();
  ~ConsoleBadgerIO();
  void outputCharacter(std::uint8_t value);
};
