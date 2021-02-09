#include "badgercomputer.h"


#include "utils.h"
#include "Z80/registers.h"
#include "spdlog/spdlog.h"

BadgerComputer::BadgerComputer() {
  memory = new QtBadgerMemory();
  io = new SpectrumIO();
  processor = new Processor(memory, io);
  connect(&timer, SIGNAL(timeout()), this, SLOT(doOneScreenRefreshesWorth()));
}

BadgerComputer::~BadgerComputer() = default;

/**
 * Here we can reset the CPU along with other peripherals, clear the screen etc maybe
 */
void BadgerComputer::reset() const { processor->reset(); }

void BadgerComputer::doOneScreenRefreshesWorth() {
  // At 4Mhz, 20 milliseconds of execution corresponds to 80,000 cycles
  for (std::uint32_t i = 0; i < 70000; i++) {
    if (!skipBreakpoint && breakpoints.find(processor->getRegisters()->getPC()) != breakpoints.end()) {
      skipBreakpoint = true;
      emit hitbreakpoint();
      spdlog::get("console")->debug("breakpoint hit!");
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
  spdlog::get("console")->debug(">>>>>>>>>>>>>>>>>>> emit gfxupdated()");
  emit gfxUpdated();
}

void BadgerComputer::step() const { processor->process(); }

void BadgerComputer::addBreakpoint(std::uint16_t pc) { breakpoints.insert(pc); }

void BadgerComputer::removeBreakpoint(std::uint16_t pc) { breakpoints.erase(pc); }

void BadgerComputer::listBreakpoints() {}

void BadgerComputer::run() {
    timer.start(20); // 50 times per second 1000/50 = 20
}

void BadgerComputer::stop() {
  timer.stop();
}
void BadgerComputer::process(const std::uint8_t count) {}
