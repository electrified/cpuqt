#pragma once
#include <cstdint>

#include "Condition.hpp"
#include "IO.h"
#include "Memory.h"
#include "MemoryAddress.h"
#include "Register.hpp"
#include "RegisterPair.hpp"
#include "alu.h"
#include "registers.h"
#include "spdlog/spdlog.h"

bool parity(std::uint8_t val);

class UnimplementedInstructionException : public std::exception {
  virtual const char *what() const throw();
};

class Processor {
  std::shared_ptr<spdlog::logger> logger;

  Memory *memory;
  IO *io;
  Registers *registers;

  bool interruptRequested = false;

  inline std::uint8_t next() {
    SPDLOG_LOGGER_DEBUG(logger, "PC: {0:x}", registers->PC);
    return memory->read(registers->PC++);
  }

  std::uint16_t MemoryAddress(const std::uint16_t memoryAddress);

  std::uint16_t MemoryAddress(const Rgstr rgstr);

  std::uint16_t MemoryAddress(const RegisterPair rgstrPair);

  std::uint16_t MemoryAddress(const RegisterPair rgstrPair, const std::uint8_t offset);

  void ADC(RegisterPair hl, RegisterPair bc);

  void ADC(Rgstr a, Rgstr b);

  void ADC(Rgstr a, std::uint8_t i);

  void ADC(Rgstr a, std::uint16_t memoryAddress);

  void ADD(RegisterPair destination, RegisterPair rgstr);

  void ADD(Rgstr a, std::uint8_t nextByte);

  void ADD(Rgstr a, Rgstr b);

  void ADD(Rgstr a, std::uint16_t memoryAddress);

  void AND(Rgstr iX2);

  void AND(std::uint8_t iX2);

  void AND(std::uint16_t memoryAddress);

  void BIT(std::uint8_t y, Rgstr rgstr);

  void BIT(std::uint8_t i, std::uint16_t memoryAddress);

  void BIT(std::uint8_t y, std::uint8_t value);

  void CALL(Condition c, std::uint16_t memoryAddress);

  void CALL(std::uint16_t memoryAddress);

  void CCF();

  void CP(std::uint8_t val);

  void CP(Rgstr val);

  void CP(std::uint16_t memoryAddress);

  void CPD();

  void CPDR();

  void CPI();

  void CPIR();

  void CPL();

  void DAA();

  void DEC(Rgstr r);

  void DEC(RegisterPair r);

  void DEC(std::uint16_t memoryAddress);

  void DI();

  void DJNZ(std::uint16_t memoryAddress);

  void EI();

  void EX(RegisterPair de, RegisterPair hl);

  void EX(std::uint16_t memoryAddress, RegisterPair ix);

  void EXX();

  void HALT();

  void IM(std::uint8_t im);

  void in(Rgstr a, std::uint16_t i);

  void INC(Rgstr r);

  void INC(RegisterPair r);

  void INC(std::uint16_t memoryAddress);

  void IND();

  void INDR();

  void INI();

  void INIR();

  void JP(Condition c, std::uint16_t i);

  void JP(std::uint16_t memoryAddress);

  void JR(Condition nz, std::uint16_t memoryAddress);

  void JR(std::uint16_t memoryAddress);

  void LD(Rgstr rgstr, std::uint8_t memoryAddress);

  void LD(Rgstr r1, Rgstr r2);

  void LD(RegisterPair r1, RegisterPair r2);

  void LD(RegisterPair regPair, std::uint16_t immediateValue);

  void LD(std::uint16_t memoryAddress, Rgstr a);

  void LD(Rgstr a, std::uint16_t memoryAddress);

  void LD(std::uint16_t memoryAddress, RegisterPair hl);

  void LD_indirect(RegisterPair hl, std::uint16_t memoryAddress);

  void LD(std::uint16_t memoryAddress, std::uint8_t i);

  void LDD();

  void LDDR();

  void LDI();

  void LDIR();

  void NEG();

  void NOP();

  void OR(Rgstr iX2);

  void OR(std::uint8_t immediateValue);

  void OR(std::uint16_t memoryAddress);

  void OTDR();

  void OTIR();

  void out(std::uint16_t address, Rgstr reg);

  void OUTD();

  void OUTI();

  void POP(RegisterPair iy);

  void PUSH(RegisterPair valueRegister);

  void RES(std::uint8_t i, Rgstr b);

  void RES(std::uint8_t i, std::uint16_t memoryAddress);

  void RET(Condition p);

  void RET();

  void RETI();

  void RETN();

  void RL(Rgstr r);

  void RL(std::uint16_t memoryAddress);

  void RLA();

  void RLC(Rgstr reg);

  void RLC(std::uint16_t memoryAddress);

  void RLCA();

  void RLD();

  void RR(Rgstr r);

  void RR(std::uint16_t memoryAddress);

  void RRA();

  void RRC(Rgstr r);

  void RRC(std::uint16_t memoryAddress);

  void RRCA();

  void RRD();

  void RST(std::uint8_t i);

  void SBC(Rgstr a, std::uint8_t nextByte);

  void SBC(Rgstr a, Rgstr b);

  void SBC(RegisterPair hl, RegisterPair hl1);

  void SBC(Rgstr a, std::uint16_t memoryAddress);

  void SCF();

  void SET(std::uint8_t y, Rgstr reg);

  void SET(std::uint8_t i, std::uint16_t memoryAddress);

  void SLA(Rgstr r);

  void SLA(std::uint16_t memoryAddress);

  void SRA(Rgstr r);

  void SRA(std::uint16_t memoryAddress);

  void SRL(Rgstr r);
  void SRL(std::uint16_t memoryAddress);

  void SUB(Rgstr iX2);
  void SUB(std::uint8_t iX2);
  void SUB(std::uint16_t memoryAddress);

  void XOR(Rgstr val);
  void XOR(std::uint8_t val);
  void XOR(std::uint16_t memoryAddress);

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

private:
  void do_adc(Rgstr rgstr, std::uint8_t val);
};
