#include "test_computer.h"

TestComputer::TestComputer()
{
//    memory = ;
//    io = ;
//    processor = new Processor(*memory, *io);
}

Memory& TestComputer::getMemory() {
    return memory;
}

IO& TestComputer::getIO() {
    return io;
}

Processor& TestComputer::getProcessor() {
    return processor;
}
