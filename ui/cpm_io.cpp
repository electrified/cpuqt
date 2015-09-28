#include "cpm_io.h"

cpm_io::cpm_io() {

}

/* Emulate CP/M bdos call 5 functions 2 (output character on screen) and 
 * 9 (output $-terminated string to screen).
 */
void cpm_io::in(Rgstr rgstr, const MemoryAddress& i, Registers* registers, Memory* memory) {
    if (registers->getC() == 2) {
        // rewrite as code, CP/M BIOS routine
        emit consoleTextOutput(registers->getE());
    }
    else if (registers->getC() == 9) {
        int i; //, c;

        // rewrite as code, CP/M BIOS routine
        for (i = registers->getDE(); memory->read(i) != '$'; i++) {
            emit consoleTextOutput(memory->read(i & 0xffff));
        }
    }
}

