#include <iostream>
#include "decoder.h"

void Decoder::decode(Memory &memory, Alu &alu, std::uint16_t &pc) {
  std::uint8_t currentInstruction[4];
  // get opcode
  currentInstruction[0] = next(memory, pc);
  switch (currentInstruction[0]) {
  case 0x00:
    // logger.debug("NOP - 0 ");
    alu.NOP();
    break;
  case 0x01:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD BC,nn - 1 n n ");
    alu.LD(RegisterPair::BC, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
  case 0x02:
    // logger.debug("LD (BC),A - 2 ");
    alu.LD(MemoryAddress(RegisterPair::BC), Rgstr::A);
    break;
  case 0x03:
    // logger.debug("INC BC - 3 ");
    alu.INC(RegisterPair::BC);
    break;
  case 0x04:
    // logger.debug("INC B - 4 ");
    alu.INC(Rgstr::B);
    break;
  case 0x05:
    // logger.debug("DEC B - 5 ");
    alu.DEC(Rgstr::B);
    break;
  case 0x06:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD B,n - 6 n ");
    alu.LD(Rgstr::B, currentInstruction[1]);
    break;
  case 0x07:
    // logger.debug("RLCA - 7 ");
    alu.RLCA();
    break;
  case 0x08:
    // logger.debug("EX AF,AF' - 8 ");
    alu.EX(RegisterPair::AF, RegisterPair::AF_prime);
    break;
  case 0x09:
    // logger.debug("ADD HL,BC - 9 ");
    alu.ADD(RegisterPair::HL, RegisterPair::BC);
    break;
  case 0x0A:
    // logger.debug("LD A,(BC) - a ");
    alu.LD(Rgstr::A, MemoryAddress(RegisterPair::BC));
    break;
  case 0x0B:
    // logger.debug("DEC BC - b ");
    alu.DEC(RegisterPair::BC);
    break;
  case 0x0C:
    // logger.debug("INC C - c ");
    alu.INC(Rgstr::C);
    break;
  case 0x0D:
    // logger.debug("DEC C - d ");
    alu.DEC(Rgstr::C);
    break;
  case 0x0E:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD C,n - e n ");
    alu.LD(Rgstr::C, currentInstruction[1]);
    break;
  case 0x0F:
    // logger.debug("RRCA - f ");
    alu.RRCA();
    break;
  case 0x10:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("DJNZ (PC+e) - 10 n ");
    alu.DJNZ(MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
  case 0x11:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD DE,nn - 11 n n ");
    alu.LD(RegisterPair::DE, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
  case 0x12:
    // logger.debug("LD (DE),A - 12 ");
    alu.LD(MemoryAddress(RegisterPair::DE), Rgstr::A);
    break;
  case 0x13:
    // logger.debug("INC DE - 13 ");
    alu.INC(RegisterPair::DE);
    break;
  case 0x14:
    // logger.debug("INC D - 14 ");
    alu.INC(Rgstr::D);
    break;
  case 0x15:
    // logger.debug("DEC D - 15 ");
    alu.DEC(Rgstr::D);
    break;
  case 0x16:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD D,n - 16 n ");
    alu.LD(Rgstr::D, currentInstruction[1]);
    break;
  case 0x17:
    // logger.debug("RLA - 17 ");
    alu.RLA();
    break;
  case 0x18:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("JR (PC+e) - 18 n ");
    alu.JR(MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
  case 0x19:
    // logger.debug("ADD HL,DE - 19 ");
    alu.ADD(RegisterPair::HL, RegisterPair::DE);
    break;
  case 0x1A:
    // logger.debug("LD A,(DE) - 1a ");
    alu.LD(Rgstr::A, MemoryAddress(RegisterPair::DE));
    break;
  case 0x1B:
    // logger.debug("DEC DE - 1b ");
    alu.DEC(RegisterPair::DE);
    break;
  case 0x1C:
    // logger.debug("INC E - 1c ");
    alu.INC(Rgstr::E);
    break;
  case 0x1D:
    // logger.debug("DEC E - 1d ");
    alu.DEC(Rgstr::E);
    break;
  case 0x1E:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD E,n - 1e n ");
    alu.LD(Rgstr::E, currentInstruction[1]);
    break;
  case 0x1F:
    // logger.debug("RRA - 1f ");
    alu.RRA();
    break;
  case 0x20:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("JR NZ,(PC+e) - 20 n ");
    alu.JR(Condition::NZ, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
  case 0x21:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD HL,nn - 21 n n ");
    alu.LD(RegisterPair::HL, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
  case 0x22:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD (nn),HL - 22 n n ");
    alu.LD(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]), RegisterPair::HL);
    break;
  case 0x23:
    // logger.debug("INC HL - 23 ");
    alu.INC(RegisterPair::HL);
    break;
  case 0x24:
    // logger.debug("INC H - 24 ");
    alu.INC(Rgstr::H);
    break;
  case 0x25:
    // logger.debug("DEC H - 25 ");
    alu.DEC(Rgstr::H);
    break;
  case 0x26:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD H,n - 26 n ");
    alu.LD(Rgstr::H, currentInstruction[1]);
    break;
  case 0x27:
    // logger.debug("DAA - 27 ");
    alu.DAA();
    break;
  case 0x28:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("JR Z,(PC+e) - 28 n ");
    alu.JR(Condition::Z, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
  case 0x29:
    // logger.debug("ADD HL,HL - 29 ");
    alu.ADD(RegisterPair::HL, RegisterPair::HL);
    break;
  case 0x2A:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD HL,(nn) - 2a n n ");
    alu.LD(RegisterPair::HL, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0x2B:
    // logger.debug("DEC HL - 2b ");
    alu.DEC(RegisterPair::HL);
    break;
  case 0x2C:
    // logger.debug("INC L - 2c ");
    alu.INC(Rgstr::L);
    break;
  case 0x2D:
    // logger.debug("DEC L - 2d ");
    alu.DEC(Rgstr::L);
    break;
  case 0x2E:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD L,n - 2e n ");
    alu.LD(Rgstr::L, currentInstruction[1]);
    break;
  case 0x2F:
    // logger.debug("CPL - 2f ");
    alu.CPL();
    break;
  case 0x30:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("JR NC,(PC+e) - 30 n ");
    alu.JR(Condition::NC, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
  case 0x31:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD SP,nn - 31 n n ");
    alu.LD(RegisterPair::SP, (currentInstruction[2] << 8) | currentInstruction[1]);
    break;
  case 0x32:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD (nn),A - 32 n n ");
    alu.LD(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]), Rgstr::A);
    break;
  case 0x33:
    // logger.debug("INC SP - 33 ");
    alu.INC(RegisterPair::SP);
    break;
  case 0x34:
    // logger.debug("INC (HL) - 34 ");
    alu.INC(MemoryAddress(RegisterPair::HL));
    break;
  case 0x35:
    // logger.debug("DEC (HL) - 35 ");
    alu.DEC(MemoryAddress(RegisterPair::HL));
    break;
  case 0x36:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD (HL),n - 36 n ");
    alu.LD(MemoryAddress(RegisterPair::HL), currentInstruction[1]);
    break;
  case 0x37:
    // logger.debug("SCF - 37 ");
    alu.SCF();
    break;
  case 0x38:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("JR C,(PC+e) - 38 n ");
    alu.JR(Condition::C, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
    break;
  case 0x39:
    // logger.debug("ADD HL,SP - 39 ");
    alu.ADD(RegisterPair::HL, RegisterPair::SP);
    break;
  case 0x3A:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("LD A,(nn) - 3a n n ");
    alu.LD(Rgstr::A, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0x3B:
    // logger.debug("DEC SP - 3b ");
    alu.DEC(RegisterPair::SP);
    break;
  case 0x3C:
    // logger.debug("INC A - 3c ");
    alu.INC(Rgstr::A);
    break;
  case 0x3D:
    // logger.debug("DEC A - 3d ");
    alu.DEC(Rgstr::A);
    break;
  case 0x3E:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("LD A,n - 3e n ");
    alu.LD(Rgstr::A, currentInstruction[1]);
    break;
  case 0x3F:
    // logger.debug("CCF - 3f ");
    alu.CCF();
    break;
  case 0x40:
    // logger.debug("LD B,B - 40 ");
    alu.LD(Rgstr::B, Rgstr::B);
    break;
  case 0x41:
    // logger.debug("LD B,C - 41 ");
    alu.LD(Rgstr::B, Rgstr::C);
    break;
  case 0x42:
    // logger.debug("LD B,D - 42 ");
    alu.LD(Rgstr::B, Rgstr::D);
    break;
  case 0x43:
    // logger.debug("LD B,E - 43 ");
    alu.LD(Rgstr::B, Rgstr::E);
    break;
  case 0x44:
    // logger.debug("LD B,H - 44 ");
    alu.LD(Rgstr::B, Rgstr::H);
    break;
  case 0x45:
    // logger.debug("LD B,L - 45 ");
    alu.LD(Rgstr::B, Rgstr::L);
    break;
  case 0x46:
    // logger.debug("LD B,(HL) - 46 ");
    alu.LD(Rgstr::B, MemoryAddress(RegisterPair::HL));
    break;
  case 0x47:
    // logger.debug("LD B,A - 47 ");
    alu.LD(Rgstr::B, Rgstr::A);
    break;
  case 0x48:
    // logger.debug("LD C,B - 48 ");
    alu.LD(Rgstr::C, Rgstr::B);
    break;
  case 0x49:
    // logger.debug("LD C,C - 49 ");
    alu.LD(Rgstr::C, Rgstr::C);
    break;
  case 0x4A:
    // logger.debug("LD C,D - 4a ");
    alu.LD(Rgstr::C, Rgstr::D);
    break;
  case 0x4B:
    // logger.debug("LD C,E - 4b ");
    alu.LD(Rgstr::C, Rgstr::E);
    break;
  case 0x4C:
    // logger.debug("LD C,H - 4c ");
    alu.LD(Rgstr::C, Rgstr::H);
    break;
  case 0x4D:
    // logger.debug("LD C,L - 4d ");
    alu.LD(Rgstr::C, Rgstr::L);
    break;
  case 0x4E:
    // logger.debug("LD C,(HL) - 4e ");
    alu.LD(Rgstr::C, MemoryAddress(RegisterPair::HL));
    break;
  case 0x4F:
    // logger.debug("LD C,A - 4f ");
    alu.LD(Rgstr::C, Rgstr::A);
    break;
  case 0x50:
    // logger.debug("LD D,B - 50 ");
    alu.LD(Rgstr::D, Rgstr::B);
    break;
  case 0x51:
    // logger.debug("LD D,C - 51 ");
    alu.LD(Rgstr::D, Rgstr::C);
    break;
  case 0x52:
    // logger.debug("LD D,D - 52 ");
    alu.LD(Rgstr::D, Rgstr::D);
    break;
  case 0x53:
    // logger.debug("LD D,E - 53 ");
    alu.LD(Rgstr::D, Rgstr::E);
    break;
  case 0x54:
    // logger.debug("LD D,H - 54 ");
    alu.LD(Rgstr::D, Rgstr::H);
    break;
  case 0x55:
    // logger.debug("LD D,L - 55 ");
    alu.LD(Rgstr::D, Rgstr::L);
    break;
  case 0x56:
    // logger.debug("LD D,(HL) - 56 ");
    alu.LD(Rgstr::D, MemoryAddress(RegisterPair::HL));
    break;
  case 0x57:
    // logger.debug("LD D,A - 57 ");
    alu.LD(Rgstr::D, Rgstr::A);
    break;
  case 0x58:
    // logger.debug("LD E,B - 58 ");
    alu.LD(Rgstr::E, Rgstr::B);
    break;
  case 0x59:
    // logger.debug("LD E,C - 59 ");
    alu.LD(Rgstr::E, Rgstr::C);
    break;
  case 0x5A:
    // logger.debug("LD E,D - 5a ");
    alu.LD(Rgstr::E, Rgstr::D);
    break;
  case 0x5B:
    // logger.debug("LD E,E - 5b ");
    alu.LD(Rgstr::E, Rgstr::E);
    break;
  case 0x5C:
    // logger.debug("LD E,H - 5c ");
    alu.LD(Rgstr::E, Rgstr::H);
    break;
  case 0x5D:
    // logger.debug("LD E,L - 5d ");
    alu.LD(Rgstr::E, Rgstr::L);
    break;
  case 0x5E:
    // logger.debug("LD E,(HL) - 5e ");
    alu.LD(Rgstr::E, MemoryAddress(RegisterPair::HL));
    break;
  case 0x5F:
    // logger.debug("LD E,A - 5f ");
    alu.LD(Rgstr::E, Rgstr::A);
    break;
  case 0x60:
    // logger.debug("LD H,B - 60 ");
    alu.LD(Rgstr::H, Rgstr::B);
    break;
  case 0x61:
    // logger.debug("LD H,C - 61 ");
    alu.LD(Rgstr::H, Rgstr::C);
    break;
  case 0x62:
    // logger.debug("LD H,D - 62 ");
    alu.LD(Rgstr::H, Rgstr::D);
    break;
  case 0x63:
    // logger.debug("LD H,E - 63 ");
    alu.LD(Rgstr::H, Rgstr::E);
    break;
  case 0x64:
    // logger.debug("LD H,H - 64 ");
    alu.LD(Rgstr::H, Rgstr::H);
    break;
  case 0x65:
    // logger.debug("LD H,L - 65 ");
    alu.LD(Rgstr::H, Rgstr::L);
    break;
  case 0x66:
    // logger.debug("LD H,(HL) - 66 ");
    alu.LD(Rgstr::H, MemoryAddress(RegisterPair::HL));
    break;
  case 0x67:
    // logger.debug("LD H,A - 67 ");
    alu.LD(Rgstr::H, Rgstr::A);
    break;
  case 0x68:
    // logger.debug("LD L,B - 68 ");
    alu.LD(Rgstr::L, Rgstr::B);
    break;
  case 0x69:
    // logger.debug("LD L,C - 69 ");
    alu.LD(Rgstr::L, Rgstr::C);
    break;
  case 0x6A:
    // logger.debug("LD L,D - 6a ");
    alu.LD(Rgstr::L, Rgstr::D);
    break;
  case 0x6B:
    // logger.debug("LD L,E - 6b ");
    alu.LD(Rgstr::L, Rgstr::E);
    break;
  case 0x6C:
    // logger.debug("LD L,H - 6c ");
    alu.LD(Rgstr::L, Rgstr::H);
    break;
  case 0x6D:
    // logger.debug("LD L,L - 6d ");
    alu.LD(Rgstr::L, Rgstr::L);
    break;
  case 0x6E:
    // logger.debug("LD L,(HL) - 6e ");
    alu.LD(Rgstr::L, MemoryAddress(RegisterPair::HL));
    break;
  case 0x6F:
    // logger.debug("LD L,A - 6f ");
    alu.LD(Rgstr::L, Rgstr::A);
    break;
  case 0x70:
    // logger.debug("LD (HL),B - 70 ");
    alu.LD(MemoryAddress(RegisterPair::HL), Rgstr::B);
    break;
  case 0x71:
    // logger.debug("LD (HL),C - 71 ");
    alu.LD(MemoryAddress(RegisterPair::HL), Rgstr::C);
    break;
  case 0x72:
    // logger.debug("LD (HL),D - 72 ");
    alu.LD(MemoryAddress(RegisterPair::HL), Rgstr::D);
    break;
  case 0x73:
    // logger.debug("LD (HL),E - 73 ");
    alu.LD(MemoryAddress(RegisterPair::HL), Rgstr::E);
    break;
  case 0x74:
    // logger.debug("LD (HL),H - 74 ");
    alu.LD(MemoryAddress(RegisterPair::HL), Rgstr::H);
    break;
  case 0x75:
    // logger.debug("LD (HL),L - 75 ");
    alu.LD(MemoryAddress(RegisterPair::HL), Rgstr::L);
    break;
  case 0x76:
    // logger.debug("HALT - 76 ");
    alu.HALT();
    break;
  case 0x77:
    // logger.debug("LD (HL),A - 77 ");
    alu.LD(MemoryAddress(RegisterPair::HL), Rgstr::A);
    break;
  case 0x78:
    // logger.debug("LD A,B - 78 ");
    alu.LD(Rgstr::A, Rgstr::B);
    break;
  case 0x79:
    // logger.debug("LD A,C - 79 ");
    alu.LD(Rgstr::A, Rgstr::C);
    break;
  case 0x7A:
    // logger.debug("LD A,D - 7a ");
    alu.LD(Rgstr::A, Rgstr::D);
    break;
  case 0x7B:
    // logger.debug("LD A,E - 7b ");
    alu.LD(Rgstr::A, Rgstr::E);
    break;
  case 0x7C:
    // logger.debug("LD A,H - 7c ");
    alu.LD(Rgstr::A, Rgstr::H);
    break;
  case 0x7D:
    // logger.debug("LD A,L - 7d ");
    alu.LD(Rgstr::A, Rgstr::L);
    break;
  case 0x7E:
    // logger.debug("LD A,(HL) - 7e ");
    alu.LD(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
  case 0x7F:
    // logger.debug("LD A,A - 7f ");
    alu.LD(Rgstr::A, Rgstr::A);
    break;
  case 0x80:
    // logger.debug("ADD A,B - 80 ");
    alu.ADD(Rgstr::A, Rgstr::B);
    break;
  case 0x81:
    // logger.debug("ADD A,C - 81 ");
    alu.ADD(Rgstr::A, Rgstr::C);
    break;
  case 0x82:
    // logger.debug("ADD A,D - 82 ");
    alu.ADD(Rgstr::A, Rgstr::D);
    break;
  case 0x83:
    // logger.debug("ADD A,E - 83 ");
    alu.ADD(Rgstr::A, Rgstr::E);
    break;
  case 0x84:
    // logger.debug("ADD A,H - 84 ");
    alu.ADD(Rgstr::A, Rgstr::H);
    break;
  case 0x85:
    // logger.debug("ADD A,L - 85 ");
    alu.ADD(Rgstr::A, Rgstr::L);
    break;
  case 0x86:
    // logger.debug("ADD A,(HL) - 86 ");
    alu.ADD(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
  case 0x87:
    // logger.debug("ADD A,A - 87 ");
    alu.ADD(Rgstr::A, Rgstr::A);
    break;
  case 0x88:
    // logger.info("ADC A,B - 88 ");
    alu.ADC(Rgstr::A, Rgstr::B);
    break;
  case 0x89:
    // logger.info("ADC A,C - 89 ");
    alu.ADC(Rgstr::A, Rgstr::C);
    break;
  case 0x8A:
    // logger.info("ADC A,D - 8a ");
    alu.ADC(Rgstr::A, Rgstr::D);
    break;
  case 0x8B:
    // logger.info("ADC A,E - 8b ");
    alu.ADC(Rgstr::A, Rgstr::E);
    break;
  case 0x8C:
    // logger.info("ADC A,H - 8c ");
    alu.ADC(Rgstr::A, Rgstr::H);
    break;
  case 0x8D:
    // logger.info("ADC A,L - 8d ");
    alu.ADC(Rgstr::A, Rgstr::L);
    break;
  case 0x8E:
    // logger.info("ADC A,(HL) - 8e ");
    alu.ADC(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
  case 0x8F:
    // logger.info("ADC A,A - 8f ");
    alu.ADC(Rgstr::A, Rgstr::A);
    break;
  case 0x90:
    // logger.debug("SUB B - 90 ");
    alu.SUB(Rgstr::B);
    break;
  case 0x91:
    // logger.debug("SUB C - 91 ");
    alu.SUB(Rgstr::C);
    break;
  case 0x92:
    // logger.debug("SUB D - 92 ");
    alu.SUB(Rgstr::D);
    break;
  case 0x93:
    // logger.debug("SUB E - 93 ");
    alu.SUB(Rgstr::E);
    break;
  case 0x94:
    // logger.debug("SUB H - 94 ");
    alu.SUB(Rgstr::H);
    break;
  case 0x95:
    // logger.debug("SUB L - 95 ");
    alu.SUB(Rgstr::L);
    break;
  case 0x96:
    // logger.debug("SUB (HL) - 96 ");
    alu.SUB(MemoryAddress(RegisterPair::HL));
    break;
  case 0x97:
    // logger.debug("SUB A - 97 ");
    alu.SUB(Rgstr::A);
    break;
  case 0x98:
    // logger.info("SBC A,B - 98 ");
    alu.SBC(Rgstr::A, Rgstr::B);
    break;
  case 0x99:
    // logger.info("SBC A,C - 99 ");
    alu.SBC(Rgstr::A, Rgstr::C);
    break;
  case 0x9A:
    // logger.info("SBC A,D - 9a ");
    alu.SBC(Rgstr::A, Rgstr::D);
    break;
  case 0x9B:
    // logger.info("SBC A,E - 9b ");
    alu.SBC(Rgstr::A, Rgstr::E);
    break;
  case 0x9C:
    // logger.info("SBC A,H - 9c ");
    alu.SBC(Rgstr::A, Rgstr::H);
    break;
  case 0x9D:
    // logger.info("SBC A,L - 9d ");
    alu.SBC(Rgstr::A, Rgstr::L);
    break;
  case 0x9E:
    // logger.info("SBC A,(HL) - 9e ");
    alu.SBC(Rgstr::A, MemoryAddress(RegisterPair::HL));
    break;
  case 0x9F:
    // logger.info("SBC A,A - 9f ");
    alu.SBC(Rgstr::A, Rgstr::A);
    break;
  case 0xA0:
    // logger.debug("AND B - a0 ");
    alu.AND(Rgstr::B);
    break;
  case 0xA1:
    // logger.debug("AND C - a1 ");
    alu.AND(Rgstr::C);
    break;
  case 0xA2:
    // logger.debug("AND D - a2 ");
    alu.AND(Rgstr::D);
    break;
  case 0xA3:
    // logger.debug("AND E - a3 ");
    alu.AND(Rgstr::E);
    break;
  case 0xA4:
    // logger.debug("AND H - a4 ");
    alu.AND(Rgstr::H);
    break;
  case 0xA5:
    // logger.debug("AND L - a5 ");
    alu.AND(Rgstr::L);
    break;
  case 0xA6:
    // logger.debug("AND (HL) - a6 ");
    alu.AND(MemoryAddress(RegisterPair::HL));
    break;
  case 0xA7:
    // logger.debug("AND A - a7 ");
    alu.AND(Rgstr::A);
    break;
  case 0xA8:
    // logger.debug("XOR B - a8 ");
    alu.XOR(Rgstr::B);
    break;
  case 0xA9:
    // logger.debug("XOR C - a9 ");
    alu.XOR(Rgstr::C);
    break;
  case 0xAA:
    // logger.debug("XOR D - aa ");
    alu.XOR(Rgstr::D);
    break;
  case 0xAB:
    // logger.debug("XOR E - ab ");
    alu.XOR(Rgstr::E);
    break;
  case 0xAC:
    // logger.debug("XOR H - ac ");
    alu.XOR(Rgstr::H);
    break;
  case 0xAD:
    // logger.debug("XOR L - ad ");
    alu.XOR(Rgstr::L);
    break;
  case 0xAE:
    // logger.debug("XOR (HL) - ae ");
    alu.XOR(MemoryAddress(RegisterPair::HL));
    break;
  case 0xAF:
    // logger.debug("XOR A - af ");
    alu.XOR(Rgstr::A);
    break;
  case 0xB0:
    // logger.debug("OR B - b0 ");
    alu.OR(Rgstr::B);
    break;
  case 0xB1:
    // logger.debug("OR C - b1 ");
    alu.OR(Rgstr::C);
    break;
  case 0xB2:
    // logger.debug("OR D - b2 ");
    alu.OR(Rgstr::D);
    break;
  case 0xB3:
    // logger.debug("OR E - b3 ");
    alu.OR(Rgstr::E);
    break;
  case 0xB4:
    // logger.debug("OR H - b4 ");
    alu.OR(Rgstr::H);
    break;
  case 0xB5:
    // logger.debug("OR L - b5 ");
    alu.OR(Rgstr::L);
    break;
  case 0xB6:
    // logger.debug("OR (HL) - b6 ");
    alu.OR(MemoryAddress(RegisterPair::HL));
    break;
  case 0xB7:
    // logger.debug("OR A - b7 ");
    alu.OR(Rgstr::A);
    break;
  case 0xB8:
    // logger.debug("CP B - b8 ");
    alu.CP(Rgstr::B);
    break;
  case 0xB9:
    // logger.debug("CP C - b9 ");
    alu.CP(Rgstr::C);
    break;
  case 0xBA:
    // logger.debug("CP D - ba ");
    alu.CP(Rgstr::D);
    break;
  case 0xBB:
    // logger.debug("CP E - bb ");
    alu.CP(Rgstr::E);
    break;
  case 0xBC:
    // logger.debug("CP H - bc ");
    alu.CP(Rgstr::H);
    break;
  case 0xBD:
    // logger.debug("CP L - bd ");
    alu.CP(Rgstr::L);
    break;
  case 0xBE:
    // logger.debug("CP (HL) - be ");
    alu.CP(MemoryAddress(RegisterPair::HL));
    break;
  case 0xBF:
    // logger.debug("CP A - bf ");
    alu.CP(Rgstr::A);
    break;
  case 0xC0:
    // logger.debug("RET NZ - c0 ");
    alu.RET(Condition::NZ);
    break;
  case 0xC1:
    // logger.debug("POP BC - c1 ");
    alu.POP(RegisterPair::BC);
    break;
  case 0xC2:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP NZ,(nn) - c2 n n ");
    alu.JP(Condition::NZ, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xC3:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP (nn) - c3 n n ");
    alu.JP(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xC4:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL NZ,(nn) - c4 n n ");
    alu.CALL(Condition::NZ, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xC5:
    // logger.debug("PUSH BC - c5 ");
    alu.PUSH(RegisterPair::BC);
    break;
  case 0xC6:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("ADD A,n - c6 n ");
    alu.ADD(Rgstr::A, currentInstruction[1]);
    break;
  case 0xC7:
    // logger.debug("RST 0H - c7 ");
    alu.RST(0x0);
    break;
  case 0xC8:
    // logger.debug("RET Z - c8 ");
    alu.RET(Condition::Z);
    break;
  case 0xC9:
    // logger.debug("RET - c9 ");
    alu.RET();
    break;
  case 0xCA:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP Z,(nn) - ca n n ");
    alu.JP(Condition::Z, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xCB:
    // get opcode
    currentInstruction[1] = next(memory, pc);
    switch (currentInstruction[1]) {
    case 0x00:
      // logger.debug("RLC B - cb 0 ");
      alu.RLC(Rgstr::B);
      break;
    case 0x01:
      // logger.debug("RLC C - cb 1 ");
      alu.RLC(Rgstr::C);
      break;
    case 0x02:
      // logger.debug("RLC D - cb 2 ");
      alu.RLC(Rgstr::D);
      break;
    case 0x03:
      // logger.debug("RLC E - cb 3 ");
      alu.RLC(Rgstr::E);
      break;
    case 0x04:
      // logger.debug("RLC H - cb 4 ");
      alu.RLC(Rgstr::H);
      break;
    case 0x05:
      // logger.debug("RLC L - cb 5 ");
      alu.RLC(Rgstr::L);
      break;
    case 0x06:
      // logger.debug("RLC (HL) - cb 6 ");
      alu.RLC(MemoryAddress(RegisterPair::HL));
      break;
    case 0x07:
      // logger.debug("RLC A - cb 7 ");
      alu.RLC(Rgstr::A);
      break;
    case 0x08:
      // logger.debug("RRC B - cb 8 ");
      alu.RRC(Rgstr::B);
      break;
    case 0x09:
      // logger.debug("RRC C - cb 9 ");
      alu.RRC(Rgstr::C);
      break;
    case 0x0A:
      // logger.debug("RRC D - cb a ");
      alu.RRC(Rgstr::D);
      break;
    case 0x0B:
      // logger.debug("RRC E - cb b ");
      alu.RRC(Rgstr::E);
      break;
    case 0x0C:
      // logger.debug("RRC H - cb c ");
      alu.RRC(Rgstr::H);
      break;
    case 0x0D:
      // logger.debug("RRC L - cb d ");
      alu.RRC(Rgstr::L);
      break;
    case 0x0E:
      // logger.debug("RRC (HL) - cb e ");
      alu.RRC(MemoryAddress(RegisterPair::HL));
      break;
    case 0x0F:
      // logger.debug("RRC A - cb f ");
      alu.RRC(Rgstr::A);
      break;
    case 0x10:
      // logger.debug("RL B - cb 10 ");
      alu.RL(Rgstr::B);
      break;
    case 0x11:
      // logger.debug("RL C - cb 11 ");
      alu.RL(Rgstr::C);
      break;
    case 0x12:
      // logger.debug("RL D - cb 12 ");
      alu.RL(Rgstr::D);
      break;
    case 0x13:
      // logger.debug("RL E - cb 13 ");
      alu.RL(Rgstr::E);
      break;
    case 0x14:
      // logger.debug("RL H - cb 14 ");
      alu.RL(Rgstr::H);
      break;
    case 0x15:
      // logger.debug("RL L - cb 15 ");
      alu.RL(Rgstr::L);
      break;
    case 0x16:
      // logger.debug("RL (HL) - cb 16 ");
      alu.RL(MemoryAddress(RegisterPair::HL));
      break;
    case 0x17:
      // logger.debug("RL A - cb 17 ");
      alu.RL(Rgstr::A);
      break;
    case 0x18:
      // logger.debug("RR B - cb 18 ");
      alu.RR(Rgstr::B);
      break;
    case 0x19:
      // logger.debug("RR C - cb 19 ");
      alu.RR(Rgstr::C);
      break;
    case 0x1A:
      // logger.debug("RR D - cb 1a ");
      alu.RR(Rgstr::D);
      break;
    case 0x1B:
      // logger.debug("RR E - cb 1b ");
      alu.RR(Rgstr::E);
      break;
    case 0x1C:
      // logger.debug("RR H - cb 1c ");
      alu.RR(Rgstr::H);
      break;
    case 0x1D:
      // logger.debug("RR L - cb 1d ");
      alu.RR(Rgstr::L);
      break;
    case 0x1E:
      // logger.debug("RR (HL) - cb 1e ");
      alu.RR(MemoryAddress(RegisterPair::HL));
      break;
    case 0x1F:
      // logger.debug("RR A - cb 1f ");
      alu.RR(Rgstr::A);
      break;
    case 0x20:
      // logger.debug("SLA B - cb 20 ");
      alu.SLA(Rgstr::B);
      break;
    case 0x21:
      // logger.debug("SLA C - cb 21 ");
      alu.SLA(Rgstr::C);
      break;
    case 0x22:
      // logger.debug("SLA D - cb 22 ");
      alu.SLA(Rgstr::D);
      break;
    case 0x23:
      // logger.debug("SLA E - cb 23 ");
      alu.SLA(Rgstr::E);
      break;
    case 0x24:
      // logger.debug("SLA H - cb 24 ");
      alu.SLA(Rgstr::H);
      break;
    case 0x25:
      // logger.debug("SLA L - cb 25 ");
      alu.SLA(Rgstr::L);
      break;
    case 0x26:
      // logger.debug("SLA (HL) - cb 26 ");
      alu.SLA(MemoryAddress(RegisterPair::HL));
      break;
    case 0x27:
      // logger.debug("SLA A - cb 27 ");
      alu.SLA(Rgstr::A);
      break;
    case 0x28:
      // logger.debug("SRA B - cb 28 ");
      alu.SRA(Rgstr::B);
      break;
    case 0x29:
      // logger.debug("SRA C - cb 29 ");
      alu.SRA(Rgstr::C);
      break;
    case 0x2A:
      // logger.debug("SRA D - cb 2a ");
      alu.SRA(Rgstr::D);
      break;
    case 0x2B:
      // logger.debug("SRA E - cb 2b ");
      alu.SRA(Rgstr::E);
      break;
    case 0x2C:
      // logger.debug("SRA H - cb 2c ");
      alu.SRA(Rgstr::H);
      break;
    case 0x2D:
      // logger.debug("SRA L - cb 2d ");
      alu.SRA(Rgstr::L);
      break;
    case 0x2E:
      // logger.debug("SRA (HL) - cb 2e ");
      alu.SRA(MemoryAddress(RegisterPair::HL));
      break;
    case 0x2F:
      // logger.debug("SRA A - cb 2f ");
      alu.SRA(Rgstr::A);
      break;
    case 0x38:
      // logger.debug("SRL B - cb 38 ");
      alu.SRL(Rgstr::B);
      break;
    case 0x39:
      // logger.debug("SRL C - cb 39 ");
      alu.SRL(Rgstr::C);
      break;
    case 0x3A:
      // logger.debug("SRL D - cb 3a ");
      alu.SRL(Rgstr::D);
      break;
    case 0x3B:
      // logger.debug("SRL E - cb 3b ");
      alu.SRL(Rgstr::E);
      break;
    case 0x3C:
      // logger.debug("SRL H - cb 3c ");
      alu.SRL(Rgstr::H);
      break;
    case 0x3D:
      // logger.debug("SRL L - cb 3d ");
      alu.SRL(Rgstr::L);
      break;
    case 0x3E:
      // logger.debug("SRL (HL) - cb 3e ");
      alu.SRL(MemoryAddress(RegisterPair::HL));
      break;
    case 0x3F:
      // logger.debug("SRL A - cb 3f ");
      alu.SRL(Rgstr::A);
      break;
    case 0x40:
      // logger.debug("BIT 0,B - cb 40 ");
      alu.BIT(0, Rgstr::B);
      break;
    case 0x41:
      // logger.debug("BIT 0,C - cb 41 ");
      alu.BIT(0, Rgstr::C);
      break;
    case 0x42:
      // logger.debug("BIT 0,D - cb 42 ");
      alu.BIT(0, Rgstr::D);
      break;
    case 0x43:
      // logger.debug("BIT 0,E - cb 43 ");
      alu.BIT(0, Rgstr::E);
      break;
    case 0x44:
      // logger.debug("BIT 0,H - cb 44 ");
      alu.BIT(0, Rgstr::H);
      break;
    case 0x45:
      // logger.debug("BIT 0,L - cb 45 ");
      alu.BIT(0, Rgstr::L);
      break;
    case 0x46:
      // logger.debug("BIT 0,(HL) - cb 46 ");
      alu.BIT(0, MemoryAddress(RegisterPair::HL));
      break;
    case 0x47:
      // logger.debug("BIT 0,A - cb 47 ");
      alu.BIT(0, Rgstr::A);
      break;
    case 0x48:
      // logger.debug("BIT 1,B - cb 48 ");
      alu.BIT(1, Rgstr::B);
      break;
    case 0x49:
      // logger.debug("BIT 1,C - cb 49 ");
      alu.BIT(1, Rgstr::C);
      break;
    case 0x4A:
      // logger.debug("BIT 1,D - cb 4a ");
      alu.BIT(1, Rgstr::D);
      break;
    case 0x4B:
      // logger.debug("BIT 1,E - cb 4b ");
      alu.BIT(1, Rgstr::E);
      break;
    case 0x4C:
      // logger.debug("BIT 1,H - cb 4c ");
      alu.BIT(1, Rgstr::H);
      break;
    case 0x4D:
      // logger.debug("BIT 1,L - cb 4d ");
      alu.BIT(1, Rgstr::L);
      break;
    case 0x4E:
      // logger.debug("BIT 1,(HL) - cb 4e ");
      alu.BIT(1, MemoryAddress(RegisterPair::HL));
      break;
    case 0x4F:
      // logger.debug("BIT 1,A - cb 4f ");
      alu.BIT(1, Rgstr::A);
      break;
    case 0x50:
      // logger.debug("BIT 2,B - cb 50 ");
      alu.BIT(2, Rgstr::B);
      break;
    case 0x51:
      // logger.debug("BIT 2,C - cb 51 ");
      alu.BIT(2, Rgstr::C);
      break;
    case 0x52:
      // logger.debug("BIT 2,D - cb 52 ");
      alu.BIT(2, Rgstr::D);
      break;
    case 0x53:
      // logger.debug("BIT 2,E - cb 53 ");
      alu.BIT(2, Rgstr::E);
      break;
    case 0x54:
      // logger.debug("BIT 2,H - cb 54 ");
      alu.BIT(2, Rgstr::H);
      break;
    case 0x55:
      // logger.debug("BIT 2,L - cb 55 ");
      alu.BIT(2, Rgstr::L);
      break;
    case 0x56:
      // logger.debug("BIT 2,(HL) - cb 56 ");
      alu.BIT(2, MemoryAddress(RegisterPair::HL));
      break;
    case 0x57:
      // logger.debug("BIT 2,A - cb 57 ");
      alu.BIT(2, Rgstr::A);
      break;
    case 0x58:
      // logger.debug("BIT 3,B - cb 58 ");
      alu.BIT(3, Rgstr::B);
      break;
    case 0x59:
      // logger.debug("BIT 3,C - cb 59 ");
      alu.BIT(3, Rgstr::C);
      break;
    case 0x5A:
      // logger.debug("BIT 3,D - cb 5a ");
      alu.BIT(3, Rgstr::D);
      break;
    case 0x5B:
      // logger.debug("BIT 3,E - cb 5b ");
      alu.BIT(3, Rgstr::E);
      break;
    case 0x5C:
      // logger.debug("BIT 3,H - cb 5c ");
      alu.BIT(3, Rgstr::H);
      break;
    case 0x5D:
      // logger.debug("BIT 3,L - cb 5d ");
      alu.BIT(3, Rgstr::L);
      break;
    case 0x5E:
      // logger.debug("BIT 3,(HL) - cb 5e ");
      alu.BIT(3, MemoryAddress(RegisterPair::HL));
      break;
    case 0x5F:
      // logger.debug("BIT 3,A - cb 5f ");
      alu.BIT(3, Rgstr::A);
      break;
    case 0x60:
      // logger.debug("BIT 4,B - cb 60 ");
      alu.BIT(4, Rgstr::B);
      break;
    case 0x61:
      // logger.debug("BIT 4,C - cb 61 ");
      alu.BIT(4, Rgstr::C);
      break;
    case 0x62:
      // logger.debug("BIT 4,D - cb 62 ");
      alu.BIT(4, Rgstr::D);
      break;
    case 0x63:
      // logger.debug("BIT 4,E - cb 63 ");
      alu.BIT(4, Rgstr::E);
      break;
    case 0x64:
      // logger.debug("BIT 4,H - cb 64 ");
      alu.BIT(4, Rgstr::H);
      break;
    case 0x65:
      // logger.debug("BIT 4,L - cb 65 ");
      alu.BIT(4, Rgstr::L);
      break;
    case 0x66:
      // logger.debug("BIT 4,(HL) - cb 66 ");
      alu.BIT(4, MemoryAddress(RegisterPair::HL));
      break;
    case 0x67:
      // logger.debug("BIT 4,A - cb 67 ");
      alu.BIT(4, Rgstr::A);
      break;
    case 0x68:
      // logger.debug("BIT 5,B - cb 68 ");
      alu.BIT(5, Rgstr::B);
      break;
    case 0x69:
      // logger.debug("BIT 5,C - cb 69 ");
      alu.BIT(5, Rgstr::C);
      break;
    case 0x6A:
      // logger.debug("BIT 5,D - cb 6a ");
      alu.BIT(5, Rgstr::D);
      break;
    case 0x6B:
      // logger.debug("BIT 5,E - cb 6b ");
      alu.BIT(5, Rgstr::E);
      break;
    case 0x6C:
      // logger.debug("BIT 5,H - cb 6c ");
      alu.BIT(5, Rgstr::H);
      break;
    case 0x6D:
      // logger.debug("BIT 5,L - cb 6d ");
      alu.BIT(5, Rgstr::L);
      break;
    case 0x6E:
      // logger.debug("BIT 5,(HL) - cb 6e ");
      alu.BIT(5, MemoryAddress(RegisterPair::HL));
      break;
    case 0x6F:
      // logger.debug("BIT 5,A - cb 6f ");
      alu.BIT(5, Rgstr::A);
      break;
    case 0x70:
      // logger.debug("BIT 6,B - cb 70 ");
      alu.BIT(6, Rgstr::B);
      break;
    case 0x71:
      // logger.debug("BIT 6,C - cb 71 ");
      alu.BIT(6, Rgstr::C);
      break;
    case 0x72:
      // logger.debug("BIT 6,D - cb 72 ");
      alu.BIT(6, Rgstr::D);
      break;
    case 0x73:
      // logger.debug("BIT 6,E - cb 73 ");
      alu.BIT(6, Rgstr::E);
      break;
    case 0x74:
      // logger.debug("BIT 6,H - cb 74 ");
      alu.BIT(6, Rgstr::H);
      break;
    case 0x75:
      // logger.debug("BIT 6,L - cb 75 ");
      alu.BIT(6, Rgstr::L);
      break;
    case 0x76:
      // logger.debug("BIT 6,(HL) - cb 76 ");
      alu.BIT(6, MemoryAddress(RegisterPair::HL));
      break;
    case 0x77:
      // logger.debug("BIT 6,A - cb 77 ");
      alu.BIT(6, Rgstr::A);
      break;
    case 0x78:
      // logger.debug("BIT 7,B - cb 78 ");
      alu.BIT(7, Rgstr::B);
      break;
    case 0x79:
      // logger.debug("BIT 7,C - cb 79 ");
      alu.BIT(7, Rgstr::C);
      break;
    case 0x7A:
      // logger.debug("BIT 7,D - cb 7a ");
      alu.BIT(7, Rgstr::D);
      break;
    case 0x7B:
      // logger.debug("BIT 7,E - cb 7b ");
      alu.BIT(7, Rgstr::E);
      break;
    case 0x7C:
      // logger.debug("BIT 7,H - cb 7c ");
      alu.BIT(7, Rgstr::H);
      break;
    case 0x7D:
      // logger.debug("BIT 7,L - cb 7d ");
      alu.BIT(7, Rgstr::L);
      break;
    case 0x7E:
      // logger.debug("BIT 7,(HL) - cb 7e ");
      alu.BIT(7, MemoryAddress(RegisterPair::HL));
      break;
    case 0x7F:
      // logger.debug("BIT 7,A - cb 7f ");
      alu.BIT(7, Rgstr::A);
      break;
    case 0x80:
      // logger.debug("RES 0,B - cb 80 ");
      alu.RES(0, Rgstr::B);
      break;
    case 0x81:
      // logger.debug("RES 0,C - cb 81 ");
      alu.RES(0, Rgstr::C);
      break;
    case 0x82:
      // logger.debug("RES 0,D - cb 82 ");
      alu.RES(0, Rgstr::D);
      break;
    case 0x83:
      // logger.debug("RES 0,E - cb 83 ");
      alu.RES(0, Rgstr::E);
      break;
    case 0x84:
      // logger.debug("RES 0,H - cb 84 ");
      alu.RES(0, Rgstr::H);
      break;
    case 0x85:
      // logger.debug("RES 0,L - cb 85 ");
      alu.RES(0, Rgstr::L);
      break;
    case 0x86:
      // logger.debug("RES 0,(HL) - cb 86 ");
      alu.RES(0, MemoryAddress(RegisterPair::HL));
      break;
    case 0x87:
      // logger.debug("RES 0,A - cb 87 ");
      alu.RES(0, Rgstr::A);
      break;
    case 0x88:
      // logger.debug("RES 1,B - cb 88 ");
      alu.RES(1, Rgstr::B);
      break;
    case 0x89:
      // logger.debug("RES 1,C - cb 89 ");
      alu.RES(1, Rgstr::C);
      break;
    case 0x8A:
      // logger.debug("RES 1,D - cb 8a ");
      alu.RES(1, Rgstr::D);
      break;
    case 0x8B:
      // logger.debug("RES 1,E - cb 8b ");
      alu.RES(1, Rgstr::E);
      break;
    case 0x8C:
      // logger.debug("RES 1,H - cb 8c ");
      alu.RES(1, Rgstr::H);
      break;
    case 0x8D:
      // logger.debug("RES 1,L - cb 8d ");
      alu.RES(1, Rgstr::L);
      break;
    case 0x8E:
      // logger.debug("RES 1,(HL) - cb 8e ");
      alu.RES(1, MemoryAddress(RegisterPair::HL));
      break;
    case 0x8F:
      // logger.debug("RES 1,A - cb 8f ");
      alu.RES(1, Rgstr::A);
      break;
    case 0x90:
      // logger.debug("RES 2,B - cb 90 ");
      alu.RES(2, Rgstr::B);
      break;
    case 0x91:
      // logger.debug("RES 2,C - cb 91 ");
      alu.RES(2, Rgstr::C);
      break;
    case 0x92:
      // logger.debug("RES 2,D - cb 92 ");
      alu.RES(2, Rgstr::D);
      break;
    case 0x93:
      // logger.debug("RES 2,E - cb 93 ");
      alu.RES(2, Rgstr::E);
      break;
    case 0x94:
      // logger.debug("RES 2,H - cb 94 ");
      alu.RES(2, Rgstr::H);
      break;
    case 0x95:
      // logger.debug("RES 2,L - cb 95 ");
      alu.RES(2, Rgstr::L);
      break;
    case 0x96:
      // logger.debug("RES 2,(HL) - cb 96 ");
      alu.RES(2, MemoryAddress(RegisterPair::HL));
      break;
    case 0x97:
      // logger.debug("RES 2,A - cb 97 ");
      alu.RES(2, Rgstr::A);
      break;
    case 0x98:
      // logger.debug("RES 3,B - cb 98 ");
      alu.RES(3, Rgstr::B);
      break;
    case 0x99:
      // logger.debug("RES 3,C - cb 99 ");
      alu.RES(3, Rgstr::C);
      break;
    case 0x9A:
      // logger.debug("RES 3,D - cb 9a ");
      alu.RES(3, Rgstr::D);
      break;
    case 0x9B:
      // logger.debug("RES 3,E - cb 9b ");
      alu.RES(3, Rgstr::E);
      break;
    case 0x9C:
      // logger.debug("RES 3,H - cb 9c ");
      alu.RES(3, Rgstr::H);
      break;
    case 0x9D:
      // logger.debug("RES 3,L - cb 9d ");
      alu.RES(3, Rgstr::L);
      break;
    case 0x9E:
      // logger.debug("RES 3,(HL) - cb 9e ");
      alu.RES(3, MemoryAddress(RegisterPair::HL));
      break;
    case 0x9F:
      // logger.debug("RES 3,A - cb 9f ");
      alu.RES(3, Rgstr::A);
      break;
    case 0xA0:
      // logger.debug("RES 4,B - cb a0 ");
      alu.RES(4, Rgstr::B);
      break;
    case 0xA1:
      // logger.debug("RES 4,C - cb a1 ");
      alu.RES(4, Rgstr::C);
      break;
    case 0xA2:
      // logger.debug("RES 4,D - cb a2 ");
      alu.RES(4, Rgstr::D);
      break;
    case 0xA3:
      // logger.debug("RES 4,E - cb a3 ");
      alu.RES(4, Rgstr::E);
      break;
    case 0xA4:
      // logger.debug("RES 4,H - cb a4 ");
      alu.RES(4, Rgstr::H);
      break;
    case 0xA5:
      // logger.debug("RES 4,L - cb a5 ");
      alu.RES(4, Rgstr::L);
      break;
    case 0xA6:
      // logger.debug("RES 4,(HL) - cb a6 ");
      alu.RES(4, MemoryAddress(RegisterPair::HL));
      break;
    case 0xA7:
      // logger.debug("RES 4,A - cb a7 ");
      alu.RES(4, Rgstr::A);
      break;
    case 0xA8:
      // logger.debug("RES 5,B - cb a8 ");
      alu.RES(5, Rgstr::B);
      break;
    case 0xA9:
      // logger.debug("RES 5,C - cb a9 ");
      alu.RES(5, Rgstr::C);
      break;
    case 0xAA:
      // logger.debug("RES 5,D - cb aa ");
      alu.RES(5, Rgstr::D);
      break;
    case 0xAB:
      // logger.debug("RES 5,E - cb ab ");
      alu.RES(5, Rgstr::E);
      break;
    case 0xAC:
      // logger.debug("RES 5,H - cb ac ");
      alu.RES(5, Rgstr::H);
      break;
    case 0xAD:
      // logger.debug("RES 5,L - cb ad ");
      alu.RES(5, Rgstr::L);
      break;
    case 0xAE:
      // logger.debug("RES 5,(HL) - cb ae ");
      alu.RES(5, MemoryAddress(RegisterPair::HL));
      break;
    case 0xAF:
      // logger.debug("RES 5,A - cb af ");
      alu.RES(5, Rgstr::A);
      break;
    case 0xB0:
      // logger.debug("RES 6,B - cb b0 ");
      alu.RES(6, Rgstr::B);
      break;
    case 0xB1:
      // logger.debug("RES 6,C - cb b1 ");
      alu.RES(6, Rgstr::C);
      break;
    case 0xB2:
      // logger.debug("RES 6,D - cb b2 ");
      alu.RES(6, Rgstr::D);
      break;
    case 0xB3:
      // logger.debug("RES 6,E - cb b3 ");
      alu.RES(6, Rgstr::E);
      break;
    case 0xB4:
      // logger.debug("RES 6,H - cb b4 ");
      alu.RES(6, Rgstr::H);
      break;
    case 0xB5:
      // logger.debug("RES 6,L - cb b5 ");
      alu.RES(6, Rgstr::L);
      break;
    case 0xB6:
      // logger.debug("RES 6,(HL) - cb b6 ");
      alu.RES(6, MemoryAddress(RegisterPair::HL));
      break;
    case 0xB7:
      // logger.debug("RES 6,A - cb b7 ");
      alu.RES(6, Rgstr::A);
      break;
    case 0xB8:
      // logger.debug("RES 7,B - cb b8 ");
      alu.RES(7, Rgstr::B);
      break;
    case 0xB9:
      // logger.debug("RES 7,C - cb b9 ");
      alu.RES(7, Rgstr::C);
      break;
    case 0xBA:
      // logger.debug("RES 7,D - cb ba ");
      alu.RES(7, Rgstr::D);
      break;
    case 0xBB:
      // logger.debug("RES 7,E - cb bb ");
      alu.RES(7, Rgstr::E);
      break;
    case 0xBC:
      // logger.debug("RES 7,H - cb bc ");
      alu.RES(7, Rgstr::H);
      break;
    case 0xBD:
      // logger.debug("RES 7,L - cb bd ");
      alu.RES(7, Rgstr::L);
      break;
    case 0xBE:
      // logger.debug("RES 7,(HL) - cb be ");
      alu.RES(7, MemoryAddress(RegisterPair::HL));
      break;
    case 0xBF:
      // logger.debug("RES 7,A - cb bf ");
      alu.RES(7, Rgstr::A);
      break;
    case 0xC0:
      // logger.debug("SET 0,B - cb c0 ");
      alu.SET(0, Rgstr::B);
      break;
    case 0xC1:
      // logger.debug("SET 0,C - cb c1 ");
      alu.SET(0, Rgstr::C);
      break;
    case 0xC2:
      // logger.debug("SET 0,D - cb c2 ");
      alu.SET(0, Rgstr::D);
      break;
    case 0xC3:
      // logger.debug("SET 0,E - cb c3 ");
      alu.SET(0, Rgstr::E);
      break;
    case 0xC4:
      // logger.debug("SET 0,H - cb c4 ");
      alu.SET(0, Rgstr::H);
      break;
    case 0xC5:
      // logger.debug("SET 0,L - cb c5 ");
      alu.SET(0, Rgstr::L);
      break;
    case 0xC6:
      // logger.debug("SET 0,(HL) - cb c6 ");
      alu.SET(0, MemoryAddress(RegisterPair::HL));
      break;
    case 0xC7:
      // logger.debug("SET 0,A - cb c7 ");
      alu.SET(0, Rgstr::A);
      break;
    case 0xC8:
      // logger.debug("SET 1,B - cb c8 ");
      alu.SET(1, Rgstr::B);
      break;
    case 0xC9:
      // logger.debug("SET 1,C - cb c9 ");
      alu.SET(1, Rgstr::C);
      break;
    case 0xCA:
      // logger.debug("SET 1,D - cb ca ");
      alu.SET(1, Rgstr::D);
      break;
    case 0xCB:
      // logger.debug("SET 1,E - cb cb ");
      alu.SET(1, Rgstr::E);
      break;
    case 0xCC:
      // logger.debug("SET 1,H - cb cc ");
      alu.SET(1, Rgstr::H);
      break;
    case 0xCD:
      // logger.debug("SET 1,L - cb cd ");
      alu.SET(1, Rgstr::L);
      break;
    case 0xCE:
      // logger.debug("SET 1,(HL) - cb ce ");
      alu.SET(1, MemoryAddress(RegisterPair::HL));
      break;
    case 0xCF:
      // logger.debug("SET 1,A - cb cf ");
      alu.SET(1, Rgstr::A);
      break;
    case 0xD0:
      // logger.debug("SET 2,B - cb d0 ");
      alu.SET(2, Rgstr::B);
      break;
    case 0xD1:
      // logger.debug("SET 2,C - cb d1 ");
      alu.SET(2, Rgstr::C);
      break;
    case 0xD2:
      // logger.debug("SET 2,D - cb d2 ");
      alu.SET(2, Rgstr::D);
      break;
    case 0xD3:
      // logger.debug("SET 2,E - cb d3 ");
      alu.SET(2, Rgstr::E);
      break;
    case 0xD4:
      // logger.debug("SET 2,H - cb d4 ");
      alu.SET(2, Rgstr::H);
      break;
    case 0xD5:
      // logger.debug("SET 2,L - cb d5 ");
      alu.SET(2, Rgstr::L);
      break;
    case 0xD6:
      // logger.debug("SET 2,(HL) - cb d6 ");
      alu.SET(2, MemoryAddress(RegisterPair::HL));
      break;
    case 0xD7:
      // logger.debug("SET 2,A - cb d7 ");
      alu.SET(2, Rgstr::A);
      break;
    case 0xD8:
      // logger.debug("SET 3,B - cb d8 ");
      alu.SET(3, Rgstr::B);
      break;
    case 0xD9:
      // logger.debug("SET 3,C - cb d9 ");
      alu.SET(3, Rgstr::C);
      break;
    case 0xDA:
      // logger.debug("SET 3,D - cb da ");
      alu.SET(3, Rgstr::D);
      break;
    case 0xDB:
      // logger.debug("SET 3,E - cb db ");
      alu.SET(3, Rgstr::E);
      break;
    case 0xDC:
      // logger.debug("SET 3,H - cb dc ");
      alu.SET(3, Rgstr::H);
      break;
    case 0xDD:
      // logger.debug("SET 3,L - cb dd ");
      alu.SET(3, Rgstr::L);
      break;
    case 0xDE:
      // logger.debug("SET 3,(HL) - cb de ");
      alu.SET(3, MemoryAddress(RegisterPair::HL));
      break;
    case 0xDF:
      // logger.debug("SET 3,A - cb df ");
      alu.SET(3, Rgstr::A);
      break;
    case 0xE0:
      // logger.debug("SET 4,B - cb e0 ");
      alu.SET(4, Rgstr::B);
      break;
    case 0xE1:
      // logger.debug("SET 4,C - cb e1 ");
      alu.SET(4, Rgstr::C);
      break;
    case 0xE2:
      // logger.debug("SET 4,D - cb e2 ");
      alu.SET(4, Rgstr::D);
      break;
    case 0xE3:
      // logger.debug("SET 4,E - cb e3 ");
      alu.SET(4, Rgstr::E);
      break;
    case 0xE4:
      // logger.debug("SET 4,H - cb e4 ");
      alu.SET(4, Rgstr::H);
      break;
    case 0xE5:
      // logger.debug("SET 4,L - cb e5 ");
      alu.SET(4, Rgstr::L);
      break;
    case 0xE6:
      // logger.debug("SET 4,(HL) - cb e6 ");
      alu.SET(4, MemoryAddress(RegisterPair::HL));
      break;
    case 0xE7:
      // logger.debug("SET 4,A - cb e7 ");
      alu.SET(4, Rgstr::A);
      break;
    case 0xE8:
      // logger.debug("SET 5,B - cb e8 ");
      alu.SET(5, Rgstr::B);
      break;
    case 0xE9:
      // logger.debug("SET 5,C - cb e9 ");
      alu.SET(5, Rgstr::C);
      break;
    case 0xEA:
      // logger.debug("SET 5,D - cb ea ");
      alu.SET(5, Rgstr::D);
      break;
    case 0xEB:
      // logger.debug("SET 5,E - cb eb ");
      alu.SET(5, Rgstr::E);
      break;
    case 0xEC:
      // logger.debug("SET 5,H - cb ec ");
      alu.SET(5, Rgstr::H);
      break;
    case 0xED:
      // logger.debug("SET 5,L - cb ed ");
      alu.SET(5, Rgstr::L);
      break;
    case 0xEE:
      // logger.debug("SET 5,(HL) - cb ee ");
      alu.SET(5, MemoryAddress(RegisterPair::HL));
      break;
    case 0xEF:
      // logger.debug("SET 5,A - cb ef ");
      alu.SET(5, Rgstr::A);
      break;
    case 0xF0:
      // logger.debug("SET 6,B - cb f0 ");
      alu.SET(6, Rgstr::B);
      break;
    case 0xF1:
      // logger.debug("SET 6,C - cb f1 ");
      alu.SET(6, Rgstr::C);
      break;
    case 0xF2:
      // logger.debug("SET 6,D - cb f2 ");
      alu.SET(6, Rgstr::D);
      break;
    case 0xF3:
      // logger.debug("SET 6,E - cb f3 ");
      alu.SET(6, Rgstr::E);
      break;
    case 0xF4:
      // logger.debug("SET 6,H - cb f4 ");
      alu.SET(6, Rgstr::H);
      break;
    case 0xF5:
      // logger.debug("SET 6,L - cb f5 ");
      alu.SET(6, Rgstr::L);
      break;
    case 0xF6:
      // logger.debug("SET 6,(HL) - cb f6 ");
      alu.SET(6, MemoryAddress(RegisterPair::HL));
      break;
    case 0xF7:
      // logger.debug("SET 6,A - cb f7 ");
      alu.SET(6, Rgstr::A);
      break;
    case 0xF8:
      // logger.debug("SET 7,B - cb f8 ");
      alu.SET(7, Rgstr::B);
      break;
    case 0xF9:
      // logger.debug("SET 7,C - cb f9 ");
      alu.SET(7, Rgstr::C);
      break;
    case 0xFA:
      // logger.debug("SET 7,D - cb fa ");
      alu.SET(7, Rgstr::D);
      break;
    case 0xFB:
      // logger.debug("SET 7,E - cb fb ");
      alu.SET(7, Rgstr::E);
      break;
    case 0xFC:
      // logger.debug("SET 7,H - cb fc ");
      alu.SET(7, Rgstr::H);
      break;
    case 0xFD:
      // logger.debug("SET 7,L - cb fd ");
      alu.SET(7, Rgstr::L);
      break;
    case 0xFE:
      // logger.debug("SET 7,(HL) - cb fe ");
      alu.SET(7, MemoryAddress(RegisterPair::HL));
      break;
    case 0xFF:
      // logger.debug("SET 7,A - cb ff ");
      alu.SET(7, Rgstr::A);
      break;
    }
    break;
  case 0xCC:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL Z,(nn) - cc n n ");
    alu.CALL(Condition::Z, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xCD:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL (nn) - cd n n ");
    alu.CALL(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xCE:
    currentInstruction[1] = next(memory, pc);
    // logger.info("ADC A,n - ce n ");
    alu.ADC(Rgstr::A, currentInstruction[1]);
    break;
  case 0xCF:
    // logger.debug("RST 8H - cf ");
    alu.RST(0x8);
    break;
  case 0xD0:
    // logger.debug("RET NC - d0 ");
    alu.RET(Condition::NC);
    break;
  case 0xD1:
    // logger.debug("POP DE - d1 ");
    alu.POP(RegisterPair::DE);
    break;
  case 0xD2:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP NC,(nn) - d2 n n ");
    alu.JP(Condition::NC, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xD3:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("OUT (n),A - d3 n ");
    alu.out(MemoryAddress(currentInstruction[1]), Rgstr::A);
    break;
  case 0xD4:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL NC,(nn) - d4 n n ");
    alu.CALL(Condition::NC, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xD5:
    // logger.debug("PUSH DE - d5 ");
    alu.PUSH(RegisterPair::DE);
    break;
  case 0xD6:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("SUB n - d6 n ");
    alu.SUB(currentInstruction[1]);
    break;
  case 0xD7:
    // logger.debug("RST 10H - d7 ");
    alu.RST(0x10);
    break;
  case 0xD8:
    // logger.debug("RET C - d8 ");
    alu.RET(Condition::C);
    break;
  case 0xD9:
    // logger.debug("EXX - d9 ");
    alu.EXX();
    break;
  case 0xDA:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP C,(nn) - da n n ");
    alu.JP(Condition::C, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xDB:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("IN A,(n) - db n ");
    alu.in(Rgstr::A, MemoryAddress(currentInstruction[1]));
    break;
  case 0xDC:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL C,(nn) - dc n n ");
    alu.CALL(Condition::C, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xDD:
    // get opcode
    currentInstruction[1] = next(memory, pc);
    switch (currentInstruction[1]) {
    case 0x09:
      // logger.debug("ADD IX,BC - dd 9 ");
      alu.ADD(RegisterPair::IX, RegisterPair::BC);
      break;
    case 0x19:
      // logger.debug("ADD IX,DE - dd 19 ");
      alu.ADD(RegisterPair::IX, RegisterPair::DE);
      break;
    case 0x21:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD IX,nn - dd 21 n n ");
      alu.LD(RegisterPair::IX, (currentInstruction[3] << 8) | currentInstruction[2]);
      break;
    case 0x22:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (nn),IX - dd 22 n n ");
      alu.LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::IX);
      break;
    case 0x23:
      // logger.debug("INC IX - dd 23 ");
      alu.INC(RegisterPair::IX);
      break;
    case 0x29:
      // logger.debug("ADD IX,IX - dd 29 ");
      alu.ADD(RegisterPair::IX, RegisterPair::IX);
      break;
    case 0x2A:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD IX,(nn) - dd 2a n n ");
      alu.LD(RegisterPair::IX, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
      break;
    case 0x2B:
      // logger.debug("DEC IX - dd 2b ");
      alu.DEC(RegisterPair::IX);
      break;
    case 0x34:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("INC (IX+d) - dd 34 n ");
      alu.INC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x35:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("DEC (IX+d) - dd 35 n ");
      alu.DEC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x36:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (IX+d),n - dd 36 n n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), currentInstruction[3]);
      break;
    case 0x39:
      // logger.debug("ADD IX,SP - dd 39 ");
      alu.ADD(RegisterPair::IX, RegisterPair::SP);
      break;
    case 0x46:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD B,(IX+d) - dd 46 n ");
      alu.LD(Rgstr::B, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x4E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD C,(IX+d) - dd 4e n ");
      alu.LD(Rgstr::C, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x56:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD D,(IX+d) - dd 56 n ");
      alu.LD(Rgstr::D, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x5E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD E,(IX+d) - dd 5e n ");
      alu.LD(Rgstr::E, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x66:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD H,(IX+d) - dd 66 n ");
      alu.LD(Rgstr::H, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x6E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD L,(IX+d) - dd 6e n ");
      alu.LD(Rgstr::L, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x70:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IX+d),B - dd 70 n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::B);
      break;
    case 0x71:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IX+d),C - dd 71 n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::C);
      break;
    case 0x72:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IX+d),D - dd 72 n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::D);
      break;
    case 0x73:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IX+d),E - dd 73 n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::E);
      break;
    case 0x74:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IX+d),H - dd 74 n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::H);
      break;
    case 0x75:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IX+d),L - dd 75 n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::L);
      break;
    case 0x77:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IX+d),A - dd 77 n ");
      alu.LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::A);
      break;
    case 0x7E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD A,(IX+d) - dd 7e n ");
      alu.LD(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x86:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("ADD A,(IX+d) - dd 86 n ");
      alu.ADD(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x8E:
      currentInstruction[2] = next(memory, pc);
      // logger.info("ADC A,(IX+d) - dd 8e n ");
      alu.ADC(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x96:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("SUB (IX+d) - dd 96 n ");
      alu.SUB(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0x9E:
      currentInstruction[2] = next(memory, pc);
      // logger.info("SBC A,(IX+d) - dd 9e n ");
      alu.SBC(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0xA6:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("AND (IX+d) - dd a6 n ");
      alu.AND(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0xAE:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("XOR (IX+d) - dd ae n ");
      alu.XOR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0xB6:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("OR (IX+d) - dd b6 n ");
      alu.OR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0xBE:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("CP (IX+d) - dd be n ");
      alu.CP(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
      break;
    case 0xCB:
      currentInstruction[2] = next(memory, pc);
      // get opcode
      currentInstruction[3] = next(memory, pc);
      switch (currentInstruction[3]) {
      case 0x06:
        // logger.debug("RLC (IX+d) - dd cb n 6 ");
        alu.RLC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x0E:
        // logger.debug("RRC (IX+d) - dd cb n e ");
        alu.RRC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x16:
        // logger.debug("RL (IX+d) - dd cb n 16 ");
        alu.RL(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x1E:
        // logger.debug("RR (IX+d) - dd cb n 1e ");
        alu.RR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x26:
        // logger.debug("SLA (IX+d) - dd cb n 26 ");
        alu.SLA(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x2E:
        // logger.debug("SRA (IX+d) - dd cb n 2e ");
        alu.SRA(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x3E:
        // logger.debug("SRL (IX+d) - dd cb n 3e ");
        alu.SRL(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x46:
        // logger.debug("BIT 0,(IX+d) - dd cb n 46 ");
        alu.BIT(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x4E:
        // logger.debug("BIT 1,(IX+d) - dd cb n 4e ");
        alu.BIT(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x56:
        // logger.debug("BIT 2,(IX+d) - dd cb n 56 ");
        alu.BIT(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x5E:
        // logger.debug("BIT 3,(IX+d) - dd cb n 5e ");
        alu.BIT(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x66:
        // logger.debug("BIT 4,(IX+d) - dd cb n 66 ");
        alu.BIT(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x6E:
        // logger.debug("BIT 5,(IX+d) - dd cb n 6e ");
        alu.BIT(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x76:
        // logger.debug("BIT 6,(IX+d) - dd cb n 76 ");
        alu.BIT(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x7E:
        // logger.debug("BIT 7,(IX+d) - dd cb n 7e ");
        alu.BIT(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x86:
        // logger.debug("RES 0,(IX+d) - dd cb n 86 ");
        alu.RES(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x8E:
        // logger.debug("RES 1,(IX+d) - dd cb n 8e ");
        alu.RES(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x96:
        // logger.debug("RES 2,(IX+d) - dd cb n 96 ");
        alu.RES(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0x9E:
        // logger.debug("RES 3,(IX+d) - dd cb n 9e ");
        alu.RES(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xA6:
        // logger.debug("RES 4,(IX+d) - dd cb n a6 ");
        alu.RES(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xAE:
        // logger.debug("RES 5,(IX+d) - dd cb n ae ");
        alu.RES(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xB6:
        // logger.debug("RES 6,(IX+d) - dd cb n b6 ");
        alu.RES(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xBE:
        // logger.debug("RES 7,(IX+d) - dd cb n be ");
        alu.RES(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xC6:
        // logger.debug("SET 0,(IX+d) - dd cb n c6 ");
        alu.SET(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xCE:
        // logger.debug("SET 1,(IX+d) - dd cb n ce ");
        alu.SET(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xD6:
        // logger.debug("SET 2,(IX+d) - dd cb n d6 ");
        alu.SET(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xDE:
        // logger.debug("SET 3,(IX+d) - dd cb n de ");
        alu.SET(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xE6:
        // logger.debug("SET 4,(IX+d) - dd cb n e6 ");
        alu.SET(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xEE:
        // logger.debug("SET 5,(IX+d) - dd cb n ee ");
        alu.SET(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xF6:
        // logger.debug("SET 6,(IX+d) - dd cb n f6 ");
        alu.SET(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      case 0xFE:
        // logger.debug("SET 7,(IX+d) - dd cb n fe ");
        alu.SET(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
        break;
      }
      break;
    case 0xE1:
      // logger.debug("POP IX - dd e1 ");
      alu.POP(RegisterPair::IX);
      break;
    case 0xE3:
      // logger.debug("EX (SP),IX - dd e3 ");
      alu.EX(MemoryAddress(RegisterPair::SP), RegisterPair::IX);
      break;
    case 0xE5:
      // logger.debug("PUSH IX - dd e5 ");
      alu.PUSH(RegisterPair::IX);
      break;
    case 0xE9:
      // logger.debug("JP (IX) - dd e9 ");
      alu.JP(MemoryAddress(RegisterPair::IX));
      break;
    case 0xF9:
      // logger.debug("LD SP,IX - dd f9 ");
      alu.LD(RegisterPair::SP, RegisterPair::IX);
      break;
    }
    break;
  case 0xDE:
    currentInstruction[1] = next(memory, pc);
    // logger.info("SBC A,n - de n ");
    alu.SBC(Rgstr::A, currentInstruction[1]);
    break;
  case 0xDF:
    // logger.debug("RST 18H - df ");
    alu.RST(0x18);
    break;
  case 0xE0:
    // logger.debug("RET PO - e0 ");
    alu.RET(Condition::PO);
    break;
  case 0xE1:
    // logger.debug("POP HL - e1 ");
    alu.POP(RegisterPair::HL);
    break;
  case 0xE2:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP PO,(nn) - e2 n n ");
    alu.JP(Condition::PO, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xE3:
    // logger.debug("EX (SP),HL - e3 ");
    alu.EX(MemoryAddress(RegisterPair::SP), RegisterPair::HL);
    break;
  case 0xE4:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL PO,(nn) - e4 n n ");
    alu.CALL(Condition::PO, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xE5:
    // logger.debug("PUSH HL - e5 ");
    alu.PUSH(RegisterPair::HL);
    break;
  case 0xE6:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("AND n - e6 n ");
    alu.AND(currentInstruction[1]);
    break;
  case 0xE7:
    // logger.debug("RST 20H - e7 ");
    alu.RST(0x20);
    break;
  case 0xE8:
    // logger.debug("RET PE - e8 ");
    alu.RET(Condition::PE);
    break;
  case 0xE9:
    // logger.debug("JP (HL) - e9 ");
    alu.JP(MemoryAddress(RegisterPair::HL));
    break;
  case 0xEA:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP PE,(nn) - ea n n ");
    alu.JP(Condition::PE, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xEB:
    // logger.debug("EX DE,HL - eb ");
    alu.EX(RegisterPair::DE, RegisterPair::HL);
    break;
  case 0xEC:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL PE,(nn) - ec n n ");
    alu.CALL(Condition::PE, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xED:
    // get opcode
    currentInstruction[1] = next(memory, pc);
    switch (currentInstruction[1]) {
    case 0x40:
      // logger.debug("IN B,(C) - ed 40 ");
      alu.in(Rgstr::B, MemoryAddress(Rgstr::C));
      break;
    case 0x41:
      // logger.debug("OUT (C),B - ed 41 ");
      alu.out(MemoryAddress(Rgstr::C), Rgstr::B);
      break;
    case 0x42:
      // logger.info("SBC HL,BC - ed 42 ");
      alu.SBC(RegisterPair::HL, RegisterPair::BC);
      break;
    case 0x43:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (nn),BC - ed 43 n n ");
      alu.LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::BC);
      break;
    case 0x44:
      // logger.debug("NEG - ed 44 ");
      alu.NEG();
      break;
    case 0x45:
      // logger.debug("RETN - ed 45 ");
      alu.RETN();
      break;
    case 0x46:
      // logger.debug("IM 0 - ed 46 ");
      alu.IM(0);
      break;
    case 0x47:
      // logger.debug("LD I,A - ed 47 ");
      alu.LD(Rgstr::I, Rgstr::A);
      break;
    case 0x48:
      // logger.debug("IN C,(C) - ed 48 ");
      alu.in(Rgstr::C, MemoryAddress(Rgstr::C));
      break;
    case 0x49:
      // logger.debug("OUT (C),C - ed 49 ");
      alu.out(MemoryAddress(Rgstr::C), Rgstr::C);
      break;
    case 0x4A:
      // logger.info("ADC HL,BC - ed 4a ");
      alu.ADC(RegisterPair::HL, RegisterPair::BC);
      break;
    case 0x4B:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD BC,(nn) - ed 4b n n ");
      alu.LD(RegisterPair::BC, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
      break;
    case 0x4D:
      // logger.debug("RETI - ed 4d ");
      alu.RETI();
      break;
    case 0x4F:
      // logger.debug("LD R,A - ed 4f ");
      alu.LD(Rgstr::R, Rgstr::A);
      break;
    case 0x50:
      // logger.debug("IN D,(C) - ed 50 ");
      alu.in(Rgstr::D, MemoryAddress(Rgstr::C));
      break;
    case 0x51:
      // logger.debug("OUT (C),D - ed 51 ");
      alu.out(MemoryAddress(Rgstr::C), Rgstr::D);
      break;
    case 0x52:
      // logger.info("SBC HL,DE - ed 52 ");
      alu.SBC(RegisterPair::HL, RegisterPair::DE);
      break;
    case 0x53:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (nn),DE - ed 53 n n ");
      alu.LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::DE);
      break;
    case 0x56:
      // logger.debug("IM 1 - ed 56 ");
      alu.IM(1);
      break;
    case 0x57:
      // logger.debug("LD A,I - ed 57 ");
      alu.LD(Rgstr::A, Rgstr::I);
      break;
    case 0x58:
      // logger.debug("IN E,(C) - ed 58 ");
      alu.in(Rgstr::E, MemoryAddress(Rgstr::C));
      break;
    case 0x59:
      // logger.debug("OUT (C),E - ed 59 ");
      alu.out(MemoryAddress(Rgstr::C), Rgstr::E);
      break;
    case 0x5A:
      // logger.info("ADC HL,DE - ed 5a ");
      alu.ADC(RegisterPair::HL, RegisterPair::DE);
      break;
    case 0x5B:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD DE,(nn) - ed 5b n n ");
      alu.LD(RegisterPair::DE, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
      break;
    case 0x5E:
      // logger.debug("IM 2 - ed 5e ");
      alu.IM(2);
      break;
    case 0x5F:
      // logger.debug("LD A,R - ed 5f ");
      alu.LD(Rgstr::A, Rgstr::R);
      break;
    case 0x60:
      // logger.debug("IN H,(C) - ed 60 ");
      alu.in(Rgstr::H, MemoryAddress(Rgstr::C));
      break;
    case 0x61:
      // logger.debug("OUT (C),H - ed 61 ");
      alu.out(MemoryAddress(Rgstr::C), Rgstr::H);
      break;
    case 0x62:
      // logger.info("SBC HL,HL - ed 62 ");
      alu.SBC(RegisterPair::HL, RegisterPair::HL);
      break;
    case 0x63:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (nn),HL - ed 63 n n ");
      alu.LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::HL);
      break;
    case 0x67:
      // logger.debug("RRD - ed 67 ");
      alu.RRD();
      break;
    case 0x68:
      // logger.debug("IN L,(C) - ed 68 ");
      alu.in(Rgstr::L, MemoryAddress(Rgstr::C));
      break;
    case 0x69:
      // logger.debug("OUT (C),L - ed 69 ");
      alu.out(MemoryAddress(Rgstr::C), Rgstr::L);
      break;
    case 0x6A:
      // logger.info("ADC HL,HL - ed 6a ");
      alu.ADC(RegisterPair::HL, RegisterPair::HL);
      break;
    case 0x6B:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD HL,(nn) - ed 6b n n ");
      alu.LD(RegisterPair::HL, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
      break;
    case 0x6F:
      // logger.debug("RLD - ed 6f ");
      alu.RLD();
      break;
    case 0x72:
      // logger.info("SBC HL,SP - ed 72 ");
      alu.SBC(RegisterPair::HL, RegisterPair::SP);
      break;
    case 0x73:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (nn),SP - ed 73 n n ");
      alu.LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::SP);
      break;
    case 0x78:
      // logger.debug("IN A,(C) - ed 78 ");
      alu.in(Rgstr::A, MemoryAddress(Rgstr::C));
      break;
    case 0x79:
      // logger.debug("OUT (C),A - ed 79 ");
      alu.out(MemoryAddress(Rgstr::C), Rgstr::A);
      break;
    case 0x7A:
      // logger.info("ADC HL,SP - ed 7a ");
      alu.ADC(RegisterPair::HL, RegisterPair::SP);
      break;
    case 0x7B:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD SP,(nn) - ed 7b n n ");
      alu.LD(RegisterPair::SP, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
      break;
    case 0xA0:
      // logger.debug("LDI - ed a0 ");
      alu.LDI();
      break;
    case 0xA1:
      // logger.debug("CPI - ed a1 ");
      alu.CPI();
      break;
    case 0xA2:
      // logger.debug("INI - ed a2 ");
      alu.INI();
      break;
    case 0xA3:
      // logger.debug("OUTI - ed a3 ");
      alu.OUTI();
      break;
    case 0xA8:
      // logger.debug("LDD - ed a8 ");
      alu.LDD();
      break;
    case 0xA9:
      // logger.debug("CPD - ed a9 ");
      alu.CPD();
      break;
    case 0xAA:
      // logger.debug("IND - ed aa ");
      alu.IND();
      break;
    case 0xAB:
      // logger.debug("OUTD - ed ab ");
      alu.OUTD();
      break;
    case 0xB0:
      // logger.debug("LDIR - ed b0 ");
      alu.LDIR();
      break;
    case 0xB1:
      // logger.debug("CPIR - ed b1 ");
      alu.CPIR();
      break;
    case 0xB2:
      // logger.debug("INIR - ed b2 ");
      alu.INIR();
      break;
    case 0xB3:
      // logger.debug("OTIR - ed b3 ");
      alu.OTIR();
      break;
    case 0xB8:
      // logger.debug("LDDR - ed b8 ");
      alu.LDDR();
      break;
    case 0xB9:
      // logger.debug("CPDR - ed b9 ");
      alu.CPDR();
      break;
    case 0xBA:
      // logger.debug("INDR - ed ba ");
      alu.INDR();
      break;
    case 0xBB:
      // logger.debug("OTDR - ed bb ");
      alu.OTDR();
      break;
    }
    break;
  case 0xEE:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("XOR n - ee n ");
    alu.XOR(currentInstruction[1]);
    break;
  case 0xEF:
    // logger.debug("RST 28H - ef ");
    alu.RST(0x28);
    break;
  case 0xF0:
    // logger.debug("RET P - f0 ");
    alu.RET(Condition::P);
    break;
  case 0xF1:
    // logger.debug("POP AF - f1 ");
    alu.POP(RegisterPair::AF);
    break;
  case 0xF2:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP P,(nn) - f2 n n ");
    alu.JP(Condition::P, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xF3:
    // logger.debug("DI - f3 ");
    alu.DI();
    break;
  case 0xF4:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL P,(nn) - f4 n n ");
    alu.CALL(Condition::P, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xF5:
    // logger.debug("PUSH AF - f5 ");
    alu.PUSH(RegisterPair::AF);
    break;
  case 0xF6:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("OR n - f6 n ");
    alu.OR(currentInstruction[1]);
    break;
  case 0xF7:
    // logger.debug("RST 30H - f7 ");
    alu.RST(0x30);
    break;
  case 0xF8:
    // logger.debug("RET M - f8 ");
    alu.RET(Condition::M);
    break;
  case 0xF9:
    // logger.debug("LD SP,HL - f9 ");
    alu.LD(RegisterPair::SP, RegisterPair::HL);
    break;
  case 0xFA:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("JP M,(nn) - fa n n ");
    alu.JP(Condition::M, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xFB:
    // logger.debug("EI - fb ");
    alu.EI();
    break;
  case 0xFC:
    currentInstruction[1] = next(memory, pc);
    currentInstruction[2] = next(memory, pc);
    // logger.debug("CALL M,(nn) - fc n n ");
    alu.CALL(Condition::M, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
    break;
  case 0xFD:
    // get opcode
    currentInstruction[1] = next(memory, pc);
    switch (currentInstruction[1]) {
    case 0x09:
      // logger.debug("ADD IY,BC - fd 9 ");
      alu.ADD(RegisterPair::IY, RegisterPair::BC);
      break;
    case 0x19:
      // logger.debug("ADD IY,DE - fd 19 ");
      alu.ADD(RegisterPair::IY, RegisterPair::DE);
      break;
    case 0x21:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD IY,nn - fd 21 n n ");
      alu.LD(RegisterPair::IY, (currentInstruction[3] << 8) | currentInstruction[2]);
      break;
    case 0x22:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (nn),IY - fd 22 n n ");
      alu.LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::IY);
      break;
    case 0x23:
      // logger.debug("INC IY - fd 23 ");
      alu.INC(RegisterPair::IY);
      break;
    case 0x29:
      // logger.debug("ADD IY,IY - fd 29 ");
      alu.ADD(RegisterPair::IY, RegisterPair::IY);
      break;
    case 0x2A:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD IY,(nn) - fd 2a n n ");
      alu.LD(RegisterPair::IY, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
      break;
    case 0x2B:
      // logger.debug("DEC IY - fd 2b ");
      alu.DEC(RegisterPair::IY);
      break;
    case 0x34:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("INC (IY+d) - fd 34 n ");
      alu.INC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x35:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("DEC (IY+d) - fd 35 n ");
      alu.DEC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x36:
      currentInstruction[2] = next(memory, pc);
      currentInstruction[3] = next(memory, pc);
      // logger.debug("LD (IY+d),n - fd 36 n n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), currentInstruction[3]);
      break;
    case 0x39:
      // logger.debug("ADD IY,SP - fd 39 ");
      alu.ADD(RegisterPair::IY, RegisterPair::SP);
      break;
    case 0x46:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD B,(IY+d) - fd 46 n ");
      alu.LD(Rgstr::B, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x4E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD C,(IY+d) - fd 4e n ");
      alu.LD(Rgstr::C, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x56:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD D,(IY+d) - fd 56 n ");
      alu.LD(Rgstr::D, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x5E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD E,(IY+d) - fd 5e n ");
      alu.LD(Rgstr::E, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x66:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD H,(IY+d) - fd 66 n ");
      alu.LD(Rgstr::H, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x6E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD L,(IY+d) - fd 6e n ");
      alu.LD(Rgstr::L, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x70:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IY+d),B - fd 70 n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::B);
      break;
    case 0x71:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IY+d),C - fd 71 n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::C);
      break;
    case 0x72:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IY+d),D - fd 72 n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::D);
      break;
    case 0x73:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IY+d),E - fd 73 n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::E);
      break;
    case 0x74:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IY+d),H - fd 74 n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::H);
      break;
    case 0x75:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IY+d),L - fd 75 n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::L);
      break;
    case 0x77:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD (IY+d),A - fd 77 n ");
      alu.LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::A);
      break;
    case 0x7E:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("LD A,(IY+d) - fd 7e n ");
      alu.LD(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x86:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("ADD A,(IY+d) - fd 86 n ");
      alu.ADD(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x8E:
      currentInstruction[2] = next(memory, pc);
      // logger.info("ADC A,(IY+d) - fd 8e n ");
      alu.ADC(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x96:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("SUB (IY+d) - fd 96 n ");
      alu.SUB(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0x9E:
      currentInstruction[2] = next(memory, pc);
      // logger.info("SBC A,(IY+d) - fd 9e n ");
      alu.SBC(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0xA6:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("AND (IY+d) - fd a6 n ");
      alu.AND(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0xAE:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("XOR (IY+d) - fd ae n ");
      alu.XOR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0xB6:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("OR (IY+d) - fd b6 n ");
      alu.OR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0xBE:
      currentInstruction[2] = next(memory, pc);
      // logger.debug("CP (IY+d) - fd be n ");
      alu.CP(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
      break;
    case 0xCB:
      currentInstruction[2] = next(memory, pc);
      // get opcode
      currentInstruction[3] = next(memory, pc);
      switch (currentInstruction[3]) {
      case 0x06:
        // logger.debug("RLC (IY+d) - fd cb n 6 ");
        alu.RLC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x0E:
        // logger.debug("RRC (IY+d) - fd cb n e ");
        alu.RRC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x16:
        // logger.debug("RL (IY+d) - fd cb n 16 ");
        alu.RL(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x1E:
        // logger.debug("RR (IY+d) - fd cb n 1e ");
        alu.RR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x26:
        // logger.debug("SLA (IY+d) - fd cb n 26 ");
        alu.SLA(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x2E:
        // logger.debug("SRA (IY+d) - fd cb n 2e ");
        alu.SRA(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x3E:
        // logger.debug("SRL (IY+d) - fd cb n 3e ");
        alu.SRL(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x46:
        // logger.debug("BIT 0,(IY+d) - fd cb n 46 ");
        alu.BIT(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x4E:
        // logger.debug("BIT 1,(IY+d) - fd cb n 4e ");
        alu.BIT(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x56:
        // logger.debug("BIT 2,(IY+d) - fd cb n 56 ");
        alu.BIT(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x5E:
        // logger.debug("BIT 3,(IY+d) - fd cb n 5e ");
        alu.BIT(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x66:
        // logger.debug("BIT 4,(IY+d) - fd cb n 66 ");
        alu.BIT(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x6E:
        // logger.debug("BIT 5,(IY+d) - fd cb n 6e ");
        alu.BIT(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x76:
        // logger.debug("BIT 6,(IY+d) - fd cb n 76 ");
        alu.BIT(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x7E:
        // logger.debug("BIT 7,(IY+d) - fd cb n 7e ");
        alu.BIT(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x86:
        // logger.debug("RES 0,(IY+d) - fd cb n 86 ");
        alu.RES(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x8E:
        // logger.debug("RES 1,(IY+d) - fd cb n 8e ");
        alu.RES(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x96:
        // logger.debug("RES 2,(IY+d) - fd cb n 96 ");
        alu.RES(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0x9E:
        // logger.debug("RES 3,(IY+d) - fd cb n 9e ");
        alu.RES(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xA6:
        // logger.debug("RES 4,(IY+d) - fd cb n a6 ");
        alu.RES(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xAE:
        // logger.debug("RES 5,(IY+d) - fd cb n ae ");
        alu.RES(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xB6:
        // logger.debug("RES 6,(IY+d) - fd cb n b6 ");
        alu.RES(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xBE:
        // logger.debug("RES 7,(IY+d) - fd cb n be ");
        alu.RES(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xC6:
        // logger.debug("SET 0,(IY+d) - fd cb n c6 ");
        alu.SET(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xCE:
        // logger.debug("SET 1,(IY+d) - fd cb n ce ");
        alu.SET(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xD6:
        // logger.debug("SET 2,(IY+d) - fd cb n d6 ");
        alu.SET(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xDE:
        // logger.debug("SET 3,(IY+d) - fd cb n de ");
        alu.SET(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xE6:
        // logger.debug("SET 4,(IY+d) - fd cb n e6 ");
        alu.SET(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xEE:
        // logger.debug("SET 5,(IY+d) - fd cb n ee ");
        alu.SET(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xF6:
        // logger.debug("SET 6,(IY+d) - fd cb n f6 ");
        alu.SET(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      case 0xFE:
        // logger.debug("SET 7,(IY+d) - fd cb n fe ");
        alu.SET(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
        break;
      }
      break;
    case 0xE1:
      // logger.debug("POP IY - fd e1 ");
      alu.POP(RegisterPair::IY);
      break;
    case 0xE3:
      // logger.debug("EX (SP),IY - fd e3 ");
      alu.EX(MemoryAddress(RegisterPair::SP), RegisterPair::IY);
      break;
    case 0xE5:
      // logger.debug("PUSH IY - fd e5 ");
      alu.PUSH(RegisterPair::IY);
      break;
    case 0xE9:
      // logger.debug("JP (IY) - fd e9 ");
      alu.JP(MemoryAddress(RegisterPair::IY));
      break;
    case 0xF9:
      // logger.debug("LD SP,IY - fd f9 ");
      alu.LD(RegisterPair::SP, RegisterPair::IY);
      break;
    }
    break;
  case 0xFE:
    currentInstruction[1] = next(memory, pc);
    // logger.debug("CP n - fe n ");
    alu.CP(currentInstruction[1]);
    break;
  case 0xFF:
    // logger.debug("RST 38H - ff ");
    alu.RST(0x38);
    break;
  }
}
