/*
 * Copyright (c) 2015, <copyright holder> <email>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef EMULATIONPROCESSOR_H
#define EMULATIONPROCESSOR_H

//#include "Z80/BaseProcessor.h"
#include "Z80/baseprocessordecoder.h"
//#include "Z80/InstructionDecoder.h"
#include "Z80/MemoryAddress.h"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"
#include "Z80/IO.h"
#include "Logger.h"

class EmulationProcessor : public BaseProcessorDecoder {
    /*
         * in java all numbers are internally represented as 32 bit. There is also
         * no unsigned therefore just using ints
         */
    std::uint8_t A, B, C, D, E, F, H, L, I, R;
    std::uint16_t IX, IY, SP;
    std::uint8_t A_alt, B_alt, C_alt, D_alt, E_alt, F_alt, H_alt, L_alt;
    IO *io;
    //interrupt enable flip flops
    bool IFF1 = false;
    bool IFF2 = false;
    bool halted = false;
    //interrupt mode
    std::uint8_t _IM;
    Logger logger;
public:
    EmulationProcessor();
//    EmulationProcessor(InstructionDecoder *decoder);
//    EmulationProcessor(EmulationProcessor *emulationProcessor);
    ~EmulationProcessor();
    void ADC(RegisterPair hl, RegisterPair bc);

    void ADC(Rgstr a, Rgstr b);

    void ADC(Rgstr a, std::uint8_t i);

    void ADC(Rgstr a, MemoryAddress memoryAddress);

    void ADD(RegisterPair destination, RegisterPair register);

    void ADD(Rgstr a, std::uint8_t nextByte);

    void ADD(Rgstr a, Rgstr b);

    void ADD(Rgstr a, MemoryAddress memoryAddress);

    void AND(Rgstr iX2);

    void AND(std::uint8_t iX2);

    void AND(MemoryAddress memoryAddress);

    void BIT(std::uint8_t y, Rgstr register);

    void BIT(std::uint8_t i, MemoryAddress memoryAddress);

    void BIT(std::uint8_t y, std::uint8_t value);

    void CALL(Condition c, MemoryAddress memoryAddress);

    void CALL(MemoryAddress memoryAddress);

    void CCF();

    void CP(std::uint8_t val);

    void CP(Rgstr val);

    void CP(MemoryAddress memoryAddress);

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
    void DEC(Rgstr r);

    void DEC(RegisterPair r);

    void DEC(MemoryAddress memoryAddress);

    void DI();

    void DJNZ(MemoryAddress memoryAddress);

    void EI();

    void EX(RegisterPair de, RegisterPair hl);

    void EX(MemoryAddress memoryAddress, RegisterPair ix);

    void EXX();

    void HALT();

    void IM(std::uint8_t im);

    void in(Rgstr a, MemoryAddress i);

    void INC(Rgstr r);

    void INC(RegisterPair r);

    void INC(MemoryAddress memoryAddress);

    void IND();

    void INDR();

    void INI();

    void INIR();

    void JP(Condition c, MemoryAddress i);

    void JP(MemoryAddress memoryAddress);

    void JR(Condition nz, MemoryAddress memoryAddress);

    void JR(MemoryAddress memoryAddress);

    void LD(Rgstr register, std::uint8_t memoryAddress);

    void LD(Rgstr r1, Rgstr r2);

    void LD(RegisterPair r1, RegisterPair r2);

    /**
     * LD SP,nn - 31 n n
     * @param registerPair
     * @param immediateValue
     */
    void LD(RegisterPair registerPair, std::uint8_t immediateValue);

    void LD(MemoryAddress memoryAddress, Rgstr a);

    void LD(Rgstr a, MemoryAddress memoryAddress);

    void LD(MemoryAddress memoryAddress, RegisterPair hl);

    void LD(RegisterPair hl, MemoryAddress memoryAddress);

    void LD(MemoryAddress memoryAddress, std::uint8_t i);

    void LDD();

    void LDDR();

    void LDI();

    void LDIR();

    void NEG();

    /**
     * NOP - 0
     */
    void NOP();

    void OR(Rgstr iX2);

    /**
     * OR n - f6 n
     * @param immediateValue
     */
    void OR(std::uint8_t immediateValue);

    void OR(MemoryAddress memoryAddress);

    void OTDR();

    void OTIR();

    void out(MemoryAddress address, Rgstr register);

    void OUTD();

    void OUTI();

    void POP(RegisterPair iy);

    void PUSH(RegisterPair valueRegister);

    void RES(std::uint8_t i, Rgstr b);

    void RES(std::uint8_t i, MemoryAddress memoryAddress);

    void RET(Condition p);

    void RET();

    void RETI();

    void RETN();

    void RL(Rgstr r);

    void RL(MemoryAddress memoryAddress);

    void RLA();

    void RLC(Rgstr register);

    void RLC(MemoryAddress memoryAddress);

    void RLCA();

    void RLD();

    void RR(Rgstr r);

    void RR(MemoryAddress memoryAddress);

    void RRA();

    void RRC(Rgstr r);

    void RRC(MemoryAddress memoryAddress);

    void RRCA();

    void RRD();

    void RST(std::uint8_t i);

    void SBC(Rgstr a, std::uint8_t nextByte);

    void SBC(Rgstr a, Rgstr b);

    void SBC(RegisterPair hl, RegisterPair hl1);

    void SBC(Rgstr a, MemoryAddress memoryAddress);

    void SCF();

    void SET(std::uint8_t y, Rgstr register);

    void SET(std::uint8_t i, MemoryAddress memoryAddress);

    void SLA(Rgstr r);

    void SLA(MemoryAddress memoryAddress);

    void SRA(Rgstr r);

    void SRA(MemoryAddress memoryAddress);

    void SRL(Rgstr r);
    void SRL(MemoryAddress memoryAddress);

    void SUB(Rgstr iX2);
    void SUB(std::uint8_t iX2);
    void SUB(MemoryAddress memoryAddress);

    void XOR(Rgstr val);
    void XOR(std::uint8_t val);
    void XOR(MemoryAddress memoryAddress);

//    std::uint8_t fetchInstruction();

//    Memory *getMemory();

//      void setMemory(int[] memory);

//    void setMemory(Memory *memory);

    std::uint16_t getRegisterPairValue(RegisterPair register);

    std::uint8_t getRegisterValue(Rgstr register);

//    void placeProgramCounterOnAddressBus();


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

private:
    IO *getIo();

    void setIo(IO* io);

    bool getNFlag();

    void setNFlag(bool flag);

    bool getParityOverflowFlag();

    void setParityOverflowFlag(bool flag);

    std::uint8_t getR();

    void setR(std::uint8_t r);

//     std::uint8_t getRegisterPairValue(RegisterPair register);
//     std::uint8_t getRegisterValue(Rgstr register);
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



    void pushPCtoStack();

    std::uint8_t readIO(std::uint16_t address);

    void reset();

    void setFlags(std::uint8_t value);

    void setRegister(Rgstr register, std::uint8_t value);

    void setRegisterPair(RegisterPair register, std::uint16_t sixteenBit);

    void setRegisterPair(RegisterPair register, std::uint8_t lowOrder, std::uint8_t highOrder);

    void unimplemented();

    void writeIO(std::uint16_t address, std::uint8_t value);

    std::uint16_t getMemoryAddress(MemoryAddress memoryAddress);

    void decrementSP();

    void doOneScreenRefreshesWorth();
};
#endif // EMULATIONPROCESSOR_H
