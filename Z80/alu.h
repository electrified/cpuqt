#ifndef ALU_H
#define ALU_H

#include <cstdint>

#include "Z80/RegisterPair.hpp"
#include "Z80/Register.hpp"
#include "Z80/Condition.hpp"
#include "Z80/MemoryAddress.h"
#include "Z80/Memory.h"
#include "Z80/IO.h"

class Alu
{
public:
    virtual void ADC(const RegisterPair hl, const RegisterPair bc) = 0;
    virtual void ADC(const Rgstr a, const Rgstr b) = 0;
    virtual void ADC(const Rgstr a, const std::uint8_t i) = 0;
    virtual void ADC(const Rgstr a, const MemoryAddress memoryAddress) = 0;

    virtual void ADD(const RegisterPair destination, const RegisterPair register) = 0;
    virtual void ADD(const Rgstr a, const std::uint8_t nextByte) = 0;
    virtual void ADD(const Rgstr a, const Rgstr b) = 0;
    virtual void ADD(const Rgstr a, const MemoryAddress memoryAddress) = 0;

    virtual void AND(const Rgstr iX2) = 0;
    virtual void AND(const std::uint8_t iX2) = 0;
    virtual void AND(const MemoryAddress memoryAddress) = 0;

    virtual void BIT(const std::uint8_t y, const Rgstr register) = 0;
    virtual void BIT(const std::uint8_t i, const MemoryAddress memoryAddress) = 0;

    virtual void CALL(const Condition c, const MemoryAddress memoryAddress) = 0;
    virtual void CALL( const MemoryAddress memoryAddress) = 0;

    virtual void CCF() = 0;

    virtual void CP(const std::uint8_t val) = 0;
    virtual void CP(const Rgstr val) = 0;
    virtual void CP(const MemoryAddress memoryAddress) = 0;

    virtual void CPD() = 0;

    virtual void CPDR() = 0;

    virtual void CPI() = 0;

    virtual void CPIR() = 0;

    virtual void CPL() = 0;

    virtual void DAA() = 0;

    virtual void DEC(const Rgstr r) = 0;
    virtual void DEC(const RegisterPair r) = 0;
    virtual void DEC(const MemoryAddress memoryAddress) = 0;

    virtual void DI() = 0;

    virtual void DJNZ(const MemoryAddress memoryAddress) = 0;

    virtual void EI() = 0;

    virtual void EX(const RegisterPair de, const RegisterPair hl) = 0;
    virtual void EX(const MemoryAddress memoryAddress, const RegisterPair ix) = 0;

    virtual void EXX() = 0;

    virtual void HALT() = 0;

    virtual void IM(const std::uint8_t im) = 0;

    virtual void in(const Rgstr a, const MemoryAddress& i) = 0;

    virtual void INC(const Rgstr r) = 0;
    virtual void INC(const RegisterPair r) = 0;
    virtual void INC(const MemoryAddress memoryAddress) = 0;

    virtual void IND() = 0;

    virtual void INDR() = 0;

    virtual void INI() = 0;

    virtual void INIR() = 0;

    virtual void JP(const Condition c, const MemoryAddress i) = 0;
    virtual void JP(const MemoryAddress memoryAddress) = 0;

    virtual void JR(const Condition nz, const MemoryAddress memoryAddress) = 0;
    virtual void JR(const MemoryAddress memoryAddress) = 0;

    virtual void LD(const Rgstr register, const std::uint8_t memoryAddress) = 0;
    virtual void LD(const Rgstr r1, const Rgstr r2) = 0;
    virtual void LD(const RegisterPair r1, const RegisterPair r2) = 0;

    virtual void LD(const RegisterPair registerPair, const std::uint16_t immediateValue) = 0;
    virtual void LD(const MemoryAddress memoryAddress, const Rgstr a) = 0;
    virtual void LD(const Rgstr a, const MemoryAddress memoryAddress) = 0;
    virtual void LD(const MemoryAddress memoryAddress, const RegisterPair hl) = 0;
    virtual void LD(const RegisterPair hl, const MemoryAddress memoryAddress) = 0;
    virtual void LD(const MemoryAddress memoryAddress, const std::uint8_t i) = 0;

    virtual void LDD() = 0;

    virtual void LDDR() = 0;

    virtual void LDI() = 0;

    virtual void LDIR() = 0;

    virtual void NEG() = 0;


    virtual void NOP() = 0;

    virtual void OR(const Rgstr iX2) = 0;
    virtual void OR(const std::uint8_t immediateValue) = 0;
    virtual void OR(const MemoryAddress memoryAddress) = 0;

    virtual void OTDR() = 0;

    virtual void OTIR() = 0;

    virtual void out(const MemoryAddress address, const Rgstr register) = 0;

    virtual void OUTD() = 0;

    virtual void OUTI() = 0;

    virtual void POP(const RegisterPair iy) = 0;

    virtual void PUSH(const RegisterPair valueRegister) = 0;

    virtual void RES(const std::uint8_t i, const Rgstr b) = 0;
    virtual void RES(const std::uint8_t i, const MemoryAddress memoryAddress) = 0;

    virtual void RET(const Condition p) = 0;

    virtual void RET() = 0;

    virtual void RETI() = 0;

    virtual void RETN() = 0;

    virtual void RL(const Rgstr r) = 0;

    virtual void RL(const MemoryAddress memoryAddress) = 0;

    virtual void RLA() = 0;

    virtual void RLC(const Rgstr register) = 0;
    virtual void RLC(const MemoryAddress memoryAddress) = 0;

    virtual void RLCA() = 0;

    virtual void RLD() = 0;

    virtual void RR(const Rgstr r) = 0;

    virtual void RR(const MemoryAddress memoryAddress) = 0;

    virtual void RRA() = 0;

    virtual void RRC(const Rgstr r) = 0;

    virtual void RRC(const MemoryAddress memoryAddress) = 0;

    virtual void RRCA() = 0;

    virtual void RRD() = 0;

    virtual void RST(const std::uint8_t i) = 0;

    virtual void SBC(const Rgstr a, const std::uint8_t nextByte) = 0;
    virtual void SBC(const Rgstr a, const Rgstr b) = 0;
    virtual void SBC(const RegisterPair hl, const RegisterPair hl1) = 0;
    virtual void SBC(const Rgstr a, const MemoryAddress memoryAddress) = 0;

    virtual void SCF() = 0;

    virtual void SET(const std::uint8_t y, const Rgstr register) = 0;

    virtual void SET(const std::uint8_t i, const MemoryAddress memoryAddress) = 0;

    virtual void SLA(const Rgstr r) = 0;
    virtual void SLA(const MemoryAddress memoryAddress) = 0;

    virtual void SRA(const Rgstr r) = 0;
    virtual void SRA(const MemoryAddress memoryAddress) = 0;

    virtual void SRL(const Rgstr r) = 0;
    virtual void SRL(const MemoryAddress memoryAddress) = 0;

    virtual void SUB(const Rgstr iX2) = 0;
    virtual void SUB(const std::uint8_t iX2) = 0;
    virtual void SUB(const MemoryAddress memoryAddress) = 0;

    virtual void XOR(const Rgstr val) = 0;
    virtual void XOR(const std::uint8_t val) = 0;
    virtual void XOR(const MemoryAddress memoryAddress) = 0;
};
#endif
