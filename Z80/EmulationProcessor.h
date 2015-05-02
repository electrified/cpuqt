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

#include "Z80/BaseProcessor.h"
#include "Z80/InstructionDecoder.h"
#include "Z80/IO.h"
#include "Logger.h"
class EmulationProcessor : public BaseProcessor {
    /*
         * in java all numbers are internally represented as 32 bit. There is also
         * no unsigned therefore just using ints
         */
    int A, B, C, D, E, F, H, L, SP;
    int IX, IY, I, R;
    int A_alt, B_alt, C_alt, D_alt, E_alt, F_alt, H_alt, L_alt;
    IO *io;
    //interrupt enable flip flops
    bool IFF1 = false;
    bool IFF2 = false;
    bool halted = false;
    //interrupt mode
    int _IM;
    Logger logger;
public:
    EmulationProcessor();

    EmulationProcessor(InstructionDecoder *instructionDecoder);

    EmulationProcessor(EmulationProcessor *emulationProcessor);

    void ADC(RegisterPair hl, RegisterPair bc);

    void ADC(Register a, Register b);

    void ADC(Register a, int i);

    void ADC(Register a, MemoryAddress memoryAddress);

    void ADD(RegisterPair destination, RegisterPair register);

    void ADD(Register a, int nextByte);

    void ADD(Register a, Register b);

    void ADD(Register a, MemoryAddress memoryAddress);

    void AND(Register iX2);

    void AND(int iX2);

    void AND(MemoryAddress memoryAddress);

    void BIT(int y, Register register);

    void BIT(int i, MemoryAddress memoryAddress);

    void BIT(int y, int value);

    void CALL(Condition c, MemoryAddress memoryAddress);

    void CALL(MemoryAddress memoryAddress);

    void CCF();

    void CP(int val);

    void CP(Register val);

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
    void DEC(Register r);

    void DEC(RegisterPair r);

    void DEC(MemoryAddress memoryAddress);

    void DI();

    void DJNZ(MemoryAddress memoryAddress);

    void EI();

    void EX(RegisterPair de, RegisterPair hl);

    void EX(MemoryAddress memoryAddress, RegisterPair ix);

    void EXX();

    void HALT();

    void IM(int im);

    void IN(Register a, MemoryAddress i);

    void INC(Register r);

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

    void LD(Register register, int memoryAddress);

    void LD(Register r1, Register r2);

    void LD(RegisterPair r1, RegisterPair r2);

    /**
     * LD SP,nn - 31 n n
     * @param registerPair
     * @param immediateValue
     */
    void LD(RegisterPair registerPair, int immediateValue);

    void LD(MemoryAddress memoryAddress, Register a);

    void LD(Register a, MemoryAddress memoryAddress);

    void LD(MemoryAddress memoryAddress, RegisterPair hl);

    void LD(RegisterPair hl, MemoryAddress memoryAddress);

    void LD(MemoryAddress memoryAddress, int i);

    void LDD();

    void LDDR();

    void LDI();

    void LDIR();

    void NEG();

    /**
     * NOP - 0
     */
    void NOP();

    void OR(Register iX2);

    /**
     * OR n - f6 n
     * @param immediateValue
     */
    void OR(int immediateValue);

    void OR(MemoryAddress memoryAddress);

    void OTDR();

    void OTIR();

    void OUT(MemoryAddress address, Register register);

    void OUTD();

    void OUTI();

    void POP(RegisterPair iy);

    void PUSH(RegisterPair valueRegister);

    void RES(int i, Register b);

    void RES(int i, MemoryAddress memoryAddress);

    void RET(Condition p);

    void RET();

    void RETI();

    void RETN();

    void RL(Register r);

    void RL(MemoryAddress memoryAddress);

    void RLA();

    void RLC(Register register);

    void RLC(MemoryAddress memoryAddress);

    void RLCA();

    void RLD();

    void RR(Register r);

    void RR(MemoryAddress memoryAddress);

    void RRA();

    void RRC(Register r);

    void RRC(MemoryAddress memoryAddress);

    void RRCA();

    void RRD();

    void RST(int i);

    void SBC(Register a, int nextByte);

    void SBC(Register a, Register b);

    void SBC(RegisterPair hl, RegisterPair hl1);

    void SBC(Register a, MemoryAddress memoryAddress);

    void SCF();

    void SET(int y, Register register);

    void SET(int i, MemoryAddress memoryAddress);

    void SLA(Register r);

    void SLA(MemoryAddress memoryAddress);

    void SRA(Register r);

    void SRA(MemoryAddress memoryAddress);

    void SRL(Register r);
    void SRL(MemoryAddress memoryAddress);

    void SUB(Register iX2);
    void SUB(int iX2);
    void SUB(MemoryAddress memoryAddress);

    void XOR(Register val);
    void XOR(int val);
    void XOR(MemoryAddress memoryAddress);

//    std::uint8_t fetchInstruction();

//    Memory *getMemory();

//      void setMemory(int[] memory);

//    void setMemory(Memory *memory);

    int getRegisterPairValue(RegisterPair register);

    int getRegisterValue(Register register);

//    void placeProgramCounterOnAddressBus();

private:
//     void setRegisterPair(RegisterPair register, int lowOrder, int highOrder);
//     void setRegisterPair(RegisterPair register, int sixteenBit);
//     int getMemoryAddress(MemoryAddress memoryAddress);
//     void writeIO(int address, int value);
//     void unimplemented();
    int getA();

    void setA(int a);

    int getAF();

    void setAF(int value);

    int getAF_alt();

    void setAF_alt(int value);

    int getA_alt();

    void setA_alt(int a_alt);

    int getB();

    void setB(int b);

    int getBC();

    void setBC(int value);

    int getBC_alt();

    void setBC_alt(int value);

    int getB_alt();

    void setB_alt(int b_alt);

    int getC();

    void setC(int c);

    bool getCFlag();

    void setCFlag(bool flag);

    int getC_alt();

    void setC_alt(int c_alt);

    int getD();

    void setD(int d);

    int getDE();

    void setDE(int value);

    int getDE_alt();

    void setDE_alt(int value);

    int getD_alt();

    void setD_alt(int d_alt);

    int getE();

    void setE(int e);

    int getE_alt();

    void setE_alt(int e_alt);

    int getF();

    void setF(int f);

    int getF_alt();

    void setF_alt(int f_alt);

    int getH();

    void setH(int h);

    bool getHFlag();

    void setHFlag(bool flag);

    int getHL();

    void setHL(int value);

    int getHL_alt();

    void setHL_alt(int value);

    int getH_alt();

    void setH_alt(int h_alt);

    int getI();

    void setI(int i);

    int getIX();

    void setIX(int iX);

    int getIXH();

    int getIXL();

    int getIY();

    void setIY(int iY);

    int getIYH();

    int getIYL();

    IO *getIo();

    void setIo(IO* io);

    int getL();

    void setL(int l);

    int getL_alt();

    void setL_alt(int l_alt);

    bool getNFlag();

    void setNFlag(bool flag);

    bool getParityOverflowFlag();

    void setParityOverflowFlag(bool flag);

    int getR();

    void setR(int r);

//     int getRegisterPairValue(RegisterPair register);
//     int getRegisterValue(Register register);
    int getSP();

    void setSP(int sP);

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

    void process();

    void process(int count);

    void pushPCtoStack();

    int readIO(int address);

    void reset();

    void setFlags(int value);

//     void setMemory(Memory* memory);
    void setRegister(Register register, int value);

    void setRegisterPair(RegisterPair register, int sixteenBit);

    void setRegisterPair(RegisterPair register, int lowOrder, int highOrder);

    void unimplemented();

    void writeIO(int address, int value);

    std::uint16_t getMemoryAddress(MemoryAddress memoryAddress);

    void decrementSP();

    void doOneScreenRefreshesWorth();
};
#endif // EMULATIONPROCESSOR_H
