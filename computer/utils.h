#pragma once
#include "../Z80/Memory.h"
#include "../Z80/registers.h"

#include <vector>

std::vector<char> ReadAllBytes(char const *filename);
void loadIntoMemory(std::vector<char> data, Memory *memory, std::uint16_t offset);
void loadIntoMemory2(Memory *memory, std::uint16_t offset, char const *filename);
void loadZ80Snapshot(std::vector<char> data, Memory *memory, Registers *registers);
void decompressBlock(std::vector<char> data, Memory* memory, std::uint16_t block_start);
std::uint16_t getMemoryOffsetOfBlock(std::uint8_t block_number);
