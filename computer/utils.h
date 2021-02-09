#pragma once
#include "../Z80/Memory.h"
#include "../Z80/registers.h"

#include <vector>
#include <string>

std::vector<uint8_t> ReadAllBytes(const std::string& filename);
void loadIntoMemory(std::vector<uint8_t> data, Memory *memory, std::uint16_t offset);
void loadIntoMemory2(Memory *memory, std::uint16_t offset, std::string filename);
void loadZ80Snapshot(std::vector<uint8_t> data, Memory *memory, Registers *registers);
std::vector<uint8_t> decompressBlock(std::vector<uint8_t> data, std::uint16_t block_start, std::uint16_t block_length);
std::uint16_t getMemoryOffsetOfBlock(std::uint8_t block_number);
void loadBlocks(std::vector<uint8_t> data, Memory *memory);
