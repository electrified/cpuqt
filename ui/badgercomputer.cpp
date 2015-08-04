#include "badgercomputer.h"

#include "ui/badgerio.h"
#include "ui/cpm_io.h"
#include "utils.h"
#include "Z80/registers.h"
#include <iostream>

BadgerComputer::BadgerComputer()
{
    memory = new QtBadgerMemory();
    io = new BadgerIO();
    Registers* registers = new Registers();
    alu = new cpm_io(memory, io, registers);
    processor = new Processor(memory, io, alu, registers);
    
    addBreakpoint(0x1b3e); //inc counter
    addBreakpoint(0x1b41); //shift
    addBreakpoint(0x1b45); //check shift
//     addBreakpoint(0x1be4);
}

BadgerComputer::~BadgerComputer()
{

}

/**
 * Here we can reset the CPU along with other peripherals, clear the screen etc maybe
 */
void BadgerComputer::reset() {
    processor->reset();
}

void BadgerComputer::doOneScreenRefreshesWorth() {
    // At 4Mhz, 20 milliseconds of execution corresponds to 80,000 cycles
    for (std::uint32_t i = 0; i < 70000; i++) {
//         if (!skipBreakpoint && breakpoints.find(processor->getRegisters()->getPC()) != breakpoints.end()) {
//             skipBreakpoint = true;
//             emit hitbreakpoint();
//             std::cout << "breakpoint hit!" << std::endl;
//             break;
//         } else 
        {
            skipBreakpoint = false;
            processor->process();
            std::cout << utils::int_to_hex(processor->getRegisters()->getPC()).toStdString() << std::endl;
        }
    }
}

void BadgerComputer::step() {
    processor->process();
}

void BadgerComputer::addBreakpoint(std::uint16_t pc) {
    breakpoints.insert(pc);
}


void BadgerComputer::removeBreakpoint(std::uint16_t pc) {
    breakpoints.erase(pc);
}