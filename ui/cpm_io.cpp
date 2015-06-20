#include "cpm_io.h"
#include <iostream>

cpm_io::cpm_io(Memory& memory, IO& io) : EmulationProcessor(memory, io){
}

void cpm_io::in(Rgstr rgstr, const MemoryAddress& i) {
    this->setRegister(rgstr, this->getIO().read(this->getMemoryAddress(i)));

    if (this->getC() == 2) {
        emit consoleTextOutput(this->getE());
    }
    else if (this->getC() == 9) {

        int     i, c;

        for (i = this->getDE(), c = 0;
             this->getMemory().read(i) != '$';
             i++) {
            emit consoleTextOutput(this->getMemory().read(i & 0xffff));
        }
    }
}
