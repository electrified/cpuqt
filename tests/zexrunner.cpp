#include "tests/zexrunner.h"
#include "tests/test_computer.h"
#include "computer/utils.h"
#include "computer/consolebadgerio.h"
#include <vector>
#include <boost/timer/timer.hpp>

int main(int argc, char** argv)
{
    TestComputer* comp = new TestComputer();
    //load zexdoc and cpm output bodge
    loadIntoMemory2(comp->getMemory(), 0x100, "/home/ed/dev/cpuqt2/bin_z80/zexdoc.bin");
    loadIntoMemory2(comp->getMemory(), 0, "/home/ed/dev/cpuqt2/bin_z80/cpm_io.rom");

    std::uint64_t i = 0;
    boost::timer::auto_cpu_timer t;
    while(true) {
//      for (std::uint64_t i = 0; i < 100000000; i++) {
        ++i;
        if (i % 10000000 == 0) {
            std::cout << i << std::endl;
        }
        comp->getProcessor()->process();
    }
}