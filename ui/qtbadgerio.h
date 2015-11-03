#ifndef QTBADGERIO_H
#define QTBADGERIO_H

#include "computer/badgerio.h"

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

#endif // QTBADGERIO_H
