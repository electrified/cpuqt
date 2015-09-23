#ifndef BADGERCOMPUTER_H
#define BADGERCOMPUTER_H

#include <cstdint>
#include "Z80/processor.h"
#include "ui/qtbadgermemory.h"
#include "ui/qtbadgerio.h"
#include "Z80/alu.h"
#include <set>

class BadgerComputer : public QObject
{
Q_OBJECT
public:
    BadgerComputer();
    ~BadgerComputer();
    void reset();
    Processor *processor;
    QtBadgerMemory* memory;
    BadgerIO* io;
    Alu* alu;
    bool skipBreakpoint = false;
    
    void process(std::uint8_t count);
    void doOneScreenRefreshesWorth();
    void step();
    void addBreakpoint(std::uint16_t pc);
    void removeBreakpoint(std::uint16_t pc);
signals:
    void hitbreakpoint();
private:
    set<uint16_t> breakpoints;
};

#endif // BADGERCOMPUTER_H
