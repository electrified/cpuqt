#include <catch2/catch.hpp>
#include <iostream>
#include <set>
#include <stdint.h>

#include "../computer/spectrum/graphics.h"

TEST_CASE("gfx") {
  std::uint16_t memoryAddress = 0x4000;
  std::uint16_t lineNumber = 9999;

  std::set<std::uint16_t> lines;
  std::set<std::uint16_t>::iterator iter;

  while (memoryAddress < 0x57FF) {
    std::uint16_t t = memoryAddressToGfx(memoryAddress);
    lines.insert(t);
    ++memoryAddress;
  }

  for (std::set<std::uint16_t>::iterator iter = lines.begin(); iter != lines.end(); ++iter) {
    std::cout << *iter << std::endl;
  }

  //     REQUIRE(lineNumber == 0);
}
