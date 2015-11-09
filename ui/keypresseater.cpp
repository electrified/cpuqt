#include "keypresseater.h"

KeyPressEater::KeyPressEater(SpectrumIO* io) {
    this->io = io;
}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (!keyEvent->isAutoRepeat()) {
          io->keydown(keyEvent->key());
          qDebug("Ate key press %d", keyEvent->key());
        }
        return true;
    } else if(event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (!keyEvent->isAutoRepeat()) {
          qDebug("Ate key up %d", keyEvent->key());
          io->keyup(keyEvent->key());
        }
        return true;
    }
    else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
