#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include <iostream>

#include "../Z80/utils.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

int main(int argc, char *const argv[]) {
  auto console = spdlog::stdout_color_mt("console");
  console->set_level(spdlog::level::debug);

  int result = Catch::Session().run(argc, argv);

  // global clean-up...

  return result;
}
