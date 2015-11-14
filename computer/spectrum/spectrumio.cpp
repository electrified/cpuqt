#include "spectrumio.h"

#include <map>
#include "spdlog/spdlog.h"

SpectrumIO::SpectrumIO() {
  //     inputKeys.push_back(0xFE04);
  std::fill_n(this->keystates, 8, 0xff);

  keyCodes[49] = spec_key(3, 0x01); // 1
  keyCodes[50] = spec_key(3, 0x02); // 2
  keyCodes[51] = spec_key(3, 0x04); // 3
  keyCodes[52] = spec_key(3, 0x08); // 4
  keyCodes[53] = spec_key(3, 0x10); // 5
  keyCodes[54] = spec_key(4, 0x10); // 6
  keyCodes[55] = spec_key(4, 0x08); // 7
  keyCodes[56] = spec_key(4, 0x04); // 8
  keyCodes[57] = spec_key(4, 0x02); // 9
  keyCodes[48] = spec_key(4, 0x01); // 0

  keyCodes[81] = spec_key(2, 0x01); // Q
  keyCodes[87] = spec_key(2, 0x02); // W
  keyCodes[69] = spec_key(2, 0x04); // E
  keyCodes[82] = spec_key(2, 0x08); // R
  keyCodes[84] = spec_key(2, 0x10); // T
  keyCodes[89] = spec_key(5, 0x10); // Y
  keyCodes[85] = spec_key(5, 0x08); // U
  keyCodes[73] = spec_key(5, 0x04); // I
  keyCodes[79] = spec_key(5, 0x02); // O
  keyCodes[80] = spec_key(5, 0x01); // P

  keyCodes[65] = spec_key(1, 0x01);       // A
  keyCodes[83] = spec_key(1, 0x02);       // S
  keyCodes[68] = spec_key(1, 0x04);       // D
  keyCodes[70] = spec_key(1, 0x08);       // F
  keyCodes[71] = spec_key(1, 0x10);       // G
  keyCodes[72] = spec_key(6, 0x10);       // H
  keyCodes[74] = spec_key(6, 0x08);       // J
  keyCodes[75] = spec_key(6, 0x04);       // K
  keyCodes[76] = spec_key(6, 0x02);       // L
  keyCodes[16777220] = spec_key(6, 0x01); // enter

  keyCodes[16777248] = spec_key(0, 0x01); // caps (shift key)
  keyCodes[90] = spec_key(0, 0x02);       // Z
  keyCodes[88] = spec_key(0, 0x04);       // X
  keyCodes[67] = spec_key(0, 0x08);       // C
  keyCodes[86] = spec_key(0, 0x10);       // V
  keyCodes[66] = spec_key(7, 0x10);       // B
  keyCodes[78] = spec_key(7, 0x08);       // N
  keyCodes[77] = spec_key(7, 0x04);       // M
  keyCodes[16777249] = spec_key(7, 0x02); // sym (control)
  keyCodes[32] = spec_key(7, 0x01);       // space

  // shifted combinations
  keyCodes[16777219] = spec_key(4, 0x01, true); // backspace => caps + 0
  keyCodes[16777234] = spec_key(3, 0x10, true); // left arrow => caps + 5
  keyCodes[16777235] = spec_key(4, 0x08, true); // up arrow => caps + 7
  keyCodes[16777236] = spec_key(4, 0x04, true); // right arrow => caps + 8
  keyCodes[16777237] = spec_key(4, 0x10, true); // down arrow => caps + 6
}

SpectrumIO::~SpectrumIO() {}

spec_key SpectrumIO::findKey(int key) {
  std::map<int, spec_key>::iterator it = keyCodes.find(key);
  if (it != keyCodes.end()) {
    return it->second;
  }
  return spec_key();
}

void SpectrumIO::keydown(int key) {
  spec_key theKey = findKey(key);
  if (theKey.mask == 0)
    return;

  keystates[theKey.row] &= ~(theKey.mask);
  if (theKey.caps)
    keystates[0] &= 0xfe;
}

void SpectrumIO::keyup(int key) {
  spec_key theKey = findKey(key);
  if (theKey.mask == 0)
    return;

  keystates[theKey.row] |= theKey.mask;
  if (theKey.caps)
    keystates[0] |= 0x01;
}

/*
 * The contents of register C are placed on the bottom half (A0 through A7) of
the address bus to select the I/O device at one of 256 possible ports. The
contents of Register B are placed on the top half (A8 through A15) of the
address bus at this time.
*/
std::uint8_t SpectrumIO::read(std::uint16_t address) {
  /*
   * WHen a key is held down, it pulls that line low.
   */
  std::uint8_t returnValue = 0xff; // no keys pressed
                                   //     spdlog::get("console")->debug("address read {0:x}", address);
  if ((address & 0x0001) == 0x0000) {
    //         uint8_t lineScanned = address >> 8;

    //         spdlog::get("console")->debug("scanning line {0:x}", lineScanned);

    for (uint8_t row = 0; row < 8; row++) {
      if (!(address & (1 << (row + 8)))) { /* bit held low, so scan this row */
        returnValue &= keystates[row];
        //             spdlog::get("console")->debug("Row: {0:x} Value: {1:x}", row, returnValue);
      }
    }

    //         if (inputKeys.size() > 0) {
    //             uint16_t key = inputKeys.front();
    //
    //             if (key >> 8 == lineScanned) {
    //                 inputKeys.erase(inputKeys.begin());
    //                 returnValue = key & 0xff;
    //             }
    //         }
  }
  return returnValue;
}

void SpectrumIO::write(std::uint16_t address, std::uint8_t value) {}