#include "emu_alu.h"
#include <boost/utility/binary.hpp>
#include <iostream>
//#include "utils.h"
//for hex outpu
#include <iomanip>
#include <sstream>
#include <assert.h>

#include "tables.h"

EmuAlu::EmuAlu(Memory* memory, IO* io, Registers* registers) :
    io(io), memory(memory), registers(registers)
{
    std::cout << "EmuAlu ctor" << std::endl;
}

EmuAlu::~EmuAlu() {
//     delete &memory;
//     delete &io;
}

void EmuAlu::ADC(RegisterPair rp1, RegisterPair rp2) {
    registers->setRegisterPair(rp1, registers->getRegisterPairValue(rp1) + registers->getRegisterPairValue(rp2) + (registers->getCFlag() ? 1 : 0));
    //TODO: warning: C4244: 'argument' : conversion from 'uint16_t' to 'uint8_t', possible loss of data
    setFlags(registers->getRegisterPairValue(rp1));
}

void EmuAlu::ADC(Rgstr a, Rgstr b) {
    registers->setRegister(a, registers->getRegisterValue(a) + registers->getRegisterValue(b) + (registers->getCFlag() ? 1 : 0));
}

void EmuAlu::ADC(Rgstr rgstr, std::uint8_t val) {
    registers->setRegister(rgstr, registers->getRegisterValue(rgstr) + val + (registers->getCFlag() ? 1 : 0));
}

void EmuAlu::ADC(Rgstr rgstr, MemoryAddress memoryAddress) {
    std::uint8_t flag = (registers->getCFlag() ? 1 : 0);
    std::uint16_t memoryAdd = getMemoryAddress(memoryAddress);
    std::uint8_t memoryValue = memory->read(memoryAdd);
    registers->setRegister(rgstr, registers->getRegisterValue(rgstr) + memoryValue + flag);
}

/**
 * The contents of rgstr pair ss (any of rgstr
 * pairs BC, DE, HL, or SP) are added to the contents of
 * rgstr pair HL and the result is stored in HL.
 * Operand ss is specified as follows in the assembled
 * object code.
 */
void EmuAlu::ADD(RegisterPair destination, RegisterPair rgstr) {
    //TODO: Set flags correctly after these operations!!!
    registers->setRegisterPair(destination,registers->getRegisterPairValue(destination) +registers->getRegisterPairValue(rgstr));
}

void EmuAlu::ADD(Rgstr destination, std::uint8_t nextByte) {
    std::uint8_t result = registers->getRegisterValue(destination) + nextByte;
    registers->setRegister(destination, result);
    registers->setSignFlag(result < 0);
    registers->setZeroFlag(result == 0);

    //     registers->setHFlag(true);
    //P/V
    //C

    registers->setNFlag(false);
}

void EmuAlu::ADD(Rgstr destination, Rgstr source) {
    ADD(destination, registers->getRegisterValue(source));
}

void EmuAlu::ADD(Rgstr destination, MemoryAddress memoryAddress) {
    ADD(destination, memory->read(getMemoryAddress(memoryAddress)));
}

void EmuAlu::AND(Rgstr iX2) {
    AND(registers->getRegisterValue(iX2));
}

void EmuAlu::AND(std::uint8_t value) {
    std::uint8_t result = registers->getA() & value;
    registers->setA(result);

    registers->setSignFlag(result < 0);
    registers->setZeroFlag(result == 0);

    registers->setHFlag(true);

    registers->setNFlag(false);
    registers->setCFlag(false);
    // P/V
}

void EmuAlu::AND(MemoryAddress memoryAddress) {
    AND(memory->read(getMemoryAddress(memoryAddress)));
}

/**
 * This instruction tests bit b in rgstr r and sets the Z flag
 * accordingly.
 */
void EmuAlu::BIT(std::uint8_t y, std::uint8_t value) {
    registers->setZeroFlag(!((value & (1 << y)) == (1 << y)));
}

void EmuAlu::BIT(std::uint8_t y, Rgstr rgstr) {
    BIT(y, registers->getRegisterValue(rgstr));
}

void EmuAlu::BIT(std::uint8_t i, MemoryAddress memoryAddress) {
    BIT(i, memory->read(getMemoryAddress(memoryAddress)));
}

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
loads the operands nn to PC to postd::uint8_t to the address in memory where the
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
condition bits in the Flag Rgstr (rgstr F).
 */

/**
 * The current contents of the Program Counter (PC) are pushed onto the top
 * of the external memory stack. The operands nn are then loaded to the PC to
 * postd::uint8_t to the address in memory where the first Op Code of a subroutine is to
 * be fetched. At the end of the subroutine, a RETurn instruction can be used
 * to return to the original program flow by popping the top of the stack back
 * to the PC. The push is accomplished by first decrementing the current
 * contents of the Stack Pointer (rgstr pair SP), loading the high-order byte
 * of the PC contents to the memory address now pointed to by the SP; then
 * decrementing SP again, and loading the low order byte of the PC contents
 * to the top of stack.
 * Because this is a 3-byte instruction, the Program Counter was incremented
 * by three before the push is executed.
 */
void EmuAlu::CALL(Condition c, MemoryAddress memoryAddress) {
    if (isConditionTrue(c)) {
        pushPCtoStack();
        registers->setPC(getMemoryAddress(memoryAddress));
//         std::cout << "Call condition true" << std::endl;
    } else {
//         std::cout << "Call condition false" << std::endl;
    }
}

void EmuAlu::CALL(MemoryAddress memoryAddress) {
    pushPCtoStack();
    registers->setPC(getMemoryAddress(memoryAddress));
}

void EmuAlu::CCF() {
    /* The Carry flag in the F rgstr is inverted. */
    registers->setHFlag(registers->getCFlag());

    registers->setCFlag(!registers->getCFlag());

    registers->setNFlag(false);
}

void EmuAlu::CP(std::uint8_t val) {
    std::uint8_t result = registers->getA() - val;

    registers->setZeroFlag(result == 0);
    registers->setSignFlag(result < 0);
    // this.setHFlag(flag);
//     // this.setParityOverflowFlag(flag);
    registers->setNFlag(true);
}

void EmuAlu::CP(Rgstr val) {
    CP(registers->getRegisterValue(val));
}

void EmuAlu::CP(MemoryAddress memoryAddress) {
    CP(memory->read(getMemoryAddress(memoryAddress)));
}

/*
 * The contents of the memory location addressed by the HL register pair is
 * compared with the contents of the Accumulator. In case of a true
 * compare, a condition bit is set. The HL and Byte Counter (register pair
 * BC) are decremented.
 */
void EmuAlu::CPD() {
    CP(memory->read(registers->getHL()));
    DEC(RegisterPair::HL);
    DEC(RegisterPair::BC);
    registers->setParityOverflowFlag(registers->getBC() != 0);
}

/*
 * The contents of the memory location addressed by the HL register pair is
compared with the contents of the Accumulator. In case of a true compare,
a condition bit is set. The HL and BC (Byte Counter) register pairs are
decremented. If decrementing causes the BC to go to zero or if A = (HL),
the instruction is terminated. If BC is not zero and A = (HL), the program
counter is decremented by two and the instruction is repeated. Interrupts are
recognized and two refresh cycles execute after each data transfer. When
BC is set to zero, prior to instruction execution, the instruction loops
through 64 Kbytes if no match is found.
*/
void EmuAlu::CPDR() {
    CPD();
    if (!registers->getZeroFlag()) {
        registers->setPC(registers->getPC() - 2); //repeat instruction
    }
}

/*
 * The contents of the memory location addressed by the HL register is
compared with the contents of the Accumulator. In case of a true compare,
a condition bit is set. Then HL is incremented and the Byte Counter
(register pair BC) is decremented.
*/
void EmuAlu::CPI() {
    CP(memory->read(registers->getHL()));

    INC(RegisterPair::HL);
    DEC(RegisterPair::BC);

    registers->setParityOverflowFlag(registers->getBC() != 0);
}

void EmuAlu::CPIR() {
    CPI();
    if (!registers->getZeroFlag()) {
        registers->setPC(registers->getPC() - 2); //repeat instruction
    }
}

/**
 * The contents of the Accumulator (rgstr A) are inverted (one’s
 * complement).
 */
void EmuAlu::CPL() {
    registers->setA(registers->getA() ^ BOOST_BINARY(11111111));
    registers->setNFlag(true);
    registers->setHFlag(true);
}

void EmuAlu::DAA() {
    int a, c, d;

    /* The following algorithm is from
        * comp.sys.sinclair's FAQ.
        */

    a = registers->getA();
    if (a > 0x99 || registers->getCFlag()) {
        c = registers->getCFlag();
        d = 0x60;
    } else {
        c = d = 0;
    }

    if ((a & 0x0f) > 0x09 || registers->getHFlag()) {
        d += 0x06;
    }

    registers->setA( registers->getA() + registers->getNFlag() ? -d : +d);
    registers->setF(SZYXP_FLAGS_TABLE[registers->getA()]
            //TODO: warning: C4805: '&' : unsafe mix of type 'int' and type 'bool' in operation
                    | ((registers->getA() ^ a) & registers->getHFlag())
            //TODO: warning: C4805: '|' : unsafe mix of type 'int' and type 'bool' in operation
                    | registers->getNFlag()
                    | c);
}

/**
 * S is set if result is negative; reset otherwise
 * Z is set if result is zero; reset otherwise
 * H is set if borrow from bit 4, reset otherwise
 * P/V is set if m was 80H before operation; reset otherwise
 * N is set
 * C is not affected
 */
void EmuAlu::DEC(MemoryAddress memoryAddress) {
    std::uint16_t address = getMemoryAddress(memoryAddress);
    std::uint8_t oldvalue = memory->read(address);
    std::uint8_t newvalue = oldvalue - 1;

    memory->write(address, newvalue);

    registers->setSignFlag(newvalue < 0);
    registers->setZeroFlag(newvalue == 0);

    //Compare with 0 to remove warning: C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
    registers->setHFlag(((oldvalue & 0x000F + newvalue & 0x000F) & 0x00F0) !=0);

    registers->setNFlag(false);
}

void EmuAlu::DEC(Rgstr rgstr) {
    registers->setParityOverflowFlag(registers->getRegisterValue(rgstr) == 0x80);
    std::uint8_t oldvalue = registers->getRegisterValue(rgstr);
    std::uint8_t newvalue = oldvalue - 1;

    registers->setRegister(rgstr, newvalue);

    registers->setSignFlag(newvalue < 0);
    registers->setZeroFlag(newvalue == 0);

    //carry for add
    //registers->setHFlag((oldvalue & 0x000F + newvalue & 0x000F) & 0x00F0));

    registers->setHFlag(((oldvalue & 0x000F + newvalue & 0x000F) & 0x00F0) !=0);

    registers->setNFlag(false);
}

/**
 * The contents of rgstr pair ss (any of the rgstr
 * pairs BC, DE, HL, or SP) are decremented. Operand ss
 * is specified as follows in the assembled object code.
 */
void EmuAlu::DEC(RegisterPair rgstrPair) {
    registers->setRegisterPair(rgstrPair,
                               registers->getRegisterPairValue(rgstrPair) - 1);
}

void EmuAlu::DI() {
    registers->setIFF1(false);
    registers->setIFF2(false);
}

/**
 * This instruction is similar to the conditional jump instructions except
 * that a rgstr value is used to determine branching. The B rgstr is
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
void EmuAlu::DJNZ(MemoryAddress memoryAddress) {
    registers->setB(registers->getB() - 1);

    if (registers->getB() > 0) {
        logger.debug("B rgstr > 0");
        registers->setPC(getMemoryAddress(memoryAddress));
    }
}

/**
 * The enable interrupt instruction sets both interrupt enable flip flops
 * (IFFI and IFF2) to a logic 1, allowing recognition of any maskable
 * interrupt. Note that during the execution of this instruction and the
 * following instruction, maskable interrupts are disabled.
 */
void EmuAlu::EI() {
    registers->setIFF1(true);
    registers->setIFF2(true);
}

void EmuAlu::EX(MemoryAddress memoryAddress, RegisterPair rgstr) {
    std::uint8_t loMemVal = memory->read(getMemoryAddress(memoryAddress));
    std::uint8_t hiMemVal = memory->read(getMemoryAddress(memoryAddress) + 1);

    switch (rgstr) {
    case RegisterPair::HL:
        memory->write(registers->getSP(), registers->getL());
        memory->write(registers->getSP() + 1, registers->getH());
        registers->setL(loMemVal);
        registers->setH(hiMemVal);
        break;
    case RegisterPair::IX:
        memory->write(registers->getSP(), registers->getIXL());
        memory->write(registers->getSP() + 1, registers->getIXH());
        registers->setIX((hiMemVal << 8) | loMemVal);
        break;
    case RegisterPair::IY:
        memory->write(registers->getSP(), registers->getIYL());
        memory->write(registers->getSP() + 1, registers->getIYH());
        registers->setIY((hiMemVal << 8) | loMemVal);
        break;
    default:
        throw UnknownRegisterPairException();
    }

}

/**
 * The 2-byte contents of the rgstr pairs AF and AF' are exchanged.
 * Rgstr pair AF consists of rgstrs A' and F'
 */
void EmuAlu::EX(RegisterPair a, RegisterPair b) {
    std::uint16_t aval =registers->getRegisterPairValue(a);
    registers->setRegisterPair(a,registers->getRegisterPairValue(b));
    registers->setRegisterPair(b, aval);
}

/**
 * Each 2-byte value in rgstr pairs BC, DE, and HL is exchanged with the
 * 2-byte value in BC', DE', and HL', respectively.
 */
void EmuAlu::EXX() {
    std::uint16_t temp = registers->getBC();
    registers->setBC(registers->getBC_alt());
    registers->setBC_alt(temp);

    temp = registers->getDE();
    registers->setDE(registers->getDE_alt());
    registers->setDE_alt(temp);

    temp = registers->getHL();
    registers->setHL(registers->getHL_alt());
    registers->setHL_alt(temp);
}

void EmuAlu::HALT() {
    registers->setHalted(true);
}

void EmuAlu::IM(std::uint8_t im) {
    registers->setIM(im);
}

/**
 * The contents of rgstr C are placed on the bottom half (A0 through A7) of
 * the address bus to select the I/O device at one of 256 possible ports. The
 * contents of Rgstr B are placed on the top half (A8 through A15) of the
 * address bus at this time. Then one byte from the selected port is placed on
 * the data bus and written to rgstr r in the CPU. Rgstr r identifies any of
 * the CPU rgstrs shown in the following table, which also indicates the
 * corresponding 3-bit r field for each. The flags are affected, checking the
 * input data.
 */
void EmuAlu::in(Rgstr rgstr, const MemoryAddress& i) {
//     assert(i.getRegisterPair() == RegisterPair::BC);
    registers->setRegister(rgstr, io->read(getMemoryAddress(i)));
}

/**
 * - Rgstr r is incremented and rgstr r identifies any of the
 * rgstrs A, B, C, D, E, H, or L, assembled as follows in the object
 * code.
 * <p/>
 * S is set if result is negative; reset otherwise Z is set if result is
 * zero; reset otherwise H is set if carry from bit 3; reset otherwise P/V
 * is set if r was 7FH before operation; reset otherwise N is reset C is not
 * affected
 */
void EmuAlu::INC(MemoryAddress memoryAddress) {
    registers->setParityOverflowFlag(memory->read(getMemoryAddress(memoryAddress)) == 0x7F);

    std::uint8_t newValue = (memory->read(getMemoryAddress(memoryAddress)) + 1) & 0xff;
    memory->write(getMemoryAddress(memoryAddress), newValue);

    registers->setSignFlag(newValue < 0);
    registers->setZeroFlag(newValue == 0);
    // H ??

    registers->setNFlag(false);
}

void EmuAlu::INC(Rgstr reg) {
    registers->setParityOverflowFlag(registers->getRegisterValue(reg) == 0x7F);

    std::uint8_t newValue = ((registers->getRegisterValue(reg) + 1) & 0xff);

    registers->setRegister(reg, newValue);

    registers->setSignFlag(newValue < 0);
    registers->setZeroFlag(newValue == 0);
    // Half carry flag setting! ??

    registers->setNFlag(false);
}

/**
 * The contents of rgstr pair ss (any of rgstr
 * pairs BC, DE, HL, or SP) are incremented. Operand ss
 * is specified as follows in the assembled object code.
 *
 * As per docs no flags are affected.
 */
void EmuAlu::INC(RegisterPair rgstrPair) {
    std::uint16_t newValue = registers->getRegisterPairValue(rgstrPair) + 1;
    registers->setRegisterPair(rgstrPair,newValue);
}

/*
 * The contents of register C are placed on the bottom half (A0 through A7) of
the address bus to select the I/O device at one of 256 possible ports.
Register B may be used as a byte counter, and its contents are placed on the
top half (A8 through A15) of the address bus at this time. Then one byte
from the selected port is placed on the data bus and written to the CPU. The
contents of the HL register pair are placed on the address bus and the input
byte is written to the corresponding location of memory. Finally, the byte
counter and register pair HL are decremented.*/
void EmuAlu::IND() {
    std::uint8_t value = io->read(registers->getC());
    memory->write(registers->getHL(), value);
    DEC(Rgstr::B);
    DEC(RegisterPair::HL);
    registers->setNFlag(true);
    registers->setZeroFlag(registers->getB() == 0);
}

void EmuAlu::INDR() {
    IND();
    if (!registers->getZeroFlag()) {
        registers->setPC(registers->getPC() -2);
    }
}

void EmuAlu::INI() {
    std::uint8_t value = io->read(registers->getC());
    memory->write(registers->getHL(), value);
    DEC(Rgstr::B);
    INC(RegisterPair::HL);
    registers->setNFlag(true);
    registers->setZeroFlag(registers->getB() == 0);
}

void EmuAlu::INIR() {
    INI();
    if (!registers->getZeroFlag()) {
        registers->setPC(registers->getPC() -2);
    }
}

/**
 * Operand nn is loaded to rgstr pair PC (Program Counter). The next
 * instruction is fetched from the location designated by the new contents
 * of the PC.
 */
void EmuAlu::JP(MemoryAddress memoryAddress) {
    registers->setPC(getMemoryAddress(memoryAddress));
}

void EmuAlu::JP(Condition condition, MemoryAddress memoryAddress) {
    std::stringstream stream;
    stream << std::hex
           << "0x" << std::setfill ('0')
           << std::setw(sizeof(std::uint16_t)*2)<< +registers->getPC();

    if (isConditionTrue(condition)) {
        logger.debug(stream.str() + " MET");
        JP(memoryAddress);
    } else {
        logger.debug(stream.str() + " NOT");
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
void EmuAlu::JR(Condition condition, MemoryAddress memoryAddress) {
    if (isConditionTrue(condition)) {
        JR(memoryAddress);
    }
}

void EmuAlu::JR(MemoryAddress memoryAddress) {
    registers->setPC(getMemoryAddress(memoryAddress));
}

/**
 * The contents of memory address (nn) are loaded to the low order
 * portion of rgstr pair HL (rgstr L), and the contents of the
 * next highest memory address (nn +1) are loaded to the high order
 * portion of HL (rgstr H). The first n operand after the Op Code is
 * the low order byte of nn .
 */
void EmuAlu::LD(RegisterPair r1, RegisterPair r2) {
    registers->setRegisterPair(r1,registers->getRegisterPairValue(r2));
}

void EmuAlu::LD(RegisterPair rgstrPair, std::uint16_t immediateValue) {
    registers->setRegisterPair(rgstrPair, immediateValue);
}

void EmuAlu::LD(MemoryAddress memoryAddress, Rgstr rgstr) {
    memory->write(getMemoryAddress(memoryAddress),registers->getRegisterValue(rgstr));
}

void EmuAlu::LD(Rgstr a, MemoryAddress memoryAddress) {
    std::uint8_t value = memory->read(getMemoryAddress(memoryAddress));
    registers->setRegister(a, value);
}

void EmuAlu::LD(MemoryAddress memoryAddress, RegisterPair rgstr) {
    memory->write(getMemoryAddress(memoryAddress),registers->getRegisterPairValue(rgstr) & 0xff);
    memory->write(getMemoryAddress(memoryAddress) + 1,registers->getRegisterPairValue(rgstr) >> 8);
}

void EmuAlu::LD(RegisterPair rgstrPair, MemoryAddress memoryAddress) {
    std::uint16_t value = memory->read(getMemoryAddress(memoryAddress)) | (memory->read(getMemoryAddress(memoryAddress) + 1) << 8);
    registers->setRegisterPair(rgstrPair, value);
}

void EmuAlu::LD(MemoryAddress memoryAddress, std::uint8_t i) {
    memory->write(getMemoryAddress(memoryAddress), i);
}

void EmuAlu::LD(Rgstr rgstr, std::uint8_t immediateValue) {
    registers->setRegister(rgstr, immediateValue);
}

void EmuAlu::LD(Rgstr destRegister, Rgstr sourceRegister) {
    std::uint8_t value =registers->getRegisterValue(sourceRegister);
    registers->setRegister(destRegister, value);

    if (destRegister == Rgstr::A && (sourceRegister == Rgstr::I || sourceRegister == Rgstr::R)) {
        setFlags(value);
    }
}

/*
 * This 2-byte instruction transfers a byte of data from the memory location
addressed by the contents of the HL register pair to the memory location
addressed by the contents of the DE register pair. Then both of these register
pairs including the BC (Byte Counter) register pair are decremented*/
void EmuAlu::LDD() {
    memory->write(registers->getDE(), memory->read(registers->getHL()));
    DEC(RegisterPair::HL);
    DEC(RegisterPair::DE);
    DEC(RegisterPair::BC);
    registers->setHFlag(false);
    registers->setNFlag(false);
    registers->setParityOverflowFlag(registers->getBC() != 0);
}

void EmuAlu::LDDR() {
    LDD();
    if (registers->getParityOverflowFlag()) {
        registers->setPC(registers->getPC() -2);
    }
}

/* A byte of data is transferred from the memory location addressed, by the
contents of the HL register pair to the memory location addressed by the
contents of the DE register pair. Then both these register pairs are
incremented and the BC (Byte Counter) register pair is decremented.*/
void EmuAlu::LDI() {
    memory->write(registers->getDE(), memory->read(registers->getHL()));
    INC(RegisterPair::HL);
    INC(RegisterPair::DE);
    DEC(RegisterPair::BC);
    registers->setHFlag(false);
    registers->setNFlag(false);
    registers->setParityOverflowFlag(registers->getBC() != 0);
}

/* This 2-byte instruction transfers a byte of data from the memory location
addressed by the contents of the HL register pair to the memory location
addressed by the DE register pair. Both these register pairs are incremented
and the BC (Byte Counter) register pair is decremented. If decrementing
causes the BC to go to zero, the instruction is terminated. If BC is not zero,
the program counter is decremented by two and the instruction is repeated.
Interrupts are recognized and two refresh cycles are executed after each
data transfer. When BC is set to zero prior to instruction execution, the
instruction loops through 64 Kbytes.*/
void EmuAlu::LDIR() {
    LDI();
    if (registers->getParityOverflowFlag()) {
        registers->setPC(registers->getPC() -2);
    }
}


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
void EmuAlu::NEG() {
    registers->setSignFlag((registers->getA() & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000));
    registers->setParityOverflowFlag(registers->getA() == 0x80);
    registers->setZeroFlag(registers->getA() == 0);
    registers->setNFlag(true);
    registers->setCFlag(registers->getA() != 0);
    registers->setA(~registers->getA() & BOOST_BINARY(11111111));
    // setHFlag(false);
}

void EmuAlu::NOP() {
//        unimplemented();
}

void EmuAlu::OR(Rgstr rgstr) {
    OR(registers->getRegisterValue(rgstr));
}

void EmuAlu::OR(std::uint8_t immediateValue) {
    std::uint8_t result = registers->getA() | immediateValue;

    registers->setA(result);

    registers->setSignFlag(result < 0);
    registers->setZeroFlag(result == 0);

    registers->setHFlag(false);

    registers->setNFlag(false);
    registers->setCFlag(false);
    // P/V
}

void EmuAlu::OR(MemoryAddress memoryAddress) {
    OR(memory->read(getMemoryAddress(memoryAddress)));
}

/*
 * The contents of the HL register pair are placed on the address bus to select a
location in memory. The byte contained in this memory location is temporarily
stored in the CPU. Then, after the byte counter (B) is decremented,
the contents of register C are placed on the bottom half (A0 through A7) of
the address bus to select the I/O device at one of 256 possible ports. Register
B may be used as a byte counter, and its decremented value is placed on
the top half (A8 through A15) of the address bus at this time. Next, the byte
to be output is placed on the data bus and written to the selected peripheral
device. Then, register pair HL is decremented and if the decremented B
register is not zero, the Program Counter (PC) is decremented by two and
the instruction is repeated. If B has gone to zero, the instruction is terminated.
Interrupts are recognized and two refresh cycles are executed after
each data transfer.
Note: When B is set to zero prior to instruction execution, the instruction
outputs 256 bytes of data.*/
void EmuAlu::OTDR() {
    OUTD();
    if (registers->getB() != 0) {
        registers->setPC(registers->getPC() -2);
    }
}

void EmuAlu::OTIR() {
    OUTI();
    if (registers->getB() != 0) {
        registers->setPC(registers->getPC() -2);
    }
}

/**
 * The operand n is placed on the bottom half (A0 through A7) of the address
 * bus to select the I/O device at one of 256 possible ports. The contents
 * of the Accumulator (rgstr A) also appear on the top half (A8 through
 * A15) of the address bus at this time. Then the byte contained in the
 * Accumulator is placed on the data bus and written to the selected
 * peripheral device.
 */
void EmuAlu::out(MemoryAddress address, Rgstr rgstr) {
    writeIO(getMemoryAddress(address),registers->getRegisterValue(rgstr));
}

/**
 * The contents of the HL register pair are placed on the address bus to select a
location in memory. The byte contained in this memory location is
temporarily stored in the CPU. Then, after the byte counter (B) is
decremented, the contents of register C are placed on the bottom half (A0
through A7) of the address bus to select the I/O device at one of 256
possible ports. Register B may be used as a byte counter, and its
decremented value is placed on the top half (A8 through A15) of the
address bus at this time. Next, the byte to be output is placed on the data bus
and written to the selected peripheral device. Finally, the register pair HL is
decremented.
*/
void EmuAlu::OUTD() {
    std::uint8_t value = memory->read(registers->getHL());
    DEC(Rgstr::B);
    writeIO(registers->getC(), value);
    DEC(RegisterPair::HL);
}

/*
 * The contents of the HL register pair are placed on the address bus to select a
location in memory. The byte contained in this memory location is
temporarily stored in the CPU. Then, after the byte counter (B) is
decremented, the contents of register C are placed on the bottom half (A0
through A7) of the address bus to select the I/O device at one of 256
possible ports. Register B may be used as a byte counter, and its
decremented value is placed on the top half (A8 through A15) of the
address bus. The byte to be output is placed on the data bus and written to a
selected peripheral device. Finally, the register pair HL is incremented.*/
void EmuAlu::OUTI() {
    std::uint8_t value = memory->read(registers->getHL());
    DEC(Rgstr::B);
    writeIO(registers->getC(), value);
    INC(RegisterPair::HL);
}

/**
 * The top two bytes of the external memory LIFO (last-in, first-out) Stack
 * are popped to rgstr pair qq. The Stack Pointer (SP) rgstr pair
 * holds the 16-bit address of the current top of the Stack. This
 * instruction first loads to the low order portion of qq, the byte at
 * memory location corresponding to the contents of SP; then SP is
 * incremented and the contents of the corresponding adjacent memory
 * location are loaded to the high order portion of qq and the SP is now
 * incremented again.
 */
void EmuAlu::POP(RegisterPair rgstr) {
    std::uint8_t lo = memory->read(registers->getSP());
    incrementSP();
    std::uint8_t hi = memory->read(registers->getSP());
    incrementSP();
    registers->setRegisterPair(rgstr, lo, hi);
}

/**
 * The contents of the Index Rgstr IX are pushed to the external memory
 * LIFO (last-in, first-out) Stack. The Stack Pointer (SP) rgstr pair
 * holds the 16-bit address of the current top of the Stack. This
 * instruction first decrements SP and loads the high order byte of IX to
 * the memory address specified by SP; then decrements SP again and loads
 * the low order byte to the memory location corresponding to this new
 * address in SP.
 *
 */
void EmuAlu::PUSH(RegisterPair valueRegister) {
    std::uint16_t value =registers->getRegisterPairValue(valueRegister);
    decrementSP();
    memory->write(registers->getSP(), value >> 8);
    decrementSP();
    memory->write(registers->getSP(), value & 0xff);
}

/* resets a bit */
void EmuAlu::RES(std::uint8_t y, Rgstr rgstr) {
    registers->setRegister(rgstr,registers->getRegisterValue(rgstr) & (BOOST_BINARY(11111111) ^ (1 << y)));
}

void EmuAlu::RES(std::uint8_t i, MemoryAddress memoryAddress) {
    std::uint8_t currentMemoryContents = memory->read(getMemoryAddress(memoryAddress));
    memory->write(getMemoryAddress(memoryAddress), currentMemoryContents & (BOOST_BINARY(11111111) ^ (1 << i)));
}

/**
 * If condition cc is true, the byte at the memory location specified by the
 * contents of the Stack Pointer (SP) rgstr pair is moved to the low
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
void EmuAlu::RET(Condition condition) {
    logger.debug("RET cc[y]");
    if (isConditionTrue(condition)) {
        RET();
    }
}

void EmuAlu::RET() {
    // TODO: this doesn't quite follow what the spec says.
    // shouldn't wipe out high order when setting low order
    registers->setPC(memory->read(registers->getSP())); // set low order
    incrementSP();
    registers->setPC(memory->read(registers->getSP()) << 8 | registers->getPC()); // set
    // high
    // order
    incrementSP();
}

/* Return from Interrupt */
void EmuAlu::RETI() {
    unimplemented("RETI");
}

/* Return from non maskable interrupt */
void EmuAlu::RETN() {
    unimplemented("RETN");
}

/*
 * The contents of the m operand are rotated left 1-bit position. The content of
bit 7 is copied to the Carry flag and the previous content of the Carry flag is
copied to bit 0.
*/
void EmuAlu::RL(MemoryAddress memoryAddress) {
    unimplemented("RL");
}

/**
 * The contents of the m operand are rotated left 1-bit position. The content of
 * bit 7 is copied to the Carry flag and the previous content of the Carry flag is
 * copied to bit 0.
 */
void EmuAlu::RL(Rgstr r) {
    unimplemented("RL");
}

/**
 * The contents of the Accumulator (rgstr A) are rotated left 1-bit
 * position through the Carry flag. The previous content of the Carry flag
 * is copied to bit 0. Bit 0 is the least-significant bit.
 */
void EmuAlu::RLA() {
    std::uint8_t tempA = registers->getA();
    registers->setA(((registers->getA() << 1) & BOOST_BINARY(11111111)) | (registers->getCFlag() ? 1 : 0));
    registers->setCFlag((tempA & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000));
}

void EmuAlu::RLC(MemoryAddress memoryAddress) {
    unimplemented("RLC");
}

void EmuAlu::RLC(Rgstr rgstr) {
    unimplemented("RLC");
}

/**
 * The contents of the Accumulator (rgstr A) are rotated left 1-bit
 * position. The sign bit (bit 7) is copied to the Carry flag and also to
 * bit 0. Bit 0 is the least-significant bit.
 * <p/>
 * S is not affected Z is not affected H is reset P/V is not affected N is
 * reset C is data from bit 7 of Accumulator
 */
void EmuAlu::RLCA() {
    registers->setA(((registers->getA() << 1) & BOOST_BINARY(11111111)) | ((registers->getA() >> (8 - 1)) & BOOST_BINARY(00000001)));
    registers->setCFlag((registers->getA() & BOOST_BINARY(1)) == 1);
}

void EmuAlu::RLD() {
    unimplemented("RLD");
}

void EmuAlu::RR(MemoryAddress memoryAddress) {
    unimplemented("RR");
}

void EmuAlu::RR(Rgstr r) {
    unimplemented("RR");
}

/**
 * The contents of the Accumulator (rgstr A) are rotated right 1-bit
 * position through the Carry flag. The previous content of the Carry flag
 * is copied to bit 7. Bit 0 is the least-significant bit.
 */
void EmuAlu::RRA() {

    std::uint8_t f2 = registers->getCFlag() ? BOOST_BINARY(1) : 0;
    registers->setCFlag((BOOST_BINARY(1) & registers->getA()) == 1);
    registers->setA((registers->getA() >> 1) | (f2 << (8 - 1)));
}

void EmuAlu::RRC(MemoryAddress memoryAddress) {
    unimplemented("RRC");
}

void EmuAlu::RRC(Rgstr r) {
    unimplemented("RRC");
}

/**
 * The contents of the Accumulator (rgstr A) are rotated right 1-bit
 * position. Bit 0 is copied to the Carry flag and also to bit 7. Bit 0 is
 * the least- significant bit.
 */
void EmuAlu::RRCA() {
    registers->setCFlag((BOOST_BINARY(1) & registers->getA()) == 1);
    registers->setA((registers->getA() >> 1) | ((registers->getA() << (8 - 1)) & BOOST_BINARY(10000000)));
    registers->setNFlag(false);
}

/**
 * The contents of the low order four bits (bits 3, 2, 1, and 0) of memory
 * location (HL) are copied to the low order four bits of the Accumulator
 * (rgstr A). The previous contents of the low order four bits of the
 * Accumulator are copied to the high order four bits (7, 6, 5, and 4) of
 * location (HL); and the previous contents of the high order four bits of
 * (HL) are copied to the low order four bits of (HL). The contents of the
 * high order bits of the Accumulator are unaffected.
 */
void EmuAlu::RRD() {
    std::uint8_t priorMemory = memory->read(registers->getHL());
    std::uint8_t priorAccumulator = registers->getA();

    registers->setA((priorMemory & BOOST_BINARY(1111)) | (priorAccumulator & BOOST_BINARY(11110000)));

    memory->write(registers->getHL(),
                  (priorMemory >> 4) | ((priorAccumulator & BOOST_BINARY(1111)) << 4));
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
 */
void EmuAlu::RST(std::uint8_t p) {
    pushPCtoStack();
    registers->setPC(p);
}

/*
 * The contents of the register pair ss (any of register pairs BC, DE, HL, or
SP) and the Carry Flag (C flag in the F register) are subtracted from the
contents of register pair HL, and the result is stored in HL. Operand ss is
specified as follows in the assembled object code.
Register
Pair ss
BC 00
DE 01
HL 10
SP 11*/
void EmuAlu::SBC(RegisterPair h1, RegisterPair h2) {
    uint16_t result = registers->getRegisterPairValue(h1) -registers->getRegisterPairValue(h2) - (registers->getCFlag() ? 1 : 0);
    registers->setRegisterPair(h1, result);
}

void EmuAlu::SBC(Rgstr a, MemoryAddress memoryAddress) {
    unimplemented("SBC");
}

void EmuAlu::SBC(Rgstr a, std::uint8_t nextByte) {
    unimplemented("SBC");
}

void EmuAlu::SBC(Rgstr a, Rgstr b) {
    unimplemented("SBC");
}

void EmuAlu::SCF() {
    /* The Carry flag in the F rgstr is set. */
    /*-
     * S is not affected
    Z is not affected
    H is reset
    P/V is not affected
    N is reset
    C is set
     */
    registers->setHFlag(false);
    registers->setCFlag(true);
    registers->setNFlag(false);
}

/**
 * Bit b in rgstr r (any of rgstrs B, C, D, E, H, L, or A) is set.
 * Operands b and r are specified as follows in the assembled object code:
 * <p/>
 * <p/>
 * Bit b in the memory location addressed by the contents of rgstr pair
 * HL is set.
 */
void EmuAlu::SET(std::uint8_t y, Rgstr rgstr) {
    registers->setRegister(rgstr,registers->getRegisterValue(rgstr) | (1 << y));
}

void EmuAlu::SET(std::uint8_t i, MemoryAddress memoryAddress) {
    std::uint8_t currentMemoryContents = memory->read(getMemoryAddress(memoryAddress));
    memory->write(getMemoryAddress(memoryAddress), currentMemoryContents | (1 << i));
}

void EmuAlu::SLA(MemoryAddress memoryAddress) {
    unimplemented("SLA");
}

void EmuAlu::SLA(Rgstr r) {
    unimplemented("SLA");
}

void EmuAlu::SRA(MemoryAddress memoryAddress) {
    unimplemented("SRA");
}

void EmuAlu::SRA(Rgstr r) {
    unimplemented("SRA");
}

void EmuAlu::SRL(MemoryAddress memoryAddress) {
    unimplemented("SRL");
}

/**
 * The contents of operand m are shifted right 1-bit position. The content of
 * bit 0 is copied to the Carry flag, and bit 7 is reset. Bit 0 is the least-
 * significant bit.
 *
 */
void EmuAlu::SRL(Rgstr m) {
    std::uint8_t val =registers->getRegisterValue(m);
    registers->setCFlag((val & 1) == 1);
    registers->setRegister(m, val >> 1);
}

/*
 * For SUB instructions
 * S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is set if borrow from bit 4; reset otherwise
P/V is set if overflow; reset otherwise
N is set
C is set if borrow; reset otherwise
*/
void EmuAlu::SUB(Rgstr reg) {
    SUB(registers->getRegisterValue(reg));
}

// TODO: flags incomplete
void EmuAlu::SUB(std::uint8_t n) {
    std::int8_t result = registers->getA() - n;
    registers->setA(result);
    
    registers->setSignFlag(result < 0);
    registers->setZeroFlag(result == 0);

    registers->setHFlag(true);

    registers->setNFlag(true);
    registers->setCFlag(false);
    // P/V
}

void EmuAlu::SUB(MemoryAddress memoryAddress) {
    SUB(memory->read(getMemoryAddress(memoryAddress)));
}

void EmuAlu::XOR(Rgstr val) {
    XOR(registers->getRegisterValue(val));
}

/*
 * S is set if result is negative; reset otherwise
* Z is set if result is zero; reset otherwise
* H is reset
* P/V is set if parity even; reset otherwise
* N is reset
* C is reset
*/
void EmuAlu::XOR(std::uint8_t val) {
    //TODO: Update tests to test flags!
    std::uint8_t newvalue = (registers->getA() ^ val);
    registers->setA(newvalue);

    registers->setSignFlag(newvalue < 0);
    registers->setZeroFlag(newvalue == 0);

    registers->setHFlag(false);
    registers->setNFlag(false);
    registers->setCFlag(false);

    //TODO: set parity flag!
}

void EmuAlu::XOR(MemoryAddress memoryAddress) {
    XOR(memory->read(getMemoryAddress(memoryAddress)));
}

void EmuAlu::decrementSP() {
    registers->setSP(registers->getSP() - 1);
}

void EmuAlu::incrementSP() {
    registers->setSP(registers->getSP() + 1);
}

bool EmuAlu::isConditionTrue(Condition condition) {
    bool retval = false;
    if (condition == Condition::NZ) {
        retval = !registers->getZeroFlag();
    } else if (condition == Condition::Z) {
        retval = registers->getZeroFlag();
    } else if (condition == Condition::NC) {
        retval = !registers->getCFlag();
    } else if (condition == Condition::C) {
        retval = registers->getCFlag();
    } else if (condition == Condition::PO) {
        retval = !registers->getParityOverflowFlag();
    } else if (condition == Condition::PE) {
        retval = registers->getParityOverflowFlag();
    } else if (condition == Condition::P) {
        retval = !registers->getSignFlag();
    } else if (condition == Condition::M) {
        retval = registers->getSignFlag();
    }
    logger.debug(retval ? "True" : "False");
    return retval;
}

void EmuAlu::pushPCtoStack() {
    decrementSP();
    memory->write(registers->getSP(), (registers->getPC() >> 8));
    decrementSP();
    memory->write(registers->getSP(), (registers->getPC() & 0xff));
}

std::uint8_t EmuAlu::readIO(std::uint16_t address) {
    return io->read(address);
}

void EmuAlu::unimplemented(std::string opcode) {
    std::cout << "Unimplemented - " << opcode << std::endl;
//     throw  UnimplementedInstructionException();
}

void EmuAlu::writeIO(std::uint16_t address, std::uint8_t value) {
//    logger.debug("Writing IO: addr:" + address + " val:" + value);
    io->write(address, value);
}

std::uint16_t EmuAlu::getMemoryAddress(MemoryAddress memoryAddress) {
    std::uint16_t address = 0;
    if (memoryAddress.getRegister() != Rgstr::unknown) {
        address = registers->getRegisterValue(memoryAddress.getRegister());
        if (memoryAddress.getOffset() > 0) {
            address += memoryAddress.getOffset();
        }
    } else if (memoryAddress.getRegisterPair() != RegisterPair::unknown) {
        address = registers->getRegisterPairValue(memoryAddress.getRegisterPair());
        if (memoryAddress.getOffset() > 0) {
            address += memoryAddress.getOffset();
        }
    } else if (memoryAddress.getMemoryAddress() > 0) {
        address = memoryAddress.getMemoryAddress();
    }
    return address;
}

void EmuAlu::setFlags(std::uint8_t value) {
    /*- S is set if I-Rgstr is negative; reset otherwise
    Z is set if I-Rgstr is zero; reset otherwise
    H is reset
    P/V contains contents of IFF2
    N is reset
    C is not affected
    If an interrupt occurs during execution of this instruction, the Parity
    flag contains a 0.
     */

    registers->setSignFlag((value & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000));
    registers->setZeroFlag(value == 0);
    registers->setHFlag(false);
    registers->setParityOverflowFlag(registers->isIFF2());
    registers->setNFlag(false); // N
}
