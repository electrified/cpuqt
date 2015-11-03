#pragma once
#include "Z80/Memory.h"

#include <vector>

std::vector<char> ReadAllBytes(char const *filename);
void loadIntoMemory(std::vector<char> data, Memory *memory, std::uint16_t offset);
void loadIntoMemory2(Memory *memory, std::uint16_t offset, char const *filename);