#pragma once
#include "../Z80/Memory.h"
#include "../Z80/registers.h"

#include <vector>
#include <string>

std::vector<char> ReadAllBytes(std::string filename);
void loadIntoMemory(std::vector<char> data, Memory *memory, std::uint16_t offset);
void loadIntoMemory2(Memory *memory, std::uint16_t offset, char const *filename);
void loadZ80Snapshot(std::vector<char> data, Memory *memory, Registers *registers);
std::vector<char> decompressBlock(std::vector<char> data, std::uint16_t block_start, std::uint16_t block_length);
std::uint16_t getMemoryOffsetOfBlock(std::uint8_t block_number);
void loadBlocks(std::vector<char> data, Memory *memory);
