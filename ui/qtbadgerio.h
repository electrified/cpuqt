#pragma once

#include "computer/cpm/serial_io.h"

#include <QObject>

class QtBadgerIO : public QObject, public SerialIO {
  Q_OBJECT
public:
  QtBadgerIO();
  ~QtBadgerIO();
  void outputCharacter(std::uint8_t value);

signals:
  void consoleTextOutput(char character);
};
