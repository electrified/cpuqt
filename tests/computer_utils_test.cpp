#include "catch.hpp"
#include <boost/utility/binary.hpp>
#include "spdlog/spdlog.h"
#include "../computer/utils.h"
#include "../Z80/Memory.h"
#include "../Z80/BadgerMemory.h"

TEST_CASE("Read_all_bytes_array_is_correct_length", "utils") {
  std::vector<char> bytes = ReadAllBytes("/home/ed/dev/cpuqt/bin_z80/test.z80");
  REQUIRE(bytes.size() == 26736);
}

TEST_CASE("Decompresses block OK") {
  auto console = spdlog::stdout_logger_mt("console");
  console->set_level(spdlog::level::debug);
  std::vector<char> bytes = ReadAllBytes("/home/ed/dev/cpuqt/bin_z80/test.z80");
  REQUIRE(bytes.size() == 26736);
  Memory* memory = new BadgerMemory();
  loadBlocks(bytes, memory);
}
