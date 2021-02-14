#include "spectrumio.h"

#include "spdlog/spdlog.h"
#include <map>

SpectrumIO::SpectrumIO() {
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

SpectrumIO::~SpectrumIO() = default;

spec_key SpectrumIO::findKey(int key) {
  auto it = keyCodes.find(key);
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

std::uint8_t SpectrumIO::read(std::uint16_t address) {
  /*
   * WHen a key is held down, it pulls that line low.
   */
  std::uint8_t returnValue = 0xff; // no keys pressed
  SPDLOG_TRACE("address read {0:x}", address);
  if ((address & 0x0001) == 0x0000) {
    for (uint8_t row = 0; row < 8; row++) {
      if (!(address & (1 << (row + 8)))) { /* bit held low, so scan this row */
        returnValue &= keystates[row];
        SPDLOG_TRACE("Row: {0:x} Value: {1:x}", row, returnValue);
      }
    }
  }
  SPDLOG_TRACE("returning");
  return returnValue;
}

void SpectrumIO::write(std::uint16_t address, std::uint8_t value) {}
