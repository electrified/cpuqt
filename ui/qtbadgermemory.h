#ifndef QTBADGERMEMORY_H
#define QTBADGERMEMORY_H

#include <QObject>
#include "Z80/BadgerMemory.h"

class QtBadgerMemory : public QObject, public BadgerMemory {
  Q_OBJECT
public:
  explicit QtBadgerMemory(QObject *parent = 0);
  void write(const std::uint16_t address, const std::uint8_t value);
signals:
  void memoryUpdated(std::uint16_t address);
  void spectrumGfxUpdated(std::uint16_t address);
public slots:
};

#endif // QTBADGERMEMORY_H
