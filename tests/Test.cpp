#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <boost/utility/binary.hpp>


#include "Z80/EmulationProcessor.h"
#include "Z80/BadgerMemory.h"
#include "Z80/TestIO.h"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"

EmulationProcessor* setupProcessor() {
    BadgerMemory memory;
    TestIO io;
    EmulationProcessor* proc = new EmulationProcessor(memory, io);
    return proc;
}

TEST_CASE("ADCA_HL_Test", "Instructions") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x8E);
    proc->getMemory().write(0x6666, 0x10);
    proc->setA(0x16);
    proc->setHL(0x6666);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0x27);
}


TEST_CASE("ADCA_IX_d_Test", "Instructions") {
    EmulationProcessor* proc = setupProcessor();
    // ADC A, (IX+d)
    proc->getMemory().write(0x0, 0xDD);
    proc->getMemory().write(0x1, 0x8E);
    proc->getMemory().write(0x2, 0x10);
    proc->getMemory().write(0x6676, 0x10);
    proc->setIX(0x6666);
    proc->setA(0x16);
//        proc->setHL(0x6666);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0x27);
}


TEST_CASE("ADCAnTest") {
    EmulationProcessor* proc = setupProcessor();

    // ADC A, n
    proc->getMemory().write(0x0,0xCE);
    proc->getMemory().write(0x1, 0xAF);
    proc->setA(0x16);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0xC6);
}


TEST_CASE("ADCArTest") {
    EmulationProcessor* proc = setupProcessor();

    // ADC A, B
    proc->getMemory().write(0x0,BOOST_BINARY(10001000));
    proc->setA(0x16);
    proc->setCFlag(true);
    proc->setB(0x99);
    proc->process();
    REQUIRE(proc->getA() == 0xB0);
}



TEST_CASE("ADDHLssTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00011001));

    proc->setDE(45);
    proc->setHL(12);
    proc->process();
    REQUIRE(proc->getHL() == 57);
}



TEST_CASE("EXAFAFprimeTest") {
    /*
     * If the content of register pair AF is number 9900H , and the content
     * of register pair AF' is number 5944H , at instruction EX AF , AF' the
     * contents of AF is 5944H , and the contents of AF' is 9900H .
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x08);
    proc->setAF(0x9900);
    proc->setAF_alt(0x5944);

    REQUIRE(proc->getAF() == 0x9900);
    REQUIRE(proc->getAF_alt() == 0x5944);

    proc->process();
    REQUIRE(proc->getAF() == 0x5944);
    REQUIRE( proc->getAF_alt() == 0x9900);
}



TEST_CASE("BITb_HL_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(01100110));
    proc->getMemory().write(0x4444, BOOST_BINARY(1111));
    proc->setHL(0x4444);
    proc->process();
    proc->process();
    REQUIRE(proc->getZeroFlag());
    REQUIRE((proc->getMemory().read(0x4444) & BOOST_BINARY(1000)) == BOOST_BINARY(1000));
}

/**
* If the contents of Index Register IX are 2000H, and bit 6 in memory
* location 2004H contains 1, at execution of BIT 6, (IX+4H) the Z flag in
* the F register contains 0, and bit 6 in memory location 2004H
* still contains 1. Bit 0 in memory location 2004H
* is the least-significant bit.
*/

TEST_CASE("BITb_IXplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xDD);
    proc->getMemory().write(0x1, 0xCB);
    proc->getMemory().write(0x2, 0x4);
    proc->getMemory().write(0x3, BOOST_BINARY(01110110));
    proc->getMemory().write(0x2004, BOOST_BINARY(1101100));
    proc->setIX(0x2000);
    proc->process();
    REQUIRE_FALSE(proc->getZeroFlag());
    REQUIRE((proc->getMemory().read(0x2004) & BOOST_BINARY(1000000)) == BOOST_BINARY(1000000));
}


TEST_CASE("CCFTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x3F);
    proc->setCFlag(false);

    proc->process();

    REQUIRE(proc->getCFlag());
}

TEST_CASE("CPLTest") {
    /*
     * If the contents of the Accumulator are 1011 0100 , at execution of
     * CPL the Accumulator contents are 0100 1011 .
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x2F);
    proc->setA(BOOST_BINARY(10110100));
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01001011));
    REQUIRE(proc->getHFlag());
    REQUIRE(proc->getNFlag());
}


TEST_CASE("CPrTest") {
    /*
     * If the Accumulator contains 63H, the HL register pair contains 6000H,
     * and memory location 6000H contains 60H, the instruction CP (HL)
     * results in the P/V flag in the F register resetting.
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x6000, 0x60);
    proc->setHL(0x6000);
    proc->setA(0x63);
    proc->process();
    REQUIRE_FALSE(proc->getParityOverflowFlag());
}



TEST_CASE("DECr8BitTest") {
    /*
     * f the D register contains byte 2AH, at execution of DEC D register D
     * contains 29H.
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00010101));
    proc->setD(0x2a);
    proc->process();
    REQUIRE(proc->getD() == 0x29);
}

TEST_CASE("DECssTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00101011));
    proc->setRegisterPair(RegisterPair::HL, 0x1001);
    proc->process();
    REQUIRE(proc->getHL() == 0x1000);
}

TEST_CASE("DITest") {

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xF3);
    REQUIRE_FALSE(proc->isIFF1());
    REQUIRE_FALSE(proc->isIFF2());
}

TEST_CASE("DJNZeTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x6);
    proc->getMemory().write(0x1, 0x0);
    proc->getMemory().write(0x2, 0x10);
    proc->getMemory().write(0x3, 0x4);
    proc->getMemory().write(0x4, 0x6);
    proc->getMemory().write(0x5, 0xEA);
    proc->getMemory().write(0x6, 0x10);
    proc->getMemory().write(0x7, 0x5);

    proc->process(2);
    REQUIRE(proc->getPC() == 4);
    proc->process();
    REQUIRE(proc->getB() == 0xEA);
    proc->process();
    REQUIRE(proc->getPC() == 13);
}


TEST_CASE("EITest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFB);
    proc->process();
    REQUIRE( proc->isIFF1());
    REQUIRE( proc->isIFF2());
}


TEST_CASE("EX_SP_HLTest") {
    /*
     * If the HL register pair contains 7012H, the SP register pair contains
     * 8856H, the memory location 8856H contains byte 11H, and memory
     * location 8857H contains byte 22H, then the instruction EX (SP), HL
     * results in the HL register pair containing number 2211H, memory
     * location 8856H containing byte 12H, memory location 8857H containing
     * byte 70H and Stack Pointer containing 8856H.
     */
    EmulationProcessor* proc = setupProcessor();
//    proc->setMemory(new int[64 * 1024]);
    proc->getMemory().write(0x8856, 0x11);
    proc->getMemory().write(0x8857, 0x22);
    proc->getMemory().write(0x0, 0xE3);
    proc->setHL(0x7012);
    proc->setSP(0x8856);
    proc->process();
    REQUIRE( proc->getHL() ==0x2211);
    REQUIRE( proc->getMemory().read(0x8856) == 0x12);
    REQUIRE( proc->getMemory().read(0x8857) == 0x70);
    REQUIRE( proc->getSP() == 0x8856);
}


TEST_CASE("EX_SP_IXTest") {
    EmulationProcessor* proc = setupProcessor();
//    proc->setMemory(new int[64 * 1024]);
    proc->getMemory().write(0x0, 0xDD);
    proc->getMemory().write(0x1, 0xE3);
    proc->getMemory().write(0x100, 0x90);
    proc->getMemory().write(0x101, 0x48);
    proc->setIX(0x3988);
    proc->setSP(0x100);
    proc->process(2);
    REQUIRE( proc->getIX() == 0x4890);
    REQUIRE( proc->getMemory().read(0x100) == 0x88);
    REQUIRE( proc->getMemory().read(0x101) == 0x39);
    REQUIRE( proc->getSP() == 0x100);

}


TEST_CASE("EX_SP_IYTest") {
    EmulationProcessor* proc = setupProcessor();
//    proc->setMemory(new int[64 * 1024]);
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xE3);
    proc->getMemory().write(0x100, 0x90);
    proc->getMemory().write(0x101, 0x48);
    proc->setIY(0x3988);
    proc->setSP(0x100);
    proc->process(2);
    REQUIRE( proc->getIY() == 0x4890);
    REQUIRE( proc->getMemory().read(0x100) == 0x88);
    REQUIRE( proc->getMemory().read(0x101)== 0x39);
    REQUIRE( proc->getSP()== 0x100);
}


/**
* If the content of register pair DE is the number 2822H, and the content
* of the register pair HL is number 499AH, at instruction EX DE, HL the
* content of register pair DE is 499AH, and the content of register pair HL
* is 2822H.
*/

TEST_CASE("EXDEHLTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xEB);
    proc->setDE(0x2822);
    proc->setHL(0x499A);
    proc->process();
    REQUIRE( proc->getDE() == 0x499A);
    REQUIRE( proc->getHL() == 0x2822);

}

/**
* If the conte
    void setRegister(Rgstr register, std::uint8_t value);

    void setRegisterPair(RegisterPair register, std::uint16_t sixteenBit);nts of register pair s BC, DE, and HL are the numbers 445AH ,
* 3DA2H , and 8859H , respectively, and the contents of register pairs BC',
* DE', and HL' are 0988H , 9300H , and 00E7H , respectively, at instruction
* EXX the contents of the register pair s are as follows: BC' contains
* 0988H; DE' contains 9300H ; HL contains 00E7H ; BC' contains 445AH ; DE'
* contains 3DA2H ; and HL' contains 8859H .
*/

TEST_CASE("EXXTest") {

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xD9);
    proc->setBC(0x445A);
    proc->setDE(0x3DA2);
    proc->setHL(0x8859);

    proc->setBC_alt(0x0988);
    proc->setDE_alt(0x9300);
    proc->setHL_alt(0x00E7);
    proc->process();

    REQUIRE(proc->getBC() == 0x0988 );
    REQUIRE(proc->getDE() == 0x9300 );
    REQUIRE(proc->getHL() == 0x00E7 );

    REQUIRE(proc->getBC_alt() == 0x445A);
    REQUIRE(proc->getDE_alt() == 0x3DA2);
    REQUIRE(proc->getHL_alt() == 0x8859);
}

TEST_CASE("INA_n_Test") {
    /*
     * If the contents of the Accumulator are 23H , and byte 7BH is
     * available at the peripheral device mapped to I/O port 7BH .
     * At execution of INA, (01H) the Accumulator contains 7BH.

     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xDB);
    proc->getMemory().write(0x1, 0x01);
    proc->getIO().write(0x01, 0x7b);
    proc->setA(0x23);
    proc->process();

    REQUIRE(proc->getA() == 0x7b);
}


TEST_CASE("INCr16BitTest") {
    EmulationProcessor* proc = setupProcessor();
    // increment BC
    proc->getMemory().write(0x0, BOOST_BINARY(00000011));
    proc->setRegisterPair(RegisterPair::BC, 50);
    proc->process();
    REQUIRE(proc->getBC() == 51);
}


TEST_CASE("INCr8BitTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00111100));
    proc->setRegister(Rgstr::A, 50);
    proc->process();
    REQUIRE(proc->getA() == 51);
}


TEST_CASE("INCssTest") {
    EmulationProcessor* proc = setupProcessor();
    // increment BC
    proc->getMemory().write(0x0, BOOST_BINARY(00000011));
    proc->setRegisterPair(RegisterPair::BC, 50);
    proc->process();
    REQUIRE(proc->getBC() == 51);
}


TEST_CASE("JPHLTest") {

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0, 0xE9);

    proc->setL(0x45);
    proc->setH(0x11);

    // proc->setZeroFlag(false);

    REQUIRE(proc->getPC() == 0x0);

    proc->process();
    REQUIRE( proc->getPC() == 0x1145);
}


TEST_CASE("JPnnTest") {

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0, 0xC3);
    proc->getMemory().write(1, 0x45);
    proc->getMemory().write(2, 0x11);
    proc->setZeroFlag(false);

    REQUIRE(proc->getPC() == 0);

    proc->process();
    REQUIRE(proc->getPC() == 0x1145);
}


TEST_CASE("JPNZnnTest") {
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
    EmulationProcessor* proc = setupProcessor();

    proc->getMemory().write(0, BOOST_BINARY(11000010));
    proc->getMemory().write(1, 0x45);
    proc->getMemory().write(2, 0x11);
    proc->setZeroFlag(false);

    REQUIRE(proc->getPC() == 0);

    proc->process();
    REQUIRE(proc->getPC() == 0x1145);
}


TEST_CASE("JReTest") {
    /*-
     * To jump forward five locations from
    address 480, the following assembly
    language statement is used
    JR $+5


    The resulting object code and fi
    nal PC value is shown below:
    Location Instruction
    480 18
    481 03
    482 -
    483 -
    484 -
    485 ←
    PC after jump
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x480, 0x18);
    proc->getMemory().write(0x481, 0x03);
    proc->setPC(0x480);

    REQUIRE(proc->getPC() == 0x480);

    proc->process();
    REQUIRE(proc->getPC() == 0x485);
}

/**
* If the Accumulator contains 7AH and the BC register pair contains
* 1212H the instruction LD (BC) , A results in 7AH in memory location
* 1212H .
*/

TEST_CASE("LD_BC_ATest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x02);
    proc->setA(0x7A);
    proc->setB(0x12);
    proc->setC(0x12);

    REQUIRE(proc->getMemory().read(0x1212) == 0x0);

    proc->process();

    REQUIRE(proc->getMemory().read(0x1212) == 0x7a);
}

/**
* If the contents of register pair DE are 1128H , and the Accumulator
* contains int A0H , the instruction LD (DE), A results in A0H in
* memory location 1128H .
*/

TEST_CASE("LD_DE_ATest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x12);
    proc->setA(0xA0);
    proc->setD(0x11);
    proc->setE(0x28);

//    EmulationProcessor cloneToCompare = new EmulationProcessor(proc);
//    cloneToCompare.getMemory().write(0x1128, 0xA0);
//    cloneToCompare.PC += 1;

    REQUIRE(proc->getMemory().read(0x1128) == 0x0);
    proc->process();
    REQUIRE(proc->getMemory().read(0x1128) == 0xA0);
}

/**
* If the contents of the Accumulator are int D7H , at execution of LD
* (3141 H) , A D7H results in memory location 3141H .
*/


TEST_CASE("LD_nn_ATest") {

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x32);
    proc->getMemory().write(0x1, 0x41);
    proc->getMemory().write(0x2, 0x31);
    proc->setA(0xd7);

    REQUIRE(proc->getMemory().read(0x3141) == 0x0);

    proc->process(3);

    REQUIRE(proc->getMemory().read(0x3141) == 0xd7);
}

/**
* If the content of register pair HL is 483AH , at instruction LD
* (B2291-1), HL address B229H contains 3AH , and address B22AH contains
* 48H .
*/

TEST_CASE("LD_nn_HLTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x22);
    proc->getMemory().write(0x1 , 0x29);
    proc->getMemory().write(0x2, 0xB2);
    proc->setH(0x48);
    proc->setL(0x3A);

    REQUIRE( proc->getMemory().read(0xB229) == 0x0);
    REQUIRE( proc->getMemory().read(0xB22A) == 0x0);

    proc->process();

    REQUIRE( proc->getMemory().read(0xB229) == 0x3A);
    REQUIRE( proc->getMemory().read(0xB22A) == 0x48);
}


TEST_CASE("LDA_BC_Test") {
    /*
     * If the BC register pair contains the number 4747H , and memory
     * address 4747H contains int 12H , then the instruction LD A , (BC)
     * results in int 12H in register A.
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x0a);
    proc->setB(0x47);
    proc->setC(0x47);

    proc->getMemory().write(0x4747, 0x12);

    REQUIRE( proc->getA() == 0x0);

    proc->process();

    REQUIRE( proc->getA() == 0x12);
}


TEST_CASE("LDA_DE_Test") {
    /*
     * If the DE register pair contains the number 30A2H and memory address
     * 30A2H contains int 22H , then the instruction LD A , (DE) results in
     * int 22H in register A
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x1a);
    proc->setD(0x30);
    proc->setE(0xA2);

    proc->getMemory().write(0x30A2, 0x22);

    REQUIRE(proc->getA() == 0x0);

    proc->process();

    REQUIRE(proc->getA() == 0x22);
}


TEST_CASE("LDA_nn_Test") {
    /*
     * If the contents of nn is number 8832H , and the content of memory
     * address 8832H is byte 04H , at instruction LD A , (nn) byte 04H is in
     * the Accumulator.
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x3a);
    proc->getMemory().write(0x1 , 0x32);
    proc->getMemory().write(0x2, 0x88);

    proc->getMemory().write(0x8832, 0x04);

    REQUIRE( proc->getA() == 0x0);

    proc->process(3);

    REQUIRE( proc->getA() == 0x04);
}


TEST_CASE("LDAITest") {
    // The contents of the Interrupt Vector Register I are loaded to the
    // Accumulator

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x57);
    proc->getMemory().write(0x2, 0xED);
    proc->getMemory().write(0x3, 0x57);
    proc->setI(0x5f);

    REQUIRE( proc->getA() == 0x0);

    proc->process();

    REQUIRE( proc->getA() == 0x5f);

    /*- S is set if I-Register is
    negative; reset otherwise
    Z is set if I-Register is zero; reset otherwise
    H is reset
    P/V contains contents of IFF2
    N is reset
    C is not affected*/
    REQUIRE_FALSE(proc->getSignFlag());
    REQUIRE(proc->getF() == 0);
    REQUIRE( proc->getH() == 0);
    REQUIRE_FALSE(proc->getNFlag());

    proc->setI(0x81); // negative

    proc->process();

    REQUIRE(proc->getA() == 0x81);
    REQUIRE(proc->getSignFlag());
    REQUIRE(proc->getF() == 128);
    REQUIRE(proc->getH() == 0);
    REQUIRE_FALSE(proc->getNFlag());
}


TEST_CASE("LDARTest") {
    // The contents of Memory Refresh Register R are loaded to the
    // Accumulator.

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x5F);
    proc->setR(0xd7);

    REQUIRE(proc->getA() == 0x0);
    REQUIRE(proc->getF() == 0x0);
    proc->process();

    REQUIRE( proc->getA() == 0xd7);
    REQUIRE( proc->getF() == 128);
}


TEST_CASE("LDddnnTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x1);
    proc->getMemory().write(0x1, 0x45);
    proc->getMemory().write(0x2, 0xd);
    proc->getMemory().write(0x3, BOOST_BINARY(0010001));
    proc->getMemory().write(0x4, 0x23);
    proc->getMemory().write(0x5, 0x43);
    proc->getMemory().write(0x6, BOOST_BINARY(0100001));
    proc->getMemory().write(0x7, 0xf5);
    proc->getMemory().write(0x8, 0x61);
    proc->getMemory().write(0x9, BOOST_BINARY(0110001));
    proc->getMemory().write(0xA, 0xfc);
    proc->getMemory().write(0xB, 0x21);

    proc->process();
    REQUIRE(proc->getC() == 0x45);
    REQUIRE(proc->getB() == 0xd);

    proc->process();
    REQUIRE(proc->getE() == 0x23);
    REQUIRE(proc->getD() == 0x43);

    proc->process();
    REQUIRE(proc->getL() == 0xf5);
    REQUIRE(proc->getH() == 0x61);

    proc->process();
    REQUIRE(proc->getSP() == 0x21fc);
}



TEST_CASE("LDHL_nn_Test") {
    /*
     * If address 2045H contains 37H , and address 2046H contains A1H , at
     * instruction LD HL , (2045H) the HL register pair contains A137H .
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x2a);
    proc->getMemory().write(0x1, 0x45);
    proc->getMemory().write(0x2, 0x20);

    proc->getMemory().write(0x2045, 0x37);
    proc->getMemory().write(0x2046, 0xA1);

    REQUIRE(proc->getHL() == 0x0);

    proc->process();

    REQUIRE( proc->getHL() == 0xA137);
}


TEST_CASE("LDIATest") {
    /*
     * The contents of the Accumulator are loaded to the Interrupt Control
     * Vector Register, I.
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x47);
    proc->setA(0xf9);

    REQUIRE( proc->getF() == 0x0);

    proc->process();

    REQUIRE( proc->getI() == 0xf9);
    REQUIRE( proc->getF() == 0b10000000);
}



TEST_CASE("LDRATest") {
    /*
     * The contents of the Accumulator are loaded to the Memory Refresh
     * register R.
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x4F);
    proc->setA(0xf9);

    REQUIRE(proc->getR() == 0x0);

    proc->process();
    REQUIRE(proc->getR() == 0xf9);
//		REQUIRE(0b0, proc->getF());
}


TEST_CASE("LDrn_Test") {
    /*
     * At execution of LD E , A5H the contents of register E are A5H .
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0b00011110);
    proc->getMemory().write(0x1, 0xA5);

    REQUIRE(proc->getE() == 0x0);

    proc->process();

    REQUIRE(proc->getE() == 0xA5);
}


TEST_CASE("LDRR_altTest") {
    /*
     * The contents of the Accumulator are loaded to the Memory Refresh
     * register R.
     */

    EmulationProcessor* proc = setupProcessor();

    // load a' into a
    proc->getMemory().write(0x0, 0b01100111);
    proc->setA(0xf9);

    REQUIRE(proc->getH() == 0x0);

    proc->process();

    REQUIRE(proc->getH() == 0xf9);
}


TEST_CASE("LDSP_HL_Test") {
    /*
     * The contents of the Accumulator are loaded to the Memory Refresh
     * register R.
     */

    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xF9);
    proc->setH(0x44);
    proc->setL(0x2E);

    REQUIRE(proc->getSP() == 0x0);

    proc->process();
    REQUIRE(proc->getSP() == 0x442E);
}


TEST_CASE("LDSPIYTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xF9);
    proc->setIY(0xA227);
    proc->process();
    REQUIRE(proc->getSP() == 0xA227);
}


TEST_CASE("LD_IXplusd_rTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xDD);
    proc->getMemory().write(0x1, 0x77);
    proc->getMemory().write(0x2, 0x01);
    proc->getMemory().write(0xA228, 0x51);
    proc->setA(0x0);
    proc->setIX(0xA227);
    proc->process();
    REQUIRE(proc->getMemory().read(0xA228) == 0x0);
}


TEST_CASE("NEGTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x44);
    proc->setA(0b10011000);
    proc->process();
    proc->process();
    REQUIRE(proc->getA() == 0b01100111);
}



TEST_CASE("OUT_C_rTest") {
    /*
     * If the contents of register C are 01H, and the contents of register D
     * are 5AH, at execution of OUT (C),D byte 5AH is written to the
     * peripheral device mapped to I/O port address 01H
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0b01010001);
    proc->setC(0x01);
    proc->setD(0x5A);
    proc->process();
    REQUIRE(proc->getIO().read(0x01) == 0x5A);
}


TEST_CASE("OUT_n_ATest") {
    /*
     * If the contents of the Accumulator are 23H , at execution of OUT (
     * 01H ), byte 23H is written to the peripheral device mapped to I/O
     * port address 01H .
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xD3);
    proc->getMemory().write(0x1, 0x01);
    proc->setA(0x23);
    proc->process();
    REQUIRE(proc->getIO().read(0x01) == 0x23);
}

/**
* If the Stack Pointer contains 1000H, memory location 1000H contains 55H,
* and location 1001H contains 33H, the instruction POP IX results in Index
* Register IX containing 3355H, and the Stack Pointer containing 1002H.
*/

TEST_CASE("POPIXTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xDD);
    proc->getMemory().write(0x1, 0xE1);
    proc->getMemory().write(0x1000, 0x55);
    proc->getMemory().write(0x1001, 0x33);
    proc->setSP(0x1000);
    proc->process(2);
    REQUIRE(proc->getIX() == 0x3355);
    REQUIRE(proc->getSP() == 0x1002);
}

/**
* If the Stack Pointer Contains 1000H, memory location 1000H contains 55H,
* and location 1001H contains 33H, the instruction POP IY results in Index
* Register IY containing 3355H, and the Stack Pointer containing 1002H.
*/

TEST_CASE("POPIYTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xE1);
    proc->getMemory().write(0x1000, 0x55);
    proc->getMemory().write(0x1001, 0x33);
    proc->setSP(0x1000);
    proc->process(2);
    REQUIRE(proc->getIY() == 0x3355);
    REQUIRE(proc->getSP() == 0x1002);
}

/**
* If the Stack Pointer contains 1000H, memory location 1000H contains 55H,
* and location 1001H contains 33H , the instruction POP HL results in
* register pair HL containing 3355H , and the Stack Pointer containing
* 1002H
*/

TEST_CASE("POPqqTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0b11100001); // HL
    proc->getMemory().write(0x1000, 0x55);
    proc->getMemory().write(0x1001, 0x33);
    proc->setSP(0x1000);
    proc->process();
    REQUIRE(proc->getHL() == 0x3355);
    REQUIRE(proc->getSP() == 0x1002);
}


TEST_CASE("PUSHIXTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xDD);
    proc->getMemory().write(0x1, 0xE5);
    proc->setIX(0x2233);
    proc->setSP(0x1007);
    proc->process();
    proc->process();
    REQUIRE(proc->getMemory().read(0x1006) == 0x22);
    REQUIRE(proc->getMemory().read(0x1005) == 0x33);
    REQUIRE(proc->getSP() == 0x1005);
}


TEST_CASE("PUSHIYTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xE5);
    proc->setIY(0x2233);
    proc->setSP(0x1007);
    proc->process();
    proc->process();
    REQUIRE(proc->getMemory().read(0x1006) == 0x22);
    REQUIRE(proc->getMemory().read(0x1005) == 0x33);
    REQUIRE(proc->getSP() == 0x1005);
}



TEST_CASE("RETccTest") {

    /*
     * If the S flag in the F register is set, the contents of the Program
     * Counter are 3535H, the contents of the Stack Pointer are 2000H , the
     * contents of memory location 2000H are B5H , and the contents of
     * memory location 2001H are 18H . At execution of RET M the contents of
     * the Stack Pointer is 2002H , and the contents of the Program Counter
     * is 18B5H , pointing to the address of the next program Op Code to be
     * fetched.
     */
    EmulationProcessor* proc = setupProcessor();
    proc->setSignFlag(true);
    proc->setPC(0x3535);
    proc->setSP(0x2000);
//    proc->setMemory(new int[64 * 1024]);
    proc->getMemory().write(0x2000, 0xB5);
    proc->getMemory().write(0x2001, 0x18);
    proc->getMemory().write(0x3535, BOOST_BINARY(11111000));
    proc->process(1);
    REQUIRE(proc->getSP() == 0x2002);
    REQUIRE(proc->getPC() == 0x18B5);

}

// RLC RRC RL RR SLA SRA SLL SRL
//
// TEST_CASE("ROTrTest") {
// Processor proc = new Processor();
// proc->setMemory(new int[] {});
// REQUIRE(true, false);
// }



TEST_CASE("RETTest") {
    /*
     * If the contents of the Program Counter are 3535H , the contents of
     * the Stack Pointer are 2000H, the contents of memory location 2000H
     * are B5H, and the contents of memory location of memory location 2001H
     * are 18H . At execution of RET the contents of the Stack Pointer is
     * 2002H, and the contents of the Program Counter is 18B5H, pointing to
     * the address of the next program Op Code to be fetched.
     */
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x3535, 0xC9);
    proc->getMemory().write(0x2000, 0xB5);
    proc->getMemory().write(0x2001, 0x18);
    proc->setPC(0x3535);
    proc->setSP(0x2000);
    proc->process();
    REQUIRE(proc->getSP() == 0x2002);
    REQUIRE(proc->getPC() == 0x18B5);
}


TEST_CASE("RLATest") {
    EmulationProcessor* proc = setupProcessor();
    proc->setCFlag(true);
    proc->setA(BOOST_BINARY(01110110));
    proc->getMemory().write(0x0, 0x17);
    proc->process();
    REQUIRE_FALSE( proc->getCFlag());
    REQUIRE(proc->getA() == BOOST_BINARY(11101101));
}

TEST_CASE("RLCATest") {
    EmulationProcessor* proc = setupProcessor();
    // increment BC
    proc->getMemory().write(0x0, 0x07);
    proc->setA(BOOST_BINARY(10001000));
    proc->process();
//    System.out.println(Integer.toBinaryString(proc->getA()));
    REQUIRE(proc->getA() == BOOST_BINARY(00010001));

    REQUIRE(proc->getCFlag());
}



TEST_CASE("RRATest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x1F);
    proc->setCFlag(false);
    proc->setA(BOOST_BINARY(11100001));
    proc->process();
    REQUIRE(proc->getCFlag());
    REQUIRE(proc->getA() == BOOST_BINARY(01110000));
}


TEST_CASE("RRCATest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x0F);
    proc->setCFlag(false);
    proc->setA(BOOST_BINARY(11100001));
    proc->process();
    REQUIRE(proc->getCFlag());
//    System.out.println(Integer.toBinaryString(proc->getA()));
    REQUIRE(proc->getA() == BOOST_BINARY(11110000));
}



TEST_CASE("RRDTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x67);
    proc->getMemory().write(0x5000, BOOST_BINARY(00100000));
    proc->setHL(0x5000);
    proc->setA(BOOST_BINARY(10000100));
    proc->process();
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(10000000));
    REQUIRE(proc->getMemory().read(0x5000) == BOOST_BINARY(01000010));
}



TEST_CASE("SCFTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x37);
    proc->setNFlag(true);
    proc->setHFlag(true);
    proc->setCFlag(false);

    proc->process();

    REQUIRE_FALSE(proc->getNFlag());
    REQUIRE(proc->getCFlag());
    REQUIRE_FALSE( proc->getHFlag());

}


TEST_CASE("SETb_HL_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(11100110));
    proc->setHL(0x3000);
    proc->process(2);
    REQUIRE((proc->getMemory().read(0x3000) & BOOST_BINARY(10000)) == BOOST_BINARY(10000));
}


TEST_CASE("SETb_IXplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xDD);
    proc->getMemory().write(0x1, 0xCB);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0x3, BOOST_BINARY(11000110));
    proc->setIX(0x2000);
    proc->process();
    proc->process();
    proc->process();
    proc->process();
    REQUIRE((proc->getMemory().read(0x2003) & 1) == 1);
}

/**
* If the contents of Index Register IY are 2000H, at execution of
* SET 0, (IY+3H) bit 0 in memory location 2003H is 1. Bit 0 in memory
* location 2003H is the least-significant bit.
*/

TEST_CASE("SETb_IYplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xCB);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0x3, BOOST_BINARY(11000110));
    proc->setIY(0x2000);
    proc->process(4);
    REQUIRE((proc->getMemory().read(0x2003) & 1) == 1);
}

TEST_CASE("SETbrTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, 0b11100111);
    proc->process(2);
    REQUIRE((proc->getA() & BOOST_BINARY(10000)) == BOOST_BINARY(10000));
}


TEST_CASE("XORsTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(10101011));
    proc->setE(0x96); // 10010110
    proc->setA(0x5D); // 01011101
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(11001011));
}

TEST_CASE("ADCArTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0,BOOST_BINARY(10001011)); // E register
    proc->setE(0x16);
    proc->setA(0xa8);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0xbf);
}


TEST_CASE("ADCAnTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCE);
    proc->getMemory().write(0x1, 0xA5); // immediate value
    proc->setA(0x17);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0xbd);
}


TEST_CASE("ADCA_hl_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x8e);
    proc->getMemory().write(0xa5, 0x33);
    proc->setA(0x17);
    proc->setHL(0xA5);
    proc->setCFlag(false);
    proc->process(1);
    REQUIRE(proc->getA() == 0x4a);
}


TEST_CASE("ADCA_ixplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0x8e);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0xa8, 0x33);
    proc->setA(0x17);
    proc->setIX(0xA5);
    proc->setCFlag(false);
    proc->process(3);
    REQUIRE(proc->getA() == 0x4a);
}


TEST_CASE("ADCA_iyplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfd);
    proc->getMemory().write(0x1, 0x8e);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0xa8, 0x33);
    proc->setA(0x17);
    proc->setIY(0xA5);
    proc->setCFlag(false);
    proc->process(3);
    REQUIRE(proc->getA() == 0x4a);
}


TEST_CASE("ADCHLssTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1, BOOST_BINARY(01011010)); //DE
    proc->setHL(0x17);
    proc->setDE(0x33);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getHL() == 0x4b);
}



TEST_CASE("ADDIXppTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0,0xDD);
    proc->getMemory().write(0x1, BOOST_BINARY(00001001)); // bc
    proc->setIX(0x333);
    proc->setBC(0x5555);
    proc->process();
    REQUIRE(proc->getIX() == 0x5888);
}


TEST_CASE("ADDIYrrTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, BOOST_BINARY(00001001)); // bc
    proc->setIY(0x333);
    proc->setBC(0x5555);
    proc->process();
    REQUIRE(proc->getIY() == 0x5888);
}



TEST_CASE("ANDrTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(10100000));
    proc->setB(BOOST_BINARY(01111011));
    proc->setA(BOOST_BINARY(11000011));
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("ANDnTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xe6);
    proc->getMemory().write(0x1, BOOST_BINARY(01111011));
    proc->setA(0b11000011);
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("AND_HL_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xa6);
    proc->getMemory().write(0x1, 0);
    proc->getMemory().write(0x2, 0);
    proc->getMemory().write(0x3, 0);
    proc->getMemory().write(0x4, BOOST_BINARY(01111011));
    proc->setA(0b11000011);
    proc->setHL(0x4);
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("AND_ixplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0xa6);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0x10, 0b01111011);
    proc->setA(0b11000011);
    proc->setIX(0x7);
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("AND_iyplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfd);
    proc->getMemory().write(0x1, 0xa6);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0x10, BOOST_BINARY(01111011));
    proc->setA(BOOST_BINARY(11000011));
    proc->setIY(0x7);
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}



TEST_CASE("BITb_IYplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("BITbrTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x1, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(01010000));
    proc->setB(BOOST_BINARY(1111011));
    proc->process();
    REQUIRE(proc->getZeroFlag());
    REQUIRE(proc->getB() == BOOST_BINARY(1111011));
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

TEST_CASE("CALLccnnTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x1a47, 0xd4);
    proc->getMemory().write(0x1a48,0x35);
    proc->getMemory().write(0x1a49,0x21);
    proc->setCFlag(false);
    proc->setPC(0x1a47);
    proc->setSP(0x3002);
    proc->process(3);
    REQUIRE(proc->getMemory().read(0x3000) == 0x4a);
    REQUIRE(proc->getMemory().read(0x3001) == 0x1a);
    REQUIRE(proc->getPC() == 0x2135);
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

TEST_CASE("CALLnnTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x1A47, 0xCD);
    proc->getMemory().write(0x1A48, 0x35);
    proc->getMemory().write(0x1A49, 0x21);
    proc->setPC(0x1A47);
    proc->setSP(0x3002);
    proc->process(3);
    REQUIRE(proc->getMemory().read(0x3001) == 0x1a);
    REQUIRE(proc->getMemory().read(0x3000) == 0x4a);
    REQUIRE(proc->getSP() == 0x3000);
    REQUIRE(proc->getPC() == 0x2135);
}



TEST_CASE("CPITest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1,0xa1);
    proc->getMemory().write(0x1111,0x3b);
    proc->setHL(0x1111);
    proc->setBC(1);
    proc->setA(0x3b);
    proc->process();
    REQUIRE(proc->getBC() == 0);
    REQUIRE(proc->getHL() == 0x1112);
    REQUIRE(proc->getZeroFlag());
    REQUIRE_FALSE(proc->getParityOverflowFlag());
}


TEST_CASE("CPDRTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1, 0xb9);
    proc->getMemory().write(0x1118,0x52);
    proc->getMemory().write(0x1117,0x0);
    proc->getMemory().write(0x1116,0xf3);
    proc->setHL(0x1118);
    proc->setBC(0x7);
    proc->setA(0xf3);
    proc->process();
    REQUIRE(proc->getBC() == 4);
    REQUIRE(proc->getHL() == 0x1115);
    REQUIRE(proc->getZeroFlag());
    REQUIRE(proc->getParityOverflowFlag());
}

/*
If the HL register pair contains 1111H, memory location 1111H contains
3BH, the Accumulator contains 3BH, and the Byte Counter contains 0001H .
At execution of CPD the Byte Counter contains 0000H, the HL register
pair contains 1110H, the flag in the F register sets, and the P/V flag in the F
register resets. There is no effect on the contents of the Accumulator or
address 1111H.
 */

TEST_CASE("CPDTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1,0xa9);
    proc->getMemory().write(0x1111,0x3b);
    proc->setHL(0x1111);
    proc->setBC(1);
    proc->setA(0x3b);
    proc->process();
    REQUIRE(proc->getBC() == 0);
    REQUIRE(proc->getHL() == 0x1110);
    REQUIRE(proc->getZeroFlag());
    REQUIRE_FALSE(proc->getParityOverflowFlag());
}


TEST_CASE("CPIRTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1, 0xb1);
    proc->getMemory().write(0x1111,0x52);
    proc->getMemory().write(0x1112,0x0);
    proc->getMemory().write(0x1113,0xf3);
    proc->setHL(0x1111);
    proc->setBC(0x7);
    proc->setA(0xf3);
    proc->process();
    REQUIRE(proc->getBC() == 4);
    REQUIRE(proc->getHL() == 0x1114);
    REQUIRE(proc->getZeroFlag());
    REQUIRE(proc->getParityOverflowFlag());
}



TEST_CASE("CPrTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(10111101));
    proc->getMemory().write(0x1, BOOST_BINARY(10111101)); // L
    proc->setA(0x17);
    proc->setL(0x17);
    proc->process();
    REQUIRE(proc->getZeroFlag());
    proc->setA(0xFF);
    proc->process();
    REQUIRE_FALSE(proc->getZeroFlag());
}


TEST_CASE("CPnTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfe);
    proc->getMemory().write(0x1, 0x3f);
    proc->getMemory().write(0x2, 0xfe);
    proc->getMemory().write(0x3, 0x3f);
    proc->setA(0x3f);
    proc->process(2);
    REQUIRE(proc->getZeroFlag());
    proc->setA(0xFF);
    proc->process();
    REQUIRE_FALSE(proc->getZeroFlag());
}


TEST_CASE("CP_hl_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xbe);
    proc->getMemory().write(0x1, 0xbe);
    proc->getMemory().write(0x1234, 0xd6);
    proc->setHL(0x1234);
    proc->setA(0xd6);
    proc->process();
    REQUIRE(proc->getZeroFlag());
    proc->getMemory().write(0x1234, 0xff);
    proc->process();
    REQUIRE_FALSE(proc->getZeroFlag());
}


TEST_CASE("CP_ixplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0xbe);
    proc->getMemory().write(0x2, 0xf);
    proc->getMemory().write(0x3, 0xdd);
    proc->getMemory().write(0x4, 0xbe);
    proc->getMemory().write(0x5, 0xf);
    proc->getMemory().write(0x1243, 0xd6);
    proc->setIX(0x1234);
    proc->setA(0xd6);
    proc->process(2);
    REQUIRE(proc->getZeroFlag());
    proc->getMemory().write(0x1234, 0xff);
    proc->process(2);
    REQUIRE_FALSE(proc->getZeroFlag());
}


TEST_CASE("CP_iyplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfd);
    proc->getMemory().write(0x1, 0xbe);
    proc->getMemory().write(0x2, 0xf);
    proc->getMemory().write(0x3, 0xfd);
    proc->getMemory().write(0x4, 0xbe);
    proc->getMemory().write(0x5, 0xf);
    proc->getMemory().write(0x1243, 0xd6);
    proc->setIY(0x1234);
    proc->setA(0xd6);
    proc->process(2);
    REQUIRE(proc->getZeroFlag());
    proc->getMemory().write(0x1243, 0xff);
    proc->process(2);
    REQUIRE_FALSE(proc->getZeroFlag());
}

/**
 * http://www.msx.org/forum/semi-msx-talk/emulation/z80-daa
 * http://wikiti.brandonw.net/?title=Z80_Instruction_Set
 */

TEST_CASE("DAATest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x27);
    REQUIRE(true == false);
}

/**
 * If the contents of Index Register IX are 2006H, at execution of DEC IX
 the contents of Index Register IX are 2005H.
 */

TEST_CASE("DECIXTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0x2b);
    proc->setIX(0x2006);
    proc->process();
    REQUIRE(proc->getIX() == 0x2005);
}


TEST_CASE("DECIYTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x1, 0xfd);
    proc->getMemory().write(0x1, 0x2b);
    proc->setIY(0x2006);
    proc->process();
    REQUIRE(proc->getIY() == 0x2005);
}


TEST_CASE("DECrTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x1, BOOST_BINARY(00101101)); //L
    proc->setL(0xFF);
    proc->process();
    REQUIRE(proc->getL() == 0xFE);
}


TEST_CASE("DEC_HL_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0, 0x35);
    proc->getMemory().write(0xffed, 0xff);
    proc->setHL(0xffed);
    proc->process();
    REQUIRE(proc->getHL() == 0xFE);
}


TEST_CASE("DEC_ixplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0x35);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0xffed, 0xff);
    proc->setIX(0xffea);
    proc->process();
    REQUIRE(proc->getMemory().read(0xffed) == 0xfe);
}


TEST_CASE("DEC_iyplusd_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfd);
    proc->getMemory().write(0x1, 0x35);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0xffed, 0xff);
    proc->setIY(0xffea);
    proc->process();
    REQUIRE(proc->getMemory().read(0xffed) == 0xfe);
}

/**
 *
 */

TEST_CASE("EXAFAFPrimeTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x08);
    proc->setAF(0x9900);
    proc->setAF_alt(0x5944);
    proc->process();
    REQUIRE(proc->getAF() == 0x5944);
    REQUIRE(proc->getAF_alt() == 0x9900);
}



TEST_CASE("HALTTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x76);
    proc->process();
    REQUIRE(proc->getPC() == 0x1);
}


TEST_CASE("IM0Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x46);
    proc->process();
    REQUIRE(proc->getIM() == 0);
}


TEST_CASE("IM1Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x56);
    proc->process();
    REQUIRE(proc->getIM()== 1);
}


TEST_CASE("IM2Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x5e);
    proc->process();
    REQUIRE(proc->getIM() == 2);
}


TEST_CASE("IN_C_Test") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}

/**
 * If the contents of register C are 07H, the contents of register B are 10H,
 * and byte 7BH is available at the peripheral device mapped to I/O port
 * address 07H . After execution of IN D, (C) register D contains 7BH.
 */

TEST_CASE("INr_C_Test") {
    EmulationProcessor* proc = setupProcessor();
    proc->getIo().write(0x7, 0x7b);
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, BOOST_BINARY(01010000));
    proc->setC(0x07);
    proc->setB(0x10);
    proc->process();
    REQUIRE(proc->getD() == 0x7B);
}



TEST_CASE("LDDRTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("LDDTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}



TEST_CASE("LDIRTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("LDITest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}



TEST_CASE("NOPTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0x0);

    proc->process();
    // assert all registers are the same and nothing has happened!
}


TEST_CASE("ORsTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("OTDRTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("OTIRTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}

/**
 * If the contents of register C are 07H, the contents of register B are 10H, the
 contents of the HL register pair are 1000H , and the contents of memory
 location 1000H are 59H, at execution of OUTD register B contains 0FH, the
 HL register pair contains 0FFFH, and byte 59H is written to the peripheral
 device mapped to I/O port address 07H.

 */

TEST_CASE("OUTDTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("OUTITest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("PUSHTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("RESTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}



TEST_CASE("RETITest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("RETNTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("RLCTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("RLDTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("RRCTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}



TEST_CASE("RRTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("RLTest") {
    /*-
    If the contents of register D and the Carry flag are
    C76543210
    010001111

    at execution of RL D the contents of register D and the Carry flag are
    C76543210
    100011110

     */
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}



TEST_CASE("RRCmTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}

/**
 * If the contents of the Program Counter are 15B3H, at execution of
 * RST 18H (Object code 11011111) the PC contains 0018H, as the address
 * of the next Op Code fetched.
 */

TEST_CASE("RSTpTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x15B3, BOOST_BINARY(11011111));
    proc->setPC(0x15B3);
    proc->process();
    REQUIRE(proc->getPC() == 0x18);
}



TEST_CASE("SBCTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("SLATest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("SRATest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}

/**
 * If the contents of register B are
 * <p/>
 * 0b10001111
 * at execution of SRL B the contents of register B and the Carry flag are
 * 0b010001111
 */

TEST_CASE("SRLTest") {
    EmulationProcessor* proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(111000));
    proc->setB(0b10001111);
    REQUIRE_FALSE(proc->getCFlag());
    proc->process();
    REQUIRE(proc->getCFlag());
    REQUIRE(proc->getB() == BOOST_BINARY(01000111));
}


TEST_CASE("SUBTest") {
    EmulationProcessor* proc = setupProcessor();
    REQUIRE(true == false);
}


TEST_CASE("DITest") {
    REQUIRE(true == false);
}



TEST_CASE("DJNZTest") {
    REQUIRE(true == false);
}


TEST_CASE("INDTest") {
    REQUIRE(true == false);
}


TEST_CASE("INDRTest") {
    REQUIRE(true == false);
}


TEST_CASE("INIRTest") {
    REQUIRE(true == false);
}


TEST_CASE("INITest") {
    REQUIRE(true == false);
}


TEST_CASE("ORTest") {
    REQUIRE(true == false);
}


TEST_CASE("svgIcon") {
    REQUIRE(true == false);
}