#pragma once

#include <QObject>
#include "Z80/MemoryAddress.h"
#include "Z80/registers.h"
#include "Z80/Memory.h"

class cpm_io : public QObject {
  Q_OBJECT
public:
  cpm_io();
  //     ~cpm_io();
  void in(Rgstr rgstr, const MemoryAddress &i, Registers *registers, Memory *memory);
signals:
  void consoleTextOutput(char character);
};
