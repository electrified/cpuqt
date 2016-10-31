#define SPDLOG_DEBUG_ON

#include "catch.hpp"
#include <boost/utility/binary.hpp>
#include "spdlog/spdlog.h"

#include "../Z80/processor.h"
#include "../Z80/BadgerMemory.h"
#include "../Z80/Register.hpp"
#include "../Z80/RegisterPair.hpp"
#include "mocks/test_computer.h"
#include "../Z80/utils.h"

// std::shared_ptr<spdlog::logger> logger = spdlog::get("console");

std::unique_ptr<TestComputer> setupComputer() {
  std::unique_ptr<TestComputer> proc(new TestComputer());
  return proc;
}

/*
 * If the Accumulator contents are 16H, the Carry Flag is set, the HL register
pair contains 6666H, and address 6666H contains 10H, at execution of
ADC A, (HL) the Accumulator contains 27H.
*/
TEST_CASE("ADCA (HL)", "Instructions") {
  //    std::unique_ptr<TestComputer> comp = setupComputer();
  TestComputer *comp = new TestComputer();
  comp->getMemory()->write(0x0, 0x8E);
  comp->getMemory()->write(0x6666, 0x10);
  comp->getProcessor()->getRegisters()->setA(0x16);
  comp->getProcessor()->getRegisters()->setHL(0x6666);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x27);
}

TEST_CASE("ADCA_IX_d_Test", "Instructions") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  // ADC A, (IX+d)
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0x8E);
  comp->getMemory()->write(0x2, 0x10);
  comp->getMemory()->write(0x6676, 0x10);
  comp->getProcessor()->getRegisters()->setIX(0x6666);
  comp->getProcessor()->getRegisters()->setA(0x16);
  //        comp->getProcessor()->getRegisters()->setHL(0x6666);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x27);
}

TEST_CASE("ADCAnTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();

  // ADC A, n
  comp->getMemory()->write(0x0, 0xCE);
  comp->getMemory()->write(0x1, 0xAF);
  comp->getProcessor()->getRegisters()->setA(0x16);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0xC6);
}

TEST_CASE("ADCAnTest2") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCE);
  comp->getMemory()->write(0x1, 0xA5); // immediate value
  comp->getProcessor()->getRegisters()->setA(0x17);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0xbd);
}

TEST_CASE("ADCArTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();

  // ADC A, B
  comp->getMemory()->write(0x0, BOOST_BINARY(10001000));
  comp->getProcessor()->getRegisters()->setA(0x16);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->getRegisters()->setB(0x99);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0xB0);
}

TEST_CASE("ADCArTest2") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(10001011)); // E register
  comp->getProcessor()->getRegisters()->setE(0x16);
  comp->getProcessor()->getRegisters()->setA(0xa8);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0xbf);
}

TEST_CASE("ADD HL ss") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  // add hl, de
  comp->getMemory()->write(0x0, BOOST_BINARY(00011001));

  comp->getProcessor()->getRegisters()->setDE(0xffff);
  comp->getProcessor()->getRegisters()->setHL(0x4000);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x3fff);
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag() == true);
}

TEST_CASE("ADD A, n") {
/* If the Accumulator contains 23h , then upon the execution of an ADD A, 33h instruction,
the Accumulator contains 56h.*/
  std::unique_ptr<TestComputer> comp = setupComputer();

  comp->getMemory()->write(0x0, 0xC6);
  comp->getMemory()->write(0x1, 0x33);
  comp->getProcessor()->getRegisters()->setA(0x23);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x56);
//   REQUIRE(comp->getProcessor()->getRegisters()->getCFlag() == true);
}

TEST_CASE("ADD A, r") {
/* If the Accumulator contains 44h and Register C contains 11h , then upon the execution of
an ADD A, C instruction, the Accumulator contains 55h .*/
  std::unique_ptr<TestComputer> comp = setupComputer();

  comp->getMemory()->write(0x0, BOOST_BINARY(10000001));
  comp->getProcessor()->getRegisters()->setA(0x44);
  comp->getProcessor()->getRegisters()->setC(0x11);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x55);
//   REQUIRE(comp->getProcessor()->getRegisters()->getCFlag() == true);
}

TEST_CASE("ADD A, (HL)") {
/* If the Accumulator contains A0h , register pair HL contains 2323h , and memory location
2323h contains byte 08h , then upon the execution of an ADD A, (HL) instruction, the
Accumulator contains A8h. */
  std::unique_ptr<TestComputer> comp = setupComputer();

  comp->getMemory()->write(0x0, 0x86);
  comp->getProcessor()->getRegisters()->setA(0xa0);
  comp->getProcessor()->getRegisters()->setHL(0x2323);
    comp->getMemory()->write(0x2323, 0x08);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0xA8);
//   REQUIRE(comp->getProcessor()->getRegisters()->getCFlag() == true);
}


TEST_CASE("EXAFAFprimeTest") {
  /*
   * If the content of register pair AF is number 9900H , and the content
   * of register pair AF' is number 5944H , at instruction EX AF , AF' the
   * contents of AF is 5944H , and the contents of AF' is 9900H .
   */
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x08);
  comp->getProcessor()->getRegisters()->setAF(0x9900);
  comp->getProcessor()->getRegisters()->setAF_alt(0x5944);

  REQUIRE(comp->getProcessor()->getRegisters()->getAF() == 0x9900);
  REQUIRE(comp->getProcessor()->getRegisters()->getAF_alt() == 0x5944);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getAF() == 0x5944);
  REQUIRE(comp->getProcessor()->getRegisters()->getAF_alt() == 0x9900);
}

TEST_CASE("BITb_HL_Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(01100110));
  comp->getMemory()->write(0x4444, BOOST_BINARY(1111));
  comp->getProcessor()->getRegisters()->setHL(0x4444);
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  REQUIRE((comp->getMemory()->read(0x4444) & BOOST_BINARY(1000)) == BOOST_BINARY(1000));
}

/**
* If the contents of Index Register IX are 2000H, and bit 6 in memory
* location 2004H contains 1, at execution of BIT 6, (IX+4H) the Z flag in
* the F register contains 0, and bit 6 in memory location 2004H
* still contains 1. Bit 0 in memory location 2004H
* is the least-significant bit.
*/

TEST_CASE("BITb_IXplusd_Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0xCB);
  comp->getMemory()->write(0x2, 0x4);
  comp->getMemory()->write(0x3, BOOST_BINARY(01110110));
  comp->getMemory()->write(0x2004, BOOST_BINARY(1101100));
  comp->getProcessor()->getRegisters()->setIX(0x2000);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getZeroFlag());
  REQUIRE((comp->getMemory()->read(0x2004) & BOOST_BINARY(1000000)) == BOOST_BINARY(1000000));
}

TEST_CASE("CCF") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x3F);
  comp->getProcessor()->getRegisters()->setCFlag(false);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag());
}

TEST_CASE("CPL") {
  /*
   * If the contents of the Accumulator are 1011 0100 , at execution of
   * CPL the Accumulator contents are 0100 1011 .
   */
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x2F);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(10110100));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01001011));
  REQUIRE(comp->getProcessor()->getRegisters()->getHFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getNFlag());
}

/*
* If the Accumulator contains 63H, the HL register pair contains 6000H,
* and memory location 6000H contains 60H, the instruction CP (HL)
* results in the P/V flag in the F register resetting.
*/
TEST_CASE("CP r") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x6000, 0x60);
  comp->getProcessor()->getRegisters()->setHL(0x6000);
  comp->getProcessor()->getRegisters()->setA(0x63);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getPVFlag());
}

TEST_CASE("CP r Test2") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(10111101));
  comp->getMemory()->write(0x1, BOOST_BINARY(10111101)); // L
  comp->getProcessor()->getRegisters()->setA(0x17);
  comp->getProcessor()->getRegisters()->setL(0x17);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  comp->getProcessor()->getRegisters()->setA(0xFF);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getZeroFlag());
}

// CP 20
// Replicating test in spectrum rom at 0xc4e

/*
The flag register has the following structure:
Bit	7	6	5	4	3	2	1	0
Flag	S	Z	F5	H	F3	P/V	N	C
The flags are set according to the result of the last instruction. The standard behaviour is:

S - Sign flag
Set if the 2-complement value is negative (copy of MSB)
Z - Zero flag
Set if the value is zero
F5 - undocumented flag
Copy of bit 5
H - Half Carry
Carry from bit 3 to bit 4
F3 - undocumented flag
Copy of bit 3
P/V - Parity or Overflow
Parity set if even number of bits set
Overflow set if the 2-complement result does not fit in the register
N - Subtract
Set if the last operation was a subtraction
C - Carry
Set if the result did not fit in the register
*/
TEST_CASE("CP s") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFE);
  comp->getMemory()->write(0x1, 0x20);
  comp->getProcessor()->getRegisters()->setA(0x0);
  comp->getProcessor()->process();
  std::uint16_t flags = comp->getProcessor()->getRegisters()->getF();
  std::cout << (std::uint16_t)flags << std::endl;
  REQUIRE(flags == (std::uint16_t)0xA3);
  // required = 0b10100011
}

TEST_CASE("CP s Test2") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFE);
  comp->getMemory()->write(0x1, 0x80);
  comp->getProcessor()->getRegisters()->setA(0x7F); // 1111111 - 10000000
  comp->getProcessor()->process();
  std::uint16_t flags = comp->getProcessor()->getRegisters()->getF();
  std::cout << (std::uint16_t)flags << std::endl;
  REQUIRE(flags == (std::uint16_t)0x87);
  // act 0b10000010
  // req 0b10000111
}

TEST_CASE("DEC r 8Bit") {
  
  /*
   * f the D register contains byte 2AH, at execution of DEC D register D
   * contains 29H.
   */
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(00010101));
  comp->getProcessor()->getRegisters()->setD(0x2a);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getD() == 0x29);
}

TEST_CASE("DEC r 16Bit") {
  // DEC HL
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x2b);
  comp->getProcessor()->getRegisters()->setHL(0x0);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0xFFFF);
}

TEST_CASE("DEC ss") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(00101011));
  comp->getProcessor()->getRegisters()->setRegisterPair(RegisterPair::HL, 0x1001);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1000);
}

TEST_CASE("DI") {

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xF3);
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->isIFF1());
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->isIFF2());
}

TEST_CASE("DJ NZ, e") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  // LD B, 1
  comp->getMemory()->write(0x0, 0x6);
  comp->getMemory()->write(0x1, 0x1);

  // DJNZ (PC+e) 4
  comp->getMemory()->write(0x2, 0x10);
  comp->getMemory()->write(0x3, 0x4);

  comp->getMemory()->write(0x4, 0x6);
  comp->getMemory()->write(0x5, 0xEA);
  comp->getMemory()->write(0x6, 0x10);
  comp->getMemory()->write(0x7, 0x5);

  comp->getProcessor()->process(2);
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 4);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0xEA);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 13);
}

TEST_CASE("EI") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFB);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->isIFF1());
  REQUIRE(comp->getProcessor()->getRegisters()->isIFF2());
}

TEST_CASE("EX (SP) HL") {
  /*
   * If the HL register pair contains 7012H, the SP register pair contains
   * 8856H, the memory location 8856H contains byte 11H, and memory
   * location 8857H contains byte 22H, then the instruction EX (SP), HL
   * results in the HL register pair containing number 2211H, memory
   * location 8856H containing byte 12H, memory location 8857H containing
   * byte 70H and Stack Pointer containing 8856H.
   */
  std::unique_ptr<TestComputer> comp = setupComputer();
  //    comp->getProcessor()->getRegisters()->setMemory(new int[64 * 1024]);
  comp->getMemory()->write(0x8856, 0x11);
  comp->getMemory()->write(0x8857, 0x22);
  comp->getMemory()->write(0x0, 0xE3);
  comp->getProcessor()->getRegisters()->setHL(0x7012);
  comp->getProcessor()->getRegisters()->setSP(0x8856);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x2211);
  REQUIRE(comp->getMemory()->read(0x8856) == 0x12);
  REQUIRE(comp->getMemory()->read(0x8857) == 0x70);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x8856);
}

TEST_CASE("EX (SP) IX") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0xE3);
  comp->getMemory()->write(0x100, 0x90);
  comp->getMemory()->write(0x101, 0x48);
  comp->getProcessor()->getRegisters()->setIX(0x3988);
  comp->getProcessor()->getRegisters()->setSP(0x100);
  comp->getProcessor()->process(2);
  REQUIRE(comp->getProcessor()->getRegisters()->getIX() == 0x4890);
  REQUIRE(comp->getMemory()->read(0x100) == 0x88);
  REQUIRE(comp->getMemory()->read(0x101) == 0x39);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x100);
}

TEST_CASE("EX (SP) IY") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0xE3);
  comp->getMemory()->write(0x100, 0x90);
  comp->getMemory()->write(0x101, 0x48);
  comp->getProcessor()->getRegisters()->setIY(0x3988);
  comp->getProcessor()->getRegisters()->setSP(0x100);
  comp->getProcessor()->process(2);
  REQUIRE(comp->getProcessor()->getRegisters()->getIY() == 0x4890);
  REQUIRE(comp->getMemory()->read(0x100) == 0x88);
  REQUIRE(comp->getMemory()->read(0x101) == 0x39);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x100);
}

/**
* If the content of register pair DE is the number 2822H, and the content
* of the register pair HL is number 499AH, at instruction EX DE, HL the
* content of register pair DE is 499AH, and the content of register pair HL
* is 2822H.
*/

TEST_CASE("EXDEHLTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xEB);
  comp->getProcessor()->getRegisters()->setDE(0x2822);
  comp->getProcessor()->getRegisters()->setHL(0x499A);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getDE() == 0x499A);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x2822);
}

/**
* If the contents of register pair s BC, DE, and HL are the numbers 445AH ,
* 3DA2H , and 8859H , respectively, and the contents of register pairs BC',
* DE', and HL' are 0988H , 9300H , and 00E7H , respectively, at instruction
* EXX the contents of the register pair s are as follows: BC' contains
* 0988H; DE' contains 9300H ; HL contains 00E7H ; BC' contains 445AH ; DE'
* contains 3DA2H ; and HL' contains 8859H .
*/

TEST_CASE("EXX") {

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xD9);
  comp->getProcessor()->getRegisters()->setBC(0x445A);
  comp->getProcessor()->getRegisters()->setDE(0x3DA2);
  comp->getProcessor()->getRegisters()->setHL(0x8859);

  comp->getProcessor()->getRegisters()->setBC_alt(0x0988);
  comp->getProcessor()->getRegisters()->setDE_alt(0x9300);
  comp->getProcessor()->getRegisters()->setHL_alt(0x00E7);
  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 0x0988);
  REQUIRE(comp->getProcessor()->getRegisters()->getDE() == 0x9300);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x00E7);

  REQUIRE(comp->getProcessor()->getRegisters()->getBC_alt() == 0x445A);
  REQUIRE(comp->getProcessor()->getRegisters()->getDE_alt() == 0x3DA2);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL_alt() == 0x8859);
}

/*
 * If the contents of the Accumulator are 23H , and byte 7BH is available at the
 * peripheral device mapped to I/O port address 01H . At execution of INA,
 * (01H) the Accumulator contains 7BH .
 */
TEST_CASE("IN A (n)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDB);
  comp->getMemory()->write(0x1, 0x01);
  comp->getIO()->write(0x01, 0x7b);
  comp->getProcessor()->getRegisters()->setA(0x23);
  comp->getProcessor()->process();
  
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x7b);
}

TEST_CASE("INC rr") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  // increment BC
  comp->getMemory()->write(0x0, BOOST_BINARY(00000011));
  comp->getProcessor()->getRegisters()->setRegisterPair(RegisterPair::BC, 50);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 51);
}

TEST_CASE("INC r") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(00111100));
  comp->getProcessor()->getRegisters()->setRegister(Rgstr::A, 50);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 51);
}

TEST_CASE("INC ss") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  // increment BC
  comp->getMemory()->write(0x0, BOOST_BINARY(00000011));
  comp->getProcessor()->getRegisters()->setRegisterPair(RegisterPair::BC, 50);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 51);
}

TEST_CASE("INC (HL)") {
  /*
   * If the HL register pair contains 3434h and address 3434h contains 82h , then upon the
execution of an INC (HL) instruction, memory location 3434h contains 83h .*/
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x34);
  comp->getMemory()->write(0x3434, 0x82);
  comp->getProcessor()->getRegisters()->setRegisterPair(RegisterPair::HL, 0x3434);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getMemory()->read(0x3434) == 0x83);
}

TEST_CASE("JP HL") {

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0, 0xE9);

  comp->getProcessor()->getRegisters()->setL(0x45);
  comp->getProcessor()->getRegisters()->setH(0x11);

  // comp->getProcessor()->getRegisters()->setZeroFlag(false);

  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x0);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x1145);
}

TEST_CASE("JP nn") {

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0, 0xC3);
  comp->getMemory()->write(1, 0x45);
  comp->getMemory()->write(2, 0x11);
  comp->getProcessor()->getRegisters()->setZeroFlag(false);

  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x1145);
}

/*
* If condition cc is true, the instruction loads operand nn to register
* pair PC (Program Counter), and the program continues with the
* instruction beginning at address nn . If condition cc is false, the
* Program Counter is incremented as usual, and the program continues
* with the next sequential instruction. Condition cc is programmed as
* one of eight status that corresponds to condition bits in the Fl ag
* Register (register F). These eight status are defined in the table
* below that also specifies the corresponding cc bit fields in the
* assembled object code.
*/
TEST_CASE("JP NZ nn") {
  std::unique_ptr<TestComputer> comp = setupComputer();

  comp->getMemory()->write(0, BOOST_BINARY(11000010));
  comp->getMemory()->write(1, 0x45);
  comp->getMemory()->write(2, 0x11);
  comp->getProcessor()->getRegisters()->setZeroFlag(false);

  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x1145);
}

TEST_CASE("JR e") {
  /*-
   * To jump forward five locations from
  address 480, the following assembly
  language statement is used
  JR $+5

  The resulting object code and final PC value is shown below:
  Location Instruction
  480 18
  481 03
  482 -
  483 -
  484 -
  485 ← PC after jump
   */
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x480, 0x18);
  comp->getMemory()->write(0x481, 0x03);
  comp->getProcessor()->getRegisters()->setPC(0x480);

  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x480);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x485);
}

TEST_CASE("JR e negative") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x480, 0x18);
  comp->getMemory()->write(0x481, BOOST_BINARY(11111101)); // -3
  comp->getProcessor()->getRegisters()->setPC(0x480);

  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x480);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x47F);
}

TEST_CASE("JR C, e") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x480, 0x38);
  comp->getMemory()->write(0x481, 0xFA); //two's complement of 6
  comp->getProcessor()->getRegisters()->setPC(0x480);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x480);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x47C);
}

/**
* If the Accumulator contains 7AH and the BC register pair contains
* 1212H the instruction LD (BC) , A results in 7AH in memory location
* 1212H .
*/

TEST_CASE("LD_BC_ATest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x02);
  comp->getProcessor()->getRegisters()->setA(0x7A);
  comp->getProcessor()->getRegisters()->setB(0x12);
  comp->getProcessor()->getRegisters()->setC(0x12);

  REQUIRE(comp->getMemory()->read(0x1212) == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getMemory()->read(0x1212) == 0x7a);
}

/**
* If the contents of register pair DE are 1128H , and the Accumulator
* contains int A0H , the instruction LD (DE), A results in A0H in
* memory location 1128H .
*/

TEST_CASE("LD (DE), A") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x12);
  comp->getProcessor()->getRegisters()->setA(0xA0);
  comp->getProcessor()->getRegisters()->setD(0x11);
  comp->getProcessor()->getRegisters()->setE(0x28);

  //    EmulationProcessor cloneToCompare = new EmulationProcessor(proc);
  //    cloneToCompare.getMemory()->write(0x1128, 0xA0);
  //    cloneToCompare.PC += 1;

  REQUIRE(comp->getMemory()->read(0x1128) == 0x0);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x1128) == 0xA0);
}

TEST_CASE("LD (HL), n") {
  /*
   * If the HL register pair contains 4444h , the instruction LD (HL), 28h results in the mem-
ory location 4444h containing byte 28h .*/
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x36);
  comp->getMemory()->write(0x1, 0x28);
  comp->getProcessor()->getRegisters()->setHL(0x4444);

  REQUIRE(comp->getMemory()->read(0x4444) == 0x0);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x4444) == 0x28);
}


/**
* If the contents of the Accumulator are int D7H , at execution of LD
* (3141 H) , A D7H results in memory location 3141H .
*/

TEST_CASE("LD (nn), A") {

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x32);
  comp->getMemory()->write(0x1, 0x41);
  comp->getMemory()->write(0x2, 0x31);
  comp->getProcessor()->getRegisters()->setA(0xd7);

  REQUIRE(comp->getMemory()->read(0x3141) == 0x0);

  comp->getProcessor()->process(3);

  REQUIRE(comp->getMemory()->read(0x3141) == 0xd7);
}

/**
* If the content of register pair HL is 483AH , at instruction LD
* (B2291-1), HL address B229H contains 3AH , and address B22AH contains
* 48H .
*/

TEST_CASE("LD (nn), HL") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x22);
  comp->getMemory()->write(0x1, 0x29);
  comp->getMemory()->write(0x2, 0xB2);
  comp->getProcessor()->getRegisters()->setH(0x48);
  comp->getProcessor()->getRegisters()->setL(0x3A);

  REQUIRE(comp->getMemory()->read(0xB229) == 0x0);
  REQUIRE(comp->getMemory()->read(0xB22A) == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getMemory()->read(0xB229) == 0x3A);
  REQUIRE(comp->getMemory()->read(0xB22A) == 0x48);
}

TEST_CASE("LDA (BC)") {
  /*
   * If the BC register pair contains the number 4747H , and memory
   * address 4747H contains int 12H , then the instruction LD A , (BC)
   * results in int 12H in register A.
   */

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x0a);
  comp->getProcessor()->getRegisters()->setB(0x47);
  comp->getProcessor()->getRegisters()->setC(0x47);

  comp->getMemory()->write(0x4747, 0x12);

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x12);
}

TEST_CASE("LD A (DE)") {
  /*
   * If the DE register pair contains the number 30A2H and memory address
   * 30A2H contains int 22H , then the instruction LD A , (DE) results in
   * int 22H in register A
   */

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x1a);
  comp->getProcessor()->getRegisters()->setD(0x30);
  comp->getProcessor()->getRegisters()->setE(0xA2);

  comp->getMemory()->write(0x30A2, 0x22);

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x22);
}

TEST_CASE("LD A (nn)") {
  /*
   * If the contents of nn is number 8832H , and the content of memory
   * address 8832H is byte 04H , at instruction LD A , (nn) byte 04H is in
   * the Accumulator.
   */

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x3a);
  comp->getMemory()->write(0x1, 0x32);
  comp->getMemory()->write(0x2, 0x88);

  comp->getMemory()->write(0x8832, 0x04);

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x0);

  comp->getProcessor()->process(3);

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x04);
}

TEST_CASE("LDA I") {
  // The contents of the Interrupt Vector Register I are loaded to the
  // Accumulator

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x57);
  comp->getMemory()->write(0x2, 0xED);
  comp->getMemory()->write(0x3, 0x57);
  comp->getProcessor()->getRegisters()->setI(0x5f);

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x5f);

  /*- S is set if I-Register is
  negative; reset otherwise
  Z is set if I-Register is zero; reset otherwise
  H is reset
  P/V contains contents of IFF2
  N is reset
  C is not affected*/
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getSignFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getF() == 0);
  REQUIRE(comp->getProcessor()->getRegisters()->getH() == 0);
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getNFlag());

  comp->getProcessor()->getRegisters()->setI(0x81); // negative

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x81);
  REQUIRE(comp->getProcessor()->getRegisters()->getSignFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getF() == 128);
  REQUIRE(comp->getProcessor()->getRegisters()->getH() == 0);
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getNFlag());
}

TEST_CASE("LD A, R") {
  // The contents of Memory Refresh Register R are loaded to the
  // Accumulator.

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x5F);
  comp->getProcessor()->getRegisters()->setR(0xd7);

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x0);
  REQUIRE(comp->getProcessor()->getRegisters()->getF() == 0x0);
  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0xd7);
  REQUIRE(comp->getProcessor()->getRegisters()->getF() == 128);
}

TEST_CASE("LD dd, nn") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x1);
  comp->getMemory()->write(0x1, 0x45);
  comp->getMemory()->write(0x2, 0xd);
  comp->getMemory()->write(0x3, BOOST_BINARY(0010001));
  comp->getMemory()->write(0x4, 0x23);
  comp->getMemory()->write(0x5, 0x43);
  comp->getMemory()->write(0x6, BOOST_BINARY(0100001));
  comp->getMemory()->write(0x7, 0xf5);
  comp->getMemory()->write(0x8, 0x61);
  comp->getMemory()->write(0x9, BOOST_BINARY(0110001));
  comp->getMemory()->write(0xA, 0xfc);
  comp->getMemory()->write(0xB, 0x21);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getC() == 0x45);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0xd);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getE() == 0x23);
  REQUIRE(comp->getProcessor()->getRegisters()->getD() == 0x43);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getL() == 0xf5);
  REQUIRE(comp->getProcessor()->getRegisters()->getH() == 0x61);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x21fc);
}

TEST_CASE("LD HL, (nn)") {
  /*
   * If address 2045H contains 37H , and address 2046H contains A1H , at
   * instruction LD HL , (2045H) the HL register pair contains A137H .
   */

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x2a);
  comp->getMemory()->write(0x1, 0x45);
  comp->getMemory()->write(0x2, 0x20);

  comp->getMemory()->write(0x2045, 0x37);
  comp->getMemory()->write(0x2046, 0xA1);

  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0xA137);
}

/*
     * The contents of the Accumulator are loaded to the Interrupt Control
     * Vector Register, I.
     */
TEST_CASE("LD I A") {

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x47);
  comp->getProcessor()->getRegisters()->setA(0xf9);

  REQUIRE(comp->getProcessor()->getRegisters()->getF() == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getI() == 0xf9);
  REQUIRE(comp->getProcessor()->getRegisters()->getF() == 0x0);
}

/*
* The contents of the Accumulator are loaded to the Memory Refresh
* register R.
*/
TEST_CASE("LD R A") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x4F);
  comp->getProcessor()->getRegisters()->setA(0xf9);
  REQUIRE(comp->getProcessor()->getRegisters()->getR() == 0x0);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getR() == 0xf9);
  //		REQUIRE(0b0, comp->getProcessor()->getRegisters()->getF());
}

TEST_CASE("LD C A Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x4F);
  comp->getProcessor()->getRegisters()->setA(0xf9);

  REQUIRE(comp->getProcessor()->getRegisters()->getC() == 0x0);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getC() == 0xf9);
  //		REQUIRE(0b0, comp->getProcessor()->getRegisters()->getF());
}

TEST_CASE("LDrn_Test") {
  /*
   * At execution of LD E, A5H the contents of register E are A5H .
   */

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(00011110));
  comp->getMemory()->write(0x1, 0xA5);

  REQUIRE(comp->getProcessor()->getRegisters()->getE() == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getE() == 0xA5);
}

TEST_CASE("LDRR_altTest") {
  /*
   * The contents of the Accumulator are loaded to the Memory Refresh
   * register R.
   */

  std::unique_ptr<TestComputer> comp = setupComputer();

  // load a' into a
  comp->getMemory()->write(0x0, BOOST_BINARY(01100111));
  comp->getProcessor()->getRegisters()->setA(0xf9);

  REQUIRE(comp->getProcessor()->getRegisters()->getH() == 0x0);

  comp->getProcessor()->process();

  REQUIRE(comp->getProcessor()->getRegisters()->getH() == 0xf9);
}

TEST_CASE("LD SP (HL)") {
  /*
   * The contents of the Accumulator are loaded to the Memory Refresh
   * register R.
   */

  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xF9);
  comp->getProcessor()->getRegisters()->setH(0x44);
  comp->getProcessor()->getRegisters()->setL(0x2E);

  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x0);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x442E);
}

TEST_CASE("LDSPIYTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0xF9);
  comp->getProcessor()->getRegisters()->setIY(0xA227);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0xA227);
}

TEST_CASE("LD (IX+d)r Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0x77);
  comp->getMemory()->write(0x2, 0x01);
  comp->getMemory()->write(0xA228, 0x51);
  comp->getProcessor()->getRegisters()->setA(0x0);
  comp->getProcessor()->getRegisters()->setIX(0xA227);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0xA228) == 0x0);
}

TEST_CASE("NEGTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x44);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(10011000));
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01100111));
}

TEST_CASE("OUT_C_rTest") {
  /*
   * If the contents of register C are 01H, and the contents of register D
   * are 5AH, at execution of OUT (C),D byte 5AH is written to the
   * peripheral device mapped to I/O port address 01H
   */
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, BOOST_BINARY(01010001));
  comp->getProcessor()->getRegisters()->setC(0x01);
  comp->getProcessor()->getRegisters()->setD(0x5A);
  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x01) == 0x5A);
}

TEST_CASE("OUT_n_ATest") {
  /*
   * If the contents of the Accumulator are 23H , at execution of OUT (
   * 01H ), byte 23H is written to the peripheral device mapped to I/O
   * port address 01H .
   */
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xD3);
  comp->getMemory()->write(0x1, 0x01);
  comp->getProcessor()->getRegisters()->setA(0x23);
  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x01) == 0x23);
}

/**
* If the Stack Pointer contains 1000H, memory location 1000H contains 55H,
* and location 1001H contains 33H, the instruction POP IX results in Index
* Register IX containing 3355H, and the Stack Pointer containing 1002H.
*/

TEST_CASE("POPIXTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0xE1);
  comp->getMemory()->write(0x1000, 0x55);
  comp->getMemory()->write(0x1001, 0x33);
  comp->getProcessor()->getRegisters()->setSP(0x1000);
  comp->getProcessor()->process(2);
  REQUIRE(comp->getProcessor()->getRegisters()->getIX() == 0x3355);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x1002);
}

/**
* If the Stack Pointer Contains 1000H, memory location 1000H contains 55H,
* and location 1001H contains 33H, the instruction POP IY results in Index
* Register IY containing 3355H, and the Stack Pointer containing 1002H.
*/

TEST_CASE("POP IY") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0xE1);
  comp->getMemory()->write(0x1000, 0x55);
  comp->getMemory()->write(0x1001, 0x33);
  comp->getProcessor()->getRegisters()->setSP(0x1000);
  comp->getProcessor()->process(2);
  REQUIRE(comp->getProcessor()->getRegisters()->getIY() == 0x3355);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x1002);
}

/**
* If the Stack Pointer contains 1000H, memory location 1000H contains 55H,
* and location 1001H contains 33H , the instruction POP HL results in
* register pair HL containing 3355H , and the Stack Pointer containing
* 1002H
*/
TEST_CASE("POP qq") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(11100001)); // HL
  comp->getMemory()->write(0x1000, 0x55);
  comp->getMemory()->write(0x1001, 0x33);
  comp->getProcessor()->getRegisters()->setSP(0x1000);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x3355);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x1002);
}

TEST_CASE("PUSH IX") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0xE5);
  comp->getProcessor()->getRegisters()->setIX(0x2233);
  comp->getProcessor()->getRegisters()->setSP(0x1007);
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x1006) == 0x22);
  REQUIRE(comp->getMemory()->read(0x1005) == 0x33);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x1005);
}

TEST_CASE("PUSH IY") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0xE5);
  comp->getProcessor()->getRegisters()->setIY(0x2233);
  comp->getProcessor()->getRegisters()->setSP(0x1007);
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x1006) == 0x22);
  REQUIRE(comp->getMemory()->read(0x1005) == 0x33);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x1005);
}

/*
 * If the AF register pair contains 2233H
 * and the Stack Pointer contains 1007H,
 * at instruction PUSH AF memory address 1006H contains 22H,
 * memory address 1005H contains 33H,
 * and the Stack Pointer contains 1005H.
*/
TEST_CASE("PUSH") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(11110101));
  comp->getProcessor()->getRegisters()->setAF(0x2233);
  comp->getProcessor()->getRegisters()->setSP(0x1007);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x1006) == 0x22);
  REQUIRE(comp->getMemory()->read(0x1005) == 0x33);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x1005);
}

/*
 * If the S flag in the F register is set, the contents of the Program
 * Counter are 3535H, the contents of the Stack Pointer are 2000H , the
 * contents of memory location 2000H are B5H , and the contents of
 * memory location 2001H are 18H . At execution of RET M the contents of
 * the Stack Pointer is 2002H , and the contents of the Program Counter
 * is 18B5H , pointing to the address of the next program Op Code to be
 * fetched.
 */
TEST_CASE("RET cc") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getProcessor()->getRegisters()->setSignFlag(true);
  comp->getProcessor()->getRegisters()->setPC(0x3535);
  comp->getProcessor()->getRegisters()->setSP(0x2000);
  comp->getMemory()->write(0x2000, 0xB5);
  comp->getMemory()->write(0x2001, 0x18);
  comp->getMemory()->write(0x3535, BOOST_BINARY(11111000));
  comp->getProcessor()->process(1);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x2002);
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x18B5);
}

/**
 * If the contents of the Program Counter are 3535H , the contents of
 * the Stack Pointer are 2000H, the contents of memory location 2000H
 * are B5H, and the contents of memory location of memory location 2001H
 * are 18H . At execution of RET the contents of the Stack Pointer is
 * 2002H, and the contents of the Program Counter is 18B5H, pointing to
 * the address of the next program Op Code to be fetched.
 */
TEST_CASE("RET") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x3535, 0xC9);
  comp->getMemory()->write(0x2000, 0xB5);
  comp->getMemory()->write(0x2001, 0x18);
  comp->getProcessor()->getRegisters()->setPC(0x3535);
  comp->getProcessor()->getRegisters()->setSP(0x2000);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x2002);
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x18B5);
}

TEST_CASE("RLA") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(01110110));
  comp->getMemory()->write(0x0, 0x17);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getCFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(11101101));
}

TEST_CASE("RLCA") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  // increment BC
  comp->getMemory()->write(0x0, 0x07);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(10001000));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(00010001));

  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag());
}

TEST_CASE("RRA") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x1F);
  comp->getProcessor()->getRegisters()->setCFlag(false);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(11100001));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01110000));
}

TEST_CASE("RRCA") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x0F);
  comp->getProcessor()->getRegisters()->setCFlag(false);
  comp->getProcessor()->getRegisters()->setNFlag(true);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(00010001));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(10001000));
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getNFlag());
}

TEST_CASE("RRD") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x67);
  comp->getMemory()->write(0x5000, BOOST_BINARY(00100000));
  comp->getProcessor()->getRegisters()->setHL(0x5000);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(10000100));
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(10000000));
  REQUIRE(comp->getMemory()->read(0x5000) == BOOST_BINARY(01000010));
}

TEST_CASE("SCF") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x37);
  comp->getProcessor()->getRegisters()->setNFlag(true);
  comp->getProcessor()->getRegisters()->setHFlag(true);
  comp->getProcessor()->getRegisters()->setCFlag(false);

  comp->getProcessor()->process();

  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getNFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag());
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getHFlag());
}

TEST_CASE("SET b (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(11100110));
  comp->getProcessor()->getRegisters()->setHL(0x3000);
  comp->getProcessor()->process(2);
  REQUIRE((comp->getMemory()->read(0x3000) & BOOST_BINARY(10000)) == BOOST_BINARY(10000));
}

TEST_CASE("SETb_IXplusd_Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0xCB);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0x3, BOOST_BINARY(11000110));
  comp->getProcessor()->getRegisters()->setIX(0x2000);
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  comp->getProcessor()->process();
  REQUIRE((comp->getMemory()->read(0x2003) & 1) == 1);
}

/**
* If the contents of Index Register IY are 2000H, at execution of
* SET 0, (IY+3H) bit 0 in memory location 2003H is 1. Bit 0 in memory
* location 2003H is the least-significant bit.
*/

TEST_CASE("SETb_IYplusd_Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0xCB);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0x3, BOOST_BINARY(11000110));
  comp->getProcessor()->getRegisters()->setIY(0x2000);
  comp->getProcessor()->process(4);
  REQUIRE((comp->getMemory()->read(0x2003) & 1) == 1);
}

TEST_CASE("SETbrTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(11100111));
  comp->getProcessor()->process(2);
  REQUIRE((comp->getProcessor()->getRegisters()->getA() & BOOST_BINARY(10000)) == BOOST_BINARY(10000));
}

TEST_CASE("XOR s") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(10101011));
  comp->getProcessor()->getRegisters()->setE(0x96); // 10010110
  comp->getProcessor()->getRegisters()->setA(0x5D); // 01011101
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(11001011));
}

TEST_CASE("XOR (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xAE);
  comp->getMemory()->write(0x1000, 0x96); // 10010110
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getProcessor()->getRegisters()->setA(0x5D); // 01011101
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(11001011));
}

TEST_CASE("ADCA_ixplusd_Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xdd);
  comp->getMemory()->write(0x1, 0x8e);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0xa8, 0x33);
  comp->getProcessor()->getRegisters()->setA(0x17);
  comp->getProcessor()->getRegisters()->setIX(0xA5);
  comp->getProcessor()->getRegisters()->setCFlag(false);
  comp->getProcessor()->process(3);
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x4a);
}

TEST_CASE("ADCA_iyplusd_Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xfd);
  comp->getMemory()->write(0x1, 0x8e);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0xa8, 0x33);
  comp->getProcessor()->getRegisters()->setA(0x17);
  comp->getProcessor()->getRegisters()->setIY(0xA5);
  comp->getProcessor()->getRegisters()->setCFlag(false);
  comp->getProcessor()->process(3);
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x4a);
}

TEST_CASE("ADCHLssTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xed);
  comp->getMemory()->write(0x1, BOOST_BINARY(01011010)); // DE
  comp->getProcessor()->getRegisters()->setHL(0x17);
  comp->getProcessor()->getRegisters()->setDE(0x33);
  comp->getProcessor()->getRegisters()->setCFlag(true);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x4b);
}

TEST_CASE("ADD IX, pp") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, BOOST_BINARY(00001001)); // bc
  comp->getProcessor()->getRegisters()->setIX(0x333);
  comp->getProcessor()->getRegisters()->setBC(0x5555);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getIX() == 0x5888);
}

TEST_CASE("ADD IY, rr") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, BOOST_BINARY(00001001)); // bc
  comp->getProcessor()->getRegisters()->setIY(0x333);
  comp->getProcessor()->getRegisters()->setBC(0x5555);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getIY() == 0x5888);
}

const Rgstr register_array[] = {Rgstr::B, Rgstr::C, Rgstr::D, Rgstr::E, Rgstr::H, Rgstr::L, Rgstr::A};
const std::uint8_t register_values[] = {BOOST_BINARY(000), BOOST_BINARY(001), BOOST_BINARY(010), BOOST_BINARY(011), BOOST_BINARY(100), BOOST_BINARY(101), BOOST_BINARY(111)};
const std::uint8_t result[] = {BOOST_BINARY(01000011), BOOST_BINARY(01000011), BOOST_BINARY(01000011), BOOST_BINARY(01000011), BOOST_BINARY(01000011), BOOST_BINARY(01000011), BOOST_BINARY(11000011)};

TEST_CASE("AND r") {
  // base instruction - needs to be combined with a register in the lowest 3 bits
  std::uint8_t and_r = BOOST_BINARY(10100000);
  
  
  for (std::uint8_t i = 0; i < 7; i++) {
    spdlog::get("console")->debug("AND {0}", register_values[i]);
    std::unique_ptr<TestComputer> comp = setupComputer();
    comp->getMemory()->write(0x0, and_r | register_values[i]);
    comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(01111011));
    comp->getProcessor()->getRegisters()->setRegister(register_array[i], BOOST_BINARY(11000011));
    spdlog::get("console")->debug("register value {0:x}", comp->getProcessor()->getRegisters()->getRegisterValue(register_array[i]));
    comp->getProcessor()->process();
    spdlog::get("console")->debug("a value {0:x}", comp->getProcessor()->getRegisters()->getA());
    REQUIRE(comp->getProcessor()->getRegisters()->getA() == result[i]);
  }
}

TEST_CASE("AND n") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xe6);
  comp->getMemory()->write(0x1, BOOST_BINARY(01111011));
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(11000011));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01000011));
}

TEST_CASE("AND (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xa6);
  comp->getMemory()->write(0x1, 0);
  comp->getMemory()->write(0x2, 0);
  comp->getMemory()->write(0x3, 0);
  comp->getMemory()->write(0x4, BOOST_BINARY(01111011));
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(11000011));
  comp->getProcessor()->getRegisters()->setHL(0x4);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01000011));
}

TEST_CASE("AND (ix+d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xdd);
  comp->getMemory()->write(0x1, 0xa6);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0xA, BOOST_BINARY(01111011));
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(11000011));
  comp->getProcessor()->getRegisters()->setIX(0x7);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01000011));
}

TEST_CASE("AND (iy+d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xfd);
  comp->getMemory()->write(0x1, 0xa6);
  comp->getMemory()->write(0x2, 0x3);

  comp->getMemory()->write(0xA, BOOST_BINARY(01111011));
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(11000011));
  comp->getProcessor()->getRegisters()->setIY(0x7);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01000011));
}

/*
 * If the contents of Index Register are 2000H,
 * and bit 6 in memory location 2004H contains 1,
 * at execution of BIT 6, (IY+4H)
 * the Z flag and the F register still contain 0,
 * and bit 6 in memory location 2004H still contains 1.
 * Bit 0 in memory location 2004H is the least-significant bit.
*/
TEST_CASE("BIT b IY+d") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0xCB);
  comp->getMemory()->write(0x2, 0x1);
  comp->getMemory()->write(0x3, BOOST_BINARY(01001110));
  comp->getMemory()->write(0x5c3b, 0x0);
  comp->getProcessor()->getRegisters()->setIY(0x5c3a);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag() == true);
}

/*
 * If bit 2 in register B contains 0, at execution of BIT 2, B the Z flag in the
* F register contains 1, and bit 2 in register B remains 0. Bit 0 in register B is
* the least-significant bit.
*/
TEST_CASE("BIT br") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(01010000));
  comp->getProcessor()->getRegisters()->setB(BOOST_BINARY(1111011));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == BOOST_BINARY(1111011));
}

/*
If the C Flag in the F register is reset, the contents of the Program Counter
are 1A47H, the contents of the Stack Pointer are 3002H, and memory
locations have the contents:
Location Contents
1A47H D4H
1448H 35H
1A49H 21H
then if an instruction fetch sequence begins, the 3-byte instruction
D43521H is fetched to the CPU for execution. The mnemonic equivalent of
this is CALL NC, 2135H . At execution of this instruction, the contents of
memory address 3001H is 1AH, the contents of address 3000H is 4AH, the
contents of the Stack Pointer is 3000H, and the contents of the Program
Counter is 2135H, pointing to the address of the first Op Code of the
subroutine now to be executed.
 */

TEST_CASE("CALL cc nn") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x1a47, 0xd4);
  comp->getMemory()->write(0x1a48, 0x35);
  comp->getMemory()->write(0x1a49, 0x21);
  comp->getProcessor()->getRegisters()->setCFlag(false);
  comp->getProcessor()->getRegisters()->setPC(0x1a47);
  comp->getProcessor()->getRegisters()->setSP(0x3002);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x3000) == 0x4a);
  REQUIRE(comp->getMemory()->read(0x3001) == 0x1a);
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x2135);
}

/**
 * If the contents of the Program Counter are 1A47H, the contents of the Stack
 * Pointer are 3002H, and memory locations have the contents:
 * 1A47H
 * contains CDH
 * IA48H
 * contains 35H
 * 1A49H
 * contains 21H
 * If an instruction fetch sequence begins, the 3-byte instruction CD3521H is
 * fetched to the CPU for execution. The mnemonic equivalent of this is CALL
 * 2135H. At execution of this instruction, the contents of memory address
 * 3001H is 1AH, the contents of address 3000H is 4AH, the contents of the
 * Stack Pointer is 3000H, and the contents of the Program Counter is 2135H,
 * pointing to the address of the first Op Code of the subroutine now to be
 * executed.
 */

TEST_CASE("CALL nn") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x1A47, 0xCD);
  comp->getMemory()->write(0x1A48, 0x35);
  comp->getMemory()->write(0x1A49, 0x21);
  comp->getProcessor()->getRegisters()->setPC(0x1A47);
  comp->getProcessor()->getRegisters()->setSP(0x3002);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x3001) == 0x1a);
  REQUIRE(comp->getMemory()->read(0x3000) == 0x4a);
  REQUIRE(comp->getProcessor()->getRegisters()->getSP() == 0x3000);
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x2135);
}

/*
 * If the HL register pair contains 1111H,
 * memory location 1111H contains 3BH,
 * the Accumulator contains 3BH,
 * and the Byte Counter contains 0001H.
At execution of CPI the Byte Counter contains 0000H,
the HL register pair contains 1112H,
the Z flag in the F register sets,
and the P/V flag in theF register resets.
There is no effect on the contents of the Accumulator or address 1111H.
*/
TEST_CASE("CPI") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xed);
  comp->getMemory()->write(0x1, 0xa1);
  comp->getMemory()->write(0x1111, 0x3b);
  comp->getProcessor()->getRegisters()->setHL(0x1111);
  comp->getProcessor()->getRegisters()->setBC(1);
  comp->getProcessor()->getRegisters()->setA(0x3b);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 0);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1112);
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getPVFlag());
}

/*
 * If the HL register pair contains 1118H, the Accumulator contains F3H, the
Byte Counter contains 0007H, and memory locations have these contents.
( 1118H) contains 52H
( 1117H) contains 00H
( 1116H) contains F3H
Then, at execution of CPDR the contents of register pair HL are 1115H,
the contents of the Byte Counter are 0004H, the P/V flag in the F register
sets, and the Z flag in the F register sets.
*/
TEST_CASE("CPDR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  // CPDR
  comp->getMemory()->write(0x0, 0xed);
  comp->getMemory()->write(0x1, 0xb9);

  comp->getMemory()->write(0x1118, 0x52);
  comp->getMemory()->write(0x1117, 0x0);
  comp->getMemory()->write(0x1116, 0xf3);
  comp->getProcessor()->getRegisters()->setHL(0x1118);
  comp->getProcessor()->getRegisters()->setBC(0x7);
  comp->getProcessor()->getRegisters()->setA(0xf3);
  comp->getProcessor()->process(3);
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 4);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1115);
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getPVFlag());
}

/*
If the HL register pair contains 1111H, memory location 1111H contains
3BH, the Accumulator contains 3BH, and the Byte Counter contains 0001H .
At execution of CPD the Byte Counter contains 0000H, the HL register
pair contains 1110H, the flag in the F register sets, and the P/V flag in the F
register resets. There is no effect on the contents of the Accumulator or
address 1111H.
 */

TEST_CASE("CPD") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xed);
  comp->getMemory()->write(0x1, 0xa9);
  comp->getMemory()->write(0x1111, 0x3b);
  comp->getProcessor()->getRegisters()->setHL(0x1111);
  comp->getProcessor()->getRegisters()->setBC(1);
  comp->getProcessor()->getRegisters()->setA(0x3b);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 0);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1110);
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getPVFlag());
}

TEST_CASE("CPIR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xed);
  comp->getMemory()->write(0x1, 0xb1);

  comp->getMemory()->write(0x1111, 0x52);
  comp->getMemory()->write(0x1112, 0x0);
  comp->getMemory()->write(0x1113, 0xf3);
  comp->getProcessor()->getRegisters()->setHL(0x1111);
  comp->getProcessor()->getRegisters()->setBC(0x7);
  comp->getProcessor()->getRegisters()->setA(0xf3);
  comp->getProcessor()->process(3);
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 4);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1114);
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getPVFlag());
}

TEST_CASE("CP n") {
  std::unique_ptr<TestComputer> comp = setupComputer();

  comp->getMemory()->write(0x0, 0xfe);
  comp->getMemory()->write(0x1, 0x3f);

  comp->getMemory()->write(0x2, 0xfe);
  comp->getMemory()->write(0x3, 0x3f);

  comp->getProcessor()->getRegisters()->setA(0x3f);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  comp->getProcessor()->getRegisters()->setA(0xFF);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getZeroFlag());
}

TEST_CASE("CP (hl)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xbe);
  comp->getMemory()->write(0x1, 0xbe);
  comp->getMemory()->write(0x1234, 0xd6);
  comp->getProcessor()->getRegisters()->setHL(0x1234);
  comp->getProcessor()->getRegisters()->setA(0xd6);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  comp->getMemory()->write(0x1234, 0xff);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getZeroFlag());
}

TEST_CASE("CP (ix+d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xdd);
  comp->getMemory()->write(0x1, 0xbe);
  comp->getMemory()->write(0x2, 0xf);

  comp->getMemory()->write(0x3, 0xdd);
  comp->getMemory()->write(0x4, 0xbe);
  comp->getMemory()->write(0x5, 0xf);

  comp->getMemory()->write(0x1243, 0xd6);
  comp->getProcessor()->getRegisters()->setIX(0x1234);
  comp->getProcessor()->getRegisters()->setA(0xd6);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  comp->getMemory()->write(0x1243, 0xb);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getZeroFlag());
}

TEST_CASE("CP_iyplusd_Test") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xfd);
  comp->getMemory()->write(0x1, 0xbe);
  comp->getMemory()->write(0x2, 0xf);

  comp->getMemory()->write(0x3, 0xfd);
  comp->getMemory()->write(0x4, 0xbe);
  comp->getMemory()->write(0x5, 0xf);

  comp->getMemory()->write(0x1243, 0xd6);
  comp->getProcessor()->getRegisters()->setIY(0x1234);
  comp->getProcessor()->getRegisters()->setA(0xd6);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getZeroFlag());
  comp->getMemory()->write(0x1243, 0xff);
  comp->getProcessor()->process();
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getZeroFlag());
}

/**
 * If the contents of Index Register IX are 2006H, at execution of DEC IX
 the contents of Index Register IX are 2005H.
 */
TEST_CASE("DEC IX") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xdd);
  comp->getMemory()->write(0x1, 0x2b);
  comp->getProcessor()->getRegisters()->setIX(0x2006);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getIX() == 0x2005);
}

TEST_CASE("DEC IY") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xfd);
  comp->getMemory()->write(0x1, 0x2b);
  comp->getProcessor()->getRegisters()->setIY(0x2006);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getIY() == 0x2005);
}

TEST_CASE("DEC r") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(00101101)); // L
  comp->getProcessor()->getRegisters()->setL(0xFF);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getL() == 0xFE);
}

TEST_CASE("DEC (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0, 0x35);
  comp->getMemory()->write(0xffed, 0xff);
  comp->getProcessor()->getRegisters()->setHL(0xffed);
  comp->getProcessor()->process();
  std::cout << utils::int_to_hex(comp->getMemory()->read(0xffed)) << std::endl;
  REQUIRE(comp->getMemory()->read(0xffed) == 0xFE);
}

TEST_CASE("DEC (ix+d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xdd);
  comp->getMemory()->write(0x1, 0x35);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0xffed, 0xff);
  comp->getProcessor()->getRegisters()->setIX(0xffea);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0xffed) == 0xfe);
}

TEST_CASE("DEC (iy+d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xfd);
  comp->getMemory()->write(0x1, 0x35);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0xffed, 0xff);
  comp->getProcessor()->getRegisters()->setIY(0xffea);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0xffed) == 0xfe);
}

TEST_CASE("EXAFAFPrimeTest") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x08);
  comp->getProcessor()->getRegisters()->setAF(0x9900);
  comp->getProcessor()->getRegisters()->setAF_alt(0x5944);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getAF() == 0x5944);
  REQUIRE(comp->getProcessor()->getRegisters()->getAF_alt() == 0x9900);
}

TEST_CASE("HALT") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x76);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x1);
}

TEST_CASE("IM0") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x46);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getIM() == 0);
}

TEST_CASE("IM1") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x56);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getIM() == 1);
}

TEST_CASE("IM2") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x5e);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getIM() == 2);
}

/*
 * If the contents of the Accumulator are 23H, and byte 7BH is available at the
peripheral device mapped to I/O port address 01H. At execution of INA,
(01H) the Accumulator contains 7BH.
*/
TEST_CASE("IN a (n)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getIO()->write(0x1, 0x7b);
  comp->getMemory()->write(0x0, 0xDB);
  comp->getMemory()->write(0x1, BOOST_BINARY(1));
  comp->getProcessor()->getRegisters()->setA(0x23);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x7B);
}

/**
 * If the contents of register C are 07H, the contents of register B are 10H,
 * and byte 7BH is available at the peripheral device mapped to I/O port
 * address 07H . After execution of IN D, (C) register D contains 7BH.
 */

TEST_CASE("IN r (C)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getIO()->write(0x7, 0x7b);
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, BOOST_BINARY(01010000));
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x10);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getD() == 0x7B);
}

/*
 * If the HL register pair contains 1114H, the DE register pair contains
2225H, the BC register pair contains 0003H, and memory locations have
these contents:
(1114H) contains A5H (2225H) contains C5H
(1113H) contains 36H (2224H) contains 59H
(1112H) contains 88H (2223H) contains 66H
Then at execution of LDDR the contents of register pairs and memory
locations are:
HL contains 1111H
DE contains 2222H
DC contains 0000H
(1114H) contains A5H (2225H) contains A5H
(1113H) contains 36H (2224H) contains 36H
(1112H) contains 88H (2223H) contains 88H
*/
TEST_CASE("LDDR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xB8);
  comp->getProcessor()->getRegisters()->setHL(0x1114);
  comp->getProcessor()->getRegisters()->setDE(0x2225);
  comp->getProcessor()->getRegisters()->setBC(0x003);

  comp->getMemory()->write(0x1114, 0xA5);
  comp->getMemory()->write(0x1113, 0x36);
  comp->getMemory()->write(0x1112, 0x88);
  comp->getMemory()->write(0x2225, 0xC5);
  comp->getMemory()->write(0x2224, 0x59);
  comp->getMemory()->write(0x2223, 0x66);
  comp->getProcessor()->process(3);

  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1111);
  REQUIRE(comp->getProcessor()->getRegisters()->getDE() == 0x2222);
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 0x0000);
  REQUIRE(comp->getMemory()->read(0x1114) == 0xA5);
  REQUIRE(comp->getMemory()->read(0x1113) == 0x36);
  REQUIRE(comp->getMemory()->read(0x1112) == 0x88);
  REQUIRE(comp->getMemory()->read(0x2225) == 0xA5);
  REQUIRE(comp->getMemory()->read(0x2224) == 0x36);
  REQUIRE(comp->getMemory()->read(0x2223) == 0x88);
}

/*
 * If the HL register pair contains 1111H, memory location 1111H contains
byte 88H, the DE register pair contains 2222H, memory location 2222H
contains byte 66H, and the BC register pair contains 7H, then instruction
LDD results in the following contents in register pairs and memory
addresses:
HL contains 1110H
(1111H) contains 88H
DE contains 2221H
(2222H) contains 88H
BC contains 6H*/
TEST_CASE("LDD") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xA8);

  comp->getProcessor()->getRegisters()->setHL(0x1111);
  comp->getMemory()->write(0x1111, 0x88);

  comp->getProcessor()->getRegisters()->setDE(0x2222);
  comp->getMemory()->write(0x2222, 0x66);

  comp->getProcessor()->getRegisters()->setBC(0x7);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1110);
  REQUIRE(comp->getMemory()->read(0x1111) == 0x88);
  REQUIRE(comp->getProcessor()->getRegisters()->getDE() == 0x2221);
  REQUIRE(comp->getMemory()->read(0x2222) == 0x88);
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 0x6);
}

/*If the HL register pair contains 11111H, the DE register pair contains
2222H, the BC register pair contains 0003H, and memory locations have
these contents:
(1111H) contains 88H (2222H) contains 66H
(1112H) contains 36H (2223H) contains 59H
(1113H) contains A5H (2224H) contains C5H
then at execution of LDIR the contents of register pairs and memory
locations are:
HL contains 1114H
DE contains 2225H
BC contains 0000H
(1111H) contains 88H (2222H) contains 88H
(1112H) contains 36H (2223H) contains 36H
(1113H) contains A5H (2224H) contains A5H
*/
TEST_CASE("LDIR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xB0);
  comp->getProcessor()->getRegisters()->setHL(0x1111);
  comp->getProcessor()->getRegisters()->setDE(0x2222);
  comp->getProcessor()->getRegisters()->setBC(0x003);

  comp->getMemory()->write(0x1111, 0x88);
  comp->getMemory()->write(0x1112, 0x36);
  comp->getMemory()->write(0x1113, 0xA5);
  comp->getMemory()->write(0x2222, 0x66);
  comp->getMemory()->write(0x2223, 0x59);
  comp->getMemory()->write(0x2224, 0xc5);
  comp->getProcessor()->process(3);

  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1114);
  REQUIRE(comp->getProcessor()->getRegisters()->getDE() == 0x2225);
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 0x0000);
  REQUIRE(comp->getMemory()->read(0x1111) == 0x88);
  REQUIRE(comp->getMemory()->read(0x1112) == 0x36);
  REQUIRE(comp->getMemory()->read(0x1113) == 0xA5);
  REQUIRE(comp->getMemory()->read(0x2222) == 0x88);
  REQUIRE(comp->getMemory()->read(0x2223) == 0x36);
  REQUIRE(comp->getMemory()->read(0x2224) == 0xA5);
}

/*
 * If the HL register pair contains 1111H, memory location 1111H contains
byte 88H, the DE register pair contains 2222H, the memory location 2222H
contains byte 66H, and the BC register pair contains 7H, then the instruction
LDI results in the following contents in register pairs and memory addresses:
HL contains 1112H
(1111H) contains 88H
DE contains 2223H
(2222H) contains 88H
BC contains 6H*/
TEST_CASE("LDI") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xA0);

  comp->getProcessor()->getRegisters()->setHL(0x1111);
  comp->getMemory()->write(0x1111, 0x88);

  comp->getProcessor()->getRegisters()->setDE(0x2222);
  comp->getMemory()->write(0x2222, 0x66);

  comp->getProcessor()->getRegisters()->setBC(0x7);

  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1112);
  REQUIRE(comp->getMemory()->read(0x1111) == 0x88);
  REQUIRE(comp->getProcessor()->getRegisters()->getDE() == 0x2223);
  REQUIRE(comp->getMemory()->read(0x2222) == 0x88);
  REQUIRE(comp->getProcessor()->getRegisters()->getBC() == 0x6);
}

TEST_CASE("NOP") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x0);

  comp->getProcessor()->process();
  // assert all registers are the same and nothing has happened!
}

/* If the H register contains 48H (0100 0100), and the Accumulator contains
12H (0001 0010), at execution of OR H the Accumulator contains 5AH
(0101 1010).*/
TEST_CASE("OR r") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(10110100));
  comp->getProcessor()->getRegisters()->setH(BOOST_BINARY(01000100));
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(00010010));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01010110));
}

TEST_CASE("OR (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xB6);
  comp->getMemory()->write(0x1234, BOOST_BINARY(01000100));
  comp->getProcessor()->getRegisters()->setHL(0x1234);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(00010010));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01010110));
}

/* If the contents of register C are 07H, the contents of register B are 03H, the
contents of the HL register pair are 1000H, and memory locations have the
following contents:
0FFEH contains 51H
0FFFH contains A9H
1000H contains 03H
then at execution of OTDR the HL register pair contain 0FFDH, register B
contains zero, and a group of bytes is written to the peripheral device
mapped to I/O port address 07H in the following sequence:
03H
A9H
51H*/
TEST_CASE("OTDR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xBB);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x03);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getMemory()->write(0xFFE, 0x51);
  comp->getMemory()->write(0xFFF, 0xA9);
  comp->getMemory()->write(0x1000, 0x03);

  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0x03);
  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0xA9);
  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0x51);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x0FFD);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0x0);
}

/*
 * If the contents of register C are 07H, the contents of register B are 03H, the
contents of the HL register pair are 1000H, and memory locations have the
following contents:
1000H contains 51H
1001H contains A9H
1002H contains 03H
then at execution of OTIR the HL register pair contains 1003H, register B
contains zero, and a group of bytes is written to the peripheral device
mapped to I/O port address 07H in the following sequence:
51H
A9H
03H*/
TEST_CASE("OTIR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xB3);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x03);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getMemory()->write(0x1000, 0x51);
  comp->getMemory()->write(0x1001, 0xA9);
  comp->getMemory()->write(0x1002, 0x03);

  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0x51);
  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0xA9);
  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0x03);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x01003);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0x0);
}

/**
 * If the contents of register C are 07H, the contents of register B are 10H, the
 contents of the HL register pair are 1000H , and the contents of memory
 location 1000H are 59H, at execution of OUTD register B contains 0FH, the
 HL register pair contains 0FFFH, and byte 59H is written to the peripheral
 device mapped to I/O port address 07H.
 */
TEST_CASE("OUTD") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xAB);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x10);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getMemory()->write(0x1000, 0x59);

  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0x59);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x0FFF);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0x0F);
}

/*
 * If the contents of register C are 07H,
 * the contents of register B are 10H,
 * the contents of the HL register pair are 1000H,
 * and the contents of memory address 1000H are 59H,
then after the execution of OUTI
register B contains 0FH,
the HL register pair contains 1001H,
and byte 59H is written to the peripheral device mapped to I/O port address 07H.*/
TEST_CASE("OUTI") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xA3);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x10);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getMemory()->write(0x1000, 0x59);

  comp->getProcessor()->process();
  REQUIRE(comp->getIO()->read(0x7) == 0x59);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1001);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0x0F);
}

/* At execution of RES 6, D, bit 6 in register D resets. Bit 0 in register D is the
least-significant bit.*/
TEST_CASE("RES b, r") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(10110010));
  comp->getProcessor()->getRegisters()->setD(BOOST_BINARY(11111111));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getD() == BOOST_BINARY(10111111));
}

TEST_CASE("RES b, (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(10100110)); //bit 4
  comp->getMemory()->write(0x2345, BOOST_BINARY(11111111));
  comp->getProcessor()->getRegisters()->setHL(0x2345);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getMemory()->read(0x2345) == BOOST_BINARY(11101111));
}

/* Given: Two interrupting devices, with A and B connected in a daisy-chain
configuration and A having a higher priority than B.
B generates an interrupt and is acknowledged. The interrupt
enable out, IEO, of B goes Low, blocking any lower priority
devices from interrupting while B is being serviced. Then A generates
an interrupt, suspending service of B. The IEO of A goes
Low, indicating that a higher priority device is being serviced.
The A routine is completed and a RETI is issued resetting the IEO
of A, allowing the B routine to continue. A second RETI is issued
on completion of the B routine and the IE0 of B is reset (high)
allowing lower priority devices interrupt access.*/
TEST_CASE("RETI", "[!mayfail]") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  REQUIRE(true == false);
}

/* If the contents of the Stack Pointer are 1000H, and the contents of the
Program Counter are 1A45H, when a non maskable interrupt (NMI) signal
is received, the CPU ignores the next instruction and instead restarts to
memory address 0066H. The current Program Counter contents of 1A45H
is pushed onto the external stack address of 0FFFH and 0FFEH, high orderbyte
first, and 0066H is loaded onto the Program Counter. That address
begins an interrupt service routine that ends with a RETN instruction.
Upon the execution of RETN the former Program Counter contents are
popped off the external memory stack, low order first, resulting in a Stack
Pointer contents again of 1000H. The program flow continues where it
left off with an Op Code fetch to address 1A45H, order-byte first, and
0066H is loaded onto the Program Counter. That address begins an
interrupt service routine that ends with a RETN instruction. At execution of
RETN the former Program Counter contents are popped off the external
memory stack, low order first, resulting in a Stack Pointer contents again of
1000H. The program flow continues where it left off with an Op Code fetch
to address 1A45H.
*/
TEST_CASE("RETN", "[!mayfail]") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  REQUIRE(true == false);
}

TEST_CASE("RLC(HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x00, 0xCB);
  comp->getMemory()->write(0x01, 0x06);
  comp->getMemory()->write(0x2828, BOOST_BINARY(10001000));
  comp->getProcessor()->getRegisters()->setHL(0x2828);
  REQUIRE(!comp->getProcessor()->getRegisters()->getCFlag());
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x2828) == BOOST_BINARY(00010001));
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag());
}
/*
 * If the contents of the HL register pair are 5000H, and the contents of the
Accumulator and memory location 5000H are
76543210
01111010 Accumulator

76543210
00110001 (5000H)

at execution of RLD the contents of the Accumulator and memory location
5000H are
76543210
01110011 Accumulator

76543210
00011010 (5000H)
*/
TEST_CASE("RLD") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0x6F);
  comp->getMemory()->write(0x5000, BOOST_BINARY(00110001));
  comp->getProcessor()->getRegisters()->setHL(0x5000);
  comp->getProcessor()->getRegisters()->setA(BOOST_BINARY(01111010));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getMemory()->read(0x5000) == BOOST_BINARY(00011010));
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == BOOST_BINARY(01110011));
}

TEST_CASE("RRC", "[!mayfail]") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  REQUIRE(true == false);
}

/*
 *  If the contents of the HL register pair are 4343H, and the contents of
memory location 4343H and the Carry flag are

at execution of RR (HL) the contents of location 4343H and the Carry
flag are
*/
TEST_CASE("RR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, 0x1E);
  comp->getMemory()->write(0x4343, BOOST_BINARY(11011101));
  comp->getProcessor()->getRegisters()->setCFlag(false);
  comp->getProcessor()->getRegisters()->setHL(0x4343);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getMemory()->read(0x4343) == BOOST_BINARY(01101110));
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag() == true);
}

/*-
If the contents of register D and the Carry flag are
C76543210
010001111

at execution of RL D the contents of register D and the Carry flag are
C76543210
100011110
 */
TEST_CASE("RL", "[!mayfail]") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  REQUIRE(true == false);
}

TEST_CASE("RRC m", "[!mayfail]") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  REQUIRE(true == false);
}

/**
 * If the contents of the Program Counter are 15B3H, at execution of
 * RST 18H (Object code 11011111) the PC contains 0018H, as the address
 * of the next Op Code fetched.
 */
TEST_CASE("RST p") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x15B3, BOOST_BINARY(11011111));
  comp->getProcessor()->getRegisters()->setPC(0x15B3);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getPC() == 0x18);
}

TEST_CASE("SBC A r") {
  // where r is E
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(10011011)); // E
  comp->getProcessor()->getRegisters()->setE(0xDE);
  comp->getProcessor()->getRegisters()->setA(0xFF);
  comp->getProcessor()->getRegisters()->setCFlag(true); // carry
  comp->getProcessor()->process();
  spdlog::get("console")->debug("A: 0x{0:x}", comp->getProcessor()->getRegisters()->getA());
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x20);
}

TEST_CASE("SBC A n") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDE);
  comp->getMemory()->write(0x1, 0xA9);
  comp->getProcessor()->getRegisters()->setA(0xFF);
  comp->getProcessor()->getRegisters()->setCFlag(true); // carry
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x55);
}

TEST_CASE("SBC A (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x9E);
  comp->getMemory()->write(0x1, 0xA9);
  comp->getMemory()->write(0xFFED, 0xDE);
  comp->getProcessor()->getRegisters()->setA(0xFF);
  comp->getProcessor()->getRegisters()->setHL(0xFFED);
  comp->getProcessor()->getRegisters()->setCFlag(true); // carry
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x20);
}

TEST_CASE("SBC A (IX + d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0x9E);
  comp->getMemory()->write(0x2, 0x7);
  comp->getMemory()->write(0xFFED, 0xDE);
  comp->getProcessor()->getRegisters()->setA(0xFF);
  comp->getProcessor()->getRegisters()->setIX(0xFFE6);
  comp->getProcessor()->getRegisters()->setCFlag(true); // carry
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x20);
}

TEST_CASE("SBC A (IY + d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0x9E);
  comp->getMemory()->write(0x2, 0x7);
  comp->getMemory()->write(0xFFED, 0xDE);
  comp->getProcessor()->getRegisters()->setA(0xFF);
  comp->getProcessor()->getRegisters()->setIY(0xFFE6);
  comp->getProcessor()->getRegisters()->setCFlag(true); // carry
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x20);
}

/*
 * If the contents of the HL, register pair are 9999H, the contents of register
pair DE are 1111H, and the Carry flag is set. At execution of SBC HL, DE
the contents of HL are 8887H.*/
TEST_CASE("SBC HL DE") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, BOOST_BINARY(01010010));
  comp->getProcessor()->getRegisters()->setHL(0x9999);
  comp->getProcessor()->getRegisters()->setDE(0x1111);
  comp->getProcessor()->getRegisters()->setCFlag(true); // carry
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x8887);
}

TEST_CASE("SBC HL DE wrap around") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, BOOST_BINARY(01010010));
  comp->getProcessor()->getRegisters()->setHL(0x3FFF);
  comp->getProcessor()->getRegisters()->setDE(0xFFFF);
  comp->getProcessor()->getRegisters()->setCFlag(false); // carry
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x4000);
}

/*
 * If the contents of register L are
76543210
10110001

at execution of SLA L the contents of register L and the Carry flag are
C76543210
101100010
*/
TEST_CASE("SLA") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(00100101));
  comp->getProcessor()->getRegisters()->setL(BOOST_BINARY(10110001));
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getL() == BOOST_BINARY(01100010));
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag() == 1);
}

TEST_CASE("SRA", "[!mayfail]") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  REQUIRE(true == false);
}

/**
 * If the contents of register B are
 * <p/>
 * 0b10001111
 * at execution of SRL B the contents of register B and the Carry flag are
 * 0b010001111
 */
TEST_CASE("SRL") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xCB);
  comp->getMemory()->write(0x1, BOOST_BINARY(111000));
  comp->getProcessor()->getRegisters()->setB(BOOST_BINARY(10001111));
  REQUIRE_FALSE(comp->getProcessor()->getRegisters()->getCFlag());
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getCFlag());
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == BOOST_BINARY(01000111));
}

/**
 * If the Accumulator contents are 29H, and register D contains 11H, at
 * execution of SUB D the Accumulator contains 18H.
 */
TEST_CASE("SUB r") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, BOOST_BINARY(10010010));
  comp->getProcessor()->getRegisters()->setA(0x29);
  comp->getProcessor()->getRegisters()->setD(0x11);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x18);
}

TEST_CASE("SUB (HL)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x96);
  comp->getMemory()->write(0xFFED, 0x11);
  comp->getProcessor()->getRegisters()->setA(0x29);
  comp->getProcessor()->getRegisters()->setHL(0xFFED);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x18);
}

TEST_CASE("SUB (IX+d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xDD);
  comp->getMemory()->write(0x1, 0x96);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0xFFED, 0x11);
  comp->getProcessor()->getRegisters()->setA(0x29);
  comp->getProcessor()->getRegisters()->setIX(0xFFEA);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x18);
}

TEST_CASE("SUB (IY+d)") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xFD);
  comp->getMemory()->write(0x1, 0x96);
  comp->getMemory()->write(0x2, 0x3);
  comp->getMemory()->write(0xFFED, 0x11);
  comp->getProcessor()->getRegisters()->setA(0x29);
  comp->getProcessor()->getRegisters()->setIY(0xFFEA);
  comp->getProcessor()->process();
  REQUIRE(comp->getProcessor()->getRegisters()->getA() == 0x18);
}

/*
 * If the contents of register C are 07H, the contents of register B are 10H, the
contents of the HL register pair are 1000H, and byte 7BH is available at the
peripheral device mapped to I/O port address 07H. At execution of IND
memory location 1000H contains 7BH, the HL register pair contains
0FFFH, and register B contains 0FH.*/
TEST_CASE("IND") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xAA);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x10);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getIO()->write(0x7, 0x7B);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x1000) == 0x7b);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0xFFF);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0xF);
}

/*
 * If the contents of register C are 07H, the contents of register B are 03H, the
contents of the HL register pair are 1000H, and the following sequence of
bytes are available at the peripheral device mapped to I/O port address 07H:
51H
A9H
03H
then at execution of INDR the HL register pair contains 0FFDH, register B
contains zero, and memory locations contain the following:
0FFEH contains 03H
0FFFH contains A9H
1000H contains 51H
*/
TEST_CASE("INDR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xBA);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x3);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getIO()->write(0x7, 0x51);
  comp->getProcessor()->process();
  comp->getIO()->write(0x7, 0xA9);
  comp->getProcessor()->process();
  comp->getIO()->write(0x7, 0x03);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0xFFE) == 0x03);
  REQUIRE(comp->getMemory()->read(0xFFF) == 0xa9);
  REQUIRE(comp->getMemory()->read(0x1000) == 0x51);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0xFFD);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0x0);
}

/*
 * If the contents of register C are 07H, the contents of register B are 03H,
the contents of the HL register pair are 1000H, and the following
sequence of bytes are available at the peripheral device mapped to I/O
port of address 07H:
51H
A9H
03H
then at execution of INIR the HL register pair contains 1003H, register B
contains zero, and memory locations contain the following:
1000H contains 51H
1001H contains A9H
1002H contains 03H*/
TEST_CASE("INIR") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xB2);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x3);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getIO()->write(0x7, 0x51);
  comp->getProcessor()->process();
  comp->getIO()->write(0x7, 0xA9);
  comp->getProcessor()->process();
  comp->getIO()->write(0x7, 0x03);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x1002) == 0x03);
  REQUIRE(comp->getMemory()->read(0x1001) == 0xa9);
  REQUIRE(comp->getMemory()->read(0x1000) == 0x51);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1003);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0x0);
}

/* If the contents of register C are 07H, the contents of register B are 10H, the
contents of the HL register pair are 1000H, and byte 7BH is available at the
peripheral device mapped to I /O port address 07H. At execution of INI
memory location 1000H contains 7BH, the HL register pair contains
1001H, and register B contains 0FH.*/
TEST_CASE("INI") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0xED);
  comp->getMemory()->write(0x1, 0xA2);
  comp->getProcessor()->getRegisters()->setC(0x07);
  comp->getProcessor()->getRegisters()->setB(0x10);
  comp->getProcessor()->getRegisters()->setHL(0x1000);
  comp->getIO()->write(0x7, 0x7B);
  comp->getProcessor()->process();
  REQUIRE(comp->getMemory()->read(0x1000) == 0x7b);
  REQUIRE(comp->getProcessor()->getRegisters()->getHL() == 0x1001);
  REQUIRE(comp->getProcessor()->getRegisters()->getB() == 0xF);
}

/**
 * http://www.msx.org/forum/semi-msx-talk/emulation/z80-daa
 * http://wikiti.brandonw.net/?title=Z80_Instruction_Set
 *
 * If an addition operation is performed between 15 (BCD) and 27 (BCD),
simple decimal arithmetic gives this result:
15+27=42
But when the binary representations are added in the Accumulator
according to standard binary arithmetic.
0001 + 0010 = 0011
0101 + 0111 = 1100
 = 3C
the sum is ambiguous. The DAA instruction adjusts this result so that the
correct BCD representation is obtained:
0011+ 0000 =0100
1100 + 0110 = 0010
 = 42
 */
TEST_CASE("DAA", "[!mayfail]") {
  std::unique_ptr<TestComputer> comp = setupComputer();
  comp->getMemory()->write(0x0, 0x27);
  REQUIRE(true == false);
}
