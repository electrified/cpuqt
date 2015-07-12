#ifndef CPM_IO_H
#define CPM_IO_H
#include <QObject>
#include "Z80/emu_alu.h"
#include "Z80/MemoryAddress.h"

class cpm_io :public QObject, public EmuAlu
{
    Q_OBJECT
public:
    cpm_io(Memory* memory, IO* io, Registers* registers);
//     ~cpm_io();
    void in(const Rgstr rgstr, const MemoryAddress& i);
signals:
    void consoleTextOutput(char character);
};

#endif // CPM_IO_H
