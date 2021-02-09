#pragma once

#include <QObject>
#include "Z80/BadgerMemory.h"

class QtBadgerMemory : public QObject, public BadgerMemory {
  Q_OBJECT
public:
  explicit QtBadgerMemory(QObject *parent = nullptr);
  void write(std::uint16_t address, std::uint8_t value) override;
signals:
  void memoryUpdated(std::uint16_t address);
  void spectrumGfxUpdated(std::uint16_t address);
public slots:
};
