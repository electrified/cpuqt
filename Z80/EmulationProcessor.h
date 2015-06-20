#ifndef EMULATIONPROCESSOR_H
#define EMULATIONPROCESSOR_H

#include "Z80/baseprocessordecoder.h"
#include "Z80/MemoryAddress.h"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"
#include "Z80/IO.h"
#include "Logger.h"

class UnimplementedInstructionException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Unimplemented instruction";
    }
};


class EmulationProcessor : public BaseProcessorDecoder {
    std::uint8_t A, B, C, D, E, F, H, L, I, R;
    std::uint16_t IX, IY, SP;
    std::uint8_t A_alt, B_alt, C_alt, D_alt, E_alt, F_alt, H_alt, L_alt;
    //interrupt enable flip flops
    bool IFF1 = false;
    bool IFF2 = false;
    bool halted = false;
    //interrupt mode
    std::uint8_t _IM;
    Logger logger;
public:
    EmulationProcessor(Memory& memory, IO& io);
    ~EmulationProcessor();
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

    /**
     * DEC B - 5
     * @param r
     */
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

    /**
     * LD SP,nn - 31 n n
     * @param registerPair
     * @param immediateValue
     */
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

    std::uint16_t getRegisterPairValue(const RegisterPair register);

    std::uint8_t getRegisterValue(const Rgstr register);

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

    void process();
    void process(std::uint8_t count);

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

    void incrementSP();

    bool isConditionTrue(Condition condition);

    bool isIFF1();

    void setIFF1(bool iFF1);

    bool isIFF2();

    void setIFF2(bool iFF2);


    void setRegister(Rgstr register, std::uint8_t value);

    void setRegisterPair(RegisterPair register, std::uint16_t sixteenBit);
    
    void doOneScreenRefreshesWorth();
    void reset();

protected:
    void pushPCtoStack();

    std::uint8_t readIO(std::uint16_t address);
    void writeIO(std::uint16_t address, std::uint8_t value);

    void setFlags(std::uint8_t value);

    void setRegisterPair(RegisterPair register, std::uint8_t lowOrder, std::uint8_t highOrder);

    void unimplemented();

    std::uint16_t getMemoryAddress(MemoryAddress memoryAddress);

    void decrementSP();
};
#endif // EMULATIONPROCESSOR_H
