#include "zexrunner.h"
#include "test_computer.h"
#include "../computer/utils.h"
#include "../computer/consolebadgerio.h"
#include <vector>
#include <boost/timer/timer.hpp>

int main(int argc, char** argv)
{
    TestComputer* comp = new TestComputer();
    //load zexdoc and cpm output bodge
    loadIntoMemory2(comp->getMemory(), 0x100, "./bin_z80/zexdoc.bin");
    loadIntoMemory2(comp->getMemory(), 0, "./bin_z80/cpm_io.rom");

    boost::timer::auto_cpu_timer t;
     for (std::uint64_t i = 0; i < 100000000; i++) {
        if (i % 10000000 == 0) {
            std::cout << i << std::endl;
        }
        comp->getProcessor()->process();
    }
}