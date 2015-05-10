#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <boost/utility/binary.hpp>


#include "Z80/EmulationProcessor.h"
#include "Z80/BadgerMemory.h"
#include "Z80/TestIO.h"

EmulationProcessor* setupProcessor() {
    EmulationProcessor* proc = new EmulationProcessor();
    proc->setMemory(new BadgerMemory());
    proc->setIO(new TestIO());
    return proc;
}

TEST_CASE("ADCA_HL_Test") {
    EmulationProcessor* proc = setupProcessor();

    proc->getMemory()->write(0x0, 0x8E);
    proc->getMemory()->write(0x6666, 0x10);
    proc->setA(0x16);
    proc->setHL(0x6666);
    proc->setCFlag(true);
    proc->process();
    REQUIRE(proc->getA() == 0x27);
}


TEST_CASE("ADCA_IX_d_Test") {
   EmulationProcessor* proc = setupProcessor();
   // ADC A, (IX+d)
   proc->getMemory()->write(0x0, 0xDD);
   proc->getMemory()->write(0x1, 0x8E);
   proc->getMemory()->write(0x2, 0x10);
   proc->getMemory()->write(0x6676, 0x10);
   proc->setIX(0x6666);
   proc->setA(0x16);
//        proc.setHL(0x6666);
   proc->setCFlag(true);
   proc->process();
   REQUIRE(proc->getA() == 0x27);
}


//TEST_CASE("ADCAnTest") {
//    EmulationProcessor proc = new EmulationProcessor();

//    // ADC A, n
//    proc.setMemory(new int[]{0xCE, 0xAF});
//    proc.setA(0x16);
//    proc.setCFlag(true);
//    proc.process();
//    REQUIRE(0xC6, proc.getA());
//}


//TEST_CASE("ADCArTest") {
//    EmulationProcessor proc = new EmulationProcessor();

//    // ADC A, B
//    proc.setMemory(int[]{BOOST_BINARY(10001000)});
//    proc.setA(0x16);
//    proc.setCFlag(true);
//    proc.setB(0x99);
//    proc.process();
//    REQUIRE(0xB0, proc.getA());
//}



//TEST_CASE("ADDHLssTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0b00011001});

//    proc.setDE(45);
//    proc.setHL(12);
//    proc.process();
//    REQUIRE(57, proc.getHL());
//}



//TEST_CASE("EXAFAFprimeTest") {
//    /*
//     * If the content of register pair AF is number 9900H , and the content
//     * of register pair AF' is number 5944H , at instruction EX AF , AF' the
//     * contents of AF is 5944H , and the contents of AF' is 9900H .
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x08});
//    proc.setAF(0x9900);
//    proc.setAF_alt(0x5944);

//    REQUIRE(0x9900, proc.getAF());
//    REQUIRE(0x5944, proc.getAF_alt());

//    proc.process();
//    REQUIRE(0x5944, proc.getAF());
//    REQUIRE(0x9900, proc.getAF_alt());
//}



//TEST_CASE("BITb_HL_Test") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xCB);
//    proc.getMemory().write(0x1, 0b01100110);
//    proc.getMemory().write(0x4444, 0b1111);
//    proc.setHL(0x4444);
//    proc.process();
//    proc.process();
//    REQUIRE(true, proc.getZeroFlag());
//    REQUIRE(true, (proc.getMemory().read(0x4444) & 0b1000) == 0b1000);
//}

///**
// * If the contents of Index Register IX are 2000H, and bit 6 in memory
// * location 2004H contains 1, at execution of BIT 6, (IX+4H) the Z flag in
// * the F register contains 0, and bit 6 in memory location 2004H
// * still contains 1. Bit 0 in memory location 2004H
// * is the least-significant bit.
// */

//TEST_CASE("BITb_IXplusd_Test") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xDD);
//    proc.getMemory().write(0x1, 0xCB);
//    proc.getMemory().write(0x2, 0x4);
//    proc.getMemory().write(0x3, 0b01110110);
//    proc.getMemory().write(0x2004, 0b1101100);
//    proc.setIX(0x2000);
//    proc.process(5);
//    REQUIRE(false, proc.getZeroFlag());
//    REQUIRE(true, (proc.getMemory().read(0x2004) & 0b1000000) == 0b1000000);
//}



//TEST_CASE("CCFTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x3F});
//    proc.setCFlag(false);

//    proc.process();

//    REQUIRE(true, proc.getCFlag());
//}



//TEST_CASE("CPLTest") {
//    /*
//     * If the contents of the Accumulator are 1011 0100 , at execution of
//     * CPL the Accumulator contents are 0100 1011 .
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x2F});
//    proc.setA(0b10110100);
//    proc.process();
//    REQUIRE(0b01001011, proc.getA());
//    REQUIRE(true, proc.getHFlag());
//    REQUIRE(true, proc.getNFlag());
//}


//TEST_CASE("CPrTest") {
//    /*
//     * If the Accumulator contains 63H, the HL register pair contains 6000H,
//     * and memory location 6000H contains 60H, the instruction CP (HL)
//     * results in the P/V flag in the F register resetting.
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xBE);
//    proc.getMemory().write(0x6000, 0x60);
//    proc.setHL(0x6000);
//    proc.setA(0x63);
//    proc.process();
//    REQUIRE(false, proc.getParityOverflowFlag());
//}



//TEST_CASE("DECr8BitTest") {
//    /*
//     * f the D register contains byte 2AH, at execution of DEC D register D
//     * contains 29H.
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0b00010101});
//    proc.setRegister(Register.D, 0x2a);
//    proc.process();
//    REQUIRE(0x29, proc.getD());
//}


//TEST_CASE("DECssTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0b00101011});
//    proc.setRegisterPair(RegisterPair.HL, 0x1001);
//    proc.process();
//    REQUIRE(0x1000, proc.getHL());
//}


//TEST_CASE("DITest") {

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xF3});
//    REQUIRE(false, proc.isIFF1());
//    REQUIRE(false, proc.isIFF2());
//}


//TEST_CASE("DJNZeTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x6, 0x0, 0x10, 0x4, 0x6, 0xEA, 0x10, 0x5,
//            0, 0, 0, 0, 0});
//    proc.process(2);
//    REQUIRE(4, proc.getPC());
//    proc.process();
//    REQUIRE(0xEA, proc.getB());
//    proc.process();
//    REQUIRE(13, proc.getPC());
//}


//TEST_CASE("EITest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xFB});
//    proc.process();
//    REQUIRE(true, proc.isIFF1());
//    REQUIRE(true, proc.isIFF2());
//}


//TEST_CASE("EX_SP_HLTest") {
//    /*
//     * If the HL register pair contains 7012H, the SP register pair contains
//     * 8856H, the memory location 8856H contains byte 11H, and memory
//     * location 8857H contains byte 22H, then the instruction EX (SP), HL
//     * results in the HL register pair containing number 2211H, memory
//     * location 8856H containing byte 12H, memory location 8857H containing
//     * byte 70H and Stack Pointer containing 8856H.
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x8856, 0x11);
//    proc.getMemory().write(0x8857, 0x22);
//    proc.getMemory().write(0x0, 0xE3);
//    proc.setHL(0x7012);
//    proc.setSP(0x8856);
//    proc.process();
//    REQUIRE(0x2211, proc.getHL());
//    REQUIRE(0x12, proc.getMemory().read(0x8856));
//    REQUIRE(0x70, proc.getMemory().read(0x8857));
//    REQUIRE(0x8856, proc.getSP());
//}


//TEST_CASE("EX_SP_IXTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xDD);
//    proc.getMemory().write(0x1, 0xE3);
//    proc.getMemory().write(0x100, 0x90);
//    proc.getMemory().write(0x101, 0x48);
//    proc.setIX(0x3988);
//    proc.setSP(0x100);
//    proc.process(2);
//    REQUIRE(0x4890, proc.getIX());
//    REQUIRE(0x88, proc.getMemory().read(0x100));
//    REQUIRE(0x39, proc.getMemory().read(0x101));
//    REQUIRE(0x100, proc.getSP());

//}


//TEST_CASE("EX_SP_IYTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xFD);
//    proc.getMemory().write(0x1, 0xE3);
//    proc.getMemory().write(0x100, 0x90);
//    proc.getMemory().write(0x101, 0x48);
//    proc.setIY(0x3988);
//    proc.setSP(0x100);
//    proc.process(2);
//    REQUIRE(0x4890, proc.getIY());
//    REQUIRE(0x88, proc.getMemory().read(0x100));
//    REQUIRE(0x39, proc.getMemory().read(0x101));
//    REQUIRE(0x100, proc.getSP());
//}


///**
// * If the content of register pair DE is the number 2822H, and the content
// * of the register pair HL is number 499AH, at instruction EX DE, HL the
// * content of register pair DE is 499AH, and the content of register pair HL
// * is 2822H.
// */

//TEST_CASE("EXDEHLTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xEB});
//    proc.setDE(0x2822);
//    proc.setHL(0x499A);
//    proc.process();
//    REQUIRE(0x499A, proc.getDE());
//    REQUIRE(0x2822, proc.getHL());

//}

///**
// * If the contents of register pair s BC, DE, and HL are the numbers 445AH ,
// * 3DA2H , and 8859H , respectively, and the contents of register pairs BC',
// * DE', and HL' are 0988H , 9300H , and 00E7H , respectively, at instruction
// * EXX the contents of the register pair s are as follows: BC' contains
// * 0988H; DE' contains 9300H ; HL contains 00E7H ; BC' contains 445AH ; DE'
// * contains 3DA2H ; and HL' contains 8859H .
// */

//TEST_CASE("EXXTest") {

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xD9});
//    proc.setBC(0x445A);
//    proc.setDE(0x3DA2);
//    proc.setHL(0x8859);

//    proc.setBC_alt(0x0988);
//    proc.setDE_alt(0x9300);
//    proc.setHL_alt(0x00E7);
//    proc.process();

//    REQUIRE(0x0988, proc.getBC());
//    REQUIRE(0x9300, proc.getDE());
//    REQUIRE(0x00E7, proc.getHL());

//    REQUIRE(0x445A, proc.getBC_alt());
//    REQUIRE(0x3DA2, proc.getDE_alt());
//    REQUIRE(0x8859, proc.getHL_alt());
//}



//TEST_CASE("INA_n_Test") {
//    /*
//     * If the contents of the Accumulator are 23H , and byte 7BH is
//     * available at the peripheral device mapped to I/O port address 01H .
//     * At execution of INA, (01H) the Accumulator contains 7BH .
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xDB, 0x01});
//    proc.getIo().write(0x01, 0x7b);
//    proc.process();

//    REQUIRE(0x7b, proc.getA());
//}


//TEST_CASE("INCr16BitTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    // increment BC
//    proc.setMemory(new int[]{0b00000011});
//    proc.setRegisterPair(RegisterPair.BC, 50);
//    proc.process();
//    REQUIRE(51, proc.getBC());
//}


//TEST_CASE("INCr8BitTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0b00111100});
//    proc.setRegister(Register.A, 50);
//    proc.process();
//    REQUIRE(51, proc.getA());
//}


//TEST_CASE("INCssTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    // increment BC
//    proc.setMemory(new int[]{0b00000011});
//    proc.setRegisterPair(RegisterPair.BC, 50);
//    proc.process();
//    REQUIRE(51, proc.getBC());
//}


//TEST_CASE("JPHLTest") {

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);

//    proc.getMemory().write(0, 0xE9);

//    proc.setL(0x45);
//    proc.setH(0x11);

//    // proc.setZeroFlag(false);

//    REQUIRE(0x0, proc.getPC());

//    proc.process();
//    REQUIRE(0x1145, proc.getPC());
//}


//TEST_CASE("JPnnTest") {

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);

//    proc.getMemory().write(0, 0xC3);
//    proc.getMemory().write(1, 0x45);
//    proc.getMemory().write(2, 0x11);
//    proc.setZeroFlag(false);

//    REQUIRE(0x0, proc.getPC());

//    proc.process();
//    REQUIRE(0x1145, proc.getPC());
//}


//TEST_CASE("JPNZnnTest") {
//    /*
//     * If condition cc is true, the instruction loads operand nn to register
//     * pair PC (Program Counter), and the program continues with the
//     * instruction beginning at address nn . If condition cc is false, the
//     * Program Counter is incremented as usual, and the program continues
//     * with the next sequential instruction. Condition cc is programmed as
//     * one of eight status that corresponds to condition bits in the Fl ag
//     * Register (register F). These eight status are defined in the table
//     * below that also specifies the corresponding cc bit fields in the
//     * assembled object code.
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);

//    proc.getMemory().write(0, 0b11000010);
//    proc.getMemory().write(1, 0x45);
//    proc.getMemory().write(2, 0x11);
//    proc.setZeroFlag(false);

//    REQUIRE(0x0, proc.getPC());

//    proc.process();
//    REQUIRE(0x1145, proc.getPC());
//}


//TEST_CASE("JReTest") {
//    /*-
//     * To jump forward five locations from
//    address 480, the following assembly
//    language statement is used
//    JR $+5


//    The resulting object code and fi
//    nal PC value is shown below:
//    Location Instruction
//    480 18
//    481 03
//    482 -
//    483 -
//    484 -
//    485 ←
//    PC after jump
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);

//    proc.getMemory().write(0x480, 0x18);
//    proc.getMemory().write(0x481, 0x03);
//    proc.setPC(0x480);

//    REQUIRE(0x480, proc.getPC());

//    proc.process();
//    REQUIRE(0x485, proc.getPC());
//}

///**
//* If the Accumulator contains 7AH and the BC register pair contains
//* 1212H the instruction LD (BC) , A results in 7AH in memory location
//* 1212H .
//*/

//TEST_CASE("LD_BC_ATest() throws CloneNotSupportedException {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{LD_BC_A}, 64 * 1024));
//    proc.A = 0x7A;
//    proc.B = 0x12;
//    proc.C = 0x12;

//    REQUIRE(0x0, proc.getMemory().read(0x1212));

//    proc.process();

//    REQUIRE(0x7a, proc.getMemory().read(0x1212));
//}

///**
// * If the contents of register pair DE are 1128H , and the Accumulator
// * contains int A0H , the instruction LD (DE), A results in A0H in
// * memory location 1128H .
// */

//TEST_CASE("LD_DE_ATest() throws CloneNotSupportedException {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{LD_DE_A}, 64 * 1024));
//    proc.A = 0xA0;
//    proc.D = 0x11;
//    proc.E = 0x28;

//    EmulationProcessor cloneToCompare = new EmulationProcessor(proc);
//    cloneToCompare.getMemory().write(0x1128, 0xA0);
//    cloneToCompare.PC += 1;

//    REQUIRE(0x0, proc.getMemory().read(0x1128));
//    proc.process();
//    REQUIRE(0xA0, proc.getMemory().read(0x1128));
//}

///**
// * If the contents of the Accumulator are int D7H , at execution of LD
// * (3141 H) , A D7H results in memory location 3141H .
// */


//TEST_CASE("LD_nn_ATest() throws CloneNotSupportedException {

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{LD_nn_A, 0x41, 0x31},
//            64 * 1024));
//    proc.A = 0xd7;

//    REQUIRE(0x0, proc.getMemory().read(0x3141));

//    proc.process(3);

//    REQUIRE(0xd7, proc.getMemory().read(0x3141));
//}

///**
// * If the content of register pair HL is 483AH , at instruction LD
// * (B2291-1), HL address B229H contains 3AH , and address B22AH contains
// * 48H .
// */

//TEST_CASE("LD_nn_HLTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{0x22, 0x29, 0xB2}, 64 * 1024));
//    proc.H = 0x48;
//    proc.L = 0x3A;

//    REQUIRE(0x0, proc.getMemory().read(0xB229));
//    REQUIRE(0x0, proc.getMemory().read(0xB22A));

//    proc.process();

//    REQUIRE(0x3A, proc.getMemory().read(0xB229));
//    REQUIRE(0x48, proc.getMemory().read(0xB22A));
//}


//TEST_CASE("LDA_BC_Test") {
//    /*
//     * If the BC register pair contains the number 4747H , and memory
//     * address 4747H contains int 12H , then the instruction LD A , (BC)
//     * results in int 12H in register A.
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{0x0a}, 64 * 1024));
//    proc.B = 0x47;
//    proc.C = 0x47;

//    proc.getMemory().write(0x4747, 0x12);

//    REQUIRE(0x0, proc.getA());

//    proc.process();

//    REQUIRE(0x12, proc.getA());
//}


//TEST_CASE("LDA_DE_Test") {
//    /*
//     * If the DE register pair contains the number 30A2H and memory address
//     * 30A2H contains int 22H , then the instruction LD A , (DE) results in
//     * int 22H in register A
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{0x1a}, 64 * 1024));
//    proc.D = 0x30;
//    proc.E = 0xA2;

//    proc.getMemory().write(0x30A2, 0x22);

//    REQUIRE(0x0, proc.getA());

//    proc.process();

//    REQUIRE(0x22, proc.getA());
//}


//TEST_CASE("LDA_nn_Test") {
//    /*
//     * If the contents of nn is number 8832H , and the content of memory
//     * address 8832H is byte 04H , at instruction LD A , (nn) byte 04H is in
//     * the Accumulator.
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{0x3a, 0x32, 0x88}, 64 * 1024));

//    proc.getMemory().write(0x8832, 0x04);

//    REQUIRE(0x0, proc.getA());

//    proc.process(3);

//    REQUIRE(0x04, proc.getA());
//}


//TEST_CASE("LDAITest") {
//    // The contents of the Interrupt Vector Register I are loaded to the
//    // Accumulator

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xED, 0x57, 0xED, 0x57});
//    proc.setI(0x5f);

//    REQUIRE(0x0, proc.getA());

//    proc.process();

//    REQUIRE(0x5f, proc.getA());

//    /*- S is set if I-Register is
//    negative; reset otherwise
//    Z is set if I-Register is zero; reset otherwise
//    H is reset
//    P/V contains contents of IFF2
//    N is reset
//    C is not affected*/
//    REQUIRE(false, proc.getSignFlag());
//    REQUIRE(0, proc.getF());
//    REQUIRE(0, proc.getH());
//    REQUIRE(false, proc.getNFlag());

//    proc.setI(0x81); // negative

//    proc.process();

//    REQUIRE(0x81, proc.getA());
//    REQUIRE(true, proc.getSignFlag());
//    REQUIRE(128, proc.getF());
//    REQUIRE(0, proc.getH());
//    REQUIRE(false, proc.getNFlag());
//}


//TEST_CASE("LDARTest") {
//    // The contents of Memory Refresh Register R are loaded to the
//    // Accumulator.

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xED, 0x5F});
//    proc.setR(0xd7);

//    REQUIRE(0x0, proc.getA());
//    REQUIRE(0x0, proc.getF());
//    proc.process();

//    REQUIRE(0xd7, proc.getA());
//    REQUIRE(128, proc.getF());
//}


//TEST_CASE("LDddnnTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x1, 0x45, 0xd, 0b0010001, 0x23, 0x43, 0b0100001,
//            0xf5, 0x61, 0b0110001, 0xfc, 0x21});

//    proc.process();

//    REQUIRE(0x45, proc.C);
//    REQUIRE(0xd, proc.B);

//    proc.process();
//    REQUIRE(0x23, proc.E);
//    REQUIRE(0x43, proc.D);

//    proc.process();
//    REQUIRE(0xf5, proc.L);
//    REQUIRE(0x61, proc.H);

//    proc.process();
//    REQUIRE(0x21fc, proc.SP);
//}



//TEST_CASE("LDHL_nn_Test") {
//    /*
//     * If address 2045H contains 37H , and address 2046H contains A1H , at
//     * instruction LD HL , (2045H) the HL register pair contains A137H .
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(Arrays.copyOf(new int[]{0x2a, 0x45, 0x20 }, 64 * 1024));

//    proc.getMemory().write(0x2045, 0x37);
//    proc.getMemory().write(0x2046, 0xA1);

//    REQUIRE(0x0, proc.getHL());

//    proc.process();

//    REQUIRE(0xA137, proc.getHL());
//}


//TEST_CASE("LDIATest") {
//    /*
//     * The contents of the Accumulator are loaded to the Interrupt Control
//     * Vector Register, I.
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xED, 0x47});
//    proc.setA(0xf9);

//    REQUIRE(0x0, proc.getF());

//    proc.process();

//    REQUIRE(0xf9, proc.getI());
//    REQUIRE(0b10000000, proc.getF());
//}



//TEST_CASE("LDRATest") {
//    /*
//     * The contents of the Accumulator are loaded to the Memory Refresh
//     * register R.
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xED, 0x4F});
//    proc.setA(0xf9);

//    REQUIRE(0x0, proc.getR());

//    proc.process();
//    REQUIRE(0xf9, proc.getR());
////		REQUIRE(0b0, proc.getF());
//}


//TEST_CASE("LDrn_Test") {
//    /*
//     * At execution of LD E , A5H the contents of register E are A5H .
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0b00011110, 0xA5});

//    REQUIRE(0x0, proc.getE());

//    proc.process();

//    REQUIRE(0xA5, proc.getE());
//}


//TEST_CASE("LDRR_altTest") {
//    /*
//     * The contents of the Accumulator are loaded to the Memory Refresh
//     * register R.
//     */

//    EmulationProcessor proc = new EmulationProcessor();

//    // load a' into a
//    proc.setMemory(new int[]{0b01100111});
//    proc.setA(0xf9);

//    REQUIRE(0x0, proc.getH());

//    proc.process();

//    REQUIRE(0xf9, proc.getH());
//}


//TEST_CASE("LDSP_HL_Test") {
//    /*
//     * The contents of the Accumulator are loaded to the Memory Refresh
//     * register R.
//     */

//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xF9});
//    proc.setH(0x44);
//    proc.setL(0x2E);

//    REQUIRE(0x0, proc.getSP());

//    proc.process();
//    REQUIRE(0x442E, proc.getSP());
//}


//TEST_CASE("LDSPIYTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xFD, 0xF9});
//    proc.setIY(0xA227);
//    proc.process();
//    REQUIRE(0xA227, proc.getSP());
//}


//TEST_CASE("LD_IXplusd_rTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[1024 * 64]); // DD7700    	LD (IX), A
//    proc.getMemory().write(0x0, 0xDD);
//    proc.getMemory().write(0x1, 0x77);
//    proc.getMemory().write(0x2, 0x01);
//    proc.getMemory().write(0xA228, 0x51);
//    proc.setA(0x0);
//    proc.setIX(0xA227);
//    proc.process();
//    REQUIRE(0x0, proc.getMemory().read(0xA228));
//}


//TEST_CASE("NEGTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[1024 * 64]);
//    proc.getMemory().write(0x0, 0xED);
//    proc.getMemory().write(0x1, 0x44);
//    proc.setA(0b10011000);
//    proc.process();
//    proc.process();
//    REQUIRE(0b01100111, proc.getA());
//}



//TEST_CASE("OUT_C_rTest") {
//    /*
//     * If the contents of register C are 01H, and the contents of register D
//     * are 5AH, at execution of OUT (C),D byte 5AH is written to the
//     * peripheral device mapped to I/O port address 01H
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xED, 0b01010001});
//    proc.setC(0x01);
//    proc.setD(0x5A);
//    proc.process();
//    REQUIRE(0x5A, proc.getIo().read(0x01));
//}


//TEST_CASE("OUT_n_ATest") {
//    /*
//     * If the contents of the Accumulator are 23H , at execution of OUT (
//     * 01H ), byte 23H is written to the peripheral device mapped to I/O
//     * port address 01H .
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0xD3, 0x01});
//    proc.setA(0x23);
//    proc.process();
//    REQUIRE(0x23, proc.getIo().read(0x01));
//}

///**
// * If the Stack Pointer contains 1000H, memory location 1000H contains 55H,
// * and location 1001H contains 33H, the instruction POP IX results in Index
// * Register IX containing 3355H, and the Stack Pointer containing 1002H.
// */

//TEST_CASE("POPIXTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xDD);
//    proc.getMemory().write(0x1, 0xE1);
//    proc.getMemory().write(0x1000, 0x55);
//    proc.getMemory().write(0x1001, 0x33);
//    proc.setSP(0x1000);
//    proc.process(2);
//    REQUIRE(0x3355, proc.getIX());
//    REQUIRE(0x1002, proc.getSP());
//}

///**
// * If the Stack Pointer Contains 1000H, memory location 1000H contains 55H,
// * and location 1001H contains 33H, the instruction POP IY results in Index
// * Register IY containing 3355H, and the Stack Pointer containing 1002H.
// */

//TEST_CASE("POPIYTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xFD);
//    proc.getMemory().write(0x1, 0xE1);
//    proc.getMemory().write(0x1000, 0x55);
//    proc.getMemory().write(0x1001, 0x33);
//    proc.setSP(0x1000);
//    proc.process(2);
//    REQUIRE(0x3355, proc.getIY());
//    REQUIRE(0x1002, proc.getSP());
//}

///**
// * If the Stack Pointer contains 1000H, memory location 1000H contains 55H,
// * and location 1001H contains 33H , the instruction POP HL results in
// * register pair HL containing 3355H , and the Stack Pointer containing
// * 1002H
// */

//TEST_CASE("POPqqTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0b11100001); // HL
//    proc.getMemory().write(0x1000, 0x55);
//    proc.getMemory().write(0x1001, 0x33);
//    proc.setSP(0x1000);
//    proc.process();
//    REQUIRE(0x3355, proc.getHL());
//    REQUIRE(0x1002, proc.getSP());
//}


//TEST_CASE("PUSHIXTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xDD);
//    proc.getMemory().write(0x1, 0xE5);
//    proc.setIX(0x2233);
//    proc.setSP(0x1007);
//    proc.process();
//    proc.process();
//    REQUIRE(0x22, proc.getMemory().read(0x1006));
//    REQUIRE(0x33, proc.getMemory().read(0x1005));
//    REQUIRE(0x1005, proc.getSP());
//}


//TEST_CASE("PUSHIYTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xFD);
//    proc.getMemory().write(0x1, 0xE5);
//    proc.setIY(0x2233);
//    proc.setSP(0x1007);
//    proc.process();
//    proc.process();
//    REQUIRE(0x22, proc.getMemory().read(0x1006));
//    REQUIRE(0x33, proc.getMemory().read(0x1005));
//    REQUIRE(0x1005, proc.getSP());
//}



//TEST_CASE("RETccTest") {

//    /*
//     * If the S flag in the F register is set, the contents of the Program
//     * Counter are 3535H, the contents of the Stack Pointer are 2000H , the
//     * contents of memory location 2000H are B5H , and the contents of
//     * memory location 2001H are 18H . At execution of RET M the contents of
//     * the Stack Pointer is 2002H , and the contents of the Program Counter
//     * is 18B5H , pointing to the address of the next program Op Code to be
//     * fetched.
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setSignFlag(true);
//    proc.setPC(0x3535);
//    proc.setSP(0x2000);
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x2000, 0xB5);
//    proc.getMemory().write(0x2001, 0x18);
//    proc.getMemory().write(0x3535, 0b11111000);
//    proc.process(1);
//    REQUIRE(0x2002, proc.getSP());
//    REQUIRE(0x18B5, proc.getPC());

//}

//// RLC RRC RL RR SLA SRA SLL SRL
////
//// TEST_CASE("ROTrTest") {
//// Processor proc = new Processor();
//// proc.setMemory(new int[] {});
//// REQUIRE(true, false);
//// }



//TEST_CASE("RETTest") {
//    /*
//     * If the contents of the Program Counter are 3535H , the contents of
//     * the Stack Pointer are 2000H, the contents of memory location 2000H
//     * are B5H, and the contents of memory location of memory location 2001H
//     * are 18H . At execution of RET the contents of the Stack Pointer is
//     * 2002H, and the contents of the Program Counter is 18B5H, pointing to
//     * the address of the next program Op Code to be fetched.
//     */
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x3535, 0xC9);
//    proc.getMemory().write(0x2000, 0xB5);
//    proc.getMemory().write(0x2001, 0x18);
//    proc.setPC(0x3535);
//    proc.setSP(0x2000);
//    proc.process();
//    REQUIRE(0x2002, proc.getSP());
//    REQUIRE(0x18B5, proc.getPC());
//}


//TEST_CASE("RLATest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setCFlag(true);
//    proc.setA(0b01110110);
//    proc.setMemory(new int[]{0x17});
//    proc.process();
//    REQUIRE(false, proc.getCFlag());
//    REQUIRE(0b11101101, proc.getA());
//}


//TEST_CASE("RLCATest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    // increment BC
//    proc.setMemory(new int[]{0x07});
//    proc.setA(0b10001000);
//    proc.process();
//    System.out.println(Integer.toBinaryString(proc.getA()));
//    REQUIRE(0b00010001, proc.getA());

//    REQUIRE(true, proc.getCFlag());
//}



//TEST_CASE("RRATest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x1F});
//    proc.setCFlag(false);
//    proc.setA(0b11100001);
//    proc.process();
//    REQUIRE(true, proc.getCFlag());
//    REQUIRE(0b01110000, proc.getA());
//}


//TEST_CASE("RRCATest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x0F});
//    proc.setCFlag(false);
//    proc.setA(0b11100001);
//    proc.process();
//    REQUIRE(true, proc.getCFlag());
//    System.out.println(Integer.toBinaryString(proc.getA()));
//    REQUIRE(0b11110000, proc.getA());
//}



//TEST_CASE("RRDTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xED);
//    proc.getMemory().write(0x1, 0x67);
//    proc.getMemory().write(0x5000, 0b00100000);
//    proc.setHL(0x5000);
//    proc.setA(0b10000100);
//    proc.process();
//    proc.process();
//    REQUIRE(0b10000000, proc.getA());
//    REQUIRE(0b01000010, proc.getMemory().read(0x5000));
//}



//TEST_CASE("SCFTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0x37});
//    proc.setNFlag(true);
//    proc.setHFlag(true);
//    proc.setCFlag(false);

//    proc.process();

//    REQUIRE(false, proc.getNFlag());
//    REQUIRE(true, proc.getCFlag());
//    REQUIRE(false, proc.getHFlag());

//}


//TEST_CASE("SETb_HL_Test") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xCB);
//    proc.getMemory().write(0x1, 0b11100110);
//    proc.setHL(0x3000);
//    proc.process(2);
//    REQUIRE(true, (proc.getMemory().read(0x3000) & 0b10000) == 0b10000);
//}


//TEST_CASE("SETb_IXplusd_Test") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xDD);
//    proc.getMemory().write(0x1, 0xCB);
//    proc.getMemory().write(0x2, 0x3);
//    proc.getMemory().write(0x3, 0b11000110);
//    proc.setIX(0x2000);
//    proc.process();
//    proc.process();
//    proc.process();
//    proc.process();
//    REQUIRE(true, (proc.getMemory().read(0x2003) & 1) == 1);
//}

///**
// * If the contents of Index Register IY are 2000H, at execution of
// * SET 0, (IY+3H) bit 0 in memory location 2003H is 1. Bit 0 in memory
// * location 2003H is the least-significant bit.
// */

//TEST_CASE("SETb_IYplusd_Test") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xFD);
//    proc.getMemory().write(0x1, 0xCB);
//    proc.getMemory().write(0x2, 0x3);
//    proc.getMemory().write(0x3, 0b11000110);
//    proc.setIY(0x2000);
//    proc.process(4);
//    REQUIRE(true, (proc.getMemory().read(0x2003) & 1) == 1);
//}


//TEST_CASE("SETbrTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[64 * 1024]);
//    proc.getMemory().write(0x0, 0xCB);
//    proc.getMemory().write(0x1, 0b11100111);
//    proc.process(2);
//    REQUIRE(true, (proc.getA() & 0b10000) == 0b10000);
//}


//TEST_CASE("XORsTest") {
//    EmulationProcessor proc = new EmulationProcessor();
//    proc.setMemory(new int[]{0b10101011});
//    proc.setE(0x96); // 10010110
//    proc.setA(0x5D); // 01011101
//    proc.process();
//    REQUIRE(0b11001011, proc.getA());
//}
