#include "badgercomputer.h"

#include "utils.h"
#include "Z80/registers.h"
#include "spdlog/spdlog.h"

BadgerComputer::BadgerComputer() {
  memory = new QtBadgerMemory();
  io = new SpectrumIO();
  processor = new Processor(memory, io);
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
      spdlog::get("console")->debug("breakpoint hit!");
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
    }
  }
}

void BadgerComputer::step() { processor->process(); }

void BadgerComputer::addBreakpoint(std::uint16_t pc) { breakpoints.insert(pc); }

void BadgerComputer::removeBreakpoint(std::uint16_t pc) { breakpoints.erase(pc); }

void BadgerComputer::listBreakpoints() {
}