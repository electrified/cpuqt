#include "utils.h"

#include <fstream>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include "spdlog/spdlog.h"

std::vector<char> ReadAllBytes(std::string filename) {
  std::ifstream ifs(filename.c_str(), std::ios::binary | std::ios::ate);
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
    //     spdlog::get("console")->debug("Writing to memory location {0:x}", i + offset);
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
  bool isVersion2 = ((data.at(7) << 8) | data.at(6)) == 0;
  spdlog::get("console")->info("isVersion2 {0}", isVersion2);
  registers->setPC((data.at(7) << 8) | data.at(6));
  registers->setSP((data.at(9) << 8) | data.at(8));
  registers->setI(data.at(10));
  registers->setDE((data.at(14) << 8) | data.at(13));
  registers->setBC_alt((data.at(16) << 8) | data.at(15));
  registers->setDE_alt((data.at(18) << 8) | data.at(17));
  registers->setHL_alt((data.at(20) << 8) | data.at(19));
  registers->setA_alt(data.at(21));
  registers->setF_alt(data.at(22));
  registers->setIY((data.at(24) << 8) | data.at(23));
  registers->setIX((data.at(26) << 8) | data.at(25));
  registers->setIFF1(data.at(27) | 3);
  registers->setIFF2(data.at(28));
  registers->setIM(data.at(29));
  /*    Offset  Length  Description
         ---------------------------
       * 30      2       Length of additional header block (see below)
       * 32      2       Program counter
       * 34      1       Hardware mode (see below)
       * 35      1       If in SamRam mode, bitwise state of 74ls259.
                         For example, bit 6=1 after an OUT 31,13 (=2*6+1)
                         If in 128 mode, contains last OUT to 0x7ffd
                         If in Timex mode, contains last OUT to 0xf4
       * 36      1       Contains 0xff if Interface I rom paged
                         If in Timex mode, contains last OUT to 0xff
       * 37      1       Bit 0: 1 if R register emulation on
                         Bit 1: 1 if LDIR emulation on
                         Bit 2: AY sound in use, even on 48K machines
                         Bit 6: (if bit 2 set) Fuller Audio Box emulation
                         Bit 7: Modify hardware (see below)
       * 38      1       Last OUT to port 0xfffd (soundchip register number)
       * 39      16      Contents of the sound chip registers
         55      2       Low T state counter
         57      1       Hi T state counter
         58      1       Flag byte used by Spectator (QL spec. emulator)
                         Ignored by Z80 when loading, zero when saving
         59      1       0xff if MGT Rom paged
         60      1       0xff if Multiface Rom paged. Should always be 0.
         61      1       0xff if 0-8191 is ROM, 0 if RAM
         62      1       0xff if 8192-16383 is ROM, 0 if RAM
         63      10      5 x keyboard mappings for user defined joystick
         73      10      5 x ASCII word: keys corresponding to mappings above
         83      1       MGT type: 0=Disciple+Epson,1=Disciple+HP,16=Plus D
         84      1       Disciple inhibit button status: 0=out, 0ff=in
         85      1       Disciple inhibit flag: 0=rom pageable, 0ff=not
      ** 86      1       Last OUT to port 0x1ffd
      */

  if (isVersion2) {
    //   spdlog::get("console")->info("PC {0}", isVersion2);
    registers->setPC((data.at(33) << 8) | data.at(32));
  }
  // read block
  loadBlocks(data, memory);
  spdlog::get("console")->debug("Finished loading snapshot");
}

void loadBlocks(std::vector<char> data, Memory *memory) {
  spdlog::get("console")->debug("data size {0:x}", data.size());
  std::uint16_t i = 0x57;
  while (i < data.size() - 4) {
    std::uint8_t b1 = data.at(i);
    std::uint8_t b2 = data.at(++i);

    std::uint16_t block_length = b1 | (b2 << 8);
    std::uint16_t offset = getMemoryOffsetOfBlock(data.at(++i));

    spdlog::get("console")->debug("block start: {0:x} block length: {1:x} offset: {2:x}", i, block_length, offset);

    std::vector<char> decompressed = decompressBlock(data, ++i, block_length);
    loadIntoMemory(decompressed, memory, offset);
    i += block_length;
  }
}

/*
 * The compression method is very simple: it replaces repetitions of at least five equal bytes by a four-byte code ED ED
 * xx yy, which stands for "byte yy repeated xx times". Only sequences of length at least 5 are coded. The exception is
 * sequences consisting of ED's; if they are encountered, even two ED's are encoded into ED ED 02 ED. Finally, every
 * byte directly following a single ED is not taken into a block, for example ED 6*00 is not encoded into ED ED ED 06 00
 * but into ED 00 ED ED 05 00. The block is terminated by an end marker, 00 ED ED 00.*/
std::vector<char> decompressBlock(std::vector<char> data, std::uint16_t block_data_start, std::uint16_t block_length) {

  spdlog::get("console")->debug("Beginning blockdecompress");
  std::vector<char> uncompressed = std::vector<char>();
  std::uint16_t i = block_data_start;

  while (i < block_data_start + block_length - 4) {
    std::uint8_t h1 = data.at(i);
    std::uint8_t h2 = data.at(i + 1);
    std::uint8_t xx = data.at(i + 2);
    std::uint8_t yy = data.at(i + 3);
    if (h1 == 0xED && h2 == 0xED) {
      for (std::uint8_t j = 0; j < xx; j++) {
        uncompressed.push_back(yy);
      }
      i += 4;
    } else {
      uncompressed.push_back(h1);
      i++;
    }
  }
  spdlog::get("console")->debug("decompressed block length: {0:x}", uncompressed.size());

  return uncompressed;
}

std::uint16_t getMemoryOffsetOfBlock(std::uint8_t block_number) {
  switch (block_number) {
  case 0:
    return 0x0;
  case 4:
    return 0x8000;
  case 5:
    return 0xc000;
  case 8:
    return 0x4000;
  default:
    return 0x0;
  }
}
