#ifndef CONSOLEBADGERIO_H
#define CONSOLEBADGERIO_H

#include "badgerio.h"

class ConsoleBadgerIO : public BadgerIO {
public:
  ConsoleBadgerIO();
  ~ConsoleBadgerIO();
  void outputCharacter(std::uint8_t value);
};

#endif // CONSOLEBADGERIO_H
