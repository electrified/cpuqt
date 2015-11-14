#pragma once

#include <cstdint>

std::uint16_t memoryAddressToGfx(std::uint16_t i) {

  return ((i & 0x700) >> 8) | ((i & 0xe0) >> 2) | ((i & 0x1800) >> 5);
}
