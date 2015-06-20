#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <boost/utility/binary.hpp>


#include "Z80/EmulationProcessor.h"
#include "Z80/BadgerMemory.h"
#include "Z80/TestIO.h"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"

std::unique_ptr<EmulationProcessor> setupProcessor() {
    BadgerMemory* memory = new BadgerMemory();
    TestIO* io = new TestIO();
//     EmulationProcessor* proc = new EmulationProcessor(*memory, *io);
    std::unique_ptr<EmulationProcessor> proc(new EmulationProcessor(*memory, *io));
    return proc;
}

/*
 * If the Accumulator contents are 16H, the Carry Flag is set, the HL register
pair contains 6666H, and address 6666H contains 10H, at execution of
ADC A, (HL) the Accumulator contains 27H.
*/
TEST_CASE("ADCA_HL_Test", "Instructions") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write((std::uint16_t)0, (std::uint8_t)0x8E);
    proc->getMemory().write(0x6666, 0x10);
    proc->setA(0x16);
    proc->setHL(0x6666);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0x27);
}


TEST_CASE("ADCA_IX_d_Test", "Instructions") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();

    // ADC A, n
    proc->getMemory().write(0x0,0xCE);
    proc->getMemory().write(0x1, 0xAF);
    proc->setA(0x16);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0xC6);
}


TEST_CASE("ADCAnTest2") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCE);
    proc->getMemory().write(0x1, 0xA5); // immediate value
    proc->setA(0x17);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0xbd);
}

TEST_CASE("ADCArTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();

    // ADC A, B
    proc->getMemory().write(0x0,BOOST_BINARY(10001000));
    proc->setA(0x16);
    proc->setCFlag(true);
    proc->setB(0x99);
    proc->process();
    REQUIRE(proc->getA() == 0xB0);
}

TEST_CASE("ADCArTest2") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0,BOOST_BINARY(10001011)); // E register
    proc->setE(0x16);
    proc->setA(0xa8);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0xbf);
}


TEST_CASE("ADDHLssTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0x2F);
    proc->setA(BOOST_BINARY(10110100));
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01001011));
    REQUIRE(proc->getHFlag());
    REQUIRE(proc->getNFlag());
}

/*
* If the Accumulator contains 63H, the HL register pair contains 6000H,
* and memory location 6000H contains 60H, the instruction CP (HL)
* results in the P/V flag in the F register resetting.
*/
TEST_CASE("CPrTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x6000, 0x60);
    proc->setHL(0x6000);
    proc->setA(0x63);
    proc->process();
    REQUIRE_FALSE(proc->getParityOverflowFlag());
}

TEST_CASE("CPrTest2") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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


TEST_CASE("DECr8BitTest") {
    /*
     * f the D register contains byte 2AH, at execution of DEC D register D
     * contains 29H.
     */
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00010101));
    proc->setD(0x2a);
    proc->process();
    REQUIRE(proc->getD() == 0x29);
}

TEST_CASE("DECssTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00101011));
    proc->setRegisterPair(RegisterPair::HL, 0x1001);
    proc->process();
    REQUIRE(proc->getHL() == 0x1000);
}

TEST_CASE("DITest") {

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xF3);
    REQUIRE_FALSE(proc->isIFF1());
    REQUIRE_FALSE(proc->isIFF2());
}

TEST_CASE("DJNZeTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    // LD B, 1
    proc->getMemory().write(0x0, 0x6);
    proc->getMemory().write(0x1, 0x1);

    // DJNZ (PC+e) 4
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xEB);
    proc->setDE(0x2822);
    proc->setHL(0x499A);
    proc->process();
    REQUIRE( proc->getDE() == 0x499A);
    REQUIRE( proc->getHL() == 0x2822);

}

/**
* If the contents of register pair s BC, DE, and HL are the numbers 445AH ,
* 3DA2H , and 8859H , respectively, and the contents of register pairs BC',
* DE', and HL' are 0988H , 9300H , and 00E7H , respectively, at instruction
* EXX the contents of the register pair s are as follows: BC' contains
* 0988H; DE' contains 9300H ; HL contains 00E7H ; BC' contains 445AH ; DE'
* contains 3DA2H ; and HL' contains 8859H .
*/

TEST_CASE("EXXTest") {

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xDB);
    proc->getMemory().write(0x1, 0x01);
    proc->getIO().write(0x01, 0x7b);
    proc->setA(0x23);
    proc->process();

    REQUIRE(proc->getA() == 0x7b);
}


TEST_CASE("INCr16BitTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    // increment BC
    proc->getMemory().write(0x0, BOOST_BINARY(00000011));
    proc->setRegisterPair(RegisterPair::BC, 50);
    proc->process();
    REQUIRE(proc->getBC() == 51);
}


TEST_CASE("INCr8BitTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00111100));
    proc->setRegister(Rgstr::A, 50);
    proc->process();
    REQUIRE(proc->getA() == 51);
}


TEST_CASE("INCssTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    // increment BC
    proc->getMemory().write(0x0, BOOST_BINARY(00000011));
    proc->setRegisterPair(RegisterPair::BC, 50);
    proc->process();
    REQUIRE(proc->getBC() == 51);
}


TEST_CASE("JPHLTest") {

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0, 0xE9);

    proc->setL(0x45);
    proc->setH(0x11);

    // proc->setZeroFlag(false);

    REQUIRE(proc->getPC() == 0x0);

    proc->process();
    REQUIRE( proc->getPC() == 0x1145);
}


TEST_CASE("JPnnTest") {

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();

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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x47);
    proc->setA(0xf9);

    REQUIRE( proc->getF() == 0x0);

    proc->process();

    REQUIRE( proc->getI() == 0xf9);
    REQUIRE( proc->getF() == BOOST_BINARY(10000000));
}



TEST_CASE("LDRATest") {
    /*
     * The contents of the Accumulator are loaded to the Memory Refresh
     * register R.
     */

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00011110));
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();

    // load a' into a
    proc->getMemory().write(0x0, BOOST_BINARY(01100111));
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

    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xF9);
    proc->setH(0x44);
    proc->setL(0x2E);

    REQUIRE(proc->getSP() == 0x0);

    proc->process();
    REQUIRE(proc->getSP() == 0x442E);
}


TEST_CASE("LDSPIYTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xF9);
    proc->setIY(0xA227);
    proc->process();
    REQUIRE(proc->getSP() == 0xA227);
}


TEST_CASE("LD_IXplusd_rTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x44);
    proc->setA(BOOST_BINARY(10011000));
    proc->process();
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01100111));
}



TEST_CASE("OUT_C_rTest") {
    /*
     * If the contents of register C are 01H, and the contents of register D
     * are 5AH, at execution of OUT (C),D byte 5AH is written to the
     * peripheral device mapped to I/O port address 01H
     */
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, BOOST_BINARY(01010001));
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(11100001)); // HL
    proc->getMemory().write(0x1000, 0x55);
    proc->getMemory().write(0x1001, 0x33);
    proc->setSP(0x1000);
    proc->process();
    REQUIRE(proc->getHL() == 0x3355);
    REQUIRE(proc->getSP() == 0x1002);
}

TEST_CASE("PUSHIXTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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

/*
 * If the AF register pair contains 2233H
 * and the Stack Pointer contains 1007H,
 * at instruction PUSH AF memory address 1006H contains 22H,
 * memory address 1005H contains 33H,
 * and the Stack Pointer contains 1005H.
*/
TEST_CASE("PUSHTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(11110101));
    proc->setAF(0x2233);
    proc->setSP(0x1007);
    proc->process();
    REQUIRE(proc->getMemory().read(0x1006) == 0x22);
    REQUIRE(proc->getMemory().read(0x1005) == 0x33);
    REQUIRE(proc->getSP() == 0x1005);
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
TEST_CASE("RETccTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->setSignFlag(true);
    proc->setPC(0x3535);
    proc->setSP(0x2000);
    proc->getMemory().write(0x2000, 0xB5);
    proc->getMemory().write(0x2001, 0x18);
    proc->getMemory().write(0x3535, BOOST_BINARY(11111000));
    proc->process(1);
    REQUIRE(proc->getSP() == 0x2002);
    REQUIRE(proc->getPC() == 0x18B5);

}

 TEST_CASE("ROTrTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
 }

/*
 * If the contents of the Program Counter are 3535H , the contents of
 * the Stack Pointer are 2000H, the contents of memory location 2000H
 * are B5H, and the contents of memory location of memory location 2001H
 * are 18H . At execution of RET the contents of the Stack Pointer is
 * 2002H, and the contents of the Program Counter is 18B5H, pointing to
 * the address of the next program Op Code to be fetched.
 */
TEST_CASE("RETTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->setCFlag(true);
    proc->setA(BOOST_BINARY(01110110));
    proc->getMemory().write(0x0, 0x17);
    proc->process();
    REQUIRE_FALSE( proc->getCFlag());
    REQUIRE(proc->getA() == BOOST_BINARY(11101101));
}

TEST_CASE("RLCATest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    // increment BC
    proc->getMemory().write(0x0, 0x07);
    proc->setA(BOOST_BINARY(10001000));
    proc->process();
//    System.out.println(Integer.toBinaryString(proc->getA()));
    REQUIRE(proc->getA() == BOOST_BINARY(00010001));

    REQUIRE(proc->getCFlag());
}



TEST_CASE("RRATest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0x1F);
    proc->setCFlag(false);
    proc->setA(BOOST_BINARY(11100001));
    proc->process();
    REQUIRE(proc->getCFlag());
    REQUIRE(proc->getA() == BOOST_BINARY(01110000));
}


TEST_CASE("RRCATest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0x0F);
    proc->setCFlag(false);
    proc->setA(BOOST_BINARY(11100001));
    proc->process();
    REQUIRE(proc->getCFlag());
//    System.out.println(Integer.toBinaryString(proc->getA()));
    REQUIRE(proc->getA() == BOOST_BINARY(11110000));
}



TEST_CASE("RRDTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(11100110));
    proc->setHL(0x3000);
    proc->process(2);
    REQUIRE((proc->getMemory().read(0x3000) & BOOST_BINARY(10000)) == BOOST_BINARY(10000));
}


TEST_CASE("SETb_IXplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xCB);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0x3, BOOST_BINARY(11000110));
    proc->setIY(0x2000);
    proc->process(4);
    REQUIRE((proc->getMemory().read(0x2003) & 1) == 1);
}

TEST_CASE("SETbrTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(11100111));
    proc->process(2);
    REQUIRE((proc->getA() & BOOST_BINARY(10000)) == BOOST_BINARY(10000));
}


TEST_CASE("XORsTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(10101011));
    proc->setE(0x96); // 10010110
    proc->setA(0x5D); // 01011101
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(11001011));
}

TEST_CASE("ADCA_ixplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1, BOOST_BINARY(01011010)); //DE
    proc->setHL(0x17);
    proc->setDE(0x33);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getHL() == 0x4b);
}



TEST_CASE("ADDIXppTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0,0xDD);
    proc->getMemory().write(0x1, BOOST_BINARY(00001001)); // bc
    proc->setIX(0x333);
    proc->setBC(0x5555);
    proc->process();
    REQUIRE(proc->getIX() == 0x5888);
}


TEST_CASE("ADDIYrrTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, BOOST_BINARY(00001001)); // bc
    proc->setIY(0x333);
    proc->setBC(0x5555);
    proc->process();
    REQUIRE(proc->getIY() == 0x5888);
}



TEST_CASE("ANDrTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(10100000));
    proc->setB(BOOST_BINARY(01111011));
    proc->setA(BOOST_BINARY(11000011));
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("ANDnTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xe6);
    proc->getMemory().write(0x1, BOOST_BINARY(01111011));
    proc->setA(BOOST_BINARY(11000011));
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("AND_HL_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xa6);
    proc->getMemory().write(0x1, 0);
    proc->getMemory().write(0x2, 0);
    proc->getMemory().write(0x3, 0);
    proc->getMemory().write(0x4, BOOST_BINARY(01111011));
    proc->setA(BOOST_BINARY(11000011));
    proc->setHL(0x4);
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("AND_ixplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0xa6);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0xA, BOOST_BINARY(01111011));
    proc->setA(BOOST_BINARY(11000011));
    proc->setIX(0x7);
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


TEST_CASE("AND_iyplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfd);
    proc->getMemory().write(0x1, 0xa6);
    proc->getMemory().write(0x2, 0x3);

    proc->getMemory().write(0xA, BOOST_BINARY(01111011));
    proc->setA(BOOST_BINARY(11000011));
    proc->setIY(0x7);
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01000011));
}


/*
 * If the contents of Index Register are 2000H,
 * and bit 6 in memory location 2004H contains 1,
 * at execution of BIT 6, (IY+4H)
 * the Z flag and the F register still contain 0,
 * and bit 6 in memory location 2004H still contains 1.
 * Bit 0 in memory location 2004H is the least-significant bit.
*/
TEST_CASE("BITb_IYplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xFD);
    proc->getMemory().write(0x1, 0xCB);
    proc->getMemory().write(0x2, BOOST_BINARY(100));
    proc->getMemory().write(0x3, BOOST_BINARY(01110110));
    proc->getMemory().write(0x2004, BOOST_BINARY(1110110)); // data with bit 6 == 1
    proc->setIX(0x2000);
    REQUIRE( (proc->getMemory().read(0x2004) & BOOST_BINARY(1000000)) == BOOST_BINARY(1000000));
    REQUIRE(proc->getZeroFlag() == false);
}

/*
 * If bit 2 in register B contains 0, at execution of BIT 2, B the Z flag in the
* F register contains 1, and bit 2 in register B remains 0. Bit 0 in register B is
* the least-significant bit.
*/
TEST_CASE("BITbrTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x1a47, 0xd4);
    proc->getMemory().write(0x1a48,0x35);
    proc->getMemory().write(0x1a49,0x21);
    proc->setCFlag(false);
    proc->setPC(0x1a47);
    proc->setSP(0x3002);
    proc->process();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x1A47, 0xCD);
    proc->getMemory().write(0x1A48, 0x35);
    proc->getMemory().write(0x1A49, 0x21);
    proc->setPC(0x1A47);
    proc->setSP(0x3002);
    proc->process();
    REQUIRE(proc->getMemory().read(0x3001) == 0x1a);
    REQUIRE(proc->getMemory().read(0x3000) == 0x4a);
    REQUIRE(proc->getSP() == 0x3000);
    REQUIRE(proc->getPC() == 0x2135);
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
TEST_CASE("CPITest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
TEST_CASE("CPDRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    //CPDR
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1, 0xb9);
    
    proc->getMemory().write(0x1118,0x52);
    proc->getMemory().write(0x1117,0x0);
    proc->getMemory().write(0x1116,0xf3);
    proc->setHL(0x1118);
    proc->setBC(0x7);
    proc->setA(0xf3);
    proc->process(3);
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xed);
    proc->getMemory().write(0x1, 0xb1);
    
    proc->getMemory().write(0x1111,0x52);
    proc->getMemory().write(0x1112,0x0);
    proc->getMemory().write(0x1113,0xf3);
    proc->setHL(0x1111);
    proc->setBC(0x7);
    proc->setA(0xf3);
    proc->process(3);
    REQUIRE(proc->getBC() == 4);
    REQUIRE(proc->getHL() == 0x1114);
    REQUIRE(proc->getZeroFlag());
    REQUIRE(proc->getParityOverflowFlag());
}

TEST_CASE("CPnTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    
    proc->getMemory().write(0x0, 0xfe);
    proc->getMemory().write(0x1, 0x3f);
    
    proc->getMemory().write(0x2, 0xfe);
    proc->getMemory().write(0x3, 0x3f);
    
    proc->setA(0x3f);
    proc->process();
    REQUIRE(proc->getZeroFlag());
    proc->setA(0xFF);
    proc->process();
    REQUIRE_FALSE(proc->getZeroFlag());
}

TEST_CASE("CP_hl_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0xbe);
    proc->getMemory().write(0x2, 0xf);
    
    proc->getMemory().write(0x3, 0xdd);
    proc->getMemory().write(0x4, 0xbe);
    proc->getMemory().write(0x5, 0xf);
    
    proc->getMemory().write(0x1243, 0xd6);
    proc->setIX(0x1234);
    proc->setA(0xd6);
    proc->process();
    REQUIRE(proc->getZeroFlag());
    proc->getMemory().write(0x1243, 0xb);
    proc->process();
    REQUIRE_FALSE(proc->getZeroFlag());
}


TEST_CASE("CP_iyplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfd);
    proc->getMemory().write(0x1, 0xbe);
    proc->getMemory().write(0x2, 0xf);
    
    proc->getMemory().write(0x3, 0xfd);
    proc->getMemory().write(0x4, 0xbe);
    proc->getMemory().write(0x5, 0xf);
    
    proc->getMemory().write(0x1243, 0xd6);
    proc->setIY(0x1234);
    proc->setA(0xd6);
    proc->process();
    REQUIRE(proc->getZeroFlag());
    proc->getMemory().write(0x1243, 0xff);
    proc->process();
    REQUIRE_FALSE(proc->getZeroFlag());
}


/**
 * If the contents of Index Register IX are 2006H, at execution of DEC IX
 the contents of Index Register IX are 2005H.
 */
TEST_CASE("DECIXTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0x2b);
    proc->setIX(0x2006);
    proc->process();
    REQUIRE(proc->getIX() == 0x2005);
}

TEST_CASE("DECIYTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xfd);
    proc->getMemory().write(0x1, 0x2b);
    proc->setIY(0x2006);
    proc->process();
    REQUIRE(proc->getIY() == 0x2005);
}

TEST_CASE("DECrTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(00101101)); //L
    proc->setL(0xFF);
    proc->process();
    REQUIRE(proc->getL() == 0xFE);
}

TEST_CASE("DEC_HL_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0, 0x35);
    proc->getMemory().write(0xffed, 0xff);
    proc->setHL(0xffed);
    proc->process();
    REQUIRE(proc->getMemory().read(0xffed) == 0xFE);
}


TEST_CASE("DEC_ixplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xdd);
    proc->getMemory().write(0x1, 0x35);
    proc->getMemory().write(0x2, 0x3);
    proc->getMemory().write(0xffed, 0xff);
    proc->setIX(0xffea);
    proc->process();
    REQUIRE(proc->getMemory().read(0xffed) == 0xfe);
}


TEST_CASE("DEC_iyplusd_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0x08);
    proc->setAF(0x9900);
    proc->setAF_alt(0x5944);
    proc->process();
    REQUIRE(proc->getAF() == 0x5944);
    REQUIRE(proc->getAF_alt() == 0x9900);
}



TEST_CASE("HALTTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0x76);
    proc->process();
    REQUIRE(proc->getPC() == 0x1);
}


TEST_CASE("IM0Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x46);
    proc->process();
    REQUIRE(proc->getIM() == 0);
}


TEST_CASE("IM1Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x56);
    proc->process();
    REQUIRE(proc->getIM()== 1);
}


TEST_CASE("IM2Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0x5e);
    proc->process();
    REQUIRE(proc->getIM() == 2);
}

/*
 * If the contents of the Accumulator are 23H, and byte 7BH is available at the
peripheral device mapped to I/O port address 01H. At execution of INA,
(01H) the Accumulator contains 7BH.
*/
TEST_CASE("INa_n_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getIO().write(0x1, 0x7b);
    proc->getMemory().write(0x0, 0xDB);
    proc->getMemory().write(0x1, BOOST_BINARY(1));
    proc->setA(0x23);
    proc->process();
    REQUIRE(proc->getA() == 0x7B);
}

/**
 * If the contents of register C are 07H, the contents of register B are 10H,
 * and byte 7BH is available at the peripheral device mapped to I/O port
 * address 07H . After execution of IN D, (C) register D contains 7BH.
 */

TEST_CASE("INr_C_Test") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getIO().write(0x7, 0x7b);
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, BOOST_BINARY(01010000));
    proc->setC(0x07);
    proc->setB(0x10);
    proc->process();
    REQUIRE(proc->getD() == 0x7B);
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
TEST_CASE("LDDRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xB8);
    proc->setHL(0x1114);
    proc->setDE(0x2225);
    proc->setBC(0x003);

    proc->getMemory().write(0x1114, 0xA5);
    proc->getMemory().write(0x1113, 0x36);
    proc->getMemory().write(0x1112, 0x88);
    proc->getMemory().write(0x2225, 0xC5);
    proc->getMemory().write(0x2224, 0x59);
    proc->getMemory().write(0x2223, 0x66);
    proc->process(3);

    REQUIRE(proc->getHL() == 0x1111);
    REQUIRE(proc->getDE() == 0x2222);
    REQUIRE(proc->getBC() == 0x0000);
    REQUIRE(proc->getMemory().read(0x1114) == 0xA5);
    REQUIRE(proc->getMemory().read(0x1113) == 0x36);
    REQUIRE(proc->getMemory().read(0x1112) == 0x88);
    REQUIRE(proc->getMemory().read(0x2225) == 0xA5);
    REQUIRE(proc->getMemory().read(0x2224) == 0x36);
    REQUIRE(proc->getMemory().read(0x2223) == 0x88);
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
TEST_CASE("LDDTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xA8);

    proc->setHL(0x1111);
    proc->getMemory().write(0x1111, 0x88);

    proc->setDE(0x2222);
    proc->getMemory().write(0x2222, 0x66);

    proc->setBC(0x7);

    proc->process();
    REQUIRE(proc->getHL() == 0x1110);
    REQUIRE(proc->getMemory().read(0x1111) == 0x88);
    REQUIRE(proc->getDE() == 0x2221);
    REQUIRE(proc->getMemory().read(0x2222) == 0x88);
    REQUIRE(proc->getBC() == 0x6);
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
TEST_CASE("LDIRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xB0);
    proc->setHL(0x1111);
    proc->setDE(0x2222);
    proc->setBC(0x003);

    proc->getMemory().write(0x1111, 0x88);
    proc->getMemory().write(0x1112, 0x36);
    proc->getMemory().write(0x1113, 0xA5);
    proc->getMemory().write(0x2222, 0x66);
    proc->getMemory().write(0x2223, 0x59);
    proc->getMemory().write(0x2224, 0xc5);
    proc->process(3);

    REQUIRE(proc->getHL() == 0x1114);
    REQUIRE(proc->getDE() == 0x2225);
    REQUIRE(proc->getBC() == 0x0000);
    REQUIRE(proc->getMemory().read(0x1111) == 0x88);
    REQUIRE(proc->getMemory().read(0x1112) == 0x36);
    REQUIRE(proc->getMemory().read(0x1113) == 0xA5);
    REQUIRE(proc->getMemory().read(0x2222) == 0x88);
    REQUIRE(proc->getMemory().read(0x2223) == 0x36);
    REQUIRE(proc->getMemory().read(0x2224) == 0xA5);
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
TEST_CASE("LDITest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xA0);

    proc->setHL(0x1111);
    proc->getMemory().write(0x1111, 0x88);

    proc->setDE(0x2222);
    proc->getMemory().write(0x2222, 0x66);

    proc->setBC(0x7);

    proc->process();
    REQUIRE(proc->getHL() == 0x1112);
    REQUIRE(proc->getMemory().read(0x1111) == 0x88);
    REQUIRE(proc->getDE() == 0x2223);
    REQUIRE(proc->getMemory().read(0x2222) == 0x88);
    REQUIRE(proc->getBC() == 0x6);
}

TEST_CASE("NOPTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0x0);

    proc->process();
    // assert all registers are the same and nothing has happened!
}

/* If the H register contains 48H (0100 0100), and the Accumulator contains
12H (0001 0010), at execution of OR H the Accumulator contains 5AH
(0101 1010).*/
TEST_CASE("ORTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, BOOST_BINARY(10110100));
    proc->setH(BOOST_BINARY(01000100));
    proc->setA(BOOST_BINARY(00010010));
    proc->process();
    REQUIRE(proc->getA() == BOOST_BINARY(01010110));

    //TODO check other variants
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
TEST_CASE("OTDRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xBB);
    proc->setC(0x07);
    proc->setB(0x03);
    proc->setHL(0x1000);
    proc->getMemory().write(0xFFE, 0x51);
    proc->getMemory().write(0xFFF, 0xA9);
    proc->getMemory().write(0x1000, 0x03);

    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0x03);
    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0xA9);
    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0x51);
    REQUIRE(proc->getHL() == 0x0FFD);
    REQUIRE(proc->getB() == 0x0);
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
TEST_CASE("OTIRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xB3);
    proc->setC(0x07);
    proc->setB(0x03);
    proc->setHL(0x1000);
    proc->getMemory().write(0x1000, 0x51);
    proc->getMemory().write(0x1001, 0xA9);
    proc->getMemory().write(0x1002, 0x03);

    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0x51);
    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0xA9);
    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0x03);
    REQUIRE(proc->getHL() == 0x01003);
    REQUIRE(proc->getB() == 0x0);
}

/**
 * If the contents of register C are 07H, the contents of register B are 10H, the
 contents of the HL register pair are 1000H , and the contents of memory
 location 1000H are 59H, at execution of OUTD register B contains 0FH, the
 HL register pair contains 0FFFH, and byte 59H is written to the peripheral
 device mapped to I/O port address 07H.
 */
TEST_CASE("OUTDTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xAB);
    proc->setC(0x07);
    proc->setB(0x10);
    proc->setHL(0x1000);
    proc->getMemory().write(0x1000, 0x59);

    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0x59);
    REQUIRE(proc->getHL() == 0x0FFF);
    REQUIRE(proc->getB() == 0x0F);
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
TEST_CASE("OUTITest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xA3);
    proc->setC(0x07);
    proc->setB(0x10);
    proc->setHL(0x1000);
    proc->getMemory().write(0x1000, 0x59);

    proc->process();
    REQUIRE(proc->getIO().read(0x7) == 0x59);
    REQUIRE(proc->getHL() == 0x1001);
    REQUIRE(proc->getB() == 0x0F);
}

/* At execution of RES 6, D, bit 6 in register D resets. Bit 0 in register D is the
least-significant bit.*/
TEST_CASE("RESTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(10110010));
    proc->setD(BOOST_BINARY(11111111));
    proc->process();
    REQUIRE(proc->getD() == BOOST_BINARY(10111111));
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
TEST_CASE("RETITest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
TEST_CASE("RETNTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

TEST_CASE("RLCTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

TEST_CASE("RLDTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

TEST_CASE("RRCTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

TEST_CASE("RRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

/*-
If the contents of register D and the Carry flag are
C76543210
010001111

at execution of RL D the contents of register D and the Carry flag are
C76543210
100011110
 */
TEST_CASE("RLTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

TEST_CASE("RRCmTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

/**
 * If the contents of the Program Counter are 15B3H, at execution of
 * RST 18H (Object code 11011111) the PC contains 0018H, as the address
 * of the next Op Code fetched.
 */
TEST_CASE("RSTpTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x15B3, BOOST_BINARY(11011111));
    proc->setPC(0x15B3);
    proc->process();
    REQUIRE(proc->getPC() == 0x18);
}

/*
 * If the Accumulator contains 16H, the carry flag is set, the HL register pair
contains 3433H, and address 3433H contains 05H, at execution of
SBC A, (HL) the Accumulator contains 10H.*/
TEST_CASE("SBCTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

TEST_CASE("SLATest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

TEST_CASE("SRATest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
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
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xCB);
    proc->getMemory().write(0x1, BOOST_BINARY(111000));
    proc->setB(BOOST_BINARY(10001111));
    REQUIRE_FALSE(proc->getCFlag());
    proc->process();
    REQUIRE(proc->getCFlag());
    REQUIRE(proc->getB() == BOOST_BINARY(01000111));
}

TEST_CASE("SUBTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    REQUIRE(true == false);
}

// TEST_CASE("DITest") {
//     REQUIRE(true == false);
// }

/*
 * If the contents of register C are 07H, the contents of register B are 10H, the
contents of the HL register pair are 1000H, and byte 7BH is available at the
peripheral device mapped to I/O port address 07H. At execution of IND
memory location 1000H contains 7BH, the HL register pair contains
0FFFH, and register B contains 0FH.*/
TEST_CASE("INDTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xAA);
    proc->setC(0x07);
    proc->setB(0x10);
    proc->setHL(0x1000);
    proc->getIO().write(0x7, 0x7B);
    proc->process();
    REQUIRE(proc->getMemory().read(0x1000) == 0x7b);
    REQUIRE(proc->getHL() == 0xFFF);
    REQUIRE(proc->getB() == 0xF);
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
TEST_CASE("INDRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xBA);
    proc->setC(0x07);
    proc->setB(0x3);
    proc->setHL(0x1000);
    proc->getIO().write(0x7, 0x51);
    proc->process();
    proc->getIO().write(0x7, 0xA9);
    proc->process();
    proc->getIO().write(0x7, 0x03);
    proc->process();
    REQUIRE(proc->getMemory().read(0xFFE) == 0x03);
    REQUIRE(proc->getMemory().read(0xFFF) == 0xa9);
    REQUIRE(proc->getMemory().read(0x1000) == 0x51);
    REQUIRE(proc->getHL() == 0xFFD);
    REQUIRE(proc->getB() == 0x0);
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
TEST_CASE("INIRTest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xB2);
    proc->setC(0x07);
    proc->setB(0x3);
    proc->setHL(0x1000);
    proc->getIO().write(0x7, 0x51);
    proc->process();
    proc->getIO().write(0x7, 0xA9);
    proc->process();
    proc->getIO().write(0x7, 0x03);
    proc->process();
    REQUIRE(proc->getMemory().read(0x1002) == 0x03);
    REQUIRE(proc->getMemory().read(0x1001) == 0xa9);
    REQUIRE(proc->getMemory().read(0x1000) == 0x51);
    REQUIRE(proc->getHL() == 0x1003);
    REQUIRE(proc->getB() == 0x0);
}

/* If the contents of register C are 07H, the contents of register B are 10H, the
contents of the HL register pair are 1000H, and byte 7BH is available at the
peripheral device mapped to I /O port address 07H. At execution of INI
memory location 1000H contains 7BH, the HL register pair contains
1001H, and register B contains 0FH.*/
TEST_CASE("INITest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0xED);
    proc->getMemory().write(0x1, 0xA2);
    proc->setC(0x07);
    proc->setB(0x10);
    proc->setHL(0x1000);
    proc->getIO().write(0x7, 0x7B);
    proc->process();
    REQUIRE(proc->getMemory().read(0x1000) == 0x7b);
    REQUIRE(proc->getHL() == 0x1001);
    REQUIRE(proc->getB() == 0xF);
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
TEST_CASE("DAATest") {
    std::unique_ptr<EmulationProcessor> proc = setupProcessor();
    proc->getMemory().write(0x0, 0x27);
    REQUIRE(true == false);
}

