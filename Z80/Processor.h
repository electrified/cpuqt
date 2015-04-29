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
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES = 0;
 * LOSS OF USE, DATA, OR PROFITS = 0; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>

#include "Z80/RegisterPair.hpp"
#include "Z80/Register.hpp"
#include "Z80/Condition.hpp"
#include "Z80/MemoryAddress.h"
#include "Z80/Memory.h"

class Processor
{
public:
    virtual void ADC(RegisterPair hl, RegisterPair bc) = 0;

    virtual void ADC(Register a, Register b) = 0;

    virtual void ADC(Register a, int i) = 0;

    virtual void ADC(Register a, MemoryAddress memoryAddress) = 0;

    virtual void ADD(RegisterPair destination, RegisterPair register) = 0;

    virtual void ADD(Register a, int nextByte) = 0;

    virtual void ADD(Register a, Register b) = 0;

    virtual void ADD(Register a, MemoryAddress memoryAddress) = 0;

    virtual void AND(Register iX2) = 0;

    virtual void AND(int iX2) = 0;

    virtual void AND(MemoryAddress memoryAddress) = 0;

    virtual void BIT(int y, Register register) = 0;

    virtual void BIT(int i, MemoryAddress memoryAddress) = 0;

    virtual void CALL(Condition c, MemoryAddress memoryAddress) = 0;

    virtual void CALL(MemoryAddress memoryAddress) = 0;

    virtual void CCF() = 0;

    virtual void CP(int val) = 0;

    virtual void CP(Register val) = 0;

    virtual void CP(MemoryAddress memoryAddress) = 0;

    virtual void CPD() = 0;

    virtual void CPDR() = 0;

    virtual void CPI() = 0;

    virtual void CPIR() = 0;

    virtual void CPL() = 0;

    virtual void DAA() = 0;

    /**
     * DEC B - 5
     * @param r
     */
    virtual void DEC(Register r) = 0;

    virtual void DEC(RegisterPair r) = 0;

    virtual void DEC(MemoryAddress memoryAddress) = 0;

    virtual void DI() = 0;

    virtual void DJNZ(MemoryAddress memoryAddress) = 0;

    virtual void EI() = 0;

    virtual void EX(RegisterPair de, RegisterPair hl) = 0;

    virtual void EX(MemoryAddress memoryAddress, RegisterPair ix) = 0;

    virtual void EXX() = 0;

    virtual void HALT() = 0;

    virtual void IM(int im) = 0;

    virtual void IN(Register a, MemoryAddress i) = 0;

    virtual void INC(Register r) = 0;

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

    virtual void LD(Register register, int memoryAddress) = 0;

    virtual void LD(Register r1, Register r2) = 0;

    virtual void LD(RegisterPair r1, RegisterPair r2) = 0;

    /**
     * LD SP,nn - 31 n n
     * @param registerPair
     * @param immediateValue
     */
    virtual void LD(RegisterPair registerPair, int immediateValue) = 0;

    virtual void LD(MemoryAddress memoryAddress, Register a) = 0;

    virtual void LD(Register a, MemoryAddress memoryAddress) = 0;

    virtual void LD(MemoryAddress memoryAddress, RegisterPair hl) = 0;

    virtual void LD(RegisterPair hl, MemoryAddress memoryAddress) = 0;

    virtual void LD(MemoryAddress memoryAddress, int i) = 0;

    virtual void LDD() = 0;

    virtual void LDDR() = 0;

    virtual void LDI() = 0;

    virtual void LDIR() = 0;

    virtual void NEG() = 0;

    /**
     * NOP - 0
     */
    virtual void NOP() = 0;

    virtual void OR(Register iX2) = 0;

    /**
     * OR n - f6 n
     * @param immediateValue
     */
    virtual void OR(int immediateValue) = 0;

    virtual void OR(MemoryAddress memoryAddress) = 0;

    virtual void OTDR() = 0;

    virtual void OTIR() = 0;

    /**
     * OUT (n),A - d3 3e8
     * @param address
     * @param register
     */
    virtual void OUT(MemoryAddress address, Register register) = 0;

    virtual void OUTD() = 0;

    virtual void OUTI() = 0;

    virtual void POP(RegisterPair iy) = 0;

    virtual void PUSH(RegisterPair valueRegister) = 0;

    virtual void RES(int i, Register b) = 0;

    virtual void RES(int i, MemoryAddress memoryAddress) = 0;

    virtual void RET(Condition p) = 0;

    virtual void RET() = 0;

    virtual void RETI() = 0;

    virtual void RETN() = 0;

    virtual void RL(Register r) = 0;

    virtual void RL(MemoryAddress memoryAddress) = 0;

    virtual void RLA() = 0;

    virtual void RLC(Register register) = 0;

    virtual void RLC(MemoryAddress memoryAddress) = 0;

    virtual void RLCA() = 0;

    virtual void RLD() = 0;

    virtual void RR(Register r) = 0;

    virtual void RR(MemoryAddress memoryAddress) = 0;

    virtual void RRA() = 0;

    virtual void RRC(Register r) = 0;

    virtual void RRC(MemoryAddress memoryAddress) = 0;

    virtual void RRCA() = 0;

    virtual void RRD() = 0;

    virtual void RST(int i) = 0;

    virtual void SBC(Register a, int nextByte) = 0;

    virtual void SBC(Register a, Register b) = 0;

    virtual void SBC(RegisterPair hl, RegisterPair hl1) = 0;

    virtual void SBC(Register a, MemoryAddress memoryAddress) = 0;

    virtual void SCF() = 0;

    virtual void SET(int y, Register register) = 0;

    virtual void SET(int i, MemoryAddress memoryAddress) = 0;

    virtual void SLA(Register r) = 0;

    virtual void SLA(MemoryAddress memoryAddress) = 0;

    virtual void SRA(Register r) = 0;

    virtual void SRA(MemoryAddress memoryAddress) = 0;

    virtual void SRL(Register r) = 0;

    virtual void SRL(MemoryAddress memoryAddress) = 0;

    virtual void SUB(Register iX2) = 0;

    virtual void SUB(int iX2) = 0;

    virtual void SUB(MemoryAddress memoryAddress) = 0;

    virtual void XOR(Register val) = 0;

    virtual void XOR(int val) = 0;

    virtual void XOR(MemoryAddress memoryAddress) = 0;

    virtual int fetchInstruction() = 0;

    virtual Memory getMemory() = 0;

//     virtual void setMemory(int[] memory) = 0;

    virtual void setMemory(Memory* memory) = 0;

    virtual int getRegisterPairValue(RegisterPair register) = 0;

    virtual int getRegisterValue(Register register) = 0;

    virtual void placeProgramCounterOnAddressBus() = 0;
};

#endif // PROCESSOR_H
