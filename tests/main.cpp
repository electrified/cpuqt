#define CATCH_CONFIG_RUNNER

#include "../computer/logger.h"

#include <catch2/catch.hpp>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

int main(int argc, char *const argv[]) {
  configureLoggers();
  int result = Catch::Session().run(argc, argv);

  // global clean-up...

  return result;
}
