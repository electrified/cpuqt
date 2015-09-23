#include "tests/zexrunner.h"
#include "tests/test_computer.h"
#include "computer/utils.h"
#include "computer/consolebadgerio.h"
#include <vector>

int main(int argc, char** argv)
{
    // construct computer
    TestComputer* comp = new TestComputer();
//     ConsoleBadgerIO* io = new ConsoleBadgerIO();
//     comp->setIO(io);
    //load zexdoc and cpm output bodge
    loadIntoMemory2(comp->getMemory(), 0x100, "/home/ed/dev/cpuqt2/bin_z80/zexdoc.bin");
    loadIntoMemory2(comp->getMemory(), 0, "/home/ed/dev/cpuqt2/bin_z80/cpm_io.rom");
    std::cout << "bopo" << std::endl;
    while(true) {
        comp->getProcessor()->process();
    }
    //start running
    
}