#include "utils.h"

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "spdlog/spdlog.h"

std::vector<char> ReadAllBytes(char const *filename) {
  std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();

  std::vector<char> result(pos);

  ifs.seekg(0, std::ios::beg);
  ifs.read(&result[0], pos);

  return result;
}

/**
* Used by frontend
*/
void loadIntoMemory(std::vector<char> data, Memory *memory, std::uint16_t offset) {
  for (std::uint16_t i = 0; i < data.size(); ++i) {
    memory->write(i + offset, data.at(i));
  }
}

/**
* Used by tests
*/
void loadIntoMemory2(Memory *memory, std::uint16_t offset, char const *filename) {
  if (boost::filesystem::exists(filename)) {
    std::ifstream testFile(filename, std::ios::binary);
    std::vector<char> fileContents((std::istreambuf_iterator<char>(testFile)), std::istreambuf_iterator<char>());

    for (std::uint16_t i = 0; i < fileContents.size(); ++i) {
      memory->write(i + offset, fileContents.at(i));
    }
  } else {
    spdlog::get("console")->info(std::string("File not found: ") + std::string(filename));
  }
}

/*
* See info at http://www.worldofspectrum.org/faq/reference/z80format.htm
*/
void loadZ80Snapshot(std::vector<char> data, Memory *memory, Registers *registers) {
/*Offset  Length  Description
        ---------------------------
        0       1       A register
        1       1       F register
        2       2       BC register pair (LSB, i.e. C, first)
        4       2       HL register pair
        6       2       Program counter
        8       2       Stack pointer
        10      1       Interrupt register
        11      1       Refresh register (Bit 7 is not significant!)
        12      1       Bit 0  : Bit 7 of the R-register
                        Bit 1-3: Border colour
                        Bit 4  : 1=Basic SamRom switched in
                        Bit 5  : 1=Block of data is compressed
                        Bit 6-7: No meaning
        13      2       DE register pair
        15      2       BC' register pair
        17      2       DE' register pair
        19      2       HL' register pair
        21      1       A' register
        22      1       F' register
        23      2       IY register (Again LSB first)
        25      2       IX register
        27      1       Interrupt flipflop, 0=DI, otherwise EI
        28      1       IFF2 (not particularly important...)
        29      1       Bit 0-1: Interrupt mode (0, 1 or 2)
                        Bit 2  : 1=Issue 2 emulation
                        Bit 3  : 1=Double interrupt frequency
                        Bit 4-5: 1=High video synchronisation
                                3=Low video synchronisation
                                0,2=Normal
                        Bit 6-7: 0=Cursor/Protek/AGF joystick
                                1=Kempston joystick
                                2=Sinclair 2 Left joystick (or user
                                  defined, for version 3 .z80 files)
                                3=Sinclair 2 Right joystick
*/
  registers->setA(data.at(0));
  registers->setF(data.at(1));
  registers->setC(data.at(2));
  registers->setB(data.at(3));
  registers->setL(data.at(4));
  registers->setH(data.at(5));
// program counter is 0 if a version 2 or 3 file
  registers->setPC((data.at(7) << 8) && data.at(6));
  registers->setSP((data.at(9) << 8) && data.at(8));
  registers->setDE((data.at(12) << 8) && data.at(13));
  registers->setBC_alt((data.at(16) << 8) && data.at(15));
  registers->setDE_alt((data.at(18) << 8) && data.at(17));
  registers->setHL_alt((data.at(20) << 8) && data.at(19));
  registers->setA_alt(data.at(21));
  registers->setF_alt(data.at(22));
  registers->setIY((data.at(24) << 8) && data.at(23));
  registers->setIX((data.at(26) << 8) && data.at(25));
//registers->setIFF1(data.at(27));
//registers->setIFF2(data.at(28));

// read block
  
  //get length of compressed data
  for (std::uint16_t i = 87; i < data.size(); ++i) {

  }
}

void decompressBlock(std::vector<char> data, Memory* memory, std::uint16_t block_start) {
//read compressed block length
std::uint16_t block_length = data.at(block_start++) & (data.at(block_start++) < 8);
std::uint16_t offset = getMemoryOffsetOfBlock(data.at(block_start++));
for (std::uint16_t i = block_start ; i < block_length; i++) {
    memory->write(i + offset, data.at(i));
}
}

std::uint16_t getMemoryOffsetOfBlock(std::uint8_t block_number) {
switch(block_number) {
case 0:
  return 0x1000;
default:
  return 0x0;
}
}
