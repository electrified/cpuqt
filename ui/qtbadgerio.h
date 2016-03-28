#pragma once

#include "computer/cpm/badgerio.h"

#include <QObject>

class QtBadgerIO : public QObject, public BadgerIO {
  Q_OBJECT
public:
  QtBadgerIO();
  ~QtBadgerIO();
  void outputCharacter(std::uint8_t value);

signals:
  void consoleTextOutput(char character);
};
