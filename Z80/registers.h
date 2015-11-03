#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"
#include <boost/utility/binary.hpp>
#include "Logger.h"
#include <bitset>

union WideReg {
  std::uint16_t all;
  struct {
    std::uint8_t low;
    std::uint8_t high;
  } bytes;
  bool bit[16];
};

// union AFReg {
//     std::uint16_t all;
//     struct {
//         std::uint8_t low;
//         std::uint8_t high;
//     };
//     struct {
//         std::uint8_t a;
//         std::bitset<8> f;
//     };
// };

class Registers {
  Logger logger;
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

  std::uint16_t getPC();

  void setPC(std::uint16_t pc);

  std::uint8_t getA();

  void setA(std::uint8_t a);

  std::uint16_t getAF();

  void setAF(std::uint16_t value);

  std::uint16_t getAF_alt();

  void setAF_alt(std::uint16_t value);

  std::uint8_t getA_alt();

  void setA_alt(std::uint8_t a_alt);

  std::uint8_t getB();

  void setB(std::uint8_t b);

  std::uint16_t getBC();

  void setBC(std::uint16_t value);

  std::uint16_t getBC_alt();

  void setBC_alt(std::uint16_t value);

  std::uint8_t getB_alt();

  void setB_alt(std::uint8_t b_alt);

  std::uint8_t getC();

  void setC(std::uint8_t c);

  bool getCFlag();

  void setCFlag(bool flag);

  std::uint8_t getC_alt();

  void setC_alt(std::uint8_t c_alt);

  std::uint8_t getD();

  void setD(std::uint8_t d);

  std::uint16_t getDE();

  void setDE(std::uint16_t value);

  std::uint16_t getDE_alt();

  void setDE_alt(std::uint16_t value);

  std::uint8_t getD_alt();

  void setD_alt(std::uint8_t d_alt);

  std::uint8_t getE();

  void setE(std::uint8_t e);

  std::uint8_t getE_alt();

  void setE_alt(std::uint8_t e_alt);

  std::uint8_t getF();

  void setF(std::uint8_t f);

  std::uint8_t getF_alt();

  void setF_alt(std::uint8_t f_alt);

  std::uint8_t getH();

  void setH(std::uint8_t h);

  bool getHFlag();

  void setHFlag(bool flag);

  std::uint16_t getHL();

  void setHL(std::uint16_t value);

  std::uint16_t getHL_alt();

  void setHL_alt(std::uint16_t value);

  std::uint8_t getH_alt();

  void setH_alt(std::uint8_t h_alt);

  std::uint8_t getI();

  void setI(std::uint8_t i);

  std::uint8_t getIM();

  void setIM(std::uint8_t im);

  std::uint16_t getIX();

  void setIX(std::uint16_t iX);

  std::uint8_t getIXH();

  std::uint8_t getIXL();

  std::uint16_t getIY();

  void setIY(std::uint16_t iY);

  std::uint8_t getIYH();

  std::uint8_t getIYL();

  std::uint8_t getL();

  void setL(std::uint8_t l);

  std::uint8_t getL_alt();

  void setL_alt(std::uint8_t l_alt);

  bool isHalted();

  void setHalted(bool val);

  bool isIFF1();

  void setIFF1(bool iFF1);

  bool isIFF2();

  void setIFF2(bool iFF2);

  std::uint16_t getRegisterPairValue(const RegisterPair register);

  std::uint8_t getRegisterValue(const Rgstr register);

  bool getNFlag();

  void setNFlag(bool flag);

  bool getParityOverflowFlag();

  void setParityOverflowFlag(bool flag);

  std::uint8_t getR();

  void setR(std::uint8_t r);

  std::uint16_t getSP();

  void setSP(std::uint16_t sP);

  bool getSignFlag();

  void setSignFlag(bool flag);

  bool getZeroFlag();

  void setZeroFlag(bool flag);

  void setRegister(Rgstr register, std::uint8_t value);

  void setRegisterPair(RegisterPair register, std::uint16_t sixteenBit);

  void setRegisterPair(RegisterPair register, std::uint8_t lowOrder, std::uint8_t highOrder);
};

#endif // REGISTERS_H
