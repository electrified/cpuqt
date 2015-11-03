#include "badgercomputer.h"

#include "ui/qtbadgerio.h"
#include "ui/cpm_io.h"
#include "utils.h"
#include "Z80/registers.h"
#include <iostream>

BadgerComputer::BadgerComputer() {
  memory = new QtBadgerMemory();
  //     io = new QtBadgerIO();
  io = new SpectrumIO();
  processor = new Processor(memory, io);

  //     addBreakpoint(0x1b3e); //inc counter
  //     addBreakpoint(0x1b41); //shift
  //     addBreakpoint(0x1b45); //check shift
  //      addBreakpoint(0x11ef);
  //     addBreakpoint(0x11da);
  // //     addBreakpoint(0x11e2);
  //      addBreakpoint(0x1219);
  //           addBreakpoint(0xeeb);
  //           addBreakpoint(0x1295);
  //     addBreakpoint(0xb24);
  //     addBreakpoint(0x11e2);
  //     addBreakpoint(0x1be4);
  //     addBreakpoint(0x15f2);
}

BadgerComputer::~BadgerComputer() {}

/**
 * Here we can reset the CPU along with other peripherals, clear the screen etc maybe
 */
void BadgerComputer::reset() { processor->reset(); }

void BadgerComputer::doOneScreenRefreshesWorth() {
  // At 4Mhz, 20 milliseconds of execution corresponds to 80,000 cycles
  for (std::uint32_t i = 0; i < 70000; i++) {
    if (!skipBreakpoint && breakpoints.find(processor->getRegisters()->getPC()) != breakpoints.end()) {
      skipBreakpoint = true;
      emit hitbreakpoint();
      std::cout << "breakpoint hit!" << std::endl;
      break;
    } else {
      skipBreakpoint = false;

      if (i == 0) {
        processor->interruptRequest(true);
      }
      processor->process();
      if (i == 0) {
        processor->interruptRequest(false);
      }

      //             std::cout << utils::int_to_hex(processor->getRegisters()->getPC()).toStdString() << std::endl;
    }
  }
}

void BadgerComputer::step() { processor->process(); }

void BadgerComputer::addBreakpoint(std::uint16_t pc) { breakpoints.insert(pc); }

void BadgerComputer::removeBreakpoint(std::uint16_t pc) { breakpoints.erase(pc); }