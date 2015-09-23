#include "tests/zexrunner.h"
#include "tests/test_computer.h"
#include "computer/utils.h"
#include "computer/consolebadgerio.h"
#include <vector>

int main(int argc, char** argv)
{
    // construct computer
    TestComputer* comp = new TestComputer();
    ConsoleBadgerIO* io = new ConsoleBadgerIO();
    comp->setIO(io);
    //load zexdoc and cpm output bodge
    auto data1 = ReadAllBytes("~/dev/cpuqt/bin_z80/zexdoc.bin");
//     
//     loadIntoMemory(data1, comp->getMemory(), 0x100);
//     
//     auto data2 = ReadAllBytes("~/dev/cpuqt/bin_z80/cpm_io.rom");
//     
//     loadIntoMemory(data2, comp->getMemory(), 0);
//     
//     while(true) {
//         comp->getProcessor()->process();
//     }
    //start running
    
}