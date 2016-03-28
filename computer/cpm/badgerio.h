#pragma once

#include <cstdint>
#include <vector>

#include "../../Z80/IO.h"

class BadgerIO : public IO {
private:
  // DLAB = Divisor Latch Access Bit
  static const int UART_PORT = 0x80; // The UART's data buffer for in/out
  static const int UART_DLL = 0x80;  // LSB of divisor latch
  static const int UART_DLM = 0x81;  // MSB of divisor latch (DLAB=1)
  static const int UART_FCR = 0x82;  // FIFO control register
  static const int UART_IER = 0x81;  // Interrupt Enable register (DLAB=0)
  static const int UART_LCR = 0x83;  // Line Control Register
  static const int UART_MCR = 0x84;  // Modem Control Register (for OUT1/OUT2)
  static const int UART_LSR = 0x85;  // Line Status Register (used for transmitter empty bit)

  std::vector<char> keyboardBuffer;
  int DLL = 0;
  int DLM = 0;
  int MCR = 0;
  int LCR = 0;
  int FCR = 0;
  int IER = 0;
  char key = 0;

  std::uint8_t memory[0xffff];

public:
  BadgerIO();
  ~BadgerIO();
  std::uint8_t read(std::uint16_t address);
  void write(std::uint16_t address, std::uint8_t value);
  virtual void outputCharacter(std::uint8_t value) = 0;
};
