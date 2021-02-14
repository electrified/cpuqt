#include "../computer/utils.h"
#include "mocks/zexrunner_computer.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <boost/timer/timer.hpp>
#include <iostream>

int main(int argc, char **argv) {
  auto console = spdlog::stdout_color_mt("console");
  console->set_level(spdlog::level::debug);

  auto *comp = new ZexRunnerComputer();
  spdlog::get("general")->debug("Computer created");
  // load zexdoc and cpm output bodge
  loadIntoMemory2(comp->getMemory(), 0x100, "./bin_z80/zexdoc.bin");
  loadIntoMemory2(comp->getMemory(), 0, "./bin_z80/cpm_io.rom");

  boost::timer::auto_cpu_timer t;
  //   for (std::uint64_t i = 0; i < 100000000; i++) {
  while (true) {
    //     if (i % 10000000 == 0) {
    //       std::cout << i << std::endl;
    //     }
    comp->getProcessor()->process();
  }
}
