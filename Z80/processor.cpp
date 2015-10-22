#include "Z80/processor.h"
#include "Z80/emu_alu.h"

#include "Logger.h"
#include <boost/utility/binary.hpp>
#include <assert.h>
#include "tables.h"
// #include <iostream>

Processor::Processor(Memory* memory, IO* io) :
memory(memory), io(io)
{
//     std::cout << "Processor ctor" << std::endl;
    registers = new Registers();
}

Processor::~Processor() {
    delete registers;
//     delete &io;
}

void Processor::decode() {
    std::uint8_t currentInstruction[4];
    // get opcode
    currentInstruction[0] = next();
    switch (currentInstruction[0]) {
    case 0x00:
    //logger.debug("NOP - 0 ");
    NOP();
    break;
    case 0x01:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD BC,nn - 1 n n ");
    LD(RegisterPair::BC, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
    case 0x02:
    //logger.debug("LD (BC),A - 2 ");
    LD(MemoryAddress(RegisterPair::BC), Rgstr::A);
    break;
    case 0x03:
    //logger.debug("INC BC - 3 ");
    INC(RegisterPair::BC);
    break;
    case 0x04:
    //logger.debug("INC B - 4 ");
    INC(Rgstr::B);
    break;
    case 0x05:
    //logger.debug("DEC B - 5 ");
    DEC(Rgstr::B);
    break;
    case 0x06:
    currentInstruction[1] = next();
    //logger.debug("LD B,n - 6 n ");
    LD(Rgstr::B, currentInstruction[1]);
    break;
    case 0x07:
    //logger.debug("RLCA - 7 ");
    RLCA();
    break;
    case 0x08:
    //logger.debug("EX AF,AF' - 8 ");
    EX(RegisterPair::AF, RegisterPair::AF_prime);
    break;
    case 0x09:
    //logger.debug("ADD HL,BC - 9 ");
    ADD(RegisterPair::HL, RegisterPair::BC);
    break;
    case 0x0A:
    //logger.debug("LD A,(BC) - a ");
    LD(Rgstr::A, MemoryAddress(RegisterPair::BC));
    break;
    case 0x0B:
    //logger.debug("DEC BC - b ");
    DEC(RegisterPair::BC);
    break;
    case 0x0C:
    //logger.debug("INC C - c ");
    INC(Rgstr::C);
    break;
    case 0x0D:
    //logger.debug("DEC C - d ");
    DEC(Rgstr::C);
    break;
    case 0x0E:
    currentInstruction[1] = next();
    //logger.debug("LD C,n - e n ");
    LD(Rgstr::C, currentInstruction[1]);
    break;
    case 0x0F:
    //logger.debug("RRCA - f ");
    RRCA();
    break;
    case 0x10:
    currentInstruction[1] = next();
    //logger.debug("DJNZ (PC+e) - 10 n ");
    DJNZ(MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
    case 0x11:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD DE,nn - 11 n n ");
    LD(RegisterPair::DE, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
    case 0x12:
    //logger.debug("LD (DE),A - 12 ");
    LD(MemoryAddress(RegisterPair::DE), Rgstr::A);
    break;
    case 0x13:
    //logger.debug("INC DE - 13 ");
    INC(RegisterPair::DE);
    break;
    case 0x14:
    //logger.debug("INC D - 14 ");
    INC(Rgstr::D);
    break;
    case 0x15:
    //logger.debug("DEC D - 15 ");
    DEC(Rgstr::D);
    break;
    case 0x16:
    currentInstruction[1] = next();
    //logger.debug("LD D,n - 16 n ");
    LD(Rgstr::D, currentInstruction[1]);
    break;
    case 0x17:
    //logger.debug("RLA - 17 ");
    RLA();
    break;
    case 0x18:
    currentInstruction[1] = next();
    //logger.debug("JR (PC+e) - 18 n ");
    JR(MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
    case 0x19:
    //logger.debug("ADD HL,DE - 19 ");
    ADD(RegisterPair::HL, RegisterPair::DE);
    break;
    case 0x1A:
    //logger.debug("LD A,(DE) - 1a ");
    LD(Rgstr::A, MemoryAddress(RegisterPair::DE));
    break;
    case 0x1B:
    //logger.debug("DEC DE - 1b ");
    DEC(RegisterPair::DE);
    break;
    case 0x1C:
    //logger.debug("INC E - 1c ");
    INC(Rgstr::E);
    break;
    case 0x1D:
    //logger.debug("DEC E - 1d ");
    DEC(Rgstr::E);
    break;
    case 0x1E:
    currentInstruction[1] = next();
    //logger.debug("LD E,n - 1e n ");
    LD(Rgstr::E, currentInstruction[1]);
    break;
    case 0x1F:
    //logger.debug("RRA - 1f ");
    RRA();
    break;
    case 0x20:
    currentInstruction[1] = next();
    //logger.debug("JR NZ,(PC+e) - 20 n ");
    JR(Condition::NZ, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
    case 0x21:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD HL,nn - 21 n n ");
    LD(RegisterPair::HL, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
    case 0x22:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD (nn),HL - 22 n n ");
    LD(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]), RegisterPair::HL);
    break;
    case 0x23:
    //logger.debug("INC HL - 23 ");
    INC(RegisterPair::HL);
    break;
    case 0x24:
    //logger.debug("INC H - 24 ");
    INC(Rgstr::H);
    break;
    case 0x25:
    //logger.debug("DEC H - 25 ");
    DEC(Rgstr::H);
    break;
    case 0x26:
    currentInstruction[1] = next();
    //logger.debug("LD H,n - 26 n ");
    LD(Rgstr::H, currentInstruction[1]);
    break;
    case 0x27:
    //logger.debug("DAA - 27 ");
    DAA();
    break;
    case 0x28:
    currentInstruction[1] = next();
    //logger.debug("JR Z,(PC+e) - 28 n ");
    JR(Condition::Z, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
    case 0x29:
    //logger.debug("ADD HL,HL - 29 ");
    ADD(RegisterPair::HL, RegisterPair::HL);
    break;
    case 0x2A:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD HL,(nn) - 2a n n ");
    LD_indirect(RegisterPair::HL, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0x2B:
    //logger.debug("DEC HL - 2b ");
    DEC(RegisterPair::HL);
    break;
    case 0x2C:
    //logger.debug("INC L - 2c ");
    INC(Rgstr::L);
    break;
    case 0x2D:
    //logger.debug("DEC L - 2d ");
    DEC(Rgstr::L);
    break;
    case 0x2E:
    currentInstruction[1] = next();
    //logger.debug("LD L,n - 2e n ");
    LD(Rgstr::L, currentInstruction[1]);
    break;
    case 0x2F:
    //logger.debug("CPL - 2f ");
    CPL();
    break;
    case 0x30:
    currentInstruction[1] = next();
    //logger.debug("JR NC,(PC+e) - 30 n ");
    JR(Condition::NC, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
    case 0x31:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD SP,nn - 31 n n ");
    LD(RegisterPair::SP, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
    case 0x32:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD (nn),A - 32 n n ");
    LD(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]), Rgstr::A);
    break;
    case 0x33:
    //logger.debug("INC SP - 33 ");
    INC(RegisterPair::SP);
    break;
    case 0x34:
    //logger.debug("INC (HL) - 34 ");
    INC(MemoryAddress(RegisterPair::HL));
    break;
    case 0x35:
    //logger.debug("DEC (HL) - 35 ");
    DEC(MemoryAddress(RegisterPair::HL));
    break;
    case 0x36:
    currentInstruction[1] = next();
    //logger.debug("LD (HL),n - 36 n ");
    LD(MemoryAddress(RegisterPair::HL), currentInstruction[1]);
    break;
    case 0x37:
    //logger.debug("SCF - 37 ");
    SCF();
    break;
    case 0x38:
    currentInstruction[1] = next();
    //logger.debug("JR C,(PC+e) - 38 n ");
    JR(Condition::C, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
    case 0x39:
    //logger.debug("ADD HL,SP - 39 ");
    ADD(RegisterPair::HL, RegisterPair::SP);
    break;
    case 0x3A:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("LD A,(nn) - 3a n n ");
    LD(Rgstr::A, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0x3B:
    //logger.debug("DEC SP - 3b ");
    DEC(RegisterPair::SP);
    break;
    case 0x3C:
    //logger.debug("INC A - 3c ");
    INC(Rgstr::A);
    break;
    case 0x3D:
    //logger.debug("DEC A - 3d ");
    DEC(Rgstr::A);
    break;
    case 0x3E:
    currentInstruction[1] = next();
    //logger.debug("LD A,n - 3e n ");
    LD(Rgstr::A, currentInstruction[1]);
    break;
    case 0x3F:
    //logger.debug("CCF - 3f ");
    CCF();
    break;
    case 0x40:
    //logger.debug("LD B,B - 40 ");
    LD(Rgstr::B, Rgstr::B);
    break;
    case 0x41:
    //logger.debug("LD B,C - 41 ");
    LD(Rgstr::B, Rgstr::C);
    break;
    case 0x42:
    //logger.debug("LD B,D - 42 ");
    LD(Rgstr::B, Rgstr::D);
    break;
    case 0x43:
    //logger.debug("LD B,E - 43 ");
    LD(Rgstr::B, Rgstr::E);
    break;
    case 0x44:
    //logger.debug("LD B,H - 44 ");
    LD(Rgstr::B, Rgstr::H);
    break;
    case 0x45:
    //logger.debug("LD B,L - 45 ");
    LD(Rgstr::B, Rgstr::L);
    break;
    case 0x46:
    //logger.debug("LD B,(HL) - 46 ");
    LD(Rgstr::B, MemoryAddress(RegisterPair::HL));
    break;
    case 0x47:
    //logger.debug("LD B,A - 47 ");
    LD(Rgstr::B, Rgstr::A);
    break;
    case 0x48:
    //logger.debug("LD C,B - 48 ");
    LD(Rgstr::C, Rgstr::B);
    break;
    case 0x49:
    //logger.debug("LD C,C - 49 ");
    LD(Rgstr::C, Rgstr::C);
    break;
    case 0x4A:
    //logger.debug("LD C,D - 4a ");
    LD(Rgstr::C, Rgstr::D);
    break;
    case 0x4B:
    //logger.debug("LD C,E - 4b ");
    LD(Rgstr::C, Rgstr::E);
    break;
    case 0x4C:
    //logger.debug("LD C,H - 4c ");
    LD(Rgstr::C, Rgstr::H);
    break;
    case 0x4D:
    //logger.debug("LD C,L - 4d ");
    LD(Rgstr::C, Rgstr::L);
    break;
    case 0x4E:
    //logger.debug("LD C,(HL) - 4e ");
    LD(Rgstr::C, MemoryAddress(RegisterPair::HL));
    break;
    case 0x4F:
    //logger.debug("LD C,A - 4f ");
    LD(Rgstr::C, Rgstr::A);
    break;
    case 0x50:
    //logger.debug("LD D,B - 50 ");
    LD(Rgstr::D, Rgstr::B);
    break;
    case 0x51:
    //logger.debug("LD D,C - 51 ");
    LD(Rgstr::D, Rgstr::C);
    break;
    case 0x52:
    //logger.debug("LD D,D - 52 ");
    LD(Rgstr::D, Rgstr::D);
    break;
    case 0x53:
    //logger.debug("LD D,E - 53 ");
    LD(Rgstr::D, Rgstr::E);
    break;
    case 0x54:
    //logger.debug("LD D,H - 54 ");
    LD(Rgstr::D, Rgstr::H);
    break;
    case 0x55:
    //logger.debug("LD D,L - 55 ");
    LD(Rgstr::D, Rgstr::L);
    break;
    case 0x56:
    //logger.debug("LD D,(HL) - 56 ");
    LD(Rgstr::D, MemoryAddress(RegisterPair::HL));
    break;
    case 0x57:
    //logger.debug("LD D,A - 57 ");
    LD(Rgstr::D, Rgstr::A);
    break;
    case 0x58:
    //logger.debug("LD E,B - 58 ");
    LD(Rgstr::E, Rgstr::B);
    break;
    case 0x59:
    //logger.debug("LD E,C - 59 ");
    LD(Rgstr::E, Rgstr::C);
    break;
    case 0x5A:
    //logger.debug("LD E,D - 5a ");
    LD(Rgstr::E, Rgstr::D);
    break;
    case 0x5B:
    //logger.debug("LD E,E - 5b ");
    LD(Rgstr::E, Rgstr::E);
    break;
    case 0x5C:
    //logger.debug("LD E,H - 5c ");
    LD(Rgstr::E, Rgstr::H);
    break;
    case 0x5D:
    //logger.debug("LD E,L - 5d ");
    LD(Rgstr::E, Rgstr::L);
    break;
    case 0x5E:
    //logger.debug("LD E,(HL) - 5e ");
    LD(Rgstr::E, MemoryAddress(RegisterPair::HL));
    break;
    case 0x5F:
    //logger.debug("LD E,A - 5f ");
    LD(Rgstr::E, Rgstr::A);
    break;
    case 0x60:
    //logger.debug("LD H,B - 60 ");
    LD(Rgstr::H, Rgstr::B);
    break;
    case 0x61:
    //logger.debug("LD H,C - 61 ");
    LD(Rgstr::H, Rgstr::C);
    break;
    case 0x62:
    //logger.debug("LD H,D - 62 ");
    LD(Rgstr::H, Rgstr::D);
    break;
    case 0x63:
    //logger.debug("LD H,E - 63 ");
    LD(Rgstr::H, Rgstr::E);
    break;
    case 0x64:
    //logger.debug("LD H,H - 64 ");
    LD(Rgstr::H, Rgstr::H);
    break;
    case 0x65:
    //logger.debug("LD H,L - 65 ");
    LD(Rgstr::H, Rgstr::L);
    break;
    case 0x66:
    //logger.debug("LD H,(HL) - 66 ");
    LD(Rgstr::H, MemoryAddress(RegisterPair::HL));
    break;
    case 0x67:
    //logger.debug("LD H,A - 67 ");
    LD(Rgstr::H, Rgstr::A);
    break;
    case 0x68:
    //logger.debug("LD L,B - 68 ");
    LD(Rgstr::L, Rgstr::B);
    break;
    case 0x69:
    //logger.debug("LD L,C - 69 ");
    LD(Rgstr::L, Rgstr::C);
    break;
    case 0x6A:
    //logger.debug("LD L,D - 6a ");
    LD(Rgstr::L, Rgstr::D);
    break;
    case 0x6B:
    //logger.debug("LD L,E - 6b ");
    LD(Rgstr::L, Rgstr::E);
    break;
    case 0x6C:
    //logger.debug("LD L,H - 6c ");
    LD(Rgstr::L, Rgstr::H);
    break;
    case 0x6D:
    //logger.debug("LD L,L - 6d ");
    LD(Rgstr::L, Rgstr::L);
    break;
    case 0x6E:
    //logger.debug("LD L,(HL) - 6e ");
    LD(Rgstr::L, MemoryAddress(RegisterPair::HL));
    break;
    case 0x6F:
    //logger.debug("LD L,A - 6f ");
    LD(Rgstr::L, Rgstr::A);
    break;
    case 0x70:
    //logger.debug("LD (HL),B - 70 ");
    LD(MemoryAddress(RegisterPair::HL), Rgstr::B);
    break;
    case 0x71:
    //logger.debug("LD (HL),C - 71 ");
    LD(MemoryAddress(RegisterPair::HL), Rgstr::C);
    break;
    case 0x72:
    //logger.debug("LD (HL),D - 72 ");
    LD(MemoryAddress(RegisterPair::HL), Rgstr::D);
    break;
    case 0x73:
    //logger.debug("LD (HL),E - 73 ");
    LD(MemoryAddress(RegisterPair::HL), Rgstr::E);
    break;
    case 0x74:
    //logger.debug("LD (HL),H - 74 ");
    LD(MemoryAddress(RegisterPair::HL), Rgstr::H);
    break;
    case 0x75:
    //logger.debug("LD (HL),L - 75 ");
    LD(MemoryAddress(RegisterPair::HL), Rgstr::L);
    break;
    case 0x76:
    //logger.debug("HALT - 76 ");
    HALT();
    break;
    case 0x77:
    //logger.debug("LD (HL),A - 77 ");
    LD(MemoryAddress(RegisterPair::HL), Rgstr::A);
    break;
    case 0x78:
    //logger.debug("LD A,B - 78 ");
    LD(Rgstr::A, Rgstr::B);
    break;
    case 0x79:
    //logger.debug("LD A,C - 79 ");
    LD(Rgstr::A, Rgstr::C);
    break;
    case 0x7A:
    //logger.debug("LD A,D - 7a ");
    LD(Rgstr::A, Rgstr::D);
    break;
    case 0x7B:
    //logger.debug("LD A,E - 7b ");
    LD(Rgstr::A, Rgstr::E);
    break;
    case 0x7C:
    //logger.debug("LD A,H - 7c ");
    LD(Rgstr::A, Rgstr::H);
    break;
    case 0x7D:
    //logger.debug("LD A,L - 7d ");
    LD(Rgstr::A, Rgstr::L);
    break;
    case 0x7E:
    //logger.debug("LD A,(HL) - 7e ");
    LD(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
    case 0x7F:
    //logger.debug("LD A,A - 7f ");
    LD(Rgstr::A, Rgstr::A);
    break;
    case 0x80:
    //logger.debug("ADD A,B - 80 ");
    ADD(Rgstr::A, Rgstr::B);
    break;
    case 0x81:
    //logger.debug("ADD A,C - 81 ");
    ADD(Rgstr::A, Rgstr::C);
    break;
    case 0x82:
    //logger.debug("ADD A,D - 82 ");
    ADD(Rgstr::A, Rgstr::D);
    break;
    case 0x83:
    //logger.debug("ADD A,E - 83 ");
    ADD(Rgstr::A, Rgstr::E);
    break;
    case 0x84:
    //logger.debug("ADD A,H - 84 ");
    ADD(Rgstr::A, Rgstr::H);
    break;
    case 0x85:
    //logger.debug("ADD A,L - 85 ");
    ADD(Rgstr::A, Rgstr::L);
    break;
    case 0x86:
    //logger.debug("ADD A,(HL) - 86 ");
    ADD(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
    case 0x87:
    //logger.debug("ADD A,A - 87 ");
    ADD(Rgstr::A, Rgstr::A);
    break;
    case 0x88:
    //logger.info("ADC A,B - 88 ");
    ADC(Rgstr::A, Rgstr::B);
    break;
    case 0x89:
    //logger.info("ADC A,C - 89 ");
    ADC(Rgstr::A, Rgstr::C);
    break;
    case 0x8A:
    //logger.info("ADC A,D - 8a ");
    ADC(Rgstr::A, Rgstr::D);
    break;
    case 0x8B:
    //logger.info("ADC A,E - 8b ");
    ADC(Rgstr::A, Rgstr::E);
    break;
    case 0x8C:
    //logger.info("ADC A,H - 8c ");
    ADC(Rgstr::A, Rgstr::H);
    break;
    case 0x8D:
    //logger.info("ADC A,L - 8d ");
    ADC(Rgstr::A, Rgstr::L);
    break;
    case 0x8E:
    //logger.info("ADC A,(HL) - 8e ");
    ADC(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
    case 0x8F:
    //logger.info("ADC A,A - 8f ");
    ADC(Rgstr::A, Rgstr::A);
    break;
    case 0x90:
    //logger.debug("SUB B - 90 ");
    SUB(Rgstr::B);
    break;
    case 0x91:
    //logger.debug("SUB C - 91 ");
    SUB(Rgstr::C);
    break;
    case 0x92:
    //logger.debug("SUB D - 92 ");
    SUB(Rgstr::D);
    break;
    case 0x93:
    //logger.debug("SUB E - 93 ");
    SUB(Rgstr::E);
    break;
    case 0x94:
    //logger.debug("SUB H - 94 ");
    SUB(Rgstr::H);
    break;
    case 0x95:
    //logger.debug("SUB L - 95 ");
    SUB(Rgstr::L);
    break;
    case 0x96:
    //logger.debug("SUB (HL) - 96 ");
    SUB(MemoryAddress(RegisterPair::HL));
    break;
    case 0x97:
    //logger.debug("SUB A - 97 ");
    SUB(Rgstr::A);
    break;
    case 0x98:
    //logger.info("SBC A,B - 98 ");
    SBC(Rgstr::A, Rgstr::B);
    break;
    case 0x99:
    //logger.info("SBC A,C - 99 ");
    SBC(Rgstr::A, Rgstr::C);
    break;
    case 0x9A:
    //logger.info("SBC A,D - 9a ");
    SBC(Rgstr::A, Rgstr::D);
    break;
    case 0x9B:
    //logger.info("SBC A,E - 9b ");
    SBC(Rgstr::A, Rgstr::E);
    break;
    case 0x9C:
    //logger.info("SBC A,H - 9c ");
    SBC(Rgstr::A, Rgstr::H);
    break;
    case 0x9D:
    //logger.info("SBC A,L - 9d ");
    SBC(Rgstr::A, Rgstr::L);
    break;
    case 0x9E:
    //logger.info("SBC A,(HL) - 9e ");
    SBC(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
    case 0x9F:
    //logger.info("SBC A,A - 9f ");
    SBC(Rgstr::A, Rgstr::A);
    break;
    case 0xA0:
    //logger.debug("AND B - a0 ");
    AND(Rgstr::B);
    break;
    case 0xA1:
    //logger.debug("AND C - a1 ");
    AND(Rgstr::C);
    break;
    case 0xA2:
    //logger.debug("AND D - a2 ");
    AND(Rgstr::D);
    break;
    case 0xA3:
    //logger.debug("AND E - a3 ");
    AND(Rgstr::E);
    break;
    case 0xA4:
    //logger.debug("AND H - a4 ");
    AND(Rgstr::H);
    break;
    case 0xA5:
    //logger.debug("AND L - a5 ");
    AND(Rgstr::L);
    break;
    case 0xA6:
    //logger.debug("AND (HL) - a6 ");
    AND(MemoryAddress(RegisterPair::HL));
    break;
    case 0xA7:
    //logger.debug("AND A - a7 ");
    AND(Rgstr::A);
    break;
    case 0xA8:
    //logger.debug("XOR B - a8 ");
    XOR(Rgstr::B);
    break;
    case 0xA9:
    //logger.debug("XOR C - a9 ");
    XOR(Rgstr::C);
    break;
    case 0xAA:
    //logger.debug("XOR D - aa ");
    XOR(Rgstr::D);
    break;
    case 0xAB:
    //logger.debug("XOR E - ab ");
    XOR(Rgstr::E);
    break;
    case 0xAC:
    //logger.debug("XOR H - ac ");
    XOR(Rgstr::H);
    break;
    case 0xAD:
    //logger.debug("XOR L - ad ");
    XOR(Rgstr::L);
    break;
    case 0xAE:
    //logger.debug("XOR (HL) - ae ");
    XOR(MemoryAddress(RegisterPair::HL));
    break;
    case 0xAF:
    //logger.debug("XOR A - af ");
    XOR(Rgstr::A);
    break;
    case 0xB0:
    //logger.debug("OR B - b0 ");
    OR(Rgstr::B);
    break;
    case 0xB1:
    //logger.debug("OR C - b1 ");
    OR(Rgstr::C);
    break;
    case 0xB2:
    //logger.debug("OR D - b2 ");
    OR(Rgstr::D);
    break;
    case 0xB3:
    //logger.debug("OR E - b3 ");
    OR(Rgstr::E);
    break;
    case 0xB4:
    //logger.debug("OR H - b4 ");
    OR(Rgstr::H);
    break;
    case 0xB5:
    //logger.debug("OR L - b5 ");
    OR(Rgstr::L);
    break;
    case 0xB6:
    //logger.debug("OR (HL) - b6 ");
    OR(MemoryAddress(RegisterPair::HL));
    break;
    case 0xB7:
    //logger.debug("OR A - b7 ");
    OR(Rgstr::A);
    break;
    case 0xB8:
    //logger.debug("CP B - b8 ");
    CP(Rgstr::B);
    break;
    case 0xB9:
    //logger.debug("CP C - b9 ");
    CP(Rgstr::C);
    break;
    case 0xBA:
    //logger.debug("CP D - ba ");
    CP(Rgstr::D);
    break;
    case 0xBB:
    //logger.debug("CP E - bb ");
    CP(Rgstr::E);
    break;
    case 0xBC:
    //logger.debug("CP H - bc ");
    CP(Rgstr::H);
    break;
    case 0xBD:
    //logger.debug("CP L - bd ");
    CP(Rgstr::L);
    break;
    case 0xBE:
    //logger.debug("CP (HL) - be ");
    CP(MemoryAddress(RegisterPair::HL));
    break;
    case 0xBF:
    //logger.debug("CP A - bf ");
    CP(Rgstr::A);
    break;
    case 0xC0:
    //logger.debug("RET NZ - c0 ");
    RET(Condition::NZ);
    break;
    case 0xC1:
    //logger.debug("POP BC - c1 ");
    POP(RegisterPair::BC);
    break;
    case 0xC2:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP NZ,(nn) - c2 n n ");
    JP(Condition::NZ, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xC3:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP (nn) - c3 n n ");
    JP(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xC4:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL NZ,(nn) - c4 n n ");
    CALL(Condition::NZ, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xC5:
    //logger.debug("PUSH BC - c5 ");
    PUSH(RegisterPair::BC);
    break;
    case 0xC6:
    currentInstruction[1] = next();
    //logger.debug("ADD A,n - c6 n ");
    ADD(Rgstr::A, currentInstruction[1]);
    break;
    case 0xC7:
    //logger.debug("RST 0H - c7 ");
    RST(0x0);
    break;
    case 0xC8:
    //logger.debug("RET Z - c8 ");
    RET(Condition::Z);
    break;
    case 0xC9:
    //logger.debug("RET - c9 ");
    RET();
    break;
    case 0xCA:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP Z,(nn) - ca n n ");
    JP(Condition::Z, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xCB:
    // get opcode
    currentInstruction[1] = next();
    switch (currentInstruction[1]) {
    case 0x00:
    //logger.debug("RLC B - cb 0 ");
    RLC(Rgstr::B);
    break;
    case 0x01:
    //logger.debug("RLC C - cb 1 ");
    RLC(Rgstr::C);
    break;
    case 0x02:
    //logger.debug("RLC D - cb 2 ");
    RLC(Rgstr::D);
    break;
    case 0x03:
    //logger.debug("RLC E - cb 3 ");
    RLC(Rgstr::E);
    break;
    case 0x04:
    //logger.debug("RLC H - cb 4 ");
    RLC(Rgstr::H);
    break;
    case 0x05:
    //logger.debug("RLC L - cb 5 ");
    RLC(Rgstr::L);
    break;
    case 0x06:
    //logger.debug("RLC (HL) - cb 6 ");
    RLC(MemoryAddress(RegisterPair::HL));
    break;
    case 0x07:
    //logger.debug("RLC A - cb 7 ");
    RLC(Rgstr::A);
    break;
    case 0x08:
    //logger.debug("RRC B - cb 8 ");
    RRC(Rgstr::B);
    break;
    case 0x09:
    //logger.debug("RRC C - cb 9 ");
    RRC(Rgstr::C);
    break;
    case 0x0A:
    //logger.debug("RRC D - cb a ");
    RRC(Rgstr::D);
    break;
    case 0x0B:
    //logger.debug("RRC E - cb b ");
    RRC(Rgstr::E);
    break;
    case 0x0C:
    //logger.debug("RRC H - cb c ");
    RRC(Rgstr::H);
    break;
    case 0x0D:
    //logger.debug("RRC L - cb d ");
    RRC(Rgstr::L);
    break;
    case 0x0E:
    //logger.debug("RRC (HL) - cb e ");
    RRC(MemoryAddress(RegisterPair::HL));
    break;
    case 0x0F:
    //logger.debug("RRC A - cb f ");
    RRC(Rgstr::A);
    break;
    case 0x10:
    //logger.debug("RL B - cb 10 ");
    RL(Rgstr::B);
    break;
    case 0x11:
    //logger.debug("RL C - cb 11 ");
    RL(Rgstr::C);
    break;
    case 0x12:
    //logger.debug("RL D - cb 12 ");
    RL(Rgstr::D);
    break;
    case 0x13:
    //logger.debug("RL E - cb 13 ");
    RL(Rgstr::E);
    break;
    case 0x14:
    //logger.debug("RL H - cb 14 ");
    RL(Rgstr::H);
    break;
    case 0x15:
    //logger.debug("RL L - cb 15 ");
    RL(Rgstr::L);
    break;
    case 0x16:
    //logger.debug("RL (HL) - cb 16 ");
    RL(MemoryAddress(RegisterPair::HL));
    break;
    case 0x17:
    //logger.debug("RL A - cb 17 ");
    RL(Rgstr::A);
    break;
    case 0x18:
    //logger.debug("RR B - cb 18 ");
    RR(Rgstr::B);
    break;
    case 0x19:
    //logger.debug("RR C - cb 19 ");
    RR(Rgstr::C);
    break;
    case 0x1A:
    //logger.debug("RR D - cb 1a ");
    RR(Rgstr::D);
    break;
    case 0x1B:
    //logger.debug("RR E - cb 1b ");
    RR(Rgstr::E);
    break;
    case 0x1C:
    //logger.debug("RR H - cb 1c ");
    RR(Rgstr::H);
    break;
    case 0x1D:
    //logger.debug("RR L - cb 1d ");
    RR(Rgstr::L);
    break;
    case 0x1E:
    //logger.debug("RR (HL) - cb 1e ");
    RR(MemoryAddress(RegisterPair::HL));
    break;
    case 0x1F:
    //logger.debug("RR A - cb 1f ");
    RR(Rgstr::A);
    break;
    case 0x20:
    //logger.debug("SLA B - cb 20 ");
    SLA(Rgstr::B);
    break;
    case 0x21:
    //logger.debug("SLA C - cb 21 ");
    SLA(Rgstr::C);
    break;
    case 0x22:
    //logger.debug("SLA D - cb 22 ");
    SLA(Rgstr::D);
    break;
    case 0x23:
    //logger.debug("SLA E - cb 23 ");
    SLA(Rgstr::E);
    break;
    case 0x24:
    //logger.debug("SLA H - cb 24 ");
    SLA(Rgstr::H);
    break;
    case 0x25:
    //logger.debug("SLA L - cb 25 ");
    SLA(Rgstr::L);
    break;
    case 0x26:
    //logger.debug("SLA (HL) - cb 26 ");
    SLA(MemoryAddress(RegisterPair::HL));
    break;
    case 0x27:
    //logger.debug("SLA A - cb 27 ");
    SLA(Rgstr::A);
    break;
    case 0x28:
    //logger.debug("SRA B - cb 28 ");
    SRA(Rgstr::B);
    break;
    case 0x29:
    //logger.debug("SRA C - cb 29 ");
    SRA(Rgstr::C);
    break;
    case 0x2A:
    //logger.debug("SRA D - cb 2a ");
    SRA(Rgstr::D);
    break;
    case 0x2B:
    //logger.debug("SRA E - cb 2b ");
    SRA(Rgstr::E);
    break;
    case 0x2C:
    //logger.debug("SRA H - cb 2c ");
    SRA(Rgstr::H);
    break;
    case 0x2D:
    //logger.debug("SRA L - cb 2d ");
    SRA(Rgstr::L);
    break;
    case 0x2E:
    //logger.debug("SRA (HL) - cb 2e ");
    SRA(MemoryAddress(RegisterPair::HL));
    break;
    case 0x2F:
    //logger.debug("SRA A - cb 2f ");
    SRA(Rgstr::A);
    break;
    case 0x38:
    //logger.debug("SRL B - cb 38 ");
    SRL(Rgstr::B);
    break;
    case 0x39:
    //logger.debug("SRL C - cb 39 ");
    SRL(Rgstr::C);
    break;
    case 0x3A:
    //logger.debug("SRL D - cb 3a ");
    SRL(Rgstr::D);
    break;
    case 0x3B:
    //logger.debug("SRL E - cb 3b ");
    SRL(Rgstr::E);
    break;
    case 0x3C:
    //logger.debug("SRL H - cb 3c ");
    SRL(Rgstr::H);
    break;
    case 0x3D:
    //logger.debug("SRL L - cb 3d ");
    SRL(Rgstr::L);
    break;
    case 0x3E:
    //logger.debug("SRL (HL) - cb 3e ");
    SRL(MemoryAddress(RegisterPair::HL));
    break;
    case 0x3F:
    //logger.debug("SRL A - cb 3f ");
    SRL(Rgstr::A);
    break;
    case 0x40:
    //logger.debug("BIT 0,B - cb 40 ");
    BIT(0, Rgstr::B);
    break;
    case 0x41:
    //logger.debug("BIT 0,C - cb 41 ");
    BIT(0, Rgstr::C);
    break;
    case 0x42:
    //logger.debug("BIT 0,D - cb 42 ");
    BIT(0, Rgstr::D);
    break;
    case 0x43:
    //logger.debug("BIT 0,E - cb 43 ");
    BIT(0, Rgstr::E);
    break;
    case 0x44:
    //logger.debug("BIT 0,H - cb 44 ");
    BIT(0, Rgstr::H);
    break;
    case 0x45:
    //logger.debug("BIT 0,L - cb 45 ");
    BIT(0, Rgstr::L);
    break;
    case 0x46:
    //logger.debug("BIT 0,(HL) - cb 46 ");
    BIT(0, MemoryAddress(RegisterPair::HL));
    break;
    case 0x47:
    //logger.debug("BIT 0,A - cb 47 ");
    BIT(0, Rgstr::A);
    break;
    case 0x48:
    //logger.debug("BIT 1,B - cb 48 ");
    BIT(1, Rgstr::B);
    break;
    case 0x49:
    //logger.debug("BIT 1,C - cb 49 ");
    BIT(1, Rgstr::C);
    break;
    case 0x4A:
    //logger.debug("BIT 1,D - cb 4a ");
    BIT(1, Rgstr::D);
    break;
    case 0x4B:
    //logger.debug("BIT 1,E - cb 4b ");
    BIT(1, Rgstr::E);
    break;
    case 0x4C:
    //logger.debug("BIT 1,H - cb 4c ");
    BIT(1, Rgstr::H);
    break;
    case 0x4D:
    //logger.debug("BIT 1,L - cb 4d ");
    BIT(1, Rgstr::L);
    break;
    case 0x4E:
    //logger.debug("BIT 1,(HL) - cb 4e ");
    BIT(1, MemoryAddress(RegisterPair::HL));
    break;
    case 0x4F:
    //logger.debug("BIT 1,A - cb 4f ");
    BIT(1, Rgstr::A);
    break;
    case 0x50:
    //logger.debug("BIT 2,B - cb 50 ");
    BIT(2, Rgstr::B);
    break;
    case 0x51:
    //logger.debug("BIT 2,C - cb 51 ");
    BIT(2, Rgstr::C);
    break;
    case 0x52:
    //logger.debug("BIT 2,D - cb 52 ");
    BIT(2, Rgstr::D);
    break;
    case 0x53:
    //logger.debug("BIT 2,E - cb 53 ");
    BIT(2, Rgstr::E);
    break;
    case 0x54:
    //logger.debug("BIT 2,H - cb 54 ");
    BIT(2, Rgstr::H);
    break;
    case 0x55:
    //logger.debug("BIT 2,L - cb 55 ");
    BIT(2, Rgstr::L);
    break;
    case 0x56:
    //logger.debug("BIT 2,(HL) - cb 56 ");
    BIT(2, MemoryAddress(RegisterPair::HL));
    break;
    case 0x57:
    //logger.debug("BIT 2,A - cb 57 ");
    BIT(2, Rgstr::A);
    break;
    case 0x58:
    //logger.debug("BIT 3,B - cb 58 ");
    BIT(3, Rgstr::B);
    break;
    case 0x59:
    //logger.debug("BIT 3,C - cb 59 ");
    BIT(3, Rgstr::C);
    break;
    case 0x5A:
    //logger.debug("BIT 3,D - cb 5a ");
    BIT(3, Rgstr::D);
    break;
    case 0x5B:
    //logger.debug("BIT 3,E - cb 5b ");
    BIT(3, Rgstr::E);
    break;
    case 0x5C:
    //logger.debug("BIT 3,H - cb 5c ");
    BIT(3, Rgstr::H);
    break;
    case 0x5D:
    //logger.debug("BIT 3,L - cb 5d ");
    BIT(3, Rgstr::L);
    break;
    case 0x5E:
    //logger.debug("BIT 3,(HL) - cb 5e ");
    BIT(3, MemoryAddress(RegisterPair::HL));
    break;
    case 0x5F:
    //logger.debug("BIT 3,A - cb 5f ");
    BIT(3, Rgstr::A);
    break;
    case 0x60:
    //logger.debug("BIT 4,B - cb 60 ");
    BIT(4, Rgstr::B);
    break;
    case 0x61:
    //logger.debug("BIT 4,C - cb 61 ");
    BIT(4, Rgstr::C);
    break;
    case 0x62:
    //logger.debug("BIT 4,D - cb 62 ");
    BIT(4, Rgstr::D);
    break;
    case 0x63:
    //logger.debug("BIT 4,E - cb 63 ");
    BIT(4, Rgstr::E);
    break;
    case 0x64:
    //logger.debug("BIT 4,H - cb 64 ");
    BIT(4, Rgstr::H);
    break;
    case 0x65:
    //logger.debug("BIT 4,L - cb 65 ");
    BIT(4, Rgstr::L);
    break;
    case 0x66:
    //logger.debug("BIT 4,(HL) - cb 66 ");
    BIT(4, MemoryAddress(RegisterPair::HL));
    break;
    case 0x67:
    //logger.debug("BIT 4,A - cb 67 ");
    BIT(4, Rgstr::A);
    break;
    case 0x68:
    //logger.debug("BIT 5,B - cb 68 ");
    BIT(5, Rgstr::B);
    break;
    case 0x69:
    //logger.debug("BIT 5,C - cb 69 ");
    BIT(5, Rgstr::C);
    break;
    case 0x6A:
    //logger.debug("BIT 5,D - cb 6a ");
    BIT(5, Rgstr::D);
    break;
    case 0x6B:
    //logger.debug("BIT 5,E - cb 6b ");
    BIT(5, Rgstr::E);
    break;
    case 0x6C:
    //logger.debug("BIT 5,H - cb 6c ");
    BIT(5, Rgstr::H);
    break;
    case 0x6D:
    //logger.debug("BIT 5,L - cb 6d ");
    BIT(5, Rgstr::L);
    break;
    case 0x6E:
    //logger.debug("BIT 5,(HL) - cb 6e ");
    BIT(5, MemoryAddress(RegisterPair::HL));
    break;
    case 0x6F:
    //logger.debug("BIT 5,A - cb 6f ");
    BIT(5, Rgstr::A);
    break;
    case 0x70:
    //logger.debug("BIT 6,B - cb 70 ");
    BIT(6, Rgstr::B);
    break;
    case 0x71:
    //logger.debug("BIT 6,C - cb 71 ");
    BIT(6, Rgstr::C);
    break;
    case 0x72:
    //logger.debug("BIT 6,D - cb 72 ");
    BIT(6, Rgstr::D);
    break;
    case 0x73:
    //logger.debug("BIT 6,E - cb 73 ");
    BIT(6, Rgstr::E);
    break;
    case 0x74:
    //logger.debug("BIT 6,H - cb 74 ");
    BIT(6, Rgstr::H);
    break;
    case 0x75:
    //logger.debug("BIT 6,L - cb 75 ");
    BIT(6, Rgstr::L);
    break;
    case 0x76:
    //logger.debug("BIT 6,(HL) - cb 76 ");
    BIT(6, MemoryAddress(RegisterPair::HL));
    break;
    case 0x77:
    //logger.debug("BIT 6,A - cb 77 ");
    BIT(6, Rgstr::A);
    break;
    case 0x78:
    //logger.debug("BIT 7,B - cb 78 ");
    BIT(7, Rgstr::B);
    break;
    case 0x79:
    //logger.debug("BIT 7,C - cb 79 ");
    BIT(7, Rgstr::C);
    break;
    case 0x7A:
    //logger.debug("BIT 7,D - cb 7a ");
    BIT(7, Rgstr::D);
    break;
    case 0x7B:
    //logger.debug("BIT 7,E - cb 7b ");
    BIT(7, Rgstr::E);
    break;
    case 0x7C:
    //logger.debug("BIT 7,H - cb 7c ");
    BIT(7, Rgstr::H);
    break;
    case 0x7D:
    //logger.debug("BIT 7,L - cb 7d ");
    BIT(7, Rgstr::L);
    break;
    case 0x7E:
    //logger.debug("BIT 7,(HL) - cb 7e ");
    BIT(7, MemoryAddress(RegisterPair::HL));
    break;
    case 0x7F:
    //logger.debug("BIT 7,A - cb 7f ");
    BIT(7, Rgstr::A);
    break;
    case 0x80:
    //logger.debug("RES 0,B - cb 80 ");
    RES(0, Rgstr::B);
    break;
    case 0x81:
    //logger.debug("RES 0,C - cb 81 ");
    RES(0, Rgstr::C);
    break;
    case 0x82:
    //logger.debug("RES 0,D - cb 82 ");
    RES(0, Rgstr::D);
    break;
    case 0x83:
    //logger.debug("RES 0,E - cb 83 ");
    RES(0, Rgstr::E);
    break;
    case 0x84:
    //logger.debug("RES 0,H - cb 84 ");
    RES(0, Rgstr::H);
    break;
    case 0x85:
    //logger.debug("RES 0,L - cb 85 ");
    RES(0, Rgstr::L);
    break;
    case 0x86:
    //logger.debug("RES 0,(HL) - cb 86 ");
    RES(0, MemoryAddress(RegisterPair::HL));
    break;
    case 0x87:
    //logger.debug("RES 0,A - cb 87 ");
    RES(0, Rgstr::A);
    break;
    case 0x88:
    //logger.debug("RES 1,B - cb 88 ");
    RES(1, Rgstr::B);
    break;
    case 0x89:
    //logger.debug("RES 1,C - cb 89 ");
    RES(1, Rgstr::C);
    break;
    case 0x8A:
    //logger.debug("RES 1,D - cb 8a ");
    RES(1, Rgstr::D);
    break;
    case 0x8B:
    //logger.debug("RES 1,E - cb 8b ");
    RES(1, Rgstr::E);
    break;
    case 0x8C:
    //logger.debug("RES 1,H - cb 8c ");
    RES(1, Rgstr::H);
    break;
    case 0x8D:
    //logger.debug("RES 1,L - cb 8d ");
    RES(1, Rgstr::L);
    break;
    case 0x8E:
    //logger.debug("RES 1,(HL) - cb 8e ");
    RES(1, MemoryAddress(RegisterPair::HL));
    break;
    case 0x8F:
    //logger.debug("RES 1,A - cb 8f ");
    RES(1, Rgstr::A);
    break;
    case 0x90:
    //logger.debug("RES 2,B - cb 90 ");
    RES(2, Rgstr::B);
    break;
    case 0x91:
    //logger.debug("RES 2,C - cb 91 ");
    RES(2, Rgstr::C);
    break;
    case 0x92:
    //logger.debug("RES 2,D - cb 92 ");
    RES(2, Rgstr::D);
    break;
    case 0x93:
    //logger.debug("RES 2,E - cb 93 ");
    RES(2, Rgstr::E);
    break;
    case 0x94:
    //logger.debug("RES 2,H - cb 94 ");
    RES(2, Rgstr::H);
    break;
    case 0x95:
    //logger.debug("RES 2,L - cb 95 ");
    RES(2, Rgstr::L);
    break;
    case 0x96:
    //logger.debug("RES 2,(HL) - cb 96 ");
    RES(2, MemoryAddress(RegisterPair::HL));
    break;
    case 0x97:
    //logger.debug("RES 2,A - cb 97 ");
    RES(2, Rgstr::A);
    break;
    case 0x98:
    //logger.debug("RES 3,B - cb 98 ");
    RES(3, Rgstr::B);
    break;
    case 0x99:
    //logger.debug("RES 3,C - cb 99 ");
    RES(3, Rgstr::C);
    break;
    case 0x9A:
    //logger.debug("RES 3,D - cb 9a ");
    RES(3, Rgstr::D);
    break;
    case 0x9B:
    //logger.debug("RES 3,E - cb 9b ");
    RES(3, Rgstr::E);
    break;
    case 0x9C:
    //logger.debug("RES 3,H - cb 9c ");
    RES(3, Rgstr::H);
    break;
    case 0x9D:
    //logger.debug("RES 3,L - cb 9d ");
    RES(3, Rgstr::L);
    break;
    case 0x9E:
    //logger.debug("RES 3,(HL) - cb 9e ");
    RES(3, MemoryAddress(RegisterPair::HL));
    break;
    case 0x9F:
    //logger.debug("RES 3,A - cb 9f ");
    RES(3, Rgstr::A);
    break;
    case 0xA0:
    //logger.debug("RES 4,B - cb a0 ");
    RES(4, Rgstr::B);
    break;
    case 0xA1:
    //logger.debug("RES 4,C - cb a1 ");
    RES(4, Rgstr::C);
    break;
    case 0xA2:
    //logger.debug("RES 4,D - cb a2 ");
    RES(4, Rgstr::D);
    break;
    case 0xA3:
    //logger.debug("RES 4,E - cb a3 ");
    RES(4, Rgstr::E);
    break;
    case 0xA4:
    //logger.debug("RES 4,H - cb a4 ");
    RES(4, Rgstr::H);
    break;
    case 0xA5:
    //logger.debug("RES 4,L - cb a5 ");
    RES(4, Rgstr::L);
    break;
    case 0xA6:
    //logger.debug("RES 4,(HL) - cb a6 ");
    RES(4, MemoryAddress(RegisterPair::HL));
    break;
    case 0xA7:
    //logger.debug("RES 4,A - cb a7 ");
    RES(4, Rgstr::A);
    break;
    case 0xA8:
    //logger.debug("RES 5,B - cb a8 ");
    RES(5, Rgstr::B);
    break;
    case 0xA9:
    //logger.debug("RES 5,C - cb a9 ");
    RES(5, Rgstr::C);
    break;
    case 0xAA:
    //logger.debug("RES 5,D - cb aa ");
    RES(5, Rgstr::D);
    break;
    case 0xAB:
    //logger.debug("RES 5,E - cb ab ");
    RES(5, Rgstr::E);
    break;
    case 0xAC:
    //logger.debug("RES 5,H - cb ac ");
    RES(5, Rgstr::H);
    break;
    case 0xAD:
    //logger.debug("RES 5,L - cb ad ");
    RES(5, Rgstr::L);
    break;
    case 0xAE:
    //logger.debug("RES 5,(HL) - cb ae ");
    RES(5, MemoryAddress(RegisterPair::HL));
    break;
    case 0xAF:
    //logger.debug("RES 5,A - cb af ");
    RES(5, Rgstr::A);
    break;
    case 0xB0:
    //logger.debug("RES 6,B - cb b0 ");
    RES(6, Rgstr::B);
    break;
    case 0xB1:
    //logger.debug("RES 6,C - cb b1 ");
    RES(6, Rgstr::C);
    break;
    case 0xB2:
    //logger.debug("RES 6,D - cb b2 ");
    RES(6, Rgstr::D);
    break;
    case 0xB3:
    //logger.debug("RES 6,E - cb b3 ");
    RES(6, Rgstr::E);
    break;
    case 0xB4:
    //logger.debug("RES 6,H - cb b4 ");
    RES(6, Rgstr::H);
    break;
    case 0xB5:
    //logger.debug("RES 6,L - cb b5 ");
    RES(6, Rgstr::L);
    break;
    case 0xB6:
    //logger.debug("RES 6,(HL) - cb b6 ");
    RES(6, MemoryAddress(RegisterPair::HL));
    break;
    case 0xB7:
    //logger.debug("RES 6,A - cb b7 ");
    RES(6, Rgstr::A);
    break;
    case 0xB8:
    //logger.debug("RES 7,B - cb b8 ");
    RES(7, Rgstr::B);
    break;
    case 0xB9:
    //logger.debug("RES 7,C - cb b9 ");
    RES(7, Rgstr::C);
    break;
    case 0xBA:
    //logger.debug("RES 7,D - cb ba ");
    RES(7, Rgstr::D);
    break;
    case 0xBB:
    //logger.debug("RES 7,E - cb bb ");
    RES(7, Rgstr::E);
    break;
    case 0xBC:
    //logger.debug("RES 7,H - cb bc ");
    RES(7, Rgstr::H);
    break;
    case 0xBD:
    //logger.debug("RES 7,L - cb bd ");
    RES(7, Rgstr::L);
    break;
    case 0xBE:
    //logger.debug("RES 7,(HL) - cb be ");
    RES(7, MemoryAddress(RegisterPair::HL));
    break;
    case 0xBF:
    //logger.debug("RES 7,A - cb bf ");
    RES(7, Rgstr::A);
    break;
    case 0xC0:
    //logger.debug("SET 0,B - cb c0 ");
    SET(0, Rgstr::B);
    break;
    case 0xC1:
    //logger.debug("SET 0,C - cb c1 ");
    SET(0, Rgstr::C);
    break;
    case 0xC2:
    //logger.debug("SET 0,D - cb c2 ");
    SET(0, Rgstr::D);
    break;
    case 0xC3:
    //logger.debug("SET 0,E - cb c3 ");
    SET(0, Rgstr::E);
    break;
    case 0xC4:
    //logger.debug("SET 0,H - cb c4 ");
    SET(0, Rgstr::H);
    break;
    case 0xC5:
    //logger.debug("SET 0,L - cb c5 ");
    SET(0, Rgstr::L);
    break;
    case 0xC6:
    //logger.debug("SET 0,(HL) - cb c6 ");
    SET(0, MemoryAddress(RegisterPair::HL));
    break;
    case 0xC7:
    //logger.debug("SET 0,A - cb c7 ");
    SET(0, Rgstr::A);
    break;
    case 0xC8:
    //logger.debug("SET 1,B - cb c8 ");
    SET(1, Rgstr::B);
    break;
    case 0xC9:
    //logger.debug("SET 1,C - cb c9 ");
    SET(1, Rgstr::C);
    break;
    case 0xCA:
    //logger.debug("SET 1,D - cb ca ");
    SET(1, Rgstr::D);
    break;
    case 0xCB:
    //logger.debug("SET 1,E - cb cb ");
    SET(1, Rgstr::E);
    break;
    case 0xCC:
    //logger.debug("SET 1,H - cb cc ");
    SET(1, Rgstr::H);
    break;
    case 0xCD:
    //logger.debug("SET 1,L - cb cd ");
    SET(1, Rgstr::L);
    break;
    case 0xCE:
    //logger.debug("SET 1,(HL) - cb ce ");
    SET(1, MemoryAddress(RegisterPair::HL));
    break;
    case 0xCF:
    //logger.debug("SET 1,A - cb cf ");
    SET(1, Rgstr::A);
    break;
    case 0xD0:
    //logger.debug("SET 2,B - cb d0 ");
    SET(2, Rgstr::B);
    break;
    case 0xD1:
    //logger.debug("SET 2,C - cb d1 ");
    SET(2, Rgstr::C);
    break;
    case 0xD2:
    //logger.debug("SET 2,D - cb d2 ");
    SET(2, Rgstr::D);
    break;
    case 0xD3:
    //logger.debug("SET 2,E - cb d3 ");
    SET(2, Rgstr::E);
    break;
    case 0xD4:
    //logger.debug("SET 2,H - cb d4 ");
    SET(2, Rgstr::H);
    break;
    case 0xD5:
    //logger.debug("SET 2,L - cb d5 ");
    SET(2, Rgstr::L);
    break;
    case 0xD6:
    //logger.debug("SET 2,(HL) - cb d6 ");
    SET(2, MemoryAddress(RegisterPair::HL));
    break;
    case 0xD7:
    //logger.debug("SET 2,A - cb d7 ");
    SET(2, Rgstr::A);
    break;
    case 0xD8:
    //logger.debug("SET 3,B - cb d8 ");
    SET(3, Rgstr::B);
    break;
    case 0xD9:
    //logger.debug("SET 3,C - cb d9 ");
    SET(3, Rgstr::C);
    break;
    case 0xDA:
    //logger.debug("SET 3,D - cb da ");
    SET(3, Rgstr::D);
    break;
    case 0xDB:
    //logger.debug("SET 3,E - cb db ");
    SET(3, Rgstr::E);
    break;
    case 0xDC:
    //logger.debug("SET 3,H - cb dc ");
    SET(3, Rgstr::H);
    break;
    case 0xDD:
    //logger.debug("SET 3,L - cb dd ");
    SET(3, Rgstr::L);
    break;
    case 0xDE:
    //logger.debug("SET 3,(HL) - cb de ");
    SET(3, MemoryAddress(RegisterPair::HL));
    break;
    case 0xDF:
    //logger.debug("SET 3,A - cb df ");
    SET(3, Rgstr::A);
    break;
    case 0xE0:
    //logger.debug("SET 4,B - cb e0 ");
    SET(4, Rgstr::B);
    break;
    case 0xE1:
    //logger.debug("SET 4,C - cb e1 ");
    SET(4, Rgstr::C);
    break;
    case 0xE2:
    //logger.debug("SET 4,D - cb e2 ");
    SET(4, Rgstr::D);
    break;
    case 0xE3:
    //logger.debug("SET 4,E - cb e3 ");
    SET(4, Rgstr::E);
    break;
    case 0xE4:
    //logger.debug("SET 4,H - cb e4 ");
    SET(4, Rgstr::H);
    break;
    case 0xE5:
    //logger.debug("SET 4,L - cb e5 ");
    SET(4, Rgstr::L);
    break;
    case 0xE6:
    //logger.debug("SET 4,(HL) - cb e6 ");
    SET(4, MemoryAddress(RegisterPair::HL));
    break;
    case 0xE7:
    //logger.debug("SET 4,A - cb e7 ");
    SET(4, Rgstr::A);
    break;
    case 0xE8:
    //logger.debug("SET 5,B - cb e8 ");
    SET(5, Rgstr::B);
    break;
    case 0xE9:
    //logger.debug("SET 5,C - cb e9 ");
    SET(5, Rgstr::C);
    break;
    case 0xEA:
    //logger.debug("SET 5,D - cb ea ");
    SET(5, Rgstr::D);
    break;
    case 0xEB:
    //logger.debug("SET 5,E - cb eb ");
    SET(5, Rgstr::E);
    break;
    case 0xEC:
    //logger.debug("SET 5,H - cb ec ");
    SET(5, Rgstr::H);
    break;
    case 0xED:
    //logger.debug("SET 5,L - cb ed ");
    SET(5, Rgstr::L);
    break;
    case 0xEE:
    //logger.debug("SET 5,(HL) - cb ee ");
    SET(5, MemoryAddress(RegisterPair::HL));
    break;
    case 0xEF:
    //logger.debug("SET 5,A - cb ef ");
    SET(5, Rgstr::A);
    break;
    case 0xF0:
    //logger.debug("SET 6,B - cb f0 ");
    SET(6, Rgstr::B);
    break;
    case 0xF1:
    //logger.debug("SET 6,C - cb f1 ");
    SET(6, Rgstr::C);
    break;
    case 0xF2:
    //logger.debug("SET 6,D - cb f2 ");
    SET(6, Rgstr::D);
    break;
    case 0xF3:
    //logger.debug("SET 6,E - cb f3 ");
    SET(6, Rgstr::E);
    break;
    case 0xF4:
    //logger.debug("SET 6,H - cb f4 ");
    SET(6, Rgstr::H);
    break;
    case 0xF5:
    //logger.debug("SET 6,L - cb f5 ");
    SET(6, Rgstr::L);
    break;
    case 0xF6:
    //logger.debug("SET 6,(HL) - cb f6 ");
    SET(6, MemoryAddress(RegisterPair::HL));
    break;
    case 0xF7:
    //logger.debug("SET 6,A - cb f7 ");
    SET(6, Rgstr::A);
    break;
    case 0xF8:
    //logger.debug("SET 7,B - cb f8 ");
    SET(7, Rgstr::B);
    break;
    case 0xF9:
    //logger.debug("SET 7,C - cb f9 ");
    SET(7, Rgstr::C);
    break;
    case 0xFA:
    //logger.debug("SET 7,D - cb fa ");
    SET(7, Rgstr::D);
    break;
    case 0xFB:
    //logger.debug("SET 7,E - cb fb ");
    SET(7, Rgstr::E);
    break;
    case 0xFC:
    //logger.debug("SET 7,H - cb fc ");
    SET(7, Rgstr::H);
    break;
    case 0xFD:
    //logger.debug("SET 7,L - cb fd ");
    SET(7, Rgstr::L);
    break;
    case 0xFE:
    //logger.debug("SET 7,(HL) - cb fe ");
    SET(7, MemoryAddress(RegisterPair::HL));
    break;
    case 0xFF:
    //logger.debug("SET 7,A - cb ff ");
    SET(7, Rgstr::A);
    break;
    }
    break;
    case 0xCC:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL Z,(nn) - cc n n ");
    CALL(Condition::Z, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xCD:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL (nn) - cd n n ");
    CALL(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xCE:
    currentInstruction[1] = next();
    //logger.info("ADC A,n - ce n ");
    ADC(Rgstr::A, currentInstruction[1]);
    break;
    case 0xCF:
    //logger.debug("RST 8H - cf ");
    RST(0x8);
    break;
    case 0xD0:
    //logger.debug("RET NC - d0 ");
    RET(Condition::NC);
    break;
    case 0xD1:
    //logger.debug("POP DE - d1 ");
    POP(RegisterPair::DE);
    break;
    case 0xD2:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP NC,(nn) - d2 n n ");
    JP(Condition::NC, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xD3:
    currentInstruction[1] = next();
    //logger.debug("OUT (n),A - d3 n ");
    out(MemoryAddress(currentInstruction[1]), Rgstr::A);
    break;
    case 0xD4:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL NC,(nn) - d4 n n ");
    CALL(Condition::NC, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xD5:
    //logger.debug("PUSH DE - d5 ");
    PUSH(RegisterPair::DE);
    break;
    case 0xD6:
    currentInstruction[1] = next();
    //logger.debug("SUB n - d6 n ");
    SUB(currentInstruction[1]);
    break;
    case 0xD7:
    //logger.debug("RST 10H - d7 ");
    RST(0x10);
    break;
    case 0xD8:
    //logger.debug("RET C - d8 ");
    RET(Condition::C);
    break;
    case 0xD9:
    //logger.debug("EXX - d9 ");
    EXX();
    break;
    case 0xDA:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP C,(nn) - da n n ");
    JP(Condition::C, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xDB:
    currentInstruction[1] = next();
    //logger.debug("IN A,(n) - db n ");
    in(Rgstr::A, MemoryAddress(currentInstruction[1]));
    break;
    case 0xDC:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL C,(nn) - dc n n ");
    CALL(Condition::C, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xDD:
    // get opcode
    currentInstruction[1] = next();
    switch (currentInstruction[1]) {
    case 0x09:
    //logger.debug("ADD IX,BC - dd 9 ");
    ADD(RegisterPair::IX, RegisterPair::BC);
    break;
    case 0x19:
    //logger.debug("ADD IX,DE - dd 19 ");
    ADD(RegisterPair::IX, RegisterPair::DE);
    break;
    case 0x21:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD IX,nn - dd 21 n n ");
    LD(RegisterPair::IX, (currentInstruction[3] << 8) | currentInstruction[2]);
    break;
    case 0x22:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (nn),IX - dd 22 n n ");
    LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::IX);
    break;
    case 0x23:
    //logger.debug("INC IX - dd 23 ");
    INC(RegisterPair::IX);
    break;
    case 0x29:
    //logger.debug("ADD IX,IX - dd 29 ");
    ADD(RegisterPair::IX, RegisterPair::IX);
    break;
    case 0x2A:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD IX,(nn) - dd 2a n n ");
    LD_indirect(RegisterPair::IX, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
    break;
    case 0x2B:
    //logger.debug("DEC IX - dd 2b ");
    DEC(RegisterPair::IX);
    break;
    case 0x34:
    currentInstruction[2] = next();
    //logger.debug("INC (IX+d) - dd 34 n ");
    INC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x35:
    currentInstruction[2] = next();
    //logger.debug("DEC (IX+d) - dd 35 n ");
    DEC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x36:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (IX+d),n - dd 36 n n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), currentInstruction[3]);
    break;
    case 0x39:
    //logger.debug("ADD IX,SP - dd 39 ");
    ADD(RegisterPair::IX, RegisterPair::SP);
    break;
    case 0x46:
    currentInstruction[2] = next();
    //logger.debug("LD B,(IX+d) - dd 46 n ");
    LD(Rgstr::B, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x4E:
    currentInstruction[2] = next();
    //logger.debug("LD C,(IX+d) - dd 4e n ");
    LD(Rgstr::C, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x56:
    currentInstruction[2] = next();
    //logger.debug("LD D,(IX+d) - dd 56 n ");
    LD(Rgstr::D, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x5E:
    currentInstruction[2] = next();
    //logger.debug("LD E,(IX+d) - dd 5e n ");
    LD(Rgstr::E, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x66:
    currentInstruction[2] = next();
    //logger.debug("LD H,(IX+d) - dd 66 n ");
    LD(Rgstr::H, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x6E:
    currentInstruction[2] = next();
    //logger.debug("LD L,(IX+d) - dd 6e n ");
    LD(Rgstr::L, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x70:
    currentInstruction[2] = next();
    //logger.debug("LD (IX+d),B - dd 70 n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::B);
    break;
    case 0x71:
    currentInstruction[2] = next();
    //logger.debug("LD (IX+d),C - dd 71 n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::C);
    break;
    case 0x72:
    currentInstruction[2] = next();
    //logger.debug("LD (IX+d),D - dd 72 n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::D);
    break;
    case 0x73:
    currentInstruction[2] = next();
    //logger.debug("LD (IX+d),E - dd 73 n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::E);
    break;
    case 0x74:
    currentInstruction[2] = next();
    //logger.debug("LD (IX+d),H - dd 74 n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::H);
    break;
    case 0x75:
    currentInstruction[2] = next();
    //logger.debug("LD (IX+d),L - dd 75 n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::L);
    break;
    case 0x77:
    currentInstruction[2] = next();
    //logger.debug("LD (IX+d),A - dd 77 n ");
    LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::A);
    break;
    case 0x7E:
    currentInstruction[2] = next();
    //logger.debug("LD A,(IX+d) - dd 7e n ");
    LD(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x86:
    currentInstruction[2] = next();
    //logger.debug("ADD A,(IX+d) - dd 86 n ");
    ADD(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x8E:
    currentInstruction[2] = next();
    //logger.info("ADC A,(IX+d) - dd 8e n ");
    ADC(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x96:
    currentInstruction[2] = next();
    //logger.debug("SUB (IX+d) - dd 96 n ");
    SUB(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x9E:
    currentInstruction[2] = next();
    //logger.info("SBC A,(IX+d) - dd 9e n ");
    SBC(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xA6:
    currentInstruction[2] = next();
    //logger.debug("AND (IX+d) - dd a6 n ");
    AND(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xAE:
    currentInstruction[2] = next();
    //logger.debug("XOR (IX+d) - dd ae n ");
    XOR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xB6:
    currentInstruction[2] = next();
    //logger.debug("OR (IX+d) - dd b6 n ");
    OR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xBE:
    currentInstruction[2] = next();
    //logger.debug("CP (IX+d) - dd be n ");
    CP(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xCB:
    currentInstruction[2] = next();
    // get opcode
    currentInstruction[3] = next();
    switch (currentInstruction[3]) {
    case 0x06:
    //logger.debug("RLC (IX+d) - dd cb n 6 ");
    RLC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x0E:
    //logger.debug("RRC (IX+d) - dd cb n e ");
    RRC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x16:
    //logger.debug("RL (IX+d) - dd cb n 16 ");
    RL(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x1E:
    //logger.debug("RR (IX+d) - dd cb n 1e ");
    RR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x26:
    //logger.debug("SLA (IX+d) - dd cb n 26 ");
    SLA(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x2E:
    //logger.debug("SRA (IX+d) - dd cb n 2e ");
    SRA(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x3E:
    //logger.debug("SRL (IX+d) - dd cb n 3e ");
    SRL(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x46:
    //logger.debug("BIT 0,(IX+d) - dd cb n 46 ");
    BIT(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x4E:
    //logger.debug("BIT 1,(IX+d) - dd cb n 4e ");
    BIT(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x56:
    //logger.debug("BIT 2,(IX+d) - dd cb n 56 ");
    BIT(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x5E:
    //logger.debug("BIT 3,(IX+d) - dd cb n 5e ");
    BIT(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x66:
    //logger.debug("BIT 4,(IX+d) - dd cb n 66 ");
    BIT(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x6E:
    //logger.debug("BIT 5,(IX+d) - dd cb n 6e ");
    BIT(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x76:
    //logger.debug("BIT 6,(IX+d) - dd cb n 76 ");
    BIT(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x7E:
    //logger.debug("BIT 7,(IX+d) - dd cb n 7e ");
    BIT(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x86:
    //logger.debug("RES 0,(IX+d) - dd cb n 86 ");
    RES(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x8E:
    //logger.debug("RES 1,(IX+d) - dd cb n 8e ");
    RES(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x96:
    //logger.debug("RES 2,(IX+d) - dd cb n 96 ");
    RES(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0x9E:
    //logger.debug("RES 3,(IX+d) - dd cb n 9e ");
    RES(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xA6:
    //logger.debug("RES 4,(IX+d) - dd cb n a6 ");
    RES(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xAE:
    //logger.debug("RES 5,(IX+d) - dd cb n ae ");
    RES(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xB6:
    //logger.debug("RES 6,(IX+d) - dd cb n b6 ");
    RES(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xBE:
    //logger.debug("RES 7,(IX+d) - dd cb n be ");
    RES(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xC6:
    //logger.debug("SET 0,(IX+d) - dd cb n c6 ");
    SET(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xCE:
    //logger.debug("SET 1,(IX+d) - dd cb n ce ");
    SET(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xD6:
    //logger.debug("SET 2,(IX+d) - dd cb n d6 ");
    SET(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xDE:
    //logger.debug("SET 3,(IX+d) - dd cb n de ");
    SET(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xE6:
    //logger.debug("SET 4,(IX+d) - dd cb n e6 ");
    SET(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xEE:
    //logger.debug("SET 5,(IX+d) - dd cb n ee ");
    SET(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xF6:
    //logger.debug("SET 6,(IX+d) - dd cb n f6 ");
    SET(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    case 0xFE:
    //logger.debug("SET 7,(IX+d) - dd cb n fe ");
    SET(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
    break;
    }
    break;
    case 0xE1:
    //logger.debug("POP IX - dd e1 ");
    POP(RegisterPair::IX);
    break;
    case 0xE3:
    //logger.debug("EX (SP),IX - dd e3 ");
    EX(MemoryAddress(RegisterPair::SP), RegisterPair::IX);
    break;
    case 0xE5:
    //logger.debug("PUSH IX - dd e5 ");
    PUSH(RegisterPair::IX);
    break;
    case 0xE9:
    //logger.debug("JP (IX) - dd e9 ");
    JP(MemoryAddress(RegisterPair::IX));
    break;
    case 0xF9:
    //logger.debug("LD SP,IX - dd f9 ");
    LD(RegisterPair::SP, RegisterPair::IX);
    break;
    }
    break;
    case 0xDE:
    currentInstruction[1] = next();
    //logger.info("SBC A,n - de n ");
    SBC(Rgstr::A, currentInstruction[1]);
    break;
    case 0xDF:
    //logger.debug("RST 18H - df ");
    RST(0x18);
    break;
    case 0xE0:
    //logger.debug("RET PO - e0 ");
    RET(Condition::PO);
    break;
    case 0xE1:
    //logger.debug("POP HL - e1 ");
    POP(RegisterPair::HL);
    break;
    case 0xE2:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP PO,(nn) - e2 n n ");
    JP(Condition::PO, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xE3:
    //logger.debug("EX (SP),HL - e3 ");
    EX(MemoryAddress(RegisterPair::SP), RegisterPair::HL);
    break;
    case 0xE4:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL PO,(nn) - e4 n n ");
    CALL(Condition::PO, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xE5:
    //logger.debug("PUSH HL - e5 ");
    PUSH(RegisterPair::HL);
    break;
    case 0xE6:
    currentInstruction[1] = next();
    //logger.debug("AND n - e6 n ");
    AND(currentInstruction[1]);
    break;
    case 0xE7:
    //logger.debug("RST 20H - e7 ");
    RST(0x20);
    break;
    case 0xE8:
    //logger.debug("RET PE - e8 ");
    RET(Condition::PE);
    break;
    case 0xE9:
    //logger.debug("JP (HL) - e9 ");
    JP(MemoryAddress(RegisterPair::HL));
    break;
    case 0xEA:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP PE,(nn) - ea n n ");
    JP(Condition::PE, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xEB:
    //logger.debug("EX DE,HL - eb ");
    EX(RegisterPair::DE, RegisterPair::HL);
    break;
    case 0xEC:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL PE,(nn) - ec n n ");
    CALL(Condition::PE, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xED:
    // get opcode
    currentInstruction[1] = next();
    switch (currentInstruction[1]) {
    case 0x40:
    //logger.debug("IN B,(C) - ed 40 ");
    in(Rgstr::B, MemoryAddress(Rgstr::C));
    break;
    case 0x41:
    //logger.debug("OUT (C),B - ed 41 ");
    out(MemoryAddress(Rgstr::C), Rgstr::B);
    break;
    case 0x42:
    //logger.info("SBC HL,BC - ed 42 ");
    SBC(RegisterPair::HL, RegisterPair::BC);
    break;
    case 0x43:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (nn),BC - ed 43 n n ");
    LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::BC);
    break;
    case 0x44:
    //logger.debug("NEG - ed 44 ");
    NEG();
    break;
    case 0x45:
    //logger.debug("RETN - ed 45 ");
    RETN();
    break;
    case 0x46:
    //logger.debug("IM 0 - ed 46 ");
    IM(0);
    break;
    case 0x47:
    //logger.debug("LD I,A - ed 47 ");
    LD(Rgstr::I, Rgstr::A);
    break;
    case 0x48:
    //logger.debug("IN C,(C) - ed 48 ");
    in(Rgstr::C, MemoryAddress(Rgstr::C));
    break;
    case 0x49:
    //logger.debug("OUT (C),C - ed 49 ");
    out(MemoryAddress(Rgstr::C), Rgstr::C);
    break;
    case 0x4A:
    //logger.info("ADC HL,BC - ed 4a ");
    ADC(RegisterPair::HL, RegisterPair::BC);
    break;
    case 0x4B:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD BC,(nn) - ed 4b n n ");
    LD_indirect(RegisterPair::BC, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
    break;
    case 0x4D:
    //logger.debug("RETI - ed 4d ");
    RETI();
    break;
    case 0x4F:
    //logger.debug("LD R,A - ed 4f ");
    LD(Rgstr::R, Rgstr::A);
    break;
    case 0x50:
    //logger.debug("IN D,(C) - ed 50 ");
    in(Rgstr::D, MemoryAddress(Rgstr::C));
    break;
    case 0x51:
    //logger.debug("OUT (C),D - ed 51 ");
    out(MemoryAddress(Rgstr::C), Rgstr::D);
    break;
    case 0x52:
    //logger.info("SBC HL,DE - ed 52 ");
    SBC(RegisterPair::HL, RegisterPair::DE);
    break;
    case 0x53:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (nn),DE - ed 53 n n ");
    LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::DE);
    break;
    case 0x56:
    //logger.debug("IM 1 - ed 56 ");
    IM(1);
    break;
    case 0x57:
    //logger.debug("LD A,I - ed 57 ");
    LD(Rgstr::A, Rgstr::I);
    break;
    case 0x58:
    //logger.debug("IN E,(C) - ed 58 ");
    in(Rgstr::E, MemoryAddress(Rgstr::C));
    break;
    case 0x59:
    //logger.debug("OUT (C),E - ed 59 ");
    out(MemoryAddress(Rgstr::C), Rgstr::E);
    break;
    case 0x5A:
    //logger.info("ADC HL,DE - ed 5a ");
    ADC(RegisterPair::HL, RegisterPair::DE);
    break;
    case 0x5B:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD DE,(nn) - ed 5b n n ");
    LD_indirect(RegisterPair::DE, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
    break;
    case 0x5E:
    //logger.debug("IM 2 - ed 5e ");
    IM(2);
    break;
    case 0x5F:
    //logger.debug("LD A,R - ed 5f ");
    LD(Rgstr::A, Rgstr::R);
    break;
    case 0x60:
    //logger.debug("IN H,(C) - ed 60 ");
    in(Rgstr::H, MemoryAddress(Rgstr::C));
    break;
    case 0x61:
    //logger.debug("OUT (C),H - ed 61 ");
    out(MemoryAddress(Rgstr::C), Rgstr::H);
    break;
    case 0x62:
    //logger.info("SBC HL,HL - ed 62 ");
    SBC(RegisterPair::HL, RegisterPair::HL);
    break;
    case 0x63:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (nn),HL - ed 63 n n ");
    LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::HL);
    break;
    case 0x67:
    //logger.debug("RRD - ed 67 ");
    RRD();
    break;
    case 0x68:
    //logger.debug("IN L,(C) - ed 68 ");
    in(Rgstr::L, MemoryAddress(Rgstr::C));
    break;
    case 0x69:
    //logger.debug("OUT (C),L - ed 69 ");
    out(MemoryAddress(Rgstr::C), Rgstr::L);
    break;
    case 0x6A:
    //logger.info("ADC HL,HL - ed 6a ");
    ADC(RegisterPair::HL, RegisterPair::HL);
    break;
    case 0x6B:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD HL,(nn) - ed 6b n n ");
    LD_indirect(RegisterPair::HL, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
    break;
    case 0x6F:
    //logger.debug("RLD - ed 6f ");
    RLD();
    break;
    case 0x72:
    //logger.info("SBC HL,SP - ed 72 ");
    SBC(RegisterPair::HL, RegisterPair::SP);
    break;
    case 0x73:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (nn),SP - ed 73 n n ");
    LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::SP);
    break;
    case 0x78:
    //logger.debug("IN A,(C) - ed 78 ");
    in(Rgstr::A, MemoryAddress(Rgstr::C));
    break;
    case 0x79:
    //logger.debug("OUT (C),A - ed 79 ");
    out(MemoryAddress(Rgstr::C), Rgstr::A);
    break;
    case 0x7A:
    //logger.info("ADC HL,SP - ed 7a ");
    ADC(RegisterPair::HL, RegisterPair::SP);
    break;
    case 0x7B:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD SP,(nn) - ed 7b n n ");
    LD_indirect(RegisterPair::SP, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
    break;
    case 0xA0:
    //logger.debug("LDI - ed a0 ");
    LDI();
    break;
    case 0xA1:
    //logger.debug("CPI - ed a1 ");
    CPI();
    break;
    case 0xA2:
    //logger.debug("INI - ed a2 ");
    INI();
    break;
    case 0xA3:
    //logger.debug("OUTI - ed a3 ");
    OUTI();
    break;
    case 0xA8:
    //logger.debug("LDD - ed a8 ");
    LDD();
    break;
    case 0xA9:
    //logger.debug("CPD - ed a9 ");
    CPD();
    break;
    case 0xAA:
    //logger.debug("IND - ed aa ");
    IND();
    break;
    case 0xAB:
    //logger.debug("OUTD - ed ab ");
    OUTD();
    break;
    case 0xB0:
    //logger.debug("LDIR - ed b0 ");
    LDIR();
    break;
    case 0xB1:
    //logger.debug("CPIR - ed b1 ");
    CPIR();
    break;
    case 0xB2:
    //logger.debug("INIR - ed b2 ");
    INIR();
    break;
    case 0xB3:
    //logger.debug("OTIR - ed b3 ");
    OTIR();
    break;
    case 0xB8:
    //logger.debug("LDDR - ed b8 ");
    LDDR();
    break;
    case 0xB9:
    //logger.debug("CPDR - ed b9 ");
    CPDR();
    break;
    case 0xBA:
    //logger.debug("INDR - ed ba ");
    INDR();
    break;
    case 0xBB:
    //logger.debug("OTDR - ed bb ");
    OTDR();
    break;
    }
    break;
    case 0xEE:
    currentInstruction[1] = next();
    //logger.debug("XOR n - ee n ");
    XOR(currentInstruction[1]);
    break;
    case 0xEF:
    //logger.debug("RST 28H - ef ");
    RST(0x28);
    break;
    case 0xF0:
    //logger.debug("RET P - f0 ");
    RET(Condition::P);
    break;
    case 0xF1:
    //logger.debug("POP AF - f1 ");
    POP(RegisterPair::AF);
    break;
    case 0xF2:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP P,(nn) - f2 n n ");
    JP(Condition::P, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xF3:
    //logger.debug("DI - f3 ");
    DI();
    break;
    case 0xF4:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL P,(nn) - f4 n n ");
    CALL(Condition::P, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xF5:
    //logger.debug("PUSH AF - f5 ");
    PUSH(RegisterPair::AF);
    break;
    case 0xF6:
    currentInstruction[1] = next();
    //logger.debug("OR n - f6 n ");
    OR(currentInstruction[1]);
    break;
    case 0xF7:
    //logger.debug("RST 30H - f7 ");
    RST(0x30);
    break;
    case 0xF8:
    //logger.debug("RET M - f8 ");
    RET(Condition::M);
    break;
    case 0xF9:
    //logger.debug("LD SP,HL - f9 ");
    LD(RegisterPair::SP, RegisterPair::HL);
    break;
    case 0xFA:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("JP M,(nn) - fa n n ");
    JP(Condition::M, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xFB:
    //logger.debug("EI - fb ");
    EI();
    break;
    case 0xFC:
    currentInstruction[1] = next();
    currentInstruction[2] = next();
    //logger.debug("CALL M,(nn) - fc n n ");
    CALL(Condition::M, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
    case 0xFD:
    // get opcode
    currentInstruction[1] = next();
    switch (currentInstruction[1]) {
    case 0x09:
    //logger.debug("ADD IY,BC - fd 9 ");
    ADD(RegisterPair::IY, RegisterPair::BC);
    break;
    case 0x19:
    //logger.debug("ADD IY,DE - fd 19 ");
    ADD(RegisterPair::IY, RegisterPair::DE);
    break;
    case 0x21:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD IY,nn - fd 21 n n ");
    LD(RegisterPair::IY, (currentInstruction[3] << 8) | currentInstruction[2]);
    break;
    case 0x22:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (nn),IY - fd 22 n n ");
    LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::IY);
    break;
    case 0x23:
    //logger.debug("INC IY - fd 23 ");
    INC(RegisterPair::IY);
    break;
    case 0x29:
    //logger.debug("ADD IY,IY - fd 29 ");
    ADD(RegisterPair::IY, RegisterPair::IY);
    break;
    case 0x2A:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD IY,(nn) - fd 2a n n ");
    LD_indirect(RegisterPair::IY, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
    break;
    case 0x2B:
    //logger.debug("DEC IY - fd 2b ");
    DEC(RegisterPair::IY);
    break;
    case 0x34:
    currentInstruction[2] = next();
    //logger.debug("INC (IY+d) - fd 34 n ");
    INC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x35:
    currentInstruction[2] = next();
    //logger.debug("DEC (IY+d) - fd 35 n ");
    DEC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x36:
    currentInstruction[2] = next();
    currentInstruction[3] = next();
    //logger.debug("LD (IY+d),n - fd 36 n n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), currentInstruction[3]);
    break;
    case 0x39:
    //logger.debug("ADD IY,SP - fd 39 ");
    ADD(RegisterPair::IY, RegisterPair::SP);
    break;
    case 0x46:
    currentInstruction[2] = next();
    //logger.debug("LD B,(IY+d) - fd 46 n ");
    LD(Rgstr::B, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x4E:
    currentInstruction[2] = next();
    //logger.debug("LD C,(IY+d) - fd 4e n ");
    LD(Rgstr::C, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x56:
    currentInstruction[2] = next();
    //logger.debug("LD D,(IY+d) - fd 56 n ");
    LD(Rgstr::D, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x5E:
    currentInstruction[2] = next();
    //logger.debug("LD E,(IY+d) - fd 5e n ");
    LD(Rgstr::E, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x66:
    currentInstruction[2] = next();
    //logger.debug("LD H,(IY+d) - fd 66 n ");
    LD(Rgstr::H, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x6E:
    currentInstruction[2] = next();
    //logger.debug("LD L,(IY+d) - fd 6e n ");
    LD(Rgstr::L, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x70:
    currentInstruction[2] = next();
    //logger.debug("LD (IY+d),B - fd 70 n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::B);
    break;
    case 0x71:
    currentInstruction[2] = next();
    //logger.debug("LD (IY+d),C - fd 71 n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::C);
    break;
    case 0x72:
    currentInstruction[2] = next();
    //logger.debug("LD (IY+d),D - fd 72 n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::D);
    break;
    case 0x73:
    currentInstruction[2] = next();
    //logger.debug("LD (IY+d),E - fd 73 n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::E);
    break;
    case 0x74:
    currentInstruction[2] = next();
    //logger.debug("LD (IY+d),H - fd 74 n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::H);
    break;
    case 0x75:
    currentInstruction[2] = next();
    //logger.debug("LD (IY+d),L - fd 75 n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::L);
    break;
    case 0x77:
    currentInstruction[2] = next();
    //logger.debug("LD (IY+d),A - fd 77 n ");
    LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::A);
    break;
    case 0x7E:
    currentInstruction[2] = next();
    //logger.debug("LD A,(IY+d) - fd 7e n ");
    LD(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x86:
    currentInstruction[2] = next();
    //logger.debug("ADD A,(IY+d) - fd 86 n ");
    ADD(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x8E:
    currentInstruction[2] = next();
    //logger.info("ADC A,(IY+d) - fd 8e n ");
    ADC(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x96:
    currentInstruction[2] = next();
    //logger.debug("SUB (IY+d) - fd 96 n ");
    SUB(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x9E:
    currentInstruction[2] = next();
    //logger.info("SBC A,(IY+d) - fd 9e n ");
    SBC(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xA6:
    currentInstruction[2] = next();
    //logger.debug("AND (IY+d) - fd a6 n ");
    AND(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xAE:
    currentInstruction[2] = next();
    //logger.debug("XOR (IY+d) - fd ae n ");
    XOR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xB6:
    currentInstruction[2] = next();
    //logger.debug("OR (IY+d) - fd b6 n ");
    OR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xBE:
    currentInstruction[2] = next();
    //logger.debug("CP (IY+d) - fd be n ");
    CP(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xCB:
    currentInstruction[2] = next();
    // get opcode
    currentInstruction[3] = next();
    switch (currentInstruction[3]) {
    case 0x06:
    //logger.debug("RLC (IY+d) - fd cb n 6 ");
    RLC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x0E:
    //logger.debug("RRC (IY+d) - fd cb n e ");
    RRC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x16:
    //logger.debug("RL (IY+d) - fd cb n 16 ");
    RL(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x1E:
    //logger.debug("RR (IY+d) - fd cb n 1e ");
    RR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x26:
    //logger.debug("SLA (IY+d) - fd cb n 26 ");
    SLA(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x2E:
    //logger.debug("SRA (IY+d) - fd cb n 2e ");
    SRA(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x3E:
    //logger.debug("SRL (IY+d) - fd cb n 3e ");
    SRL(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x46:
    //logger.debug("BIT 0,(IY+d) - fd cb n 46 ");
    BIT(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x4E:
    //logger.debug("BIT 1,(IY+d) - fd cb n 4e ");
    BIT(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x56:
    //logger.debug("BIT 2,(IY+d) - fd cb n 56 ");
    BIT(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x5E:
    //logger.debug("BIT 3,(IY+d) - fd cb n 5e ");
    BIT(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x66:
    //logger.debug("BIT 4,(IY+d) - fd cb n 66 ");
    BIT(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x6E:
    //logger.debug("BIT 5,(IY+d) - fd cb n 6e ");
    BIT(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x76:
    //logger.debug("BIT 6,(IY+d) - fd cb n 76 ");
    BIT(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x7E:
    //logger.debug("BIT 7,(IY+d) - fd cb n 7e ");
    BIT(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x86:
    //logger.debug("RES 0,(IY+d) - fd cb n 86 ");
    RES(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x8E:
    //logger.debug("RES 1,(IY+d) - fd cb n 8e ");
    RES(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x96:
    //logger.debug("RES 2,(IY+d) - fd cb n 96 ");
    RES(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0x9E:
    //logger.debug("RES 3,(IY+d) - fd cb n 9e ");
    RES(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xA6:
    //logger.debug("RES 4,(IY+d) - fd cb n a6 ");
    RES(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xAE:
    //logger.debug("RES 5,(IY+d) - fd cb n ae ");
    RES(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xB6:
    //logger.debug("RES 6,(IY+d) - fd cb n b6 ");
    RES(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xBE:
    //logger.debug("RES 7,(IY+d) - fd cb n be ");
    RES(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xC6:
    //logger.debug("SET 0,(IY+d) - fd cb n c6 ");
    SET(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xCE:
    //logger.debug("SET 1,(IY+d) - fd cb n ce ");
    SET(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xD6:
    //logger.debug("SET 2,(IY+d) - fd cb n d6 ");
    SET(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xDE:
    //logger.debug("SET 3,(IY+d) - fd cb n de ");
    SET(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xE6:
    //logger.debug("SET 4,(IY+d) - fd cb n e6 ");
    SET(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xEE:
    //logger.debug("SET 5,(IY+d) - fd cb n ee ");
    SET(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xF6:
    //logger.debug("SET 6,(IY+d) - fd cb n f6 ");
    SET(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    case 0xFE:
    //logger.debug("SET 7,(IY+d) - fd cb n fe ");
    SET(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
    break;
    }
    break;
    case 0xE1:
    //logger.debug("POP IY - fd e1 ");
    POP(RegisterPair::IY);
    break;
    case 0xE3:
    //logger.debug("EX (SP),IY - fd e3 ");
    EX(MemoryAddress(RegisterPair::SP), RegisterPair::IY);
    break;
    case 0xE5:
    //logger.debug("PUSH IY - fd e5 ");
    PUSH(RegisterPair::IY);
    break;
    case 0xE9:
    //logger.debug("JP (IY) - fd e9 ");
    JP(MemoryAddress(RegisterPair::IY));
    break;
    case 0xF9:
    //logger.debug("LD SP,IY - fd f9 ");
    LD(RegisterPair::SP, RegisterPair::IY);
    break;
    }
    break;
    case 0xFE:
    currentInstruction[1] = next();
    //logger.debug("CP n - fe n ");
    CP(currentInstruction[1]);
    break;
    case 0xFF:
    //logger.debug("RST 38H - ff ");
    RST(0x38);
    break;
    }
}


void Processor:: process() {
//        if (halted) {
//            decode(); //NOP
//        } else {
//     decoder->
//     *memory, *alu, 
    decode();
//        }
}

/**
 * Helper for tests etc
 */
void Processor::process(std::uint8_t count) {
    for (std::uint8_t i = 0; i < count; i++) {
        process();
    }
}

Memory* Processor::getMemory() {
    return memory;
}

IO* Processor::getIO() {
    return io;
}

Registers* Processor::getRegisters() {
    return registers;
}

/**
 * Q-6:What happens when the Z80 CPU is RESET?
 * <p/>
 * Thomas Scherrer:
 * The program counter is reset to 0000h
 * Interrupt mode 0.
 * Interrupt are dissabled.
 * The rgstr I = 00h
 * The rgstr R = 00h
 * <p/>
 * During reset time, the address bus and data bus go to a hight impadance state and all controll output signals go to the inactive state.
 * <p/>
 * The Z80 CPU will execute instruction at address 0000h
 */
void Processor::reset() {
    registers->setPC(0x0);
    registers->setI(0x0);
    registers->setR(0x0);
//    registers._IM = 0;
}


void Processor::ADC(RegisterPair rp1, RegisterPair rp2) {
    registers->setRegisterPair(rp1, registers->getRegisterPairValue(rp1) + registers->getRegisterPairValue(rp2) + (registers->getCFlag() ? 1 : 0));
    //TODO: warning: C4244: 'argument' : conversion from 'uint16_t' to 'uint8_t', possible loss of data
    setFlags(registers->getRegisterPairValue(rp1));
}

void Processor::ADC(Rgstr a, Rgstr b) {
    registers->setRegister(a, registers->getRegisterValue(a) + registers->getRegisterValue(b) + (registers->getCFlag() ? 1 : 0));
}

void Processor::ADC(Rgstr rgstr, std::uint8_t val) {
    registers->setRegister(rgstr, registers->getRegisterValue(rgstr) + val + (registers->getCFlag() ? 1 : 0));
}

void Processor::ADC(Rgstr rgstr, std::uint16_t memoryAddress) {
    std::uint8_t memoryValue = memory->read(memoryAddress);
    registers->setRegister(rgstr, registers->getRegisterValue(rgstr) + memoryValue + registers->getCFlag());
}

/**
 * The contents of rgstr pair ss (any of rgstr
 * pairs BC, DE, HL, or SP) are added to the contents of
 * rgstr pair HL and the result is stored in HL.
 * Operand ss is specified as follows in the assembled
 * object code.
 */
void Processor::ADD(RegisterPair destination, RegisterPair rgstr) {
    //TODO: Set flags correctly after these operations!!!
    std::uint16_t a = registers->getRegisterPairValue(destination);
    std::uint16_t b = registers->getRegisterPairValue(rgstr);
    std::uint16_t newvalue = a + b;
    registers->setRegisterPair(destination, newvalue);
    
    registers->setHFlag((((a & 0x0FFF) + (newvalue & 0x0FFF)) & 0xF000) !=0);
    
    // see http://stackoverflow.com/questions/8034566/overflow-and-carry-flags-on-z80
    //carry out: a + b > 0xffff
    // equivalent to a > 0xffff - b
    registers->setCFlag( a > 0xffff - b);
    registers->setParityOverflowFlag(a ^ b ^ registers->getCFlag());
    registers->setNFlag(false);
}

void Processor::ADD(Rgstr destination, std::uint8_t nextByte) {
    std::uint8_t oldvalue = registers->getRegisterValue(destination);
    std::uint8_t newvalue = registers->getRegisterValue(destination) + nextByte;
    registers->setRegister(destination, newvalue);
    registers->setSignFlag(newvalue & 0x80);
    registers->setZeroFlag(newvalue == 0);

    registers->setHFlag((((oldvalue & 0x000F) + (newvalue & 0x000F)) & 0x00F0) !=0);
    registers->setNFlag(false);
    
    // see http://stackoverflow.com/questions/8034566/overflow-and-carry-flags-on-z80
    //carry out: a + b > 0xff
    // equivalent to a > 0xff - b
    registers->setCFlag( oldvalue > 0xff - nextByte);
    registers->setParityOverflowFlag(oldvalue ^ nextByte ^ registers->getCFlag());
}

void Processor::ADD(Rgstr destination, Rgstr source) {
    ADD(destination, registers->getRegisterValue(source));
}

void Processor::ADD(Rgstr destination, std::uint16_t memoryAddress) {
    ADD(destination, memory->read(memoryAddress));
}

void Processor::AND(Rgstr iX2) {
    AND(registers->getRegisterValue(iX2));
}

/*
 * S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is set
P/V is reset if overflow; reset otherwise
N is reset
C is reset
*/
void Processor::AND(std::uint8_t value) {
    std::uint8_t result = registers->getA() & value;
    registers->setA(result);

    registers->setSignFlag(result & 0x80);
    registers->setZeroFlag(result == 0);

    registers->setHFlag(true);
    registers->setParityOverflowFlag(parity(result));
    registers->setNFlag(false);
    registers->setCFlag(false);
    // P/V
}

void Processor::AND(std::uint16_t memoryAddress) {
    AND(memory->read(memoryAddress));
}

/**
 * This instruction tests bit b in rgstr r and sets the Z flag
 * accordingly.
 * 
 * S is unknown
Z is set if specified Bit is 0; reset otherwise
H is set
P/V is unknown
N is reset
C is not affected

 */
void Processor::BIT(std::uint8_t y, std::uint8_t value) {
    registers->setZeroFlag(!(value & (1 << y)));
    registers->setHFlag(true);
    registers->setNFlag(false);
}

void Processor::BIT(std::uint8_t y, Rgstr rgstr) {
    BIT(y, registers->getRegisterValue(rgstr));
}

void Processor::BIT(std::uint8_t i, std::uint16_t memoryAddress) {
    BIT(i, memory->read(memoryAddress));
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
void Processor::CALL(Condition c, std::uint16_t memoryAddress) {
    if (isConditionTrue(c)) {
        pushPCtoStack();
        registers->setPC(memoryAddress);
    }
}

void Processor::CALL(std::uint16_t memoryAddress) {
    pushPCtoStack();
    registers->setPC(memoryAddress);
}

void Processor::CCF() {
    /* The Carry flag in the F rgstr is inverted. */
    registers->setHFlag(registers->getCFlag());

    registers->setCFlag(!registers->getCFlag());

    registers->setNFlag(false);
}


std::uint8_t Processor::_compare(std::uint8_t n) {
    std::uint8_t oldvalue = registers->getA();
    std::uint16_t newvalue = oldvalue - n;
//     std::cout << "newvalue " << (std::uint16_t)newvalue << std::endl;
    
    registers->setSignFlag(newvalue & 0x80);
    registers->setZeroFlag(newvalue == 0);

    registers->setHFlag(((oldvalue & 0x0010) - (newvalue & 0x0010)) > 0);
    registers->setNFlag(true);
    
    // see http://stackoverflow.com/questions/8034566/overflow-and-carry-flags-on-z80
    //carry out: a + b > 0xff
    // equivalent to a > 0xff - b
    
//     std::uint8_t carryOut = oldvalue > 0xff - n;
//     
//     std::uint8_t carryIn = oldvalue ^ newvalue ^ n;
//     carryIn = (carryIn >> 7) ^ carryOut;
    
    registers->setCFlag( newvalue & 0x100 );
    registers->setParityOverflowFlag( (oldvalue & 0x80) != (n & 0x80) && (oldvalue & 0x80) != (newvalue & 0x80) );
    return newvalue & 0xff;
}

void Processor::CP(std::uint8_t val) {
    registers->setF(val & 0x28);
    _compare(val);
}

void Processor::CP(Rgstr val) {
    CP(registers->getRegisterValue(val));
}

void Processor::CP(std::uint16_t memoryAddress) {
    CP(memory->read(memoryAddress));
}

/*
 * The contents of the memory location addressed by the HL register pair is
 * compared with the contents of the Accumulator. In case of a true
 * compare, a condition bit is set. The HL and Byte Counter (register pair
 * BC) are decremented.
 */
void Processor::CPD() {
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
void Processor::CPDR() {
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
void Processor::CPI() {
    CP(memory->read(registers->getHL()));

    INC(RegisterPair::HL);
    DEC(RegisterPair::BC);

    registers->setParityOverflowFlag(registers->getBC() != 0);
}

void Processor::CPIR() {
    CPI();
    if (!registers->getZeroFlag()) {
        registers->setPC(registers->getPC() - 2); //repeat instruction
    }
}

/**
 * The contents of the Accumulator (rgstr A) are inverted (one’s
 * complement).
 */
void Processor::CPL() {
    registers->setA(registers->getA() ^ 0xFF);
    registers->setNFlag(true);
    registers->setHFlag(true);
}

void Processor::DAA() {
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

    registers->setA( registers->getA() + (registers->getNFlag() ? -d : +d));
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
void Processor::DEC(std::uint16_t memoryAddress) {
    std::uint16_t address = memoryAddress;
    std::uint8_t oldvalue = memory->read(address);
    std::uint8_t newvalue = oldvalue - 1;

    memory->write(address, newvalue);

    registers->setSignFlag(newvalue & 0x80);
    registers->setZeroFlag(newvalue == 0);

    //Compare with 0 to remove warning: C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
    registers->setHFlag((((oldvalue & 0x000F) + (newvalue & 0x000F)) & 0x00F0) !=0);

    registers->setNFlag(false);
}

void Processor::DEC(Rgstr rgstr) {
    registers->setParityOverflowFlag(registers->getRegisterValue(rgstr) == 0x80);
    std::uint8_t oldvalue = registers->getRegisterValue(rgstr);
    std::uint8_t newvalue = oldvalue - 1;

    registers->setRegister(rgstr, newvalue);

    registers->setSignFlag(newvalue & 0x80);
    registers->setZeroFlag(newvalue == 0);

    registers->setHFlag((((oldvalue & 0x000F) + (newvalue & 0x000F)) & 0x00F0) !=0);

    registers->setNFlag(false);
}

/**
 * The contents of rgstr pair ss (any of the rgstr
 * pairs BC, DE, HL, or SP) are decremented. Operand ss
 * is specified as follows in the assembled object code.
 */
void Processor::DEC(RegisterPair rgstrPair) {
    registers->setRegisterPair(rgstrPair,
                               registers->getRegisterPairValue(rgstrPair) - 1);
}

void Processor::DI() {
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
void Processor::DJNZ(std::uint16_t memoryAddress) {
    registers->setB(registers->getB() - 1);

    if (registers->getB() > 0) {
        //logger.debug("B rgstr > 0");
        registers->setPC(memoryAddress);
    }
}

/**
 * The enable interrupt instruction sets both interrupt enable flip flops
 * (IFFI and IFF2) to a logic 1, allowing recognition of any maskable
 * interrupt. Note that during the execution of this instruction and the
 * following instruction, maskable interrupts are disabled.
 */
void Processor::EI() {
    registers->setIFF1(true);
    registers->setIFF2(true);
}

void Processor::EX(std::uint16_t memoryAddress, RegisterPair rgstr) {
    std::uint8_t loMemVal = memory->read(memoryAddress);
    std::uint8_t hiMemVal = memory->read(memoryAddress + 1);

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
void Processor::EX(RegisterPair a, RegisterPair b) {
    std::uint16_t aval =registers->getRegisterPairValue(a);
    registers->setRegisterPair(a,registers->getRegisterPairValue(b));
    registers->setRegisterPair(b, aval);
}

/**
 * Each 2-byte value in rgstr pairs BC, DE, and HL is exchanged with the
 * 2-byte value in BC', DE', and HL', respectively.
 */
void Processor::EXX() {
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

void Processor::HALT() {
    registers->setHalted(true);
}

void Processor::IM(std::uint8_t im) {
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
void Processor::in(Rgstr rgstr, const std::uint16_t i) {
//     assert(i.getRegisterPair() == RegisterPair::BC);
    registers->setRegister(rgstr, io->read(i));
    //TODO flags
}

/**
 * - Rgstr r is incremented and rgstr r identifies any of the
 * rgstrs A, B, C, D, E, H, or L, assembled as follows in the object
 * code.
 * <p/>
 * S is set if result is negative; reset otherwise 
 * Z is set if result is zero; reset otherwise 
 * H is set if carry from bit 3; reset otherwise 
 * P/V is set if r was 7FH before operation; reset otherwise 
 * N is reset 
 * C is not affected
 */
void Processor::INC(std::uint16_t memoryAddress) {
    registers->setParityOverflowFlag(memory->read(memoryAddress) == 0x7F);

    std::uint8_t newValue = memory->read(memoryAddress) + 1;
    memory->write(memoryAddress, newValue);

    registers->setSignFlag(newValue & 0x80);
    registers->setZeroFlag(newValue == 0);
    // H ??

    registers->setNFlag(false);
}

void Processor::INC(Rgstr reg) {
    registers->setParityOverflowFlag(registers->getRegisterValue(reg) == 0x7F);

    std::uint8_t newValue = registers->getRegisterValue(reg) + 1;

    registers->setRegister(reg, newValue);

    registers->setSignFlag(newValue & 0x80);
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
void Processor::INC(RegisterPair rgstrPair) {
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
void Processor::IND() {
    std::uint8_t value = io->read(registers->getC());
    memory->write(registers->getHL(), value);
    DEC(Rgstr::B);
    DEC(RegisterPair::HL);
    registers->setNFlag(true);
    registers->setZeroFlag(registers->getB() == 0);
}

void Processor::INDR() {
    IND();
    if (!registers->getZeroFlag()) {
        registers->setPC(registers->getPC() -2);
    }
}

void Processor::INI() {
    std::uint8_t value = io->read(registers->getC());
    memory->write(registers->getHL(), value);
    DEC(Rgstr::B);
    INC(RegisterPair::HL);
    registers->setNFlag(true);
    registers->setZeroFlag(registers->getB() == 0);
}

void Processor::INIR() {
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
void Processor::JP(std::uint16_t memoryAddress) {
    registers->setPC(memoryAddress);
}

void Processor::JP(Condition condition, std::uint16_t memoryAddress) {
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
void Processor::JR(Condition condition, std::uint16_t memoryAddress) {
    if (isConditionTrue(condition)) {
        JR(memoryAddress);
    }
}

void Processor::JR(std::uint16_t memoryAddress) {
    registers->setPC(memoryAddress);
}

/**
 * The contents of memory address (nn) are loaded to the low order
 * portion of rgstr pair HL (rgstr L), and the contents of the
 * next highest memory address (nn +1) are loaded to the high order
 * portion of HL (rgstr H). The first n operand after the Op Code is
 * the low order byte of nn .
 */
void Processor::LD(RegisterPair r1, RegisterPair r2) {
    registers->setRegisterPair(r1,registers->getRegisterPairValue(r2));
}

void Processor::LD(RegisterPair rgstrPair, std::uint16_t immediateValue) {
    registers->setRegisterPair(rgstrPair, immediateValue);
}

void Processor::LD(std::uint16_t memoryAddress, Rgstr rgstr) {
    memory->write(memoryAddress,registers->getRegisterValue(rgstr));
}

void Processor::LD(Rgstr a, std::uint16_t memoryAddress) {
    std::uint8_t value = memory->read(memoryAddress);
    registers->setRegister(a, value);
}

void Processor::LD(std::uint16_t memoryAddress, RegisterPair rgstr) {
    memory->write(memoryAddress,registers->getRegisterPairValue(rgstr) & 0xff);
    memory->write(memoryAddress + 1,registers->getRegisterPairValue(rgstr) >> 8);
}

void Processor::LD_indirect(RegisterPair rgstrPair, std::uint16_t memoryAddress) {
    std::uint16_t value = memory->read(memoryAddress) | (memory->read(memoryAddress + 1) << 8);
    registers->setRegisterPair(rgstrPair, value);
}

void Processor::LD(std::uint16_t memoryAddress, std::uint8_t i) {
    memory->write(memoryAddress, i);
}

void Processor::LD(Rgstr rgstr, std::uint8_t immediateValue) {
    registers->setRegister(rgstr, immediateValue);
}

void Processor::LD(Rgstr destRegister, Rgstr sourceRegister) {
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
void Processor::LDD() {
    memory->write(registers->getDE(), memory->read(registers->getHL()));
    DEC(RegisterPair::HL);
    DEC(RegisterPair::DE);
    DEC(RegisterPair::BC);
    registers->setHFlag(false);
    registers->setNFlag(false);
    registers->setParityOverflowFlag(registers->getBC() != 0);
}

void Processor::LDDR() {
    LDD();
    if (registers->getParityOverflowFlag()) {
        registers->setPC(registers->getPC() -2);
    }
}

/* A byte of data is transferred from the memory location addressed, by the
contents of the HL register pair to the memory location addressed by the
contents of the DE register pair. Then both these register pairs are
incremented and the BC (Byte Counter) register pair is decremented.*/
void Processor::LDI() {
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
void Processor::LDIR() {
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
void Processor::NEG() {
    registers->setSignFlag((registers->getA() & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000));
    registers->setParityOverflowFlag(registers->getA() == 0x80);
    registers->setZeroFlag(registers->getA() == 0);
    registers->setNFlag(true);
    registers->setCFlag(registers->getA() != 0);
    registers->setA(~registers->getA() & 0xFF);
    // setHFlag(false);
}

void Processor::NOP() {
//        unimplemented();
}

void Processor::OR(Rgstr rgstr) {
    OR(registers->getRegisterValue(rgstr));
}

void Processor::OR(std::uint8_t immediateValue) {
    std::uint8_t result = registers->getA() | immediateValue;

    registers->setA(result);

    registers->setSignFlag(result & 0x80);
    registers->setZeroFlag(result == 0);

    registers->setHFlag(false);

    registers->setNFlag(false);
    registers->setCFlag(false);
    registers->setParityOverflowFlag(parity(result));
}

void Processor::OR(std::uint16_t memoryAddress) {
    OR(memory->read(memoryAddress));
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
void Processor::OTDR() {
    OUTD();
    if (registers->getB() != 0) {
        registers->setPC(registers->getPC() -2);
    }
}

void Processor::OTIR() {
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
void Processor::out(std::uint16_t address, Rgstr rgstr) {
    writeIO(address,registers->getRegisterValue(rgstr));
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
void Processor::OUTD() {
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
void Processor::OUTI() {
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
void Processor::POP(RegisterPair rgstr) {
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
void Processor::PUSH(RegisterPair valueRegister) {
    std::uint16_t value =registers->getRegisterPairValue(valueRegister);
    decrementSP();
    memory->write(registers->getSP(), value >> 8);
    decrementSP();
    memory->write(registers->getSP(), value & 0xff);
}

/* resets a bit */
void Processor::RES(std::uint8_t y, Rgstr rgstr) {
    registers->setRegister(rgstr,registers->getRegisterValue(rgstr) & (BOOST_BINARY(11111111) ^ (1 << y)));
}

void Processor::RES(std::uint8_t i, std::uint16_t memoryAddress) {
    std::uint8_t currentMemoryContents = memory->read(memoryAddress);
    memory->write(memoryAddress, currentMemoryContents & (BOOST_BINARY(11111111) ^ (1 << i)));
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
void Processor::RET(Condition condition) {
    //logger.debug("RET cc[y]");
    if (isConditionTrue(condition)) {
        RET();
    }
}

void Processor::RET() {
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
void Processor::RETI() {
    unimplemented("RETI");
}

/* Return from non maskable interrupt */
void Processor::RETN() {
    unimplemented("RETN");
}

/*
 * The contents of the m operand are rotated left 1-bit position. The content of
bit 7 is copied to the Carry flag and the previous content of the Carry flag is
copied to bit 0.
*/
void Processor::RL(std::uint16_t memoryAddress) {
    unimplemented("RL");
}

/**
 * The contents of the m operand are rotated left 1-bit position. The content of
 * bit 7 is copied to the Carry flag and the previous content of the Carry flag is
 * copied to bit 0.
 */
void Processor::RL(Rgstr r) {
    std::uint8_t tempA = registers->getRegisterValue(r);
    registers->setRegister(r, tempA << 1 | (registers->getCFlag() ? 1 : 0));
    registers->setCFlag(tempA & 0x80);
}

/**
 * The contents of the Accumulator (rgstr A) are rotated left 1-bit
 * position through the Carry flag. The previous content of the Carry flag
 * is copied to bit 0. Bit 0 is the least-significant bit.
 */
void Processor::RLA() {
    RL(Rgstr::A);
}

void Processor::RLC(std::uint16_t memoryAddress) {
    unimplemented("RLC");
}

/*
 * The contents of register r are rotated left 1-bit position. The content of bit 7
is copied to the Carry flag and also to bit 0.

S is not affected.
Z is not affected.
H is reset.
P/V is not affected.
N is reset.
C is data from bit 0 of Accumulator.

*/
void Processor::RLC(Rgstr rgstr) {
    std::uint8_t tempA = registers->getRegisterValue(rgstr);
    registers->setRegister(rgstr, tempA << 1 | ((tempA >> 7) & 0x1));
    registers->setCFlag((tempA >> 7) & 0x1);
    registers->setHFlag(false);
    registers->setNFlag(false);
}

/**
 * The contents of the Accumulator (rgstr A) are rotated left 1-bit
 * position. The sign bit (bit 7) is copied to the Carry flag and also to
 * bit 0. Bit 0 is the least-significant bit.
 * <p/>
 * S is not affected Z is not affected H is reset P/V is not affected N is
 * reset C is data from bit 7 of Accumulator
 */
void Processor::RLCA() {
    RLC(Rgstr::A);
}

void Processor::RLD() {
    unimplemented("RLD");
}

/*The contents of operand m are rotated right 1-bit position through the Carry
flag. The content of bit 0 is copied to the Carry flag and the previous
content of the Carry flag is copied to bit 7. Bit 0 is the least-significant bit.

S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity even; reset otherwise,
N is reset
C is data from bit 0 of source register

*/
void Processor::RR(std::uint16_t memoryAddress) {
    std::uint8_t tempA = memory->read(memoryAddress);
    
    std::uint8_t f2 = registers->getCFlag();
    registers->setCFlag(tempA & 1);
    
    std::uint8_t result = (tempA >> 1) | (f2 << 7);
    
    memory->write(memoryAddress, result);
    registers->setSignFlag(result & 0x80);
    registers->setZeroFlag(result == 0x0);
    registers->setHFlag(false);
    registers->setParityOverflowFlag(parity(result));
    registers->setNFlag(false);
}

void Processor::RR(Rgstr r) {
    std::uint8_t tempA = registers->getRegisterValue(r);
    
    std::uint8_t f2 = registers->getCFlag();
    registers->setCFlag(tempA & 1);
    std::uint8_t result = (tempA >> 1) | (f2 << 7);
    registers->setRegister(r, result);
    registers->setSignFlag(result & 0x80);
    registers->setZeroFlag(result == 0x0);
    registers->setHFlag(false);
    registers->setParityOverflowFlag(parity(result));
    registers->setNFlag(false);
}

/**
 * The contents of the Accumulator (rgstr A) are rotated right 1-bit
 * position through the Carry flag. The previous content of the Carry flag
 * is copied to bit 7. Bit 0 is the least-significant bit.
 */
void Processor::RRA() {
    RR(Rgstr::A);
}

void Processor::RRC(std::uint16_t memoryAddress) {
    unimplemented("RRC");
}

void Processor::RRC(Rgstr r) {
    std::uint8_t tempA = registers->getRegisterValue(r);
    registers->setCFlag(registers->getA() & 1);
    std::uint8_t result = (tempA >> 1) | ((tempA << 7) & 0x80);
    registers->setRegister(r, result);
    registers->setSignFlag(result & 0x80);
    registers->setZeroFlag(result == 0x0);
    registers->setHFlag(false);
    registers->setParityOverflowFlag(parity(result));
    registers->setNFlag(false);
}

/**
 * The contents of the Accumulator (rgstr A) are rotated right 1-bit
 * position. Bit 0 is copied to the Carry flag and also to bit 7. Bit 0 is
 * the least- significant bit.
 */
void Processor::RRCA() {
    RRC(Rgstr::A);
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
void Processor::RRD() {
    std::uint8_t priorMemory = memory->read(registers->getHL());
    std::uint8_t priorAccumulator = registers->getA();

    registers->setA((priorMemory & 0xF) | (priorAccumulator & 0xF0));

    memory->write(registers->getHL(),
                  (priorMemory >> 4) | ((priorAccumulator & 0xF) << 4));
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
void Processor::RST(std::uint8_t p) {
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
SP 11

S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is set if borrow from bit 12; reset otherwise
P/V is reset if overflow; reset otherwise
N is set
C is set if borrow; reset otherwise

*/
void Processor::SBC(RegisterPair h1, RegisterPair h2) {
    uint16_t oldvalue = registers->getRegisterPairValue(h1);
    uint16_t newvalue = oldvalue - registers->getRegisterPairValue(h2) - registers->getCFlag();
    registers->setRegisterPair(h1, newvalue);
    
    registers->setSignFlag(newvalue & 0x8000);
    registers->setZeroFlag(newvalue == 0);

    //Compare with 0 to remove warning: C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
//     registers->setHFlag((((oldvalue & 0x0FFF) + (newvalue & 0x0FFF)) & 0xF000) !=0);

    registers->setNFlag(true);
}

void Processor::SBC(Rgstr a, std::uint16_t memoryAddress) {
    SBC(a, memory->read(memoryAddress));
}

void Processor::SBC(Rgstr a, std::uint8_t nextByte) {
    uint8_t oldvalue = registers->getRegisterValue(a);
    uint8_t newvalue = oldvalue - nextByte - registers->getCFlag();
    registers->setRegister(a, newvalue);
    
    registers->setSignFlag(newvalue & 0x80);
    registers->setZeroFlag(newvalue == 0);

    //Compare with 0 to remove warning: C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
    registers->setHFlag((((oldvalue & 0x000F) + (newvalue & 0x000F)) & 0x00F0) !=0);

    registers->setNFlag(true);
    
    //TODO C flag not set
}

void Processor::SBC(Rgstr a, Rgstr b) {
    SBC(a, registers->getRegisterValue(b));
}

void Processor::SCF() {
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
void Processor::SET(std::uint8_t y, Rgstr rgstr) {
    registers->setRegister(rgstr,registers->getRegisterValue(rgstr) | (1 << y));
}

void Processor::SET(std::uint8_t i, std::uint16_t memoryAddress) {
    std::uint8_t currentMemoryContents = memory->read(memoryAddress);
    memory->write(memoryAddress, currentMemoryContents | (1 << i));
}

void Processor::SLA(std::uint16_t memoryAddress) {
    unimplemented("SLA");
}

void Processor::SLA(Rgstr r) {
    unimplemented("SLA");
}

void Processor::SRA(std::uint16_t memoryAddress) {
    unimplemented("SRA");
}

void Processor::SRA(Rgstr r) {
    unimplemented("SRA");
}

void Processor::SRL(std::uint16_t memoryAddress) {
    unimplemented("SRL");
}

/**
 * The contents of operand m are shifted right 1-bit position. The content of
 * bit 0 is copied to the Carry flag, and bit 7 is reset. Bit 0 is the least-
 * significant bit.
 *
 */
void Processor::SRL(Rgstr m) {
    std::uint8_t val =registers->getRegisterValue(m);
    registers->setCFlag((val & 1) == 1);
    registers->setRegister(m, val >> 1);
}

void Processor::SUB(Rgstr reg) {
    SUB(registers->getRegisterValue(reg));
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
void Processor::SUB(std::uint8_t n) {
    std::uint8_t result = _compare(n);
    registers->setA(result);
    registers->setF((registers->getF() & ~0x28) ^ (result & 0x28));
}

void Processor::SUB(std::uint16_t memoryAddress) {
    SUB(memory->read(memoryAddress));
}

void Processor::XOR(Rgstr val) {
    XOR(registers->getRegisterValue(val));
}

bool parity(std::uint8_t val) {
    std::uint8_t j = val;
    bool parity = true;
    for(std::uint8_t i = 0; i < 8; ++i) {
        parity ^= j & 1;
        j >>= 1;
    }
    return parity;
}

/*
 * S is set if result is negative; reset otherwise
* Z is set if result is zero; reset otherwise
* H is reset
* P/V is set if parity even; reset otherwise
* N is reset
* C is reset
*/
void Processor::XOR(std::uint8_t val) {
    std::uint8_t newvalue = (registers->getA() ^ val);
    registers->setA(newvalue);

    registers->setSignFlag(newvalue & 0x80);
    registers->setZeroFlag(newvalue == 0);

    registers->setHFlag(false);
    registers->setNFlag(false);
    registers->setCFlag(false);
    registers->setParityOverflowFlag(parity(newvalue));
}

void Processor::XOR(std::uint16_t memoryAddress) {
    XOR(memory->read(memoryAddress));
}

void Processor::decrementSP() {
    registers->setSP(registers->getSP() - 1);
}

void Processor::incrementSP() {
    registers->setSP(registers->getSP() + 1);
}

bool Processor::isConditionTrue(Condition condition) {
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
    return retval;
}

void Processor::pushPCtoStack() {
    decrementSP();
    memory->write(registers->getSP(), (registers->getPC() >> 8));
    decrementSP();
    memory->write(registers->getSP(), (registers->getPC() & 0xff));
}

std::uint8_t Processor::readIO(std::uint16_t address) {
    return io->read(address);
}

void Processor::unimplemented(std::string opcode) {
    logger.debug("Unimplemented - " + opcode);
//     throw  UnimplementedInstructionException();
}

void Processor::writeIO(std::uint16_t address, std::uint8_t value) {
//    //logger.debug("Writing IO: addr:" + address + " val:" + value);
    io->write(address, value);
}

void Processor::setFlags(std::uint8_t value) {
    /*- S is set if I-Rgstr is negative; reset otherwise
    Z is set if I-Rgstr is zero; reset otherwise
    H is reset
    P/V contains contents of IFF2
    N is reset
    C is not affected
    If an interrupt occurs during execution of this instruction, the Parity
    flag contains a 0.
     */

    registers->setSignFlag(value & 0x80);
    registers->setZeroFlag(value == 0);
    registers->setHFlag(false);
    registers->setParityOverflowFlag(registers->isIFF2());
    registers->setNFlag(false); // N
}
