#pragma once

#include "Register.hpp"
#include "RegisterPair.hpp"
#include "spdlog/spdlog.h"
#include <bitset>
#include <boost/utility/binary.hpp>
#include <cstdint>

union WideReg {
  std::uint16_t all;
  struct {
    std::uint8_t low;
    std::uint8_t high;
  } bytes;
  bool bit[16];
};

class Registers {
  WideReg IR;
  WideReg IX;
  WideReg IY;
  WideReg SP;

  WideReg AF;
  WideReg BC;
  WideReg DE;
  WideReg HL;

  WideReg AF_alt;
  WideReg BC_alt;
  WideReg DE_alt;
  WideReg HL_alt;

  // interrupt enable flip flops
  bool IFF1 = false;
  bool IFF2 = false;
  bool halted = false;
  // interrupt mode
  std::uint8_t _IM = 0;
  std::uint16_t addressBus = 0;

public:
  /*
   * Program Counter (PC) The program counter holds the 16-bit address of the
   * current instruction being fetched from memory. The PC is automatically
   * incremented after its contents have been transferred to the address
   * lines. When a program jump occurs, the new value is automatically placed
   * in the PC, overriding the incrementer.
   */
  std::uint16_t PC = 0;

  Registers();

  [[nodiscard]] std::uint16_t getPC() const;

  void setPC(std::uint16_t pc);

  std::uint8_t getA() const;

  void setA(std::uint8_t a);

  std::uint16_t getAF() const;

  void setAF(std::uint16_t value);

  std::uint16_t getAF_alt() const;

  void setAF_alt(std::uint16_t value);

  std::uint8_t getA_alt() const;

  void setA_alt(std::uint8_t a_alt);

  std::uint8_t getB() const;

  void setB(std::uint8_t b);

  std::uint16_t getBC() const;

  void setBC(std::uint16_t value);

  std::uint16_t getBC_alt() const;

  void setBC_alt(std::uint16_t value);

  std::uint8_t getB_alt() const;

  void setB_alt(std::uint8_t b_alt);

  std::uint8_t getC() const;

  void setC(std::uint8_t c);

  bool getCFlag();

  void setCFlag(bool flag);

  std::uint8_t getC_alt() const;

  void setC_alt(std::uint8_t c_alt);

  std::uint8_t getD() const;

  void setD(std::uint8_t d);

  std::uint16_t getDE() const;

  void setDE(std::uint16_t value);

  std::uint16_t getDE_alt() const;

  void setDE_alt(std::uint16_t value);

  std::uint8_t getD_alt() const;

  void setD_alt(std::uint8_t d_alt);

  std::uint8_t getE() const;

  void setE(std::uint8_t e);

  std::uint8_t getE_alt() const;

  void setE_alt(std::uint8_t e_alt);

  std::uint8_t getF() const;

  void setF(std::uint8_t f);

  std::uint8_t getF_alt() const;

  void setF_alt(std::uint8_t f_alt);

  std::uint8_t getH() const;

  void setH(std::uint8_t h);

  bool getHFlag() const;

  void setHFlag(bool flag);

  std::uint16_t getHL() const;

  void setHL(std::uint16_t value);

  std::uint16_t getHL_alt() const;

  void setHL_alt(std::uint16_t value);

  std::uint8_t getH_alt() const;

  void setH_alt(std::uint8_t h_alt);

  std::uint8_t getI() const;

  void setI(std::uint8_t i);

  std::uint8_t getIM() const;

  void setIM(std::uint8_t im);

  std::uint16_t getIX() const;

  void setIX(std::uint16_t iX);

  std::uint8_t getIXH() const;

  std::uint8_t getIXL() const;

  std::uint16_t getIY() const;

  void setIY(std::uint16_t iY);

  std::uint8_t getIYH() const;

  std::uint8_t getIYL() const;

  std::uint8_t getL() const;

  void setL(std::uint8_t l);

  std::uint8_t getL_alt() const;

  void setL_alt(std::uint8_t l_alt);

  bool isHalted() const;

  void setHalted(bool val);

  bool isIFF1() const;

  void setIFF1(bool iFF1);

  bool isIFF2() const;

  void setIFF2(bool iFF2);

  std::uint16_t getRegisterPairValue(const RegisterPair reg);

  std::uint8_t getRegisterValue(const Rgstr reg);

  bool getNFlag() const;

  void setNFlag(bool flag);

  bool getPVFlag() const;

  void setPVFlag(bool flag);

  std::uint8_t getR() const;

  void setR(std::uint8_t r);

  std::uint16_t getSP() const;

  void setSP(std::uint16_t sP);

  bool getSignFlag() const;

  void setSignFlag(bool flag);

  bool getZeroFlag() const;

  void setZeroFlag(bool flag);

  void setRegister(Rgstr reg, std::uint8_t value);

  void setRegisterPair(RegisterPair reg, std::uint16_t sixteenBit);

  void setRegisterPair(RegisterPair reg, std::uint8_t lowOrder, std::uint8_t highOrder);
};
