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

#include "EmulationProcessor.h"

#include "Z80/Processor.h"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"
#include "Z80/Condition.hpp"
#include "Z80/Memory.h"
#include "Z80/MemoryAddress.h"
#include "Z80/IO.h"
#include "Z80/TestIO.h"
#include "Z80/InstructionDecoder.h"
#include "Z80/InstructionDecoderGenerated.h"

    /*
     * in java all numbers are internally represented as 32 bit. There is also
     * no unsigned therefore just using ints
     */
    int A, B, C, D, E, F, H, L, SP;
    int IX, IY, I, R;
    int A_alt, B_alt, C_alt, D_alt, E_alt, F_alt, H_alt, L_alt;
    IO* io;
    //interrupt enable flip flops
    bool IFF1 = false;
    bool IFF2 = false;
    bool halted = false;
    //interrupt mode
    int IM = 0;

     EmulationProcessor::EmulationProcessor() {
        this(new InstructionDecoderGenerated());
    }

     EmulationProcessor::EmulationProcessor(InstructionDecoder* instructionDecoder) {
        this->instructionDecoder = instructionDecoder;
        io = new TestIO();
        instructionDecoder->setProcessor(this);
    }

     EmulationProcessor::EmulationProcessor(EmulationProcessor* processor) {
        this.A = processor->getA();
        this.B = processor->getB();
        this.C = processor->getC();
        this.D = processor->getD();
        this.E = processor->getE();
        this.F = processor->getF();
        this.H = processor->getH();
        this.L = processor->getL();
        this.PC = processor->getPC();
        this.IFF1 = processor->isIFF1();
        this.IFF2 = processor->isIFF2();
        this.setMemory(processor->getMemory()->clone());
        this.SP = processor->getSP();
    }

    
     void EmulationProcessor::EmulationProcessor::ADC(RegisterPair hl, RegisterPair bc) {
        unimplemented();
    }

    
     void EmulationProcessor::EmulationProcessor::ADC(Register a, Register b) {
        setRegister(a, this.getRegisterValue(a) + this.getRegisterValue(b) + (getCFlag() ? 1 : 0));
    }

    
     void EmulationProcessor::EmulationProcessor::ADC(Register register, int val) {
        setRegister(register, this.getRegisterValue(register) + val + (getCFlag() ? 1 : 0));
    }

    
     void EmulationProcessor::ADC(Register register, MemoryAddress memoryAddress) {
        setRegister(register, this.getRegisterValue(register) + getMemory().read(getMemoryAddress(memoryAddress)) + (getCFlag() ? 1 : 0));
    }

//    
//     void ADC(RegisterPair rp2) {
//        setHL(getHL() + getRegisterPairValue(rp2) + (getCFlag() ? 1 : 0));
//    }

    /**
     * @param val
     */
//    
//     void ADCA(Register val) {
//        ADCA(getRegisterValue(val));
//    }
//
//    
//     void ADCA(int val) {
//        this.setA(this.getA() + val + (getCFlag() ? 1 : 0));
//    }

    /**
     * The contents of register pair ss (any of register
     * pairs BC, DE, HL, or SP) are added to the contents of
     * register pair HL and the result is stored in HL.
     * Operand ss is specified as follows in the assembled
     * object code.
     */
    
     void EmulationProcessor::ADD(RegisterPair destination, RegisterPair register) {
        setRegisterPair(destination, getRegisterPairValue(destination) + getRegisterPairValue(register));
    }

    
     void EmulationProcessor::ADD(Register destination, int nextByte) {
        setRegister(destination, getRegisterValue(destination) + nextByte);
    }

    
     void EmulationProcessor::ADD(Register destination, Register source) {
        setRegister(destination, getRegisterValue(destination) + getRegisterValue(source));
    }

    
     void EmulationProcessor::ADD(Register destination, MemoryAddress memoryAddress) {
        setRegister(destination, getRegisterValue(destination) + getMemory().read(getMemoryAddress(memoryAddress)));
    }

    
     void EmulationProcessor::AND(Register iX2) {
        AND(getRegisterValue(iX2));
    }

    
     void EmulationProcessor::AND(int value) {
        setA(getA() & value);
    }

    
     void EmulationProcessor::AND(MemoryAddress memoryAddress) {
        setA(getA() & getMemory().read(getMemoryAddress(memoryAddress)));
    }

    /**
     * This instruction tests bit b in register r and sets the Z flag
     * accordingly.
     *
     * @param y
     * @param value
     */
//    
     void EmulationProcessor::BIT(int y, int value) {
        setZeroFlag(!((value & (1 << y)) == (1 << y)));
    }

    
     void EmulationProcessor::BIT(int y, Register register) {
        int registerValue = getRegisterValue(register);
        BIT(y, registerValue);
    }

    
     void EmulationProcessor::BIT(int i, MemoryAddress memoryAddress) {
        int value = getMemory().read(getMemoryAddress(memoryAddress));
        BIT(i, value);
    }

//    
//     void BIT(int y, int displacement, RegisterPair register) {
//        int value = getMemory().read(getRegisterPairValue(register) + displacement);
//        BIT(y, value);
//    }

	/*-
     * 765432  10
	 * SZXNXP/VNC
	 * 
	 * Symbol Field Name
	 * C Carry Flag
	 * N Add/Subtract
	 * P/V Parity/Overflow Flag
	 * H Half Carry Flag
	 * Z Zero Flag
	 * S Sign Flag
	 * X Not Used
	 * 
	 */

    /*
    If condition cc is true, this instruction pushes the current contents of the
Program Counter (PC) onto the top of the external memory stack, then
loads the operands nn to PC to point to the address in memory where the
first Op Code of a subroutine is to be fetched. At the end of the subroutine,
a RETurn instruction can be used to return to the original program flow by
popping the top of the stack back to PC. If condition cc is false, the
Program Counter is incremented as usual, and the program continues with
the next sequential instruction. The stack push is accomplished by first
decrementing the current contents of the Stack Pointer (SP), loading the
high-order byte of the PC contents to the memory address now pointed to
by SP; then decrementing SP again, and loading the low order byte of the
PC contents to the top of the stack.
Because this is a 3-byte instruction, the Program Counter was incremented
by three before the push is executed.
Condition cc is programmed as one of eight status that corresponds to
condition bits in the Flag Register (register F).
     */
//    
//     void CALL(Condition cc, int i) {
//        if (isConditionTrue(cc)) {
//            CALL(i);
//        }
//    }

    /**
     * The current contents of the Program Counter (PC) are pushed onto the top
     * of the external memory stack. The operands nn are then loaded to the PC to
     * point to the address in memory where the first Op Code of a subroutine is to
     * be fetched. At the end of the subroutine, a RETurn instruction can be used
     * to return to the original program flow by popping the top of the stack back
     * to the PC. The push is accomplished by first decrementing the current
     * contents of the Stack Pointer (register pair SP), loading the high-order byte
     * of the PC contents to the memory address now pointed to by the SP; then
     * decrementing SP again, and loading the low order byte of the PC contents
     * to the top of stack.
     * Because this is a 3-byte instruction, the Program Counter was incremented
     * by three before the push is executed.
     */
    
     void EmulationProcessor::CALL(Condition c, MemoryAddress memoryAddress) {
        if (isConditionTrue(c)) {
            pushPCtoStack();
            setPC(getMemoryAddress(memoryAddress));
        }
    }

    
     void EmulationProcessor::CALL(MemoryAddress memoryAddress) {
        pushPCtoStack();
        setPC(getMemoryAddress(memoryAddress));
    }

    /**
     *
     */
    
     void EmulationProcessor::CCF() {
        /* The Carry flag in the F register is inverted. */
        setHFlag(getCFlag());

        setCFlag(!getCFlag());

        setNFlag(false);
    }

    /**
     * @param val
     */
    
     void EmulationProcessor::CP(int val) {
        int result = this.getA() - val;

        this.setZeroFlag(result == 0);
        this.setSignFlag(result < 0);
        // this.setHFlag(flag);
        // this.setParityOverflowFlag(flag);
        this.setNFlag(true);
    }

    
     void EmulationProcessor::CP(Register val) {
        CP(getRegisterValue(val));
    }

    
     void EmulationProcessor::CP(MemoryAddress memoryAddress) {
        CP(getMemory().read(getMemoryAddress(memoryAddress)));
    }

    
     void EmulationProcessor::CPD() {
        unimplemented();
    }

    
     void EmulationProcessor::CPDR() {
        unimplemented();
    }

    
     void EmulationProcessor::CPI() {
        unimplemented();
    }

    
     void EmulationProcessor::CPIR() {
        unimplemented();
    }

    /**
     * The contents of the Accumulator (register A) are inverted (one’s
     * complement).
     */
    
     void EmulationProcessor::CPL() {

        setA(getA() ^ 0b11111111);
        setNFlag(true);
        setHFlag(true);
    }

    
     void EmulationProcessor::DAA() {
        unimplemented();
    }

    /**
     * - S is set if result is negative; reset otherwise Z is set if result is
     * zero; reset otherwise H is set if borrow from bit 4, reset otherwise P/V
     * is set if m was 80H before operation; reset otherwise N is set C is not
     * affected
     */
    
     void EmulationProcessor::DEC(MemoryAddress memoryAddress) {
        int address = getMemoryAddress(memoryAddress);
        int newvalue = getMemory().read(address) - 1;

        getMemory().write(address, newvalue);

        if (newvalue < 0) {
            setSignFlag(true);
        } else if (newvalue == 0) {
            setZeroFlag(true);
        }
        // H ??

        setNFlag(false);
    }

    
     void EmulationProcessor::DEC(Register register) {
        setRegister(register, getRegisterValue(register) - 1);

        if (getRegisterValue(register) < 0) {
            setSignFlag(true);
        } else if (getRegisterValue(register) == 0) {
            setZeroFlag(true);
        }
        // H ??

        setNFlag(false);
    }

    /**
     * The contents of register pair ss (any of the register
     * pairs BC, DE, HL, or SP) are decremented. Operand ss
     * is specified as follows in the assembled object code.
     */
    
     void EmulationProcessor::DEC(RegisterPair registerPair) {
        setRegisterPair(registerPair,
                getRegisterPairValue(registerPair) - 1);
    }

    /**
     *
     */
    
     void EmulationProcessor::DI() {
        setIFF1(false);
        setIFF2(false);
    }


    /**
     * This instruction is similar to the conditional jump instructions except
     * that a register value is used to determine branching. The B register is
     * decremented, and if a non zero value remains, the value of the
     * displacement e is added to the Program Counter (PC).
     * <p/>
     * The next instruction is fetched from the location designated by the new
     * contents of the PC. The jump is measured from the address of the
     * instruction Op Code and has a range of -126 to +129 bytes. The assembler
     * automatically adjusts for the twice incremented PC. If the result of
     * decrementing leaves B with a zero value, the next instruction executed is
     * taken from the location following this instruction
     */
//    
//     void DJNZ(int jump) {
//        setB(getB() - 1);
//
//        if (getB() > 0) {
//            logger.debug("B register > 0");
//            setPC(getPC() + jump);
//        }
//    }
    
     void EmulationProcessor::DJNZ(MemoryAddress memoryAddress) {
        setB(getB() - 1);

        if (getB() > 0) {
            logger.debug("B register > 0");
            setPC(getMemoryAddress(memoryAddress));
        }
    }

    /**
     * The enable interrupt instruction sets both interrupt enable flip flops
     * (IFFI and IFF2) to a logic 1, allowing recognition of any maskable
     * interrupt. Note that during the execution of this instruction and the
     * following instruction, maskable interrupts are disabled.
     */
    
     void EmulationProcessor::EI() {

        setIFF1(true);
        setIFF2(true);
    }

    
     void EmulationProcessor::EX(MemoryAddress memoryAddress, RegisterPair register) {
        int loMemVal = getMemory().read(getMemoryAddress(memoryAddress));
        int hiMemVal = getMemory().read(getMemoryAddress(memoryAddress) + 1);

        switch (register) {
            case HL:
                this.getMemory().write(getSP(), getL());
                this.getMemory().write(getSP() + 1, getH());
                setL(loMemVal);
                setH(hiMemVal);
                break;
            case IX:
                this.getMemory().write(getSP(), getIXL());
                this.getMemory().write(getSP() + 1, getIXH());
                setIX((hiMemVal << 8) | loMemVal);
                break;
            case IY:
                this.getMemory().write(getSP(), getIYL());
                this.getMemory().write(getSP() + 1, getIYH());
                setIY((hiMemVal << 8) | loMemVal);
                break;
        }

    }

    /**
     * The 2-byte contents of the register pairs AF and AF' are exchanged.
     * Register pair AF consists of registers A' and F'
     */
    
     void EmulationProcessor::EX(RegisterPair a, RegisterPair b) {
        int aval = getRegisterPairValue(a);
        setRegisterPair(a, getRegisterPairValue(b));
        setRegisterPair(b, aval);
    }

    /**
     * Each 2-byte value in register pairs BC, DE, and HL is exchanged with the
     * 2-byte value in BC', DE', and HL', respectively.
     */
    
     void EmulationProcessor::EXX() {

        int temp = getBC();
        setBC(getBC_alt());
        setBC_alt(temp);

        temp = getDE();
        setDE(getDE_alt());
        setDE_alt(temp);

        temp = getHL();
        setHL(getHL_alt());
        setHL_alt(temp);
    }

    
     void EmulationProcessor::HALT() {
        halted = true;
    }

    
     void EmulationProcessor::IM(int im) {
        this.IM = im;
    }


    /**
     * The contents of register C are placed on the bottom half (A0 through A7) of
     * the address bus to select the I/O device at one of 256 possible ports. The
     * contents of Register B are placed on the top half (A8 through A15) of the
     * address bus at this time. Then one byte from the selected port is placed on
     * the data bus and written to register r in the CPU. Register r identifies any of
     * the CPU registers shown in the following table, which also indicates the
     * corresponding 3-bit r field for each. The flags are affected, checking the
     * input data.
     *
     * @param register
     * @param i
     */
    
     void EmulationProcessor::IN(Register register, MemoryAddress i) {
        //(getB() << 8) |
        setRegister(register, getIo().read(getMemoryAddress(i)));
    }


    /**
     * The operand n is placed on the bottom half (A0 through A7) of the address
     * bus to select the I/O device at one of 256 possible ports. The contents
     * of the Accumulator also appear on the top half (A8 through A15) of the
     * address bus at this time. Then one byte from the selected port is placed
     * on the data bus and written to the Accumulator (register A) in the CPU
     */


    /**
     * - Register r is incremented and register r identifies any of the
     * registers A, B, C, D, E, H, or L, assembled as follows in the object
     * code.
     * <p/>
     * S is set if result is negative; reset otherwise Z is set if result is
     * zero; reset otherwise H is set if carry from bit 3; reset otherwise P/V
     * is set if r was 7FH before operation; reset otherwise N is reset C is not
     * affected
     */
    
     void EmulationProcessor::INC(MemoryAddress memoryAddress) {
        if (getMemory().read(getMemoryAddress(memoryAddress)) == 0x7F) {
            setParityOverflowFlag(true);
        }

        int newValue = (getMemory().read(getMemoryAddress(memoryAddress)) + 1) & 0xff;
        getMemory().write(getMemoryAddress(memoryAddress), newValue);

        if (newValue < 0) {
            setSignFlag(true);
        } else if (newValue == 0) {
            setZeroFlag(true);
        }
        // H ??

        setNFlag(false);
    }

    
     void EmulationProcessor::INC(Register reg) {

        if (getRegisterValue(reg) == 0x7F) {
            setParityOverflowFlag(true);
        }

        setRegister(reg, ((getRegisterValue(reg) + 1) & 0xff));

        if (getRegisterValue(reg) < 0) {
            setSignFlag(true);
        } else if (getRegisterValue(reg) == 0) {
            setZeroFlag(true);
        }
        // H ??

        setNFlag(false);
    }

    /**
     * The contents of register pair ss (any of register
     * pairs BC, DE, HL, or SP) are incremented. Operand ss
     * is specified as follows in the assembled object code.
     */
    
     void EmulationProcessor::INC(RegisterPair registerPair) {
        setRegisterPair(registerPair,
                getRegisterPairValue(registerPair) + 1);
    }

    
     void EmulationProcessor::IND() {
        unimplemented();
    }

    
     void EmulationProcessor::INDR() {
        unimplemented();
    }

    
     void EmulationProcessor::INI() {
        unimplemented();
    }

    
     void EmulationProcessor::INIR() {
        unimplemented();
    }

    /**
     * Operand nn is loaded to register pair PC (Program Counter). The next
     * instruction is fetched from the location designated by the new contents
     * of the PC.
     */
    
     void EmulationProcessor::JP(MemoryAddress memoryAddress) {
        setPC(getMemoryAddress(memoryAddress));
    }

    
     void EmulationProcessor::JP(Condition condition, MemoryAddress memoryAddress) {
        if (isConditionTrue(condition)) {
            JP(memoryAddress);
        }
    }

    /**
     * This instruction provides for unconditional branching to other segments
     * of a program. The value of the displacement e is added to the Program
     * Counter (PC) and the next instruction is fetched from the location
     * designated by the new contents of the PC. This jump is measured from the
     * address of the instruction Op Code and has a range of-126 to +129 bytes.
     * The assembler automatically adjusts for the twice incremented PC.
     */
    
     void EmulationProcessor::JR(Condition condition, MemoryAddress memoryAddress) {
        if (isConditionTrue(condition)) {
            JR(memoryAddress);
        }
    }

    
     void EmulationProcessor::JR(MemoryAddress memoryAddress) {
        setPC(getMemoryAddress(memoryAddress));
    }

    /**
     * The contents of memory address (nn) are loaded to the low order
     * portion of register pair HL (register L), and the contents of the
     * next highest memory address (nn +1) are loaded to the high order
     * portion of HL (register H). The first n operand after the Op Code is
     * the low order byte of nn .
     */

    
     void EmulationProcessor::LD(RegisterPair r1, RegisterPair r2) {
        setRegisterPair(r1, getRegisterPairValue(r2));
    }

    
     void EmulationProcessor::LD(RegisterPair registerPair, int immediateValue) {
        setRegisterPair(registerPair, immediateValue);
    }

    
     void EmulationProcessor::LD(MemoryAddress memoryAddress, Register register) {
        getMemory().write(getMemoryAddress(memoryAddress), getRegisterValue(register));
    }

    
     void EmulationProcessor::LD(Register a, MemoryAddress memoryAddress) {
        int value = getMemory().read(getMemoryAddress(memoryAddress));
        setRegister(a, value);
        setFlags(value);
    }

    
     void EmulationProcessor::LD(MemoryAddress memoryAddress, RegisterPair register) {
        getMemory().write(getMemoryAddress(memoryAddress), getRegisterPairValue(register) & 0xff);
        getMemory().write(getMemoryAddress(memoryAddress) + 1, getRegisterPairValue(register) >> 8);
    }

    
     void EmulationProcessor::LD(RegisterPair registerPair, MemoryAddress memoryAddress) {
            int value = getMemory().read(getMemoryAddress(memoryAddress)) | (getMemory().read(getMemoryAddress(memoryAddress) + 1) << 8);
        setRegisterPair(registerPair, value);
        setFlags(value);
    }

    
     void EmulationProcessor::LD(MemoryAddress memoryAddress, int i) {
        getMemory().write(getMemoryAddress(memoryAddress), i);
        setFlags(i);
    }

    /**
     * The 8-bit integer n is loaded to any register r, where r
     * identifies register A, B, C, D, E, H, or L,
     */
    
     void EmulationProcessor::LD(Register register, int immediateValue) {
        setRegister(register, immediateValue);
    }

    
     void EmulationProcessor::LD(Register destRegister, Register sourceRegister) {
        int value = getRegisterValue(sourceRegister);
        setRegister(destRegister, value);
        setFlags(value);
    }

    
     void EmulationProcessor::LDD() {
        unimplemented();
    }

    
     void EmulationProcessor::LDDR() {
        unimplemented();
    }

    
     void EmulationProcessor::LDI() {
        unimplemented();
    }

    
     void EmulationProcessor::LDIR() {
        unimplemented();
    }

    /**
     * The contents of the low order portion of register pair HL (register L)
     * are loaded to memory address ( nn ), and the contents of the high order
     * portion of HL (register H) are loaded to the next highest memory address
     * ( nn +1). The first n operand after the Op Code is the low order byte of
     * nn .
     */
//    
//     void LD(RegisterPair registerPair, int lowOrder, int highOrder) {
//        int memAddress = (highOrder << 8)|lowOrder;
//
//        int value = getRegisterPairValue(registerPair);
//
//        getMemory().write(memAddress, value & 0xff);
//        getMemory().write(++memAddress, value >> 8);
//    }

    /**
     * The contents of the Accumulator are negated (two’s complement). This is
     * the same as subtracting the contents of the Accumulator from zero. Note
     * that 80H is left unchanged.
     * <p/>
     * S is set if result is negative; reset otherwise Z is set if result is 0;
     * reset otherwise H is set if borrow from bit 4; reset otherwise P/V is set
     * if Accumulator was 80H before operation; reset otherwise N is set C is
     * set if Accumulator was not 00H before operation; reset otherwise
     */
    
     void EmulationProcessor::NEG() {
        setSignFlag((getA() & 0b10000000) == 0b10000000);
        setParityOverflowFlag(getA() == 0x80);
        setZeroFlag(getA() == 0);
        setNFlag(true);
        setCFlag(getA() != 0);
        setA(~getA() & 0b11111111);
        // setHFlag(false);
    }

    
     void EmulationProcessor::NOP() {
//        unimplemented();
    }

    
     void EmulationProcessor::OR(Register register) {
        setA((getA() | getRegisterValue(register)));
    }

    
     void EmulationProcessor::OR(int immediateValue) {
        setA((getA() | immediateValue));
        setFlags(getA());
    }

    
     void EmulationProcessor::OR(MemoryAddress memoryAddress) {
        unimplemented();
    }

    
     void EmulationProcessor::OTDR() {
        unimplemented();
    }

    
     void EmulationProcessor::OTIR() {
        unimplemented();
    }

    /**
     * @param register
     */
//    
//     void OUT(Register register) {
//        /*
//		 * The contents of register C are placed on the bottom half (A0 through
//		 * A7) of the address bus to select the I/O device at one of 256
//		 * possible ports. The contents of Register B are placed on the top half
//		 * (A8 through A15) of the address bus at this time. Then the byte
//		 * contained in register r is placed on the data bus and written to the
//		 * selected peripheral device.
//		 */
//
////        logger.debug(String.format("OUT (C), %s", register));
//        addressBus = getC() | (getB() << 8);
//        io.write(addressBus, getRegisterValue(register));
//    }

    /**
     * The operand n is placed on the bottom half (A0 through A7) of the address
     * bus to select the I/O device at one of 256 possible ports. The contents
     * of the Accumulator (register A) also appear on the top half (A8 through
     * A15) of the address bus at this time. Then the byte contained in the
     * Accumulator is placed on the data bus and written to the selected
     * peripheral device.
     */
    
     void EmulationProcessor::OUT(MemoryAddress address, Register register) {
//        writeIO(address | (getA() << 8), getRegisterValue(register));
        writeIO(getMemoryAddress(address), getRegisterValue(register));
    }

    
     void EmulationProcessor::OUTD() {
        unimplemented();
    }

    
     void EmulationProcessor::OUTI() {
        unimplemented();
    }

    /**
     * The top two bytes of the external memory LIFO (last-in, first-out) Stack
     * are popped to register pair qq. The Stack Pointer (SP) register pair
     * holds the 16-bit address of the current top of the Stack. This
     * instruction first loads to the low order portion of qq, the byte at
     * memory location corresponding to the contents of SP; then SP is
     * incremented and the contents of the corresponding adjacent memory
     * location are loaded to the high order portion of qq and the SP is now
     * incremented again.
     */
    
     void EmulationProcessor::POP(RegisterPair register) {

        int lo = getMemory().read(getSP());

        incrementSP();
        int hi = getMemory().read(getSP());
        incrementSP();
        setRegisterPair(register, lo, hi);
    }

    /**
     * The contents of the Index Register IX are pushed to the external memory
     * LIFO (last-in, first-out) Stack. The Stack Pointer (SP) register pair
     * holds the 16-bit address of the current top of the Stack. This
     * instruction first decrements SP and loads the high order byte of IX to
     * the memory address specified by SP; then decrements SP again and loads
     * the low order byte to the memory location corresponding to this new
     * address in SP.
     *
     * @param valueRegister
     */
    
     void EmulationProcessor::PUSH(RegisterPair valueRegister) {
        int value = getRegisterPairValue(valueRegister);
        decrementSP();
        getMemory().write(getSP(), value >>> 8);
        decrementSP();
        getMemory().write(getSP(), value & 0b11111111);
    }

    
     void EmulationProcessor::RES(int i, Register b) {
        unimplemented();
    }

    
     void EmulationProcessor::RES(int i, MemoryAddress memoryAddress) {
        unimplemented();
    }

    /**
     * The byte at the memory location specified by the contents of the Stack
     * Pointer (SP) register pair is moved to the low order eight bits of the
     * Program Counter (PC). The SP is now incremented and the byte at the
     * memory location specified by the new contents of this instruction is
     * fetched from the memory location specified by the PC. This instruction is
     * normally used to return to the main line program at the completion of a
     * routine entered by a CALL instruction.
     * @param p
     */

    /**
     * If condition cc is true, the byte at the memory location specified by the
     * contents of the Stack Pointer (SP) register pair is moved to the low
     * order eight bits of the Program Counter (PC). The SP is incremented and
     * the byte at the memory location specified by the new contents of the SP
     * are moved to the high order eight bits of the PC. The SP is incremented
     * again. The next Op Code following this instruction is fetched from the
     * memory location specified by the PC. This instruction is normally used to
     * return to the main line program at the completion of a routine entered by
     * a CALL instruction. If condition cc is false, the PC is simply
     * incremented as usual, and the program continues with the next sequential
     * instruction.
     */
     void EmulationProcessor::RET(Condition condition) {
        logger.debug("RET cc[y]");
        if (isConditionTrue(condition)) {
            RET();
        }
    }

    
     void EmulationProcessor::RET() {
        // TODO: this doesn't quite follow what the spec says.
        // shouldn't wipe out high order when setting low order
        setPC(getMemory().read(getSP())); // set low order
        incrementSP();
        setPC(getMemory().read(getSP()) << 8 | getPC()); // set
        // high
        // order
        incrementSP();
    }

    
     void EmulationProcessor::RETI() {
        unimplemented();
    }

    
     void EmulationProcessor::RETN() {
        unimplemented();
    }

    
     void EmulationProcessor::RL(MemoryAddress memoryAddress) {
        unimplemented();
    }

    /**
     * The contents of the m operand are rotated left 1-bit position. The content of
     * bit 7 is copied to the Carry flag and the previous content of the Carry flag is
     * copied to bit 0.
     *
     * @param r
     */
    
     void EmulationProcessor::RL(Register r) {
        unimplemented();
    }

    /**
     * The contents of the Accumulator (register A) are rotated left 1-bit
     * position through the Carry flag. The previous content of the Carry flag
     * is copied to bit 0. Bit 0 is the least-significant bit.
     */
    
     void EmulationProcessor::RLA() {

        int tempA = getA();
        setA(((getA() << 1) & 0b11111111) | (getCFlag() ? 1 : 0));
        setCFlag((tempA & 0b10000000) == 0b10000000);
    }

    
     void EmulationProcessor::RLC(MemoryAddress memoryAddress) {
        unimplemented();
    }

    
     void EmulationProcessor::RLC(Register register) {
        unimplemented();
    }

    /**
     * The contents of the Accumulator (register A) are rotated left 1-bit
     * position. The sign bit (bit 7) is copied to the Carry flag and also to
     * bit 0. Bit 0 is the least-significant bit.
     * <p/>
     * S is not affected Z is not affected H is reset P/V is not affected N is
     * reset C is data from bit 7 of Accumulator
     */
    
     void EmulationProcessor::RLCA() {

        setA(((getA() << 1) & 0b11111111) | ((getA() >>> (8 - 1)) & 0b00000001));
        setCFlag((getA() & 0b1) == 1);
    }

    
     void EmulationProcessor::RLD() {
        unimplemented();
    }

    
     void EmulationProcessor::RR(MemoryAddress memoryAddress) {
        unimplemented();
    }

    
     void EmulationProcessor::RR(Register r) {
        unimplemented();
    }

    /**
     * The contents of the Accumulator (register A) are rotated right 1-bit
     * position through the Carry flag. The previous content of the Carry flag
     * is copied to bit 7. Bit 0 is the least-significant bit.
     */
    
     void EmulationProcessor::RRA() {

        int f2 = getCFlag() ? 0b1 : 0;
        setCFlag((0b1 & getA()) == 1);
        setA((getA() >>> 1) | (f2 << (8 - 1)));
    }

    
     void EmulationProcessor::RRC(MemoryAddress memoryAddress) {
        unimplemented();
    }

    
     void EmulationProcessor::RRC(Register r) {
        unimplemented();
    }

    /**
     * The contents of the Accumulator (register A) are rotated right 1-bit
     * position. Bit 0 is copied to the Carry flag and also to bit 7. Bit 0 is
     * the least- significant bit.
     */
    
     void EmulationProcessor::RRCA() {

        setCFlag((0b1 & getA()) == 1);
        setA((getA() >>> 1) | ((getA() << (8 - 1)) & 0b10000000));
    }

    /**
     * The contents of the low order four bits (bits 3, 2, 1, and 0) of memory
     * location (HL) are copied to the low order four bits of the Accumulator
     * (register A). The previous contents of the low order four bits of the
     * Accumulator are copied to the high order four bits (7, 6, 5, and 4) of
     * location (HL); and the previous contents of the high order four bits of
     * (HL) are copied to the low order four bits of (HL). The contents of the
     * high order bits of the Accumulator are unaffected.
     */
    
     void EmulationProcessor::RRD() {
        int priorMemory = getMemory().read(getHL());
        int priorAccumulator = getA();

        setA((priorMemory & 0b1111) | (priorAccumulator & 0b11110000));

        getMemory().write(getHL(),
                (priorMemory >>> 4) | ((priorAccumulator & 0b1111) << 4));
    }

    /**
     * The current Program Counter (PC) contents are pushed onto the external
     * memory stack, and the page zero memory location given by operand p is
     * loaded to the PC. Program execution then begins with the Op Code in the
     * address now pointed to by PC. The push is performed by first decrementing
     * the contents of the Stack Pointer (SP), loading the high-order byte of PC to
     * the memory address now pointed to by SP, decrementing SP again, and
     * loading the low order byte of PC to the address now pointed to by SP. The
     * Restart instruction allows for a jump to one of eight addresses indicated in
     * the table below. The operand p is assembled to the object code using the
     * corresponding T state.
     *
     * @param p
     */
    
     void EmulationProcessor::RST(int p) {
        pushPCtoStack();
        setPC(p);
    }

    
     void EmulationProcessor::SBC(RegisterPair hl, RegisterPair hl1) {
        unimplemented();
    }

    
     void EmulationProcessor::SBC(Register a, MemoryAddress memoryAddress) {
        unimplemented();
    }

    
     void EmulationProcessor::SBC(Register a, int nextByte) {
        unimplemented();
    }

    
     void EmulationProcessor::SBC(Register a, Register b) {
        unimplemented();
    }

    /**
     *
     */
    
     void EmulationProcessor::SCF() {
        /* The Carry flag in the F register is set. */
        /*-
         * S is not affected
		Z is not affected
		H is reset
		P/V is not affected
		N is reset
		C is set
		 */
        setHFlag(false);
        setCFlag(true);
        setNFlag(false);
    }

    /**
     * Bit b in register r (any of registers B, C, D, E, H, L, or A) is set.
     * Operands b and r are specified as follows in the assembled object code:
     * <p/>
     * <p/>
     * Bit b in the memory location addressed by the contents of register pair
     * HL is set.
     *
     * @param y
     * @param register
     */
    
     void EmulationProcessor::SET(int y, Register register) {
        setRegister(register, getRegisterValue(register) | (1 << y));
    }

    
     void EmulationProcessor::SET(int i, MemoryAddress memoryAddress) {
        int currentMemoryContents = getMemory().read(getMemoryAddress(memoryAddress));
        getMemory().write(getMemoryAddress(memoryAddress), currentMemoryContents | (1 << i));
    }

    
     void EmulationProcessor::SLA(MemoryAddress memoryAddress) {
        unimplemented();
    }

    
     void EmulationProcessor::SLA(Register r) {
        unimplemented();
    }

    
     void EmulationProcessor::SRA(MemoryAddress memoryAddress) {
        unimplemented();
    }

    
     void EmulationProcessor::SRA(Register r) {
        unimplemented();
    }

    
     void EmulationProcessor::SRL(MemoryAddress memoryAddress) {
        unimplemented();
    }

    /**
     * The contents of operand m are shifted right 1-bit position. The content of
     * bit 0 is copied to the Carry flag, and bit 7 is reset. Bit 0 is the least-
     * significant bit.
     *
     * @param m
     */
    
     void EmulationProcessor::SRL(Register m) {
        int val = getRegisterValue(m);
        setCFlag((val & 1) == 1);
        setRegister(m, val >> 1);
    }

    
     void EmulationProcessor::SUB(Register iX2) {
        unimplemented();
    }

    
     void EmulationProcessor::SUB(int iX2) {
        unimplemented();
    }

    
     void EmulationProcessor::SUB(MemoryAddress memoryAddress) {
        unimplemented();
    }

    /**
     * @param val
     */
    
     void EmulationProcessor::XOR(Register val) {
        XOR(getRegisterValue(val));
    }

    
     void EmulationProcessor::XOR(int val) {
        setA((getA() ^ val));
    }

    
     void EmulationProcessor::XOR(MemoryAddress memoryAddress) {
        unimplemented();
    }

     void EmulationProcessor::decrementSP() {
        setSP((getSP() - 1) & 0xffff);
    }

     void EmulationProcessor::doOneScreenRefreshesWorth() {
        // At 4Mhz, 20 milliseconds of execution corresponds to 80,000 cycles
        for (int i = 0; i < 80000; i++) {
            process();
        }
    }

    /**
     * @return the a
     */
     int EmulationProcessor::getA() {
        return A;
    }

    /**
     * @param a the a to set
     */
     void EmulationProcessor::setA(int a) {
        this.A = a;
    }

     int EmulationProcessor::getAF() {
        return (getA() << 8) | getF();
    }

     void EmulationProcessor::setAF(int value) {
        setA((value >> 8) & 0xff);
        setF(value & 0xff);
    }

     int EmulationProcessor::getAF_alt() {
        return (getA_alt() << 8) | getF_alt();
    }

     void EmulationProcessor::setAF_alt(int value) {
        setA_alt((value >> 8) & 0xff);
        setF_alt(value & 0xff);
    }

    /**
     * @return the a_alt
     */
     int EmulationProcessor::getA_alt() {
        return A_alt;
    }

    /**
     * @param a_alt the a_alt to set
     */
     void EmulationProcessor::setA_alt(int a_alt) {
        A_alt = a_alt;
    }

    /**
     * @return the b
     */
     int EmulationProcessor::getB() {
        return B;
    }

    /**
     * @param b the b to set
     */
     void EmulationProcessor::setB(int b) {
        this.B = b;
    }

     int EmulationProcessor::getBC() {
        return (B << 8) | C;
    }

     void EmulationProcessor::setBC(int value) {
        setB((value >> 8) & 0xff);
        setC(value & 0xff);
    }

     int EmulationProcessor::getBC_alt() {
        return (B_alt << 8) | C_alt;
    }

     void EmulationProcessor::setBC_alt(int value) {
        setB_alt((value >> 8) & 0xff);
        setC_alt(value & 0xff);
    }

    /**
     * @return the b_alt
     */
     int EmulationProcessor::getB_alt() {
        return B_alt;
    }

    /**
     * @param b_alt the b_alt to set
     */
     void EmulationProcessor::setB_alt(int b_alt) {
        B_alt = b_alt;
    }

    /**
     * @return the c
     */
     int EmulationProcessor::getC() {
        return C;
    }

    /**
     * @param c the c to set
     */
     void EmulationProcessor::setC(int c) {
        this.C = c;
    }

     bool EmulationProcessor::getCFlag() {
        return (F & 0b1) == 0b1;
    }

     void EmulationProcessor::setCFlag(bool flag) {
        if (flag) {
            F |= 0b1;
        } else {
            F &= ~0b1;
        }
    }

    /**
     * @return the c_alt
     */
     int EmulationProcessor::getC_alt() {
        return C_alt;
    }

    /**
     * @param c_alt the c_alt to set
     */
     void EmulationProcessor::setC_alt(int c_alt) {
        C_alt = c_alt;
    }

    /**
     * @return the d
     */
     int EmulationProcessor::getD() {
        return D;
    }

    /**
     * @param d the d to set
     */
     void EmulationProcessor::setD(int d) {
        this.D = d;
    }

    int EmulationProcessor::getDE() {
        return (D << 8) | E;
    }

     void EmulationProcessor::setDE(int value) {
        setD((value >> 8) & 0xff);
        setE(value & 0xff);
    }

     int EmulationProcessor::getDE_alt() {
        return (D_alt << 8) | E_alt;
    }

     void EmulationProcessor::setDE_alt(int value) {
        setD_alt((value >> 8) & 0xff);
        setE_alt(value & 0xff);
    }

    /**
     * @return the d_alt
     */
     int EmulationProcessor::getD_alt() {
        return D_alt;
    }

    /**
     * @param d_alt the d_alt to set
     */
     void EmulationProcessor::setD_alt(int d_alt) {
        D_alt = d_alt;
    }

    /**
     * @return the e
     */
     int EmulationProcessor::getE() {
        return E;
    }

    /**
     * @param e the e to set
     */
     void EmulationProcessor::setE(int e) {
        this.E = e;
    }

    /**
     * @return the e_alt
     */
     int EmulationProcessor::getE_alt() {
        return E_alt;
    }

    /**
     * @param e_alt the e_alt to set
     */
     void EmulationProcessor::setE_alt(int e_alt) {
        E_alt = e_alt;
    }

    /**
     * @return the f
     */
     int EmulationProcessor::getF() {
        return F;
    }

    /**
     * @param f the f to set
     */
     void EmulationProcessor::setF(int f) {
        this.F = f;
    }

    /**
     * @return the f_alt
     */
     int EmulationProcessor::getF_alt() {
        return F_alt;
    }

    /**
     * @param f_alt the f_alt to set
     */
     void EmulationProcessor::setF_alt(int f_alt) {
        F_alt = f_alt;
    }

    /**
     * @return the h
     */
     int EmulationProcessor::getH() {
        return H;
    }

    /**
     * @param h the h to set
     */
     void EmulationProcessor::setH(int h) {
        this.H = h;
    }

     bool EmulationProcessor::getHFlag() {
        return (F & 0b100000) == 0b100000;
    }

     void EmulationProcessor::setHFlag(bool flag) {
        if (flag) {
            F |= 0b100000;
        } else {
            F &= ~0b100000;
        }
    }

     int EmulationProcessor::getHL() {
        return (getH() << 8) | getL();
    }

     void EmulationProcessor::setHL(int value) {
        setH((value >> 8) & 0xff);
        setL(value & 0xff);
    }

     int EmulationProcessor::getHL_alt() {
        return (H_alt << 8) | L_alt;
    }

     void EmulationProcessor::setHL_alt(int value) {
        setH_alt((value >> 8) & 0xff);
        setL_alt(value & 0xff);
    }

    /**
     * @return the h_alt
     */
     int EmulationProcessor::getH_alt() {
        return H_alt;
    }

    /**
     * @param h_alt the h_alt to set
     */
     void EmulationProcessor::setH_alt(int h_alt) {
        H_alt = h_alt;
    }

    /**
     * @return the i
     */
     int EmulationProcessor::getI() {
        return I;
    }

    /**
     * @param i the i to set
     */
     void EmulationProcessor::setI(int i) {
        I = i;
    }

    /**
     * @return the iX
     */
     int EmulationProcessor::getIX() {
        return IX;
    }

    /**
     * @param iX the iX to set
     */
     void EmulationProcessor::setIX(int iX) {
        IX = iX;
    }

    /**
     * @return upper byte of IX
     */
     int EmulationProcessor::getIXH() {
        return IX >> 8;
    }

    /**
     * @return lower byte of IX
     */
     int EmulationProcessor::getIXL() {
        return IX & 0b11111111;
    }

//    
//     void CP(AlgorithmicInstructionDecoder.BlockInstructionOp bli) {
//        int result = getA() - getMemory().read(getHL());
//
//        setSignFlag((result & 0b10000000) == 0b10000000);
//        setZeroFlag(result == 0);
//        setHFlag(false); //H is set if borrow from bit 4; reset otherwise
//        setParityOverflowFlag(isIFF2()); //        P/V is set if BC -1 x 0; reset otherwise
//        setNFlag(true); // N
//
//        if (result == 0) {
//            setBC(getBC() - 1);
//            switch (bli) {
//                case D:
//                    setHL(getHL() - 1);
////                    break;
//                case DR:
//                    break;
//                case I:
//                    setHL(getHL() + 1);
////                    break;
//                case IR:
//                    break;
//            }
//        }
//    }

    /**
     * @return the iY
     */
     int EmulationProcessor::getIY() {
        return IY;
    }

    /**
     * @param iY the iY to set
     */
     void EmulationProcessor::setIY(int iY) {
        IY = iY;
    }

     int EmulationProcessor::getIYH() {
        return IY >> 8;
    }

     int EmulationProcessor::getIYL() {
        return IY & 0b11111111;
    }

     IO EmulationProcessor::getIo() {
        return io;
    }

     void setIo(IO io) {
        this.io = io;
    }

    /**
     * @return the l
     */
     int EmulationProcessor::getL() {
        return L;
    }

    /**
     * @param l the l to set
     */
     void EmulationProcessor::setL(int l) {
        this.L = l;
    }

    /**
     * @return the l_alt
     */
     int EmulationProcessor::getL_alt() {
        return L_alt;
    }

    /**
     * @param EmulationProcessor::l_alt the l_alt to set
     */
     void EmulationProcessor::setL_alt(int l_alt) {
        L_alt = l_alt;
    }

     bool EmulationProcessor::getNFlag() {
        return (F & 0b10000) == 0b10000;
    }

     void EmulationProcessor::setNFlag(bool flag) {
        if (flag) {
            F |= 0b10000;
        } else {
            F &= ~0b10000;
        }
    }

     bool EmulationProcessor::getParityOverflowFlag() {
        return (F & 0b100) == 0b100;
    }

     void EmulationProcessor::setParityOverflowFlag(bool flag) {
        if (flag) {
            F |= 0b100;
        } else {
            F &= ~0b100;
        }
    }

    /**
     * @return the r
     */
     int EmulationProcessor::getR() {
        return R;
    }

    /**
     * @param r the r to set
     */
     void EmulationProcessor::setR(int r) {
        R = r;
    }

    //    
     int EmulationProcessor::getRegisterPairValue(RegisterPair register) {
//		logger.debug("Getting value for register " + register);
        switch (register) {
            case BC:
                return getBC();
            case DE:
                return getDE();
            case HL:
                return getHL();
            case SP:
                return getSP();
            case AF:
                return getAF();
            case IX:
                return getIX();
            case IY:
                return getIY();
            case PC:
                return getPC();
            case BC_prime:
                return getBC_alt();
            case DE_prime:
                return getDE_alt();
            case HL_prime:
                return getHL_alt();
            case AF_prime:
                return getAF_alt();
            default:
                throw new RuntimeException("Invalid register " + register);
        }
    }

    //    
     int EmulationProcessor::getRegisterValue(Register register) {
//		logger.debug("Getting value for register " + register);
        switch (register) {
            case A:
                return getA();
            case B:
                return getB();
            case C:
                return getC();
            case D:
                return getD();
            case E:
                return getE();
            case H:
                return getH();
            case L:
                return getL();
//            case HL:
//                return getMemory().read(getHL());
//            case IX:
//                return getIX();
            case IXL:
                return getIXL();
            case IXH:
                return getIXH();
            case R:
                return getR();
            case I:
                return getI();
            default:
                throw new RuntimeException("Invalid register " + register);
        }
    }

    /**
     * @return the sP
     */
//    
     int EmulationProcessor::getSP() {
        return SP;
    }

    /**
     * @param sP the sP to set
     */
//    
     void EmulationProcessor::setSP(int sP) {
        SP = sP;
    }

     bool EmulationProcessor::getSignFlag() {
        return (F & 0b10000000) == 0b10000000;
    }

     void EmulationProcessor::setSignFlag(bool flag) {
        if (flag) {
            F |= 0b10000000;
        } else {
            F &= ~0b10000000;
        }
    }

     bool EmulationProcessor::getZeroFlag() {
        return (F & 0b1000000) == 0b1000000;
    }

     void EmulationProcessor::setZeroFlag(bool flag) {
        if (flag) {
            F |= 0b1000000;
        } else {
            F &= ~0b1000000;
        }
    }

     void EmulationProcessor::incrementSP() {
        setSP(getSP() + 1);
    }

     bool EmulationProcessor::isConditionTrue(Condition condition) {
        bool retval = false;
        if (condition == Condition.NZ) {
            logger.debug("NZ");
            if (!getZeroFlag()) {
                retval = true;
            }
        } else if (condition == Condition.Z) {
            logger.debug("Z");
            if (getZeroFlag()) {
                retval = true;
            }
        } else if (condition == Condition.NC) {
            logger.debug("NC");
            if (!getCFlag()) {
                retval = true;
            }
        } else if (condition == Condition.C) {
            logger.debug("C");
            if (getCFlag()) {
                retval = true;
            }
        } else if (condition == Condition.PO) {
            logger.debug("PO");
            if (!getParityOverflowFlag()) {
                retval = true;
            }
        } else if (condition == Condition.PE) {
            logger.debug("PE");
            if (getParityOverflowFlag()) {
                retval = true;
            }
        } else if (condition == Condition.P) {
            logger.debug("P");
            if (!getSignFlag()) {
                retval = true;
            }
        } else if (condition == Condition.M) {
            logger.debug("M");
            if (getSignFlag()) {
                retval = true;
            }
        }
        return retval;
    }

    /**
     * @return the iFF1
     */
     bool EmulationProcessor::isIFF1() {
        return IFF1;
    }

    /**
     * @param iFF1 the iFF1 to set
     */
     void EmulationProcessor::setIFF1(bool iFF1) {
        IFF1 = iFF1;
    }

    /**
     * @return the iFF2
     */
     bool EmulationProcessor::isIFF2() {
        return IFF2;
    }

    /**
     * @param iFF2 the iFF2 to set
     */
     void EmulationProcessor::setIFF2(bool iFF2) {
        IFF2 = iFF2;
    }

     void EmulationProcessor::process() {
//        if (halted) {
//            decoder.decode(); //NOP
//        } else {
//            placeProgramCounterOnAddressBus();
        instructionDecoder.decode();
//        }
    }

     void EmulationProcessor::process(int count) {
        for (int i = 0; i < count; i++) {
            process();
        }
    }

     void EmulationProcessor::pushPCtoStack() {
        decrementSP();
        getMemory().write(getSP(), (getPC() >> 8));
        decrementSP();
        getMemory().write(getSP(), (getPC() & 0xff));
    }

    /**
     * @param address
     * @return
     */
     int EmulationProcessor::eadIO(int address) {
        return io.read(address);
    }

    /**
     * Q-6:What happens when the Z80 CPU is RESET?
     * <p/>
     * Thomas Scherrer:
     * The program counter is reset to 0000h
     * Interrupt mode 0.
     * Interrupt are dissabled.
     * The register I = 00h
     * The register R = 00h
     * <p/>
     * During reset time, the address bus and data bus go to a hight impadance state and all controll output signals go to the inactive state.
     * <p/>
     * The Z80 CPU will execute instruction at address 0000h
     */
//    
     void EmulationProcessor::reset() {
        setPC(0x0);
        setI(0x0);
        setR(0x0);
        IM = 0;
    }

    /**
     * @param value
     */
     void EmulationProcessor::setFlags(int value) {

		/*- S is set if I-Register is negative; reset otherwise
		Z is set if I-Register is zero; reset otherwise
		H is reset
		P/V contains contents of IFF2
		N is reset
		C is not affected
		If an interrupt occurs during execution of this instruction, the Parity
		flag contains a 0.
		 */

        setSignFlag((value & 0b10000000) == 0b10000000);
        setZeroFlag(value == 0);
        setHFlag(false);
        setParityOverflowFlag(isIFF2());
        setNFlag(false); // N
    }

    /**
     * @param memory the memory to set
     */
    
     void EmulationProcessor::setMemory(Memory memory) {
        this.memory = memory;
    }

     void EmulationProcessor::setRegister(Register register, int value) {
        logger.debug("Setting value 0x" + Integer.toHexString(value)
                + " for register " + register);
        switch (register) {
            case A:
                setA(value);
                break;
            case B:
                setB(value);
                break;
            case C:
                setC(value);
                break;
            case D:
                setD(value);
                break;
            case E:
                setE(value);
                break;
            case H:
                setH(value);
                break;
            case L:
                setL(value);
                break;
//            case HL:
//                setHL(value);
//                break;
            case R:
                setR(value);
                break;
            case I:
                setI(value);
                break;
            default:
                throw new RuntimeException("Invalid register " + register);
        }
    }

     void EmulationProcessor::setRegisterPair(RegisterPair register, int sixteenBit) {
        setRegisterPair(register, sixteenBit & 0xff, ((sixteenBit >> 8) & 0xff));
    }

     void EmulationProcessor::setRegisterPair(RegisterPair register, int lowOrder, int highOrder) {
        switch (register) {
            case BC:
                B = highOrder;
                C = lowOrder;
                break;
            case BC_prime:
                B_alt = highOrder;
                C_alt = lowOrder;
                break;
            case DE:
                D = highOrder;
                E = lowOrder;
                break;
            case DE_prime:
                D_alt = highOrder;
                E_alt = lowOrder;
                break;
            case HL:
                H = highOrder;
                L = lowOrder;
                break;
            case HL_prime:
                H_alt = highOrder;
                L_alt = lowOrder;
                break;
            case SP:
                SP = highOrder << 8 | lowOrder;
                break;
            case AF:
                A = highOrder;
                F = lowOrder;
                break;
            case AF_prime:
                A_alt = highOrder;
                F_alt = lowOrder;
                break;
            case IX:
                IX = highOrder << 8 | lowOrder;
                break;
            case IY:
                IY = highOrder << 8 | lowOrder;
                break;
            default:
                logger.error("unknown register pair");
        }
    }

     void EmulationProcessor::unimplemented() {
        throw new RuntimeException("Unimplemented instruction");
    }

    /**
     * @param address
     * @param value
     */
     void EmulationProcessor::writeIO(int address, int value) {
        logger.debug("Writing IO: addr:" + address + " val:" + value);
        io.write(address, value);
    }

     int EmulationProcessor::getMemoryAddress(MemoryAddress memoryAddress) {
        int address = 0;
        if (memoryAddress.getRegister() != null) {
            address = this.getRegisterValue(memoryAddress.getRegister());
            if (memoryAddress.getOffset() != null) {
                address += memoryAddress.getOffset();
            }
        } else if (memoryAddress.getRegisterPair() != null) {
            address = this.getRegisterPairValue(memoryAddress.getRegisterPair());
            if (memoryAddress.getOffset() != null) {
                address += memoryAddress.getOffset();
            }
        } else if (memoryAddress.getMemoryAddress() != null) {
            address = memoryAddress.getMemoryAddress();
        }

        return address;
    }
