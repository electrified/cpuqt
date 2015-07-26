#include "cpm_io.h"

cpm_io::cpm_io(Memory* memory, IO* io, Registers* registers) : EmuAlu(memory, io, registers){

}

void cpm_io::in(Rgstr rgstr, const MemoryAddress& i) {
    this->registers->setRegister(rgstr, this->io->read(this->getMemoryAddress(i)));

    if (this->registers->getC() == 2) {
        emit consoleTextOutput(this->registers->getE());
    }
    else if (this->registers->getC() == 9) {

        int     i, c;

        for (i = this->registers->getDE(), c = 0;
             this->memory->read(i) != '$';
             i++) {
            emit consoleTextOutput(this->memory->read(i & 0xffff));
        }
    }
}
