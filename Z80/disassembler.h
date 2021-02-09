#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "RegisterPair.hpp"
#include "Register.hpp"
#include "MemoryAddress.h"
#include "Memory.h"
#include "decoder.h"
#include "DisassemblyResult.h"

class Disassembler : public Alu {
  std::uint16_t programCounterAtStartOfInstructionExecution = 0;
  Decoder *decoder;
  Memory *memory;
  void add(std::string mnemonic);

public:
  std::vector<std::string> results;
  void ADC(RegisterPair hl, RegisterPair bc) override;

  void ADC(Rgstr a, Rgstr b) override;

  void ADC(Rgstr a, std::uint8_t i) override;

  void ADC(Rgstr a, MemoryAddress memoryAddress) override;

  void ADD(RegisterPair destination, RegisterPair registerPair) override;

  void ADD(Rgstr a, std::uint8_t nextByte) override;

  void ADD(Rgstr a, Rgstr b) override;

  void ADD(Rgstr a, MemoryAddress memoryAddress) override;

  void AND(Rgstr iX2) override;

  void AND(std::uint8_t iX2) override;

  void AND(MemoryAddress memoryAddress) override;

  void BIT(std::uint8_t y, Rgstr rgstr) override;

  void BIT(std::uint8_t i, MemoryAddress memoryAddress) override;

  void CALL(Condition c, MemoryAddress memoryAddress) override;

  void CALL(MemoryAddress memoryAddress) override;

  void CCF() override;

  void CP(std::uint8_t val) override;

  void CP(Rgstr val) override;

  void CP(MemoryAddress memoryAddress) override;

  void CPD() override;

  void CPDR() override;

  void CPI() override;

  void CPIR() override;

  void CPL() override;

  void DAA() override;

  void DEC(Rgstr r) override;

  void DEC(RegisterPair r) override;

  void DEC(MemoryAddress memoryAddress) override;

  void DI() override;

  void DJNZ(MemoryAddress memoryAddress) override;

  void EI() override;

  void EX(RegisterPair de, RegisterPair hl) override;

  void EX(MemoryAddress memoryAddress, RegisterPair ix) override;

  void EXX() override;

  void HALT() override;

  void IM(std::uint8_t im) override;

  void in(const Rgstr a, const MemoryAddress i) override;

  void INC(Rgstr r) override;

  void INC(RegisterPair r) override;

  void INC(MemoryAddress memoryAddress) override;

  void IND() override;

  void INDR() override;

  void INI() override;

  void INIR() override;

  void JP(Condition c, MemoryAddress i) override;

  void JP(MemoryAddress memoryAddress) override;

  void JR(Condition nz, MemoryAddress memoryAddress) override;

  void JR(MemoryAddress memoryAddress) override;

  void LD(Rgstr rgstr, std::uint8_t memoryAddress) override;

  void LD(Rgstr r1, Rgstr r2) override;

  void LD(RegisterPair r1, RegisterPair r2) override;

  void LD(RegisterPair regPair, std::uint16_t immediateValue) override;

  void LD(MemoryAddress memoryAddress, Rgstr a) override;

  void LD(Rgstr a, MemoryAddress memoryAddress) override;

  void LD(MemoryAddress memoryAddress, RegisterPair hl) override;

  void LD(RegisterPair hl, MemoryAddress memoryAddress) override;

  void LD(MemoryAddress memoryAddress, std::uint8_t i) override;

  void LDD() override;

  void LDDR() override;

  void LDI() override;

  void LDIR() override;

  void NEG() override;

  void NOP() override;

  void OR(Rgstr iX2) override;

  void OR(std::uint8_t immediateValue) override;

  void OR(MemoryAddress memoryAddress) override;

  void OTDR() override;

  void OTIR() override;

  void out(MemoryAddress address, Rgstr rgstr) override;

  void OUTD() override;

  void OUTI() override;

  void POP(RegisterPair iy) override;

  void PUSH(RegisterPair valueRegister) override;

  void RES(std::uint8_t i, Rgstr b) override;

  void RES(std::uint8_t i, MemoryAddress memoryAddress) override;

  void RET(Condition p) override;

  void RET() override;

  void RETI() override;

  void RETN() override;

  void RL(Rgstr r) override;

  void RL(MemoryAddress memoryAddress) override;

  void RLA() override;

  void RLC(Rgstr rgstr) override;

  void RLC(MemoryAddress memoryAddress) override;

  void RLCA() override;

  void RLD() override;

  void RR(Rgstr r) override;

  void RR(MemoryAddress memoryAddress) override;

  void RRA() override;

  void RRC(Rgstr r) override;

  void RRC(MemoryAddress memoryAddress) override;

  void RRCA() override;

  void RRD() override;

  void RST(std::uint8_t i) override;

  void SBC(Rgstr a, std::uint8_t nextByte) override;

  void SBC(Rgstr a, Rgstr b) override;

  void SBC(RegisterPair hl, RegisterPair hl1) override;

  void SBC(Rgstr a, MemoryAddress memoryAddress) override;

  void SCF() override;

  void SET(std::uint8_t y, Rgstr rgstr) override;

  void SET(std::uint8_t i, MemoryAddress memoryAddress) override;

  void SLA(Rgstr r) override;

  void SLA(MemoryAddress memoryAddress) override;

  void SRA(Rgstr r) override;

  void SRA(MemoryAddress memoryAddress) override;

  void SRL(Rgstr r) override;

  void SRL(MemoryAddress memoryAddress) override;

  void SUB(Rgstr iX2) override;

  void SUB(std::uint8_t iX2) override;

  void SUB(MemoryAddress memoryAddress) override;

  void XOR(Rgstr val) override;

  void XOR(std::uint8_t val) override;

  void XOR(MemoryAddress memoryAddress) override;

  explicit Disassembler(Memory *memory);
  ~Disassembler();
  void disassemble(std::uint16_t start, std::uint16_t end);
  void disassemble();
  std::string getDisassembly(std::uint16_t index);
};
