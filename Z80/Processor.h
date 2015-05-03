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
    virtual void ADC(Rgstr a, Rgstr b) = 0;
    virtual void ADC(Rgstr a, std::uint8_t i) = 0;
    virtual void ADC(Rgstr a, MemoryAddress memoryAddress) = 0;

    virtual void ADD(RegisterPair destination, RegisterPair register) = 0;
    virtual void ADD(Rgstr a, std::uint8_t nextByte) = 0;
    virtual void ADD(Rgstr a, Rgstr b) = 0;
    virtual void ADD(Rgstr a, MemoryAddress memoryAddress) = 0;

    virtual void AND(Rgstr iX2) = 0;
    virtual void AND(std::uint8_t iX2) = 0;
    virtual void AND(MemoryAddress memoryAddress) = 0;

    virtual void BIT(std::uint8_t y, Rgstr register) = 0;
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

    /**
     * DEC B - 5
     * @param r
     */
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

    virtual void LD(Rgstr register, std::uint8_t memoryAddress) = 0;
    virtual void LD(Rgstr r1, Rgstr r2) = 0;
    virtual void LD(RegisterPair r1, RegisterPair r2) = 0;

    /**
     * LD SP,nn - 31 n n
     * @param registerPair
     * @param immediateValue
     */
    virtual void LD(RegisterPair registerPair, std::uint8_t immediateValue) = 0;
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

    virtual void out(MemoryAddress address, Rgstr register) = 0;

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

    virtual void RLC(Rgstr register) = 0;
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

    virtual void SET(std::uint8_t y, Rgstr register) = 0;

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

    virtual std::uint8_t fetchInstruction() = 0;

    virtual Memory* getMemory() = 0;

//     virtual void setMemory(int[] memory) = 0;

    virtual void setMemory(Memory* memory) = 0;

    virtual std::uint16_t getRegisterPairValue(RegisterPair register) = 0;

    virtual std::uint8_t getRegisterValue(Rgstr register) = 0;

    virtual void placeProgramCounterOnAddressBus() = 0;
};

#endif // PROCESSOR_H
