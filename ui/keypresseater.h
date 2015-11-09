#pragma once

#include <QObject>
#include <QKeyEvent>
#include "computer/spectrum/spectrumio.h"

class KeyPressEater : public QObject
{
    Q_OBJECT
    SpectrumIO* io;
protected:
    bool eventFilter(QObject *obj, QEvent *event);
public:
  KeyPressEater(SpectrumIO* io);
};