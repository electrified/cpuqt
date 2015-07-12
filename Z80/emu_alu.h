#ifndef EMULATIONPROCESSOR_H
#define EMULATIONPROCESSOR_H

#include "Z80/processor.h"
#include "Z80/decoder.h"
#include "Z80/MemoryAddress.h"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"
#include "Z80/registers.h"
#include "Z80/IO.h"
#include "Logger.h"

class UnimplementedInstructionException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Unimplemented instruction";
    }
};

class EmuAlu : public Alu {
protected:
    Logger logger;
    Memory* memory;
    IO* io;
    Registers* registers;
public:
    EmuAlu(Memory* memory, IO* io, Registers* registers);
    ~EmuAlu();
    void ADC(const RegisterPair hl, const RegisterPair bc);

    void ADC(const Rgstr a, const Rgstr b);

    void ADC(const Rgstr a, const std::uint8_t i);

    void ADC(const Rgstr a, const MemoryAddress memoryAddress);

    void ADD(const RegisterPair destination, const RegisterPair rgstr);

    void ADD(const Rgstr a, const std::uint8_t nextByte);

    void ADD(const Rgstr a, const Rgstr b);

    void ADD(const Rgstr a, const MemoryAddress memoryAddress);

    void AND(const Rgstr iX2);

    void AND(const std::uint8_t iX2);

    void AND(const MemoryAddress memoryAddress);

    void BIT(const std::uint8_t y, const Rgstr rgstr);

    void BIT(const std::uint8_t i, const MemoryAddress memoryAddress);

    void BIT(const std::uint8_t y, const std::uint8_t value);

    void CALL(const Condition c, const MemoryAddress memoryAddress);

    void CALL(const MemoryAddress memoryAddress);

    void CCF();

    void CP(const std::uint8_t val);

    void CP(const Rgstr val);

    void CP(const MemoryAddress memoryAddress);

    void CPD();

    void CPDR();

    void CPI();

    void CPIR();

    void CPL();

    void DAA();

    void DEC(const Rgstr r);

    void DEC(const RegisterPair r);

    void DEC(const MemoryAddress memoryAddress);

    void DI();

    void DJNZ(const MemoryAddress memoryAddress);

    void EI();

    void EX(const RegisterPair de, const RegisterPair hl);

    void EX(const MemoryAddress memoryAddress, const RegisterPair ix);

    void EXX();

    void HALT();

    void IM(const std::uint8_t im);

    void in(const Rgstr a,const MemoryAddress& i);

    void INC(const Rgstr r);

    void INC(const RegisterPair r);

    void INC(const MemoryAddress memoryAddress);

    void IND();

    void INDR();

    void INI();

    void INIR();

    void JP(const Condition c, const MemoryAddress i);

    void JP(const MemoryAddress memoryAddress);

    void JR(const Condition nz, const MemoryAddress memoryAddress);

    void JR(const MemoryAddress memoryAddress);

    void LD(const Rgstr register, const std::uint8_t memoryAddress);

    void LD(const Rgstr r1, const Rgstr r2);

    void LD(const RegisterPair r1, const RegisterPair r2);

    void LD(const RegisterPair registerPair, const std::uint16_t immediateValue);

    void LD(const MemoryAddress memoryAddress, const Rgstr a);

    void LD(const Rgstr a, const MemoryAddress memoryAddress);

    void LD(const MemoryAddress memoryAddress, const RegisterPair hl);

    void LD(const RegisterPair hl, const MemoryAddress memoryAddress);

    void LD(const MemoryAddress memoryAddress, const std::uint8_t i);

    void LDD();

    void LDDR();

    void LDI();

    void LDIR();

    void NEG();

    void NOP();

    void OR(const Rgstr iX2);

    void OR(const std::uint8_t immediateValue);

    void OR(const MemoryAddress memoryAddress);

    void OTDR();

    void OTIR();

    void out(const MemoryAddress address, const Rgstr register);

    void OUTD();

    void OUTI();

    void POP(const RegisterPair iy);

    void PUSH(const RegisterPair valueRegister);

    void RES(const std::uint8_t i, const Rgstr b);

    void RES(const std::uint8_t i, const MemoryAddress memoryAddress);

    void RET(const Condition p);

    void RET();

    void RETI();

    void RETN();

    void RL(const Rgstr r);

    void RL(const MemoryAddress memoryAddress);

    void RLA();

    void RLC(const Rgstr register);

    void RLC(const MemoryAddress memoryAddress);

    void RLCA();

    void RLD();

    void RR(const Rgstr r);

    void RR(const MemoryAddress memoryAddress);

    void RRA();

    void RRC(const Rgstr r);

    void RRC(const MemoryAddress memoryAddress);

    void RRCA();

    void RRD();

    void RST(const std::uint8_t i);

    void SBC(const Rgstr a, const std::uint8_t nextByte);

    void SBC(const Rgstr a, const Rgstr b);

    void SBC(const RegisterPair hl, const RegisterPair hl1);

    void SBC(const Rgstr a, const MemoryAddress memoryAddress);

    void SCF();

    void SET(const std::uint8_t y, const Rgstr register);

    void SET(const std::uint8_t i, const MemoryAddress memoryAddress);

    void SLA(const Rgstr r);

    void SLA(const MemoryAddress memoryAddress);

    void SRA(const Rgstr r);

    void SRA(const MemoryAddress memoryAddress);

    void SRL(const Rgstr r);
    void SRL(const MemoryAddress memoryAddress);

    void SUB(const Rgstr iX2);
    void SUB(const std::uint8_t iX2);
    void SUB(const MemoryAddress memoryAddress);

    void XOR(const Rgstr val);
    void XOR(const std::uint8_t val);
    void XOR(const MemoryAddress memoryAddress);

    void incrementSP();

    bool isConditionTrue(Condition condition);
protected:
    void pushPCtoStack();

    std::uint8_t readIO(std::uint16_t address);
    void writeIO(std::uint16_t address, std::uint8_t value);


    void unimplemented();

    std::uint16_t getMemoryAddress(MemoryAddress memoryAddress);

    void decrementSP();

    void setFlags(std::uint8_t value);

};
#endif // EMULATIONPROCESSOR_H
