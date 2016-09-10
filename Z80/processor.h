#pragma once

#include <cstdint>

#include "RegisterPair.hpp"
#include "Register.hpp"
#include "Condition.hpp"
#include "MemoryAddress.h"
#include "Memory.h"
#include "IO.h"
#include "alu.h"
#include "registers.h"
#include "spdlog/spdlog.h"

bool parity(std::uint8_t val);

class UnimplementedInstructionException : public std::exception {
  virtual const char *what() const throw() { return "Unimplemented instruction"; }
};

class Processor {
  std::shared_ptr<spdlog::logger> logger;
  
  Memory *memory;
  IO *io;
  Registers *registers;

  bool interruptRequested = false;

  inline std::uint8_t next() { return memory->read(registers->PC++); }

  std::uint16_t MemoryAddress(const std::uint16_t memoryAddress) { return memoryAddress; }

  std::uint16_t MemoryAddress(const Rgstr rgstr) { return registers->getRegisterValue(rgstr); }

  std::uint16_t MemoryAddress(const RegisterPair rgstrPair) { return registers->getRegisterPairValue(rgstrPair); }

  std::uint16_t MemoryAddress(const RegisterPair rgstrPair, const std::uint8_t offset) {
    return (std::int16_t)registers->getRegisterPairValue(rgstrPair) + (std::int8_t)offset;
  }
  
  void ADC(const RegisterPair hl, const RegisterPair bc);

  void ADC(const Rgstr a, const Rgstr b);

  void ADC(const Rgstr a, const std::uint8_t i);

  void ADC(const Rgstr a, const std::uint16_t memoryAddress);

  void ADD(const RegisterPair destination, const RegisterPair rgstr);

  void ADD(const Rgstr a, const std::uint8_t nextByte);

  void ADD(const Rgstr a, const Rgstr b);

  void ADD(const Rgstr a, const std::uint16_t memoryAddress);

  void AND(const Rgstr iX2);

  void AND(const std::uint8_t iX2);

  void AND(const std::uint16_t memoryAddress);

  void BIT(const std::uint8_t y, const Rgstr rgstr);

  void BIT(const std::uint8_t i, const std::uint16_t memoryAddress);

  void BIT(const std::uint8_t y, const std::uint8_t value);

  void CALL(const Condition c, const std::uint16_t memoryAddress);

  void CALL(const std::uint16_t memoryAddress);

  void CCF();

  void CP(const std::uint8_t val);

  void CP(const Rgstr val);

  void CP(const std::uint16_t memoryAddress);

  void CPD();

  void CPDR();

  void CPI();

  void CPIR();

  void CPL();

  void DAA();

  void DEC(const Rgstr r);

  void DEC(const RegisterPair r);

  void DEC(const std::uint16_t memoryAddress);

  void DI();

  void DJNZ(const std::uint16_t memoryAddress);

  void EI();

  void EX(const RegisterPair de, const RegisterPair hl);

  void EX(const std::uint16_t memoryAddress, const RegisterPair ix);

  void EXX();

  void HALT();

  void IM(const std::uint8_t im);

  void in(const Rgstr a, const std::uint16_t i);

  void INC(const Rgstr r);

  void INC(const RegisterPair r);

  void INC(const std::uint16_t memoryAddress);

  void IND();

  void INDR();

  void INI();

  void INIR();

  void JP(const Condition c, const std::uint16_t i);

  void JP(const std::uint16_t memoryAddress);

  void JR(const Condition nz, const std::uint16_t memoryAddress);

  void JR(const std::uint16_t memoryAddress);

  void LD(const Rgstr rgstr, const std::uint8_t memoryAddress);

  void LD(const Rgstr r1, const Rgstr r2);

  void LD(const RegisterPair r1, const RegisterPair r2);

  void LD(const RegisterPair registerPair, const std::uint16_t immediateValue);

  void LD(const std::uint16_t memoryAddress, const Rgstr a);

  void LD(const Rgstr a, const std::uint16_t memoryAddress);

  void LD(const std::uint16_t memoryAddress, const RegisterPair hl);

  void LD_indirect(const RegisterPair hl, const std::uint16_t memoryAddress);

  void LD(const std::uint16_t memoryAddress, const std::uint8_t i);

  void LDD();

  void LDDR();

  void LDI();

  void LDIR();

  void NEG();

  void NOP();

  void OR(const Rgstr iX2);

  void OR(const std::uint8_t immediateValue);

  void OR(const std::uint16_t memoryAddress);

  void OTDR();

  void OTIR();

  void out(const std::uint16_t address, const Rgstr register);

  void OUTD();

  void OUTI();

  void POP(const RegisterPair iy);

  void PUSH(const RegisterPair valueRegister);

  void RES(const std::uint8_t i, const Rgstr b);

  void RES(const std::uint8_t i, const std::uint16_t memoryAddress);

  void RET(const Condition p);

  void RET();

  void RETI();

  void RETN();

  void RL(const Rgstr r);

  void RL(const std::uint16_t memoryAddress);

  void RLA();

  void RLC(const Rgstr register);

  void RLC(const std::uint16_t memoryAddress);

  void RLCA();

  void RLD();

  void RR(const Rgstr r);

  void RR(const std::uint16_t memoryAddress);

  void RRA();

  void RRC(const Rgstr r);

  void RRC(const std::uint16_t memoryAddress);

  void RRCA();

  void RRD();

  void RST(const std::uint8_t i);

  void SBC(const Rgstr a, const std::uint8_t nextByte);

  void SBC(const Rgstr a, const Rgstr b);

  void SBC(const RegisterPair hl, const RegisterPair hl1);

  void SBC(const Rgstr a, const std::uint16_t memoryAddress);

  void SCF();

  void SET(const std::uint8_t y, const Rgstr register);

  void SET(const std::uint8_t i, const std::uint16_t memoryAddress);

  void SLA(const Rgstr r);

  void SLA(const std::uint16_t memoryAddress);

  void SRA(const Rgstr r);

  void SRA(const std::uint16_t memoryAddress);

  void SRL(const Rgstr r);
  void SRL(const std::uint16_t memoryAddress);

  void SUB(const Rgstr iX2);
  void SUB(const std::uint8_t iX2);
  void SUB(const std::uint16_t memoryAddress);

  void XOR(const Rgstr val);
  void XOR(const std::uint8_t val);
  void XOR(const std::uint16_t memoryAddress);

  void incrementSP();

  bool isConditionTrue(Condition condition);

  // used by SUB and CP
  std::uint8_t _compare(std::uint8_t x);

protected:
  void pushPCtoStack();

  std::uint8_t readIO(std::uint16_t address);
  void writeIO(std::uint16_t address, std::uint8_t value);

  void unimplemented(std::string);

  void decrementSP();

  void setFlags(std::uint8_t value);

public:
  Processor(Memory *memory, IO *io);
  ~Processor();
  void decode();
  void process();
  void process(std::uint8_t count);
  Memory *getMemory();
  IO *getIO();
  Registers *getRegisters();
  Alu *getAlu();
  void placeProgramCounterOnAddressBus();
  void reset();
  void interruptRequest(bool state);
};
