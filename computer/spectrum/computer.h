#ifndef COMPUTER_H
#define COMPUTER_H

#include "Z80/processor.h"

class Computer
{
    Processor processor;
public:
    Computer();
    ~Computer();
};

#endif // COMPUTER_H
