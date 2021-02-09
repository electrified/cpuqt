#pragma once

#include <cstdint>

#include "Condition.hpp"
#include "IO.h"
#include "Memory.h"
#include "MemoryAddress.h"
#include "Register.hpp"
#include "RegisterPair.hpp"

class Alu {
public:
  virtual void ADC(RegisterPair hl, RegisterPair bc) = 0;
  virtual void ADC(Rgstr a, Rgstr b) = 0;
  virtual void ADC(Rgstr a, std::uint8_t i) = 0;
  virtual void ADC(Rgstr a, MemoryAddress memoryAddress) = 0;

  virtual void ADD(RegisterPair destination, RegisterPair source) = 0;
  virtual void ADD(Rgstr a, std::uint8_t nextByte) = 0;
  virtual void ADD(Rgstr a, Rgstr b) = 0;
  virtual void ADD(Rgstr a, MemoryAddress memoryAddress) = 0;

  virtual void AND(Rgstr iX2) = 0;
  virtual void AND(std::uint8_t iX2) = 0;
  virtual void AND(MemoryAddress memoryAddress) = 0;

  virtual void BIT(std::uint8_t y, Rgstr reg) = 0;
  virtual void BIT(std::uint8_t i, MemoryAddress memoryAddress) = 0;

  virtual void CALL(Condition c, MemoryAddress memoryAddress) = 0;
  virtual void CALL(MemoryAddress memoryAddress) = 0;

  virtual void CCF() = 0;

  virtual void CP(std::uint8_t val) = 0;
  virtual void CP(Rgstr val) = 0;
  virtual void CP(MemoryAddress memoryAddress) = 0;

  virtual void CPD() = 0;

  virtual void CPDR() = 0;

  virtual void CPI() = 0;

  virtual void CPIR() = 0;

  virtual void CPL() = 0;

  virtual void DAA() = 0;

  virtual void DEC(Rgstr r) = 0;
  virtual void DEC(RegisterPair r) = 0;
  virtual void DEC(MemoryAddress memoryAddress) = 0;

  virtual void DI() = 0;

  virtual void DJNZ(MemoryAddress memoryAddress) = 0;

  virtual void EI() = 0;

  virtual void EX(RegisterPair de, RegisterPair hl) = 0;
  virtual void EX(MemoryAddress memoryAddress, RegisterPair ix) = 0;

  virtual void EXX() = 0;

  virtual void HALT() = 0;

  virtual void IM(std::uint8_t im) = 0;

  virtual void in(Rgstr a, MemoryAddress i) = 0;

  virtual void INC(Rgstr r) = 0;
  virtual void INC(RegisterPair r) = 0;
  virtual void INC(MemoryAddress memoryAddress) = 0;

  virtual void IND() = 0;

  virtual void INDR() = 0;

  virtual void INI() = 0;

  virtual void INIR() = 0;

  virtual void JP(Condition c, MemoryAddress i) = 0;
  virtual void JP(MemoryAddress memoryAddress) = 0;

  virtual void JR(Condition nz, MemoryAddress memoryAddress) = 0;
  virtual void JR(MemoryAddress memoryAddress) = 0;

  virtual void LD(Rgstr reg, std::uint8_t memoryAddress) = 0;
  virtual void LD(Rgstr r1, Rgstr r2) = 0;
  virtual void LD(RegisterPair r1, RegisterPair r2) = 0;

  virtual void LD(RegisterPair regPair, std::uint16_t immediateValue) = 0;
  virtual void LD(MemoryAddress memoryAddress, Rgstr a) = 0;
  virtual void LD(Rgstr a, MemoryAddress memoryAddress) = 0;
  virtual void LD(MemoryAddress memoryAddress, RegisterPair hl) = 0;
  virtual void LD(RegisterPair hl, MemoryAddress memoryAddress) = 0;
  virtual void LD(MemoryAddress memoryAddress, std::uint8_t i) = 0;

  virtual void LDD() = 0;

  virtual void LDDR() = 0;

  virtual void LDI() = 0;

  virtual void LDIR() = 0;

  virtual void NEG() = 0;

  virtual void NOP() = 0;

  virtual void OR(Rgstr iX2) = 0;
  virtual void OR(std::uint8_t immediateValue) = 0;
  virtual void OR(MemoryAddress memoryAddress) = 0;

  virtual void OTDR() = 0;

  virtual void OTIR() = 0;

  virtual void out(MemoryAddress address, Rgstr reg) = 0;

  virtual void OUTD() = 0;

  virtual void OUTI() = 0;

  virtual void POP(RegisterPair iy) = 0;

  virtual void PUSH(RegisterPair valueRegister) = 0;

  virtual void RES(std::uint8_t i, Rgstr b) = 0;
  virtual void RES(std::uint8_t i, MemoryAddress memoryAddress) = 0;

  virtual void RET(Condition p) = 0;

  virtual void RET() = 0;

  virtual void RETI() = 0;

  virtual void RETN() = 0;

  virtual void RL(Rgstr r) = 0;

  virtual void RL(MemoryAddress memoryAddress) = 0;

  virtual void RLA() = 0;

  virtual void RLC(Rgstr reg) = 0;
  virtual void RLC(MemoryAddress memoryAddress) = 0;

  virtual void RLCA() = 0;

  virtual void RLD() = 0;

  virtual void RR(Rgstr r) = 0;

  virtual void RR(MemoryAddress memoryAddress) = 0;

  virtual void RRA() = 0;

  virtual void RRC(Rgstr r) = 0;

  virtual void RRC(MemoryAddress memoryAddress) = 0;

  virtual void RRCA() = 0;

  virtual void RRD() = 0;

  virtual void RST(std::uint8_t i) = 0;

  virtual void SBC(Rgstr a, std::uint8_t nextByte) = 0;
  virtual void SBC(Rgstr a, Rgstr b) = 0;
  virtual void SBC(RegisterPair hl, RegisterPair hl1) = 0;
  virtual void SBC(Rgstr a, MemoryAddress memoryAddress) = 0;

  virtual void SCF() = 0;

  virtual void SET(std::uint8_t y, Rgstr reg) = 0;

  virtual void SET(std::uint8_t i, MemoryAddress memoryAddress) = 0;

  virtual void SLA(Rgstr r) = 0;
  virtual void SLA(MemoryAddress memoryAddress) = 0;

  virtual void SRA(Rgstr r) = 0;
  virtual void SRA(MemoryAddress memoryAddress) = 0;

  virtual void SRL(Rgstr r) = 0;
  virtual void SRL(MemoryAddress memoryAddress) = 0;

  virtual void SUB(Rgstr iX2) = 0;
  virtual void SUB(std::uint8_t iX2) = 0;
  virtual void SUB(MemoryAddress memoryAddress) = 0;

  virtual void XOR(Rgstr val) = 0;
  virtual void XOR(std::uint8_t val) = 0;
  virtual void XOR(MemoryAddress memoryAddress) = 0;
};
