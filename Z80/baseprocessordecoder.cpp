#include "Z80/baseprocessordecoder.h"
//#include <cstdint>
//#include "Z80/MemoryAddress.h"
//#include "Z80/Register.hpp"
//#include "Z80/RegisterPair.hpp"
//#include "Z80/Condition.hpp"
//#include "Z80/Memory.h"

void BaseProcessorDecoder::decode() {
std::uint8_t currentInstruction[4];
// get opcode
currentInstruction[0] = getNextByte();
switch (currentInstruction[0]) {
case 0x00:
// NOP - 0 
logger.debug("NOP - 0 ");
NOP();
break;
case 0x01:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD BC,nn - 1 n n 
logger.debug("LD BC,nn - 1 n n ");
LD(RegisterPair::BC, (currentInstruction[2] << 8) | currentInstruction[1]);
break;
case 0x02:
// LD (BC),A - 2 
logger.debug("LD (BC),A - 2 ");
LD(MemoryAddress(RegisterPair::BC), Rgstr::A);
break;
case 0x03:
// INC BC - 3 
logger.debug("INC BC - 3 ");
INC(RegisterPair::BC);
break;
case 0x04:
// INC B - 4 
logger.debug("INC B - 4 ");
INC(Rgstr::B);
break;
case 0x05:
// DEC B - 5 
logger.debug("DEC B - 5 ");
DEC(Rgstr::B);
break;
case 0x06:
//GetData
currentInstruction[1] = getNextByte();
// LD B,n - 6 n 
logger.debug("LD B,n - 6 n ");
LD(Rgstr::B, currentInstruction[1]);
break;
case 0x07:
// RLCA - 7 
logger.debug("RLCA - 7 ");
RLCA();
break;
case 0x08:
// EX AF,AF' - 8 
logger.debug("EX AF,AF' - 8 ");
EX(RegisterPair::AF, RegisterPair::AF_prime);
break;
case 0x09:
// ADD HL,BC - 9 
logger.debug("ADD HL,BC - 9 ");
ADD(RegisterPair::HL, RegisterPair::BC);
break;
case 0x0A:
// LD A,(BC) - a 
logger.debug("LD A,(BC) - a ");
LD(Rgstr::A, MemoryAddress(RegisterPair::BC));
break;
case 0x0B:
// DEC BC - b 
logger.debug("DEC BC - b ");
DEC(RegisterPair::BC);
break;
case 0x0C:
// INC C - c 
logger.debug("INC C - c ");
INC(Rgstr::C);
break;
case 0x0D:
// DEC C - d 
logger.debug("DEC C - d ");
DEC(Rgstr::C);
break;
case 0x0E:
//GetData
currentInstruction[1] = getNextByte();
// LD C,n - e n 
logger.debug("LD C,n - e n ");
LD(Rgstr::C, currentInstruction[1]);
break;
case 0x0F:
// RRCA - f 
logger.debug("RRCA - f ");
RRCA();
break;
case 0x10:
//GetData
currentInstruction[1] = getNextByte();
// DJNZ (PC+e) - 10 n 
logger.debug("DJNZ (PC+e) - 10 n ");
DJNZ(MemoryAddress(RegisterPair::PC, currentInstruction[1]));
break;
case 0x11:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD DE,nn - 11 n n 
logger.debug("LD DE,nn - 11 n n ");
LD(RegisterPair::DE, (currentInstruction[2] << 8) | currentInstruction[1]);
break;
case 0x12:
// LD (DE),A - 12 
logger.debug("LD (DE),A - 12 ");
LD(MemoryAddress(RegisterPair::DE), Rgstr::A);
break;
case 0x13:
// INC DE - 13 
logger.debug("INC DE - 13 ");
INC(RegisterPair::DE);
break;
case 0x14:
// INC D - 14 
logger.debug("INC D - 14 ");
INC(Rgstr::D);
break;
case 0x15:
// DEC D - 15 
logger.debug("DEC D - 15 ");
DEC(Rgstr::D);
break;
case 0x16:
//GetData
currentInstruction[1] = getNextByte();
// LD D,n - 16 n 
logger.debug("LD D,n - 16 n ");
LD(Rgstr::D, currentInstruction[1]);
break;
case 0x17:
// RLA - 17 
logger.debug("RLA - 17 ");
RLA();
break;
case 0x18:
//GetData
currentInstruction[1] = getNextByte();
// JR (PC+e) - 18 n 
logger.debug("JR (PC+e) - 18 n ");
JR(MemoryAddress(RegisterPair::PC, currentInstruction[1]));
break;
case 0x19:
// ADD HL,DE - 19 
logger.debug("ADD HL,DE - 19 ");
ADD(RegisterPair::HL, RegisterPair::DE);
break;
case 0x1A:
// LD A,(DE) - 1a 
logger.debug("LD A,(DE) - 1a ");
LD(Rgstr::A, MemoryAddress(RegisterPair::DE));
break;
case 0x1B:
// DEC DE - 1b 
logger.debug("DEC DE - 1b ");
DEC(RegisterPair::DE);
break;
case 0x1C:
// INC E - 1c 
logger.debug("INC E - 1c ");
INC(Rgstr::E);
break;
case 0x1D:
// DEC E - 1d 
logger.debug("DEC E - 1d ");
DEC(Rgstr::E);
break;
case 0x1E:
//GetData
currentInstruction[1] = getNextByte();
// LD E,n - 1e n 
logger.debug("LD E,n - 1e n ");
LD(Rgstr::E, currentInstruction[1]);
break;
case 0x1F:
// RRA - 1f 
logger.debug("RRA - 1f ");
RRA();
break;
case 0x20:
//GetData
currentInstruction[1] = getNextByte();
// JR NZ,(PC+e) - 20 n 
logger.debug("JR NZ,(PC+e) - 20 n ");
JR(Condition::NZ, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
break;
case 0x21:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD HL,nn - 21 n n 
logger.debug("LD HL,nn - 21 n n ");
LD(RegisterPair::HL, (currentInstruction[2] << 8) | currentInstruction[1]);
break;
case 0x22:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD (nn),HL - 22 n n 
logger.debug("LD (nn),HL - 22 n n ");
LD(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]), RegisterPair::HL);
break;
case 0x23:
// INC HL - 23 
logger.debug("INC HL - 23 ");
INC(RegisterPair::HL);
break;
case 0x24:
// INC H - 24 
logger.debug("INC H - 24 ");
INC(Rgstr::H);
break;
case 0x25:
// DEC H - 25 
logger.debug("DEC H - 25 ");
DEC(Rgstr::H);
break;
case 0x26:
//GetData
currentInstruction[1] = getNextByte();
// LD H,n - 26 n 
logger.debug("LD H,n - 26 n ");
LD(Rgstr::H, currentInstruction[1]);
break;
case 0x27:
// DAA - 27 
logger.debug("DAA - 27 ");
DAA();
break;
case 0x28:
//GetData
currentInstruction[1] = getNextByte();
// JR Z,(PC+e) - 28 n 
logger.debug("JR Z,(PC+e) - 28 n ");
JR(Condition::Z, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
break;
case 0x29:
// ADD HL,HL - 29 
logger.debug("ADD HL,HL - 29 ");
ADD(RegisterPair::HL, RegisterPair::HL);
break;
case 0x2A:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD HL,(nn) - 2a n n 
logger.debug("LD HL,(nn) - 2a n n ");
LD(RegisterPair::HL, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0x2B:
// DEC HL - 2b 
logger.debug("DEC HL - 2b ");
DEC(RegisterPair::HL);
break;
case 0x2C:
// INC L - 2c 
logger.debug("INC L - 2c ");
INC(Rgstr::L);
break;
case 0x2D:
// DEC L - 2d 
logger.debug("DEC L - 2d ");
DEC(Rgstr::L);
break;
case 0x2E:
//GetData
currentInstruction[1] = getNextByte();
// LD L,n - 2e n 
logger.debug("LD L,n - 2e n ");
LD(Rgstr::L, currentInstruction[1]);
break;
case 0x2F:
// CPL - 2f 
logger.debug("CPL - 2f ");
CPL();
break;
case 0x30:
//GetData
currentInstruction[1] = getNextByte();
// JR NC,(PC+e) - 30 n 
logger.debug("JR NC,(PC+e) - 30 n ");
JR(Condition::NC, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
break;
case 0x31:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD SP,nn - 31 n n 
logger.debug("LD SP,nn - 31 n n ");
LD(RegisterPair::SP, (currentInstruction[2] << 8) | currentInstruction[1]);
break;
case 0x32:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD (nn),A - 32 n n 
logger.debug("LD (nn),A - 32 n n ");
LD(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]), Rgstr::A);
break;
case 0x33:
// INC SP - 33 
logger.debug("INC SP - 33 ");
INC(RegisterPair::SP);
break;
case 0x34:
// INC (HL) - 34 
logger.debug("INC (HL) - 34 ");
INC(MemoryAddress(RegisterPair::HL));
break;
case 0x35:
// DEC (HL) - 35 
logger.debug("DEC (HL) - 35 ");
DEC(MemoryAddress(RegisterPair::HL));
break;
case 0x36:
//GetData
currentInstruction[1] = getNextByte();
// LD (HL),n - 36 n 
logger.debug("LD (HL),n - 36 n ");
LD(MemoryAddress(RegisterPair::HL), currentInstruction[1]);
break;
case 0x37:
// SCF - 37 
logger.debug("SCF - 37 ");
SCF();
break;
case 0x38:
//GetData
currentInstruction[1] = getNextByte();
// JR C,(PC+e) - 38 n 
logger.debug("JR C,(PC+e) - 38 n ");
JR(Condition::C, MemoryAddress(RegisterPair::PC, currentInstruction[1]));
break;
case 0x39:
// ADD HL,SP - 39 
logger.debug("ADD HL,SP - 39 ");
ADD(RegisterPair::HL, RegisterPair::SP);
break;
case 0x3A:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// LD A,(nn) - 3a n n 
logger.debug("LD A,(nn) - 3a n n ");
LD(Rgstr::A, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0x3B:
// DEC SP - 3b 
logger.debug("DEC SP - 3b ");
DEC(RegisterPair::SP);
break;
case 0x3C:
// INC A - 3c 
logger.debug("INC A - 3c ");
INC(Rgstr::A);
break;
case 0x3D:
// DEC A - 3d 
logger.debug("DEC A - 3d ");
DEC(Rgstr::A);
break;
case 0x3E:
//GetData
currentInstruction[1] = getNextByte();
// LD A,n - 3e n 
logger.debug("LD A,n - 3e n ");
LD(Rgstr::A, currentInstruction[1]);
break;
case 0x3F:
// CCF - 3f 
logger.debug("CCF - 3f ");
CCF();
break;
case 0x40:
// LD B,B - 40 
logger.debug("LD B,B - 40 ");
LD(Rgstr::B, Rgstr::B);
break;
case 0x41:
// LD B,C - 41 
logger.debug("LD B,C - 41 ");
LD(Rgstr::B, Rgstr::C);
break;
case 0x42:
// LD B,D - 42 
logger.debug("LD B,D - 42 ");
LD(Rgstr::B, Rgstr::D);
break;
case 0x43:
// LD B,E - 43 
logger.debug("LD B,E - 43 ");
LD(Rgstr::B, Rgstr::E);
break;
case 0x44:
// LD B,H - 44 
logger.debug("LD B,H - 44 ");
LD(Rgstr::B, Rgstr::H);
break;
case 0x45:
// LD B,L - 45 
logger.debug("LD B,L - 45 ");
LD(Rgstr::B, Rgstr::L);
break;
case 0x46:
// LD B,(HL) - 46 
logger.debug("LD B,(HL) - 46 ");
LD(Rgstr::B, MemoryAddress(RegisterPair::HL));
break;
case 0x47:
// LD B,A - 47 
logger.debug("LD B,A - 47 ");
LD(Rgstr::B, Rgstr::A);
break;
case 0x48:
// LD C,B - 48 
logger.debug("LD C,B - 48 ");
LD(Rgstr::C, Rgstr::B);
break;
case 0x49:
// LD C,C - 49 
logger.debug("LD C,C - 49 ");
LD(Rgstr::C, Rgstr::C);
break;
case 0x4A:
// LD C,D - 4a 
logger.debug("LD C,D - 4a ");
LD(Rgstr::C, Rgstr::D);
break;
case 0x4B:
// LD C,E - 4b 
logger.debug("LD C,E - 4b ");
LD(Rgstr::C, Rgstr::E);
break;
case 0x4C:
// LD C,H - 4c 
logger.debug("LD C,H - 4c ");
LD(Rgstr::C, Rgstr::H);
break;
case 0x4D:
// LD C,L - 4d 
logger.debug("LD C,L - 4d ");
LD(Rgstr::C, Rgstr::L);
break;
case 0x4E:
// LD C,(HL) - 4e 
logger.debug("LD C,(HL) - 4e ");
LD(Rgstr::C, MemoryAddress(RegisterPair::HL));
break;
case 0x4F:
// LD C,A - 4f 
logger.debug("LD C,A - 4f ");
LD(Rgstr::C, Rgstr::A);
break;
case 0x50:
// LD D,B - 50 
logger.debug("LD D,B - 50 ");
LD(Rgstr::D, Rgstr::B);
break;
case 0x51:
// LD D,C - 51 
logger.debug("LD D,C - 51 ");
LD(Rgstr::D, Rgstr::C);
break;
case 0x52:
// LD D,D - 52 
logger.debug("LD D,D - 52 ");
LD(Rgstr::D, Rgstr::D);
break;
case 0x53:
// LD D,E - 53 
logger.debug("LD D,E - 53 ");
LD(Rgstr::D, Rgstr::E);
break;
case 0x54:
// LD D,H - 54 
logger.debug("LD D,H - 54 ");
LD(Rgstr::D, Rgstr::H);
break;
case 0x55:
// LD D,L - 55 
logger.debug("LD D,L - 55 ");
LD(Rgstr::D, Rgstr::L);
break;
case 0x56:
// LD D,(HL) - 56 
logger.debug("LD D,(HL) - 56 ");
LD(Rgstr::D, MemoryAddress(RegisterPair::HL));
break;
case 0x57:
// LD D,A - 57 
logger.debug("LD D,A - 57 ");
LD(Rgstr::D, Rgstr::A);
break;
case 0x58:
// LD E,B - 58 
logger.debug("LD E,B - 58 ");
LD(Rgstr::E, Rgstr::B);
break;
case 0x59:
// LD E,C - 59 
logger.debug("LD E,C - 59 ");
LD(Rgstr::E, Rgstr::C);
break;
case 0x5A:
// LD E,D - 5a 
logger.debug("LD E,D - 5a ");
LD(Rgstr::E, Rgstr::D);
break;
case 0x5B:
// LD E,E - 5b 
logger.debug("LD E,E - 5b ");
LD(Rgstr::E, Rgstr::E);
break;
case 0x5C:
// LD E,H - 5c 
logger.debug("LD E,H - 5c ");
LD(Rgstr::E, Rgstr::H);
break;
case 0x5D:
// LD E,L - 5d 
logger.debug("LD E,L - 5d ");
LD(Rgstr::E, Rgstr::L);
break;
case 0x5E:
// LD E,(HL) - 5e 
logger.debug("LD E,(HL) - 5e ");
LD(Rgstr::E, MemoryAddress(RegisterPair::HL));
break;
case 0x5F:
// LD E,A - 5f 
logger.debug("LD E,A - 5f ");
LD(Rgstr::E, Rgstr::A);
break;
case 0x60:
// LD H,B - 60 
logger.debug("LD H,B - 60 ");
LD(Rgstr::H, Rgstr::B);
break;
case 0x61:
// LD H,C - 61 
logger.debug("LD H,C - 61 ");
LD(Rgstr::H, Rgstr::C);
break;
case 0x62:
// LD H,D - 62 
logger.debug("LD H,D - 62 ");
LD(Rgstr::H, Rgstr::D);
break;
case 0x63:
// LD H,E - 63 
logger.debug("LD H,E - 63 ");
LD(Rgstr::H, Rgstr::E);
break;
case 0x64:
// LD H,H - 64 
logger.debug("LD H,H - 64 ");
LD(Rgstr::H, Rgstr::H);
break;
case 0x65:
// LD H,L - 65 
logger.debug("LD H,L - 65 ");
LD(Rgstr::H, Rgstr::L);
break;
case 0x66:
// LD H,(HL) - 66 
logger.debug("LD H,(HL) - 66 ");
LD(Rgstr::H, MemoryAddress(RegisterPair::HL));
break;
case 0x67:
// LD H,A - 67 
logger.debug("LD H,A - 67 ");
LD(Rgstr::H, Rgstr::A);
break;
case 0x68:
// LD L,B - 68 
logger.debug("LD L,B - 68 ");
LD(Rgstr::L, Rgstr::B);
break;
case 0x69:
// LD L,C - 69 
logger.debug("LD L,C - 69 ");
LD(Rgstr::L, Rgstr::C);
break;
case 0x6A:
// LD L,D - 6a 
logger.debug("LD L,D - 6a ");
LD(Rgstr::L, Rgstr::D);
break;
case 0x6B:
// LD L,E - 6b 
logger.debug("LD L,E - 6b ");
LD(Rgstr::L, Rgstr::E);
break;
case 0x6C:
// LD L,H - 6c 
logger.debug("LD L,H - 6c ");
LD(Rgstr::L, Rgstr::H);
break;
case 0x6D:
// LD L,L - 6d 
logger.debug("LD L,L - 6d ");
LD(Rgstr::L, Rgstr::L);
break;
case 0x6E:
// LD L,(HL) - 6e 
logger.debug("LD L,(HL) - 6e ");
LD(Rgstr::L, MemoryAddress(RegisterPair::HL));
break;
case 0x6F:
// LD L,A - 6f 
logger.debug("LD L,A - 6f ");
LD(Rgstr::L, Rgstr::A);
break;
case 0x70:
// LD (HL),B - 70 
logger.debug("LD (HL),B - 70 ");
LD(MemoryAddress(RegisterPair::HL), Rgstr::B);
break;
case 0x71:
// LD (HL),C - 71 
logger.debug("LD (HL),C - 71 ");
LD(MemoryAddress(RegisterPair::HL), Rgstr::C);
break;
case 0x72:
// LD (HL),D - 72 
logger.debug("LD (HL),D - 72 ");
LD(MemoryAddress(RegisterPair::HL), Rgstr::D);
break;
case 0x73:
// LD (HL),E - 73 
logger.debug("LD (HL),E - 73 ");
LD(MemoryAddress(RegisterPair::HL), Rgstr::E);
break;
case 0x74:
// LD (HL),H - 74 
logger.debug("LD (HL),H - 74 ");
LD(MemoryAddress(RegisterPair::HL), Rgstr::H);
break;
case 0x75:
// LD (HL),L - 75 
logger.debug("LD (HL),L - 75 ");
LD(MemoryAddress(RegisterPair::HL), Rgstr::L);
break;
case 0x76:
// HALT - 76 
logger.debug("HALT - 76 ");
HALT();
break;
case 0x77:
// LD (HL),A - 77 
logger.debug("LD (HL),A - 77 ");
LD(MemoryAddress(RegisterPair::HL), Rgstr::A);
break;
case 0x78:
// LD A,B - 78 
logger.debug("LD A,B - 78 ");
LD(Rgstr::A, Rgstr::B);
break;
case 0x79:
// LD A,C - 79 
logger.debug("LD A,C - 79 ");
LD(Rgstr::A, Rgstr::C);
break;
case 0x7A:
// LD A,D - 7a 
logger.debug("LD A,D - 7a ");
LD(Rgstr::A, Rgstr::D);
break;
case 0x7B:
// LD A,E - 7b 
logger.debug("LD A,E - 7b ");
LD(Rgstr::A, Rgstr::E);
break;
case 0x7C:
// LD A,H - 7c 
logger.debug("LD A,H - 7c ");
LD(Rgstr::A, Rgstr::H);
break;
case 0x7D:
// LD A,L - 7d 
logger.debug("LD A,L - 7d ");
LD(Rgstr::A, Rgstr::L);
break;
case 0x7E:
// LD A,(HL) - 7e 
logger.debug("LD A,(HL) - 7e ");
LD(Rgstr::A, MemoryAddress(RegisterPair::HL));
break;
case 0x7F:
// LD A,A - 7f 
logger.debug("LD A,A - 7f ");
LD(Rgstr::A, Rgstr::A);
break;
case 0x80:
// ADD A,B - 80 
logger.debug("ADD A,B - 80 ");
ADD(Rgstr::A, Rgstr::B);
break;
case 0x81:
// ADD A,C - 81 
logger.debug("ADD A,C - 81 ");
ADD(Rgstr::A, Rgstr::C);
break;
case 0x82:
// ADD A,D - 82 
logger.debug("ADD A,D - 82 ");
ADD(Rgstr::A, Rgstr::D);
break;
case 0x83:
// ADD A,E - 83 
logger.debug("ADD A,E - 83 ");
ADD(Rgstr::A, Rgstr::E);
break;
case 0x84:
// ADD A,H - 84 
logger.debug("ADD A,H - 84 ");
ADD(Rgstr::A, Rgstr::H);
break;
case 0x85:
// ADD A,L - 85 
logger.debug("ADD A,L - 85 ");
ADD(Rgstr::A, Rgstr::L);
break;
case 0x86:
// ADD A,(HL) - 86 
logger.debug("ADD A,(HL) - 86 ");
ADD(Rgstr::A, MemoryAddress(RegisterPair::HL));
break;
case 0x87:
// ADD A,A - 87 
logger.debug("ADD A,A - 87 ");
ADD(Rgstr::A, Rgstr::A);
break;
case 0x88:
// ADC A,B - 88 
logger.debug("ADC A,B - 88 ");
ADC(Rgstr::A, Rgstr::B);
break;
case 0x89:
// ADC A,C - 89 
logger.debug("ADC A,C - 89 ");
ADC(Rgstr::A, Rgstr::C);
break;
case 0x8A:
// ADC A,D - 8a 
logger.debug("ADC A,D - 8a ");
ADC(Rgstr::A, Rgstr::D);
break;
case 0x8B:
// ADC A,E - 8b 
logger.debug("ADC A,E - 8b ");
ADC(Rgstr::A, Rgstr::E);
break;
case 0x8C:
// ADC A,H - 8c 
logger.debug("ADC A,H - 8c ");
ADC(Rgstr::A, Rgstr::H);
break;
case 0x8D:
// ADC A,L - 8d 
logger.debug("ADC A,L - 8d ");
ADC(Rgstr::A, Rgstr::L);
break;
case 0x8E:
// ADC A,(HL) - 8e 
logger.debug("ADC A,(HL) - 8e ");
ADC(Rgstr::A, MemoryAddress(RegisterPair::HL));
break;
case 0x8F:
// ADC A,A - 8f 
logger.debug("ADC A,A - 8f ");
ADC(Rgstr::A, Rgstr::A);
break;
case 0x90:
// SUB B - 90 
logger.debug("SUB B - 90 ");
SUB(Rgstr::B);
break;
case 0x91:
// SUB C - 91 
logger.debug("SUB C - 91 ");
SUB(Rgstr::C);
break;
case 0x92:
// SUB D - 92 
logger.debug("SUB D - 92 ");
SUB(Rgstr::D);
break;
case 0x93:
// SUB E - 93 
logger.debug("SUB E - 93 ");
SUB(Rgstr::E);
break;
case 0x94:
// SUB H - 94 
logger.debug("SUB H - 94 ");
SUB(Rgstr::H);
break;
case 0x95:
// SUB L - 95 
logger.debug("SUB L - 95 ");
SUB(Rgstr::L);
break;
case 0x96:
// SUB (HL) - 96 
logger.debug("SUB (HL) - 96 ");
SUB(MemoryAddress(RegisterPair::HL));
break;
case 0x97:
// SUB A - 97 
logger.debug("SUB A - 97 ");
SUB(Rgstr::A);
break;
case 0x98:
// SBC A,B - 98 
logger.debug("SBC A,B - 98 ");
SBC(Rgstr::A, Rgstr::B);
break;
case 0x99:
// SBC A,C - 99 
logger.debug("SBC A,C - 99 ");
SBC(Rgstr::A, Rgstr::C);
break;
case 0x9A:
// SBC A,D - 9a 
logger.debug("SBC A,D - 9a ");
SBC(Rgstr::A, Rgstr::D);
break;
case 0x9B:
// SBC A,E - 9b 
logger.debug("SBC A,E - 9b ");
SBC(Rgstr::A, Rgstr::E);
break;
case 0x9C:
// SBC A,H - 9c 
logger.debug("SBC A,H - 9c ");
SBC(Rgstr::A, Rgstr::H);
break;
case 0x9D:
// SBC A,L - 9d 
logger.debug("SBC A,L - 9d ");
SBC(Rgstr::A, Rgstr::L);
break;
case 0x9E:
// SBC A,(HL) - 9e 
logger.debug("SBC A,(HL) - 9e ");
SBC(Rgstr::A, MemoryAddress(RegisterPair::HL));
break;
case 0x9F:
// SBC A,A - 9f 
logger.debug("SBC A,A - 9f ");
SBC(Rgstr::A, Rgstr::A);
break;
case 0xA0:
// AND B - a0 
logger.debug("AND B - a0 ");
AND(Rgstr::B);
break;
case 0xA1:
// AND C - a1 
logger.debug("AND C - a1 ");
AND(Rgstr::C);
break;
case 0xA2:
// AND D - a2 
logger.debug("AND D - a2 ");
AND(Rgstr::D);
break;
case 0xA3:
// AND E - a3 
logger.debug("AND E - a3 ");
AND(Rgstr::E);
break;
case 0xA4:
// AND H - a4 
logger.debug("AND H - a4 ");
AND(Rgstr::H);
break;
case 0xA5:
// AND L - a5 
logger.debug("AND L - a5 ");
AND(Rgstr::L);
break;
case 0xA6:
// AND (HL) - a6 
logger.debug("AND (HL) - a6 ");
AND(MemoryAddress(RegisterPair::HL));
break;
case 0xA7:
// AND A - a7 
logger.debug("AND A - a7 ");
AND(Rgstr::A);
break;
case 0xA8:
// XOR B - a8 
logger.debug("XOR B - a8 ");
XOR(Rgstr::B);
break;
case 0xA9:
// XOR C - a9 
logger.debug("XOR C - a9 ");
XOR(Rgstr::C);
break;
case 0xAA:
// XOR D - aa 
logger.debug("XOR D - aa ");
XOR(Rgstr::D);
break;
case 0xAB:
// XOR E - ab 
logger.debug("XOR E - ab ");
XOR(Rgstr::E);
break;
case 0xAC:
// XOR H - ac 
logger.debug("XOR H - ac ");
XOR(Rgstr::H);
break;
case 0xAD:
// XOR L - ad 
logger.debug("XOR L - ad ");
XOR(Rgstr::L);
break;
case 0xAE:
// XOR (HL) - ae 
logger.debug("XOR (HL) - ae ");
XOR(MemoryAddress(RegisterPair::HL));
break;
case 0xAF:
// XOR A - af 
logger.debug("XOR A - af ");
XOR(Rgstr::A);
break;
case 0xB0:
// OR B - b0 
logger.debug("OR B - b0 ");
OR(Rgstr::B);
break;
case 0xB1:
// OR C - b1 
logger.debug("OR C - b1 ");
OR(Rgstr::C);
break;
case 0xB2:
// OR D - b2 
logger.debug("OR D - b2 ");
OR(Rgstr::D);
break;
case 0xB3:
// OR E - b3 
logger.debug("OR E - b3 ");
OR(Rgstr::E);
break;
case 0xB4:
// OR H - b4 
logger.debug("OR H - b4 ");
OR(Rgstr::H);
break;
case 0xB5:
// OR L - b5 
logger.debug("OR L - b5 ");
OR(Rgstr::L);
break;
case 0xB6:
// OR (HL) - b6 
logger.debug("OR (HL) - b6 ");
OR(MemoryAddress(RegisterPair::HL));
break;
case 0xB7:
// OR A - b7 
logger.debug("OR A - b7 ");
OR(Rgstr::A);
break;
case 0xB8:
// CP B - b8 
logger.debug("CP B - b8 ");
CP(Rgstr::B);
break;
case 0xB9:
// CP C - b9 
logger.debug("CP C - b9 ");
CP(Rgstr::C);
break;
case 0xBA:
// CP D - ba 
logger.debug("CP D - ba ");
CP(Rgstr::D);
break;
case 0xBB:
// CP E - bb 
logger.debug("CP E - bb ");
CP(Rgstr::E);
break;
case 0xBC:
// CP H - bc 
logger.debug("CP H - bc ");
CP(Rgstr::H);
break;
case 0xBD:
// CP L - bd 
logger.debug("CP L - bd ");
CP(Rgstr::L);
break;
case 0xBE:
// CP (HL) - be 
logger.debug("CP (HL) - be ");
CP(MemoryAddress(RegisterPair::HL));
break;
case 0xBF:
// CP A - bf 
logger.debug("CP A - bf ");
CP(Rgstr::A);
break;
case 0xC0:
// RET NZ - c0 
logger.debug("RET NZ - c0 ");
RET(Condition::NZ);
break;
case 0xC1:
// POP BC - c1 
logger.debug("POP BC - c1 ");
POP(RegisterPair::BC);
break;
case 0xC2:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP NZ,(nn) - c2 n n 
logger.debug("JP NZ,(nn) - c2 n n ");
JP(Condition::NZ, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xC3:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP (nn) - c3 n n 
logger.debug("JP (nn) - c3 n n ");
JP(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xC4:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL NZ,(nn) - c4 n n 
logger.debug("CALL NZ,(nn) - c4 n n ");
CALL(Condition::NZ, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xC5:
// PUSH BC - c5 
logger.debug("PUSH BC - c5 ");
PUSH(RegisterPair::BC);
break;
case 0xC6:
//GetData
currentInstruction[1] = getNextByte();
// ADD A,n - c6 n 
logger.debug("ADD A,n - c6 n ");
ADD(Rgstr::A, currentInstruction[1]);
break;
case 0xC7:
// RST 0H - c7 
logger.debug("RST 0H - c7 ");
RST(0x0);
break;
case 0xC8:
// RET Z - c8 
logger.debug("RET Z - c8 ");
RET(Condition::Z);
break;
case 0xC9:
// RET - c9 
logger.debug("RET - c9 ");
RET();
break;
case 0xCA:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP Z,(nn) - ca n n 
logger.debug("JP Z,(nn) - ca n n ");
JP(Condition::Z, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xCB:
// get opcode
currentInstruction[1] = getNextByte();
switch (currentInstruction[1]) {
case 0x00:
// RLC B - cb 0 
logger.debug("RLC B - cb 0 ");
RLC(Rgstr::B);
break;
case 0x01:
// RLC C - cb 1 
logger.debug("RLC C - cb 1 ");
RLC(Rgstr::C);
break;
case 0x02:
// RLC D - cb 2 
logger.debug("RLC D - cb 2 ");
RLC(Rgstr::D);
break;
case 0x03:
// RLC E - cb 3 
logger.debug("RLC E - cb 3 ");
RLC(Rgstr::E);
break;
case 0x04:
// RLC H - cb 4 
logger.debug("RLC H - cb 4 ");
RLC(Rgstr::H);
break;
case 0x05:
// RLC L - cb 5 
logger.debug("RLC L - cb 5 ");
RLC(Rgstr::L);
break;
case 0x06:
// RLC (HL) - cb 6 
logger.debug("RLC (HL) - cb 6 ");
RLC(MemoryAddress(RegisterPair::HL));
break;
case 0x07:
// RLC A - cb 7 
logger.debug("RLC A - cb 7 ");
RLC(Rgstr::A);
break;
case 0x08:
// RRC B - cb 8 
logger.debug("RRC B - cb 8 ");
RRC(Rgstr::B);
break;
case 0x09:
// RRC C - cb 9 
logger.debug("RRC C - cb 9 ");
RRC(Rgstr::C);
break;
case 0x0A:
// RRC D - cb a 
logger.debug("RRC D - cb a ");
RRC(Rgstr::D);
break;
case 0x0B:
// RRC E - cb b 
logger.debug("RRC E - cb b ");
RRC(Rgstr::E);
break;
case 0x0C:
// RRC H - cb c 
logger.debug("RRC H - cb c ");
RRC(Rgstr::H);
break;
case 0x0D:
// RRC L - cb d 
logger.debug("RRC L - cb d ");
RRC(Rgstr::L);
break;
case 0x0E:
// RRC (HL) - cb e 
logger.debug("RRC (HL) - cb e ");
RRC(MemoryAddress(RegisterPair::HL));
break;
case 0x0F:
// RRC A - cb f 
logger.debug("RRC A - cb f ");
RRC(Rgstr::A);
break;
case 0x10:
// RL B - cb 10 
logger.debug("RL B - cb 10 ");
RL(Rgstr::B);
break;
case 0x11:
// RL C - cb 11 
logger.debug("RL C - cb 11 ");
RL(Rgstr::C);
break;
case 0x12:
// RL D - cb 12 
logger.debug("RL D - cb 12 ");
RL(Rgstr::D);
break;
case 0x13:
// RL E - cb 13 
logger.debug("RL E - cb 13 ");
RL(Rgstr::E);
break;
case 0x14:
// RL H - cb 14 
logger.debug("RL H - cb 14 ");
RL(Rgstr::H);
break;
case 0x15:
// RL L - cb 15 
logger.debug("RL L - cb 15 ");
RL(Rgstr::L);
break;
case 0x16:
// RL (HL) - cb 16 
logger.debug("RL (HL) - cb 16 ");
RL(MemoryAddress(RegisterPair::HL));
break;
case 0x17:
// RL A - cb 17 
logger.debug("RL A - cb 17 ");
RL(Rgstr::A);
break;
case 0x18:
// RR B - cb 18 
logger.debug("RR B - cb 18 ");
RR(Rgstr::B);
break;
case 0x19:
// RR C - cb 19 
logger.debug("RR C - cb 19 ");
RR(Rgstr::C);
break;
case 0x1A:
// RR D - cb 1a 
logger.debug("RR D - cb 1a ");
RR(Rgstr::D);
break;
case 0x1B:
// RR E - cb 1b 
logger.debug("RR E - cb 1b ");
RR(Rgstr::E);
break;
case 0x1C:
// RR H - cb 1c 
logger.debug("RR H - cb 1c ");
RR(Rgstr::H);
break;
case 0x1D:
// RR L - cb 1d 
logger.debug("RR L - cb 1d ");
RR(Rgstr::L);
break;
case 0x1E:
// RR (HL) - cb 1e 
logger.debug("RR (HL) - cb 1e ");
RR(MemoryAddress(RegisterPair::HL));
break;
case 0x1F:
// RR A - cb 1f 
logger.debug("RR A - cb 1f ");
RR(Rgstr::A);
break;
case 0x20:
// SLA B - cb 20 
logger.debug("SLA B - cb 20 ");
SLA(Rgstr::B);
break;
case 0x21:
// SLA C - cb 21 
logger.debug("SLA C - cb 21 ");
SLA(Rgstr::C);
break;
case 0x22:
// SLA D - cb 22 
logger.debug("SLA D - cb 22 ");
SLA(Rgstr::D);
break;
case 0x23:
// SLA E - cb 23 
logger.debug("SLA E - cb 23 ");
SLA(Rgstr::E);
break;
case 0x24:
// SLA H - cb 24 
logger.debug("SLA H - cb 24 ");
SLA(Rgstr::H);
break;
case 0x25:
// SLA L - cb 25 
logger.debug("SLA L - cb 25 ");
SLA(Rgstr::L);
break;
case 0x26:
// SLA (HL) - cb 26 
logger.debug("SLA (HL) - cb 26 ");
SLA(MemoryAddress(RegisterPair::HL));
break;
case 0x27:
// SLA A - cb 27 
logger.debug("SLA A - cb 27 ");
SLA(Rgstr::A);
break;
case 0x28:
// SRA B - cb 28 
logger.debug("SRA B - cb 28 ");
SRA(Rgstr::B);
break;
case 0x29:
// SRA C - cb 29 
logger.debug("SRA C - cb 29 ");
SRA(Rgstr::C);
break;
case 0x2A:
// SRA D - cb 2a 
logger.debug("SRA D - cb 2a ");
SRA(Rgstr::D);
break;
case 0x2B:
// SRA E - cb 2b 
logger.debug("SRA E - cb 2b ");
SRA(Rgstr::E);
break;
case 0x2C:
// SRA H - cb 2c 
logger.debug("SRA H - cb 2c ");
SRA(Rgstr::H);
break;
case 0x2D:
// SRA L - cb 2d 
logger.debug("SRA L - cb 2d ");
SRA(Rgstr::L);
break;
case 0x2E:
// SRA (HL) - cb 2e 
logger.debug("SRA (HL) - cb 2e ");
SRA(MemoryAddress(RegisterPair::HL));
break;
case 0x2F:
// SRA A - cb 2f 
logger.debug("SRA A - cb 2f ");
SRA(Rgstr::A);
break;
case 0x38:
// SRL B - cb 38 
logger.debug("SRL B - cb 38 ");
SRL(Rgstr::B);
break;
case 0x39:
// SRL C - cb 39 
logger.debug("SRL C - cb 39 ");
SRL(Rgstr::C);
break;
case 0x3A:
// SRL D - cb 3a 
logger.debug("SRL D - cb 3a ");
SRL(Rgstr::D);
break;
case 0x3B:
// SRL E - cb 3b 
logger.debug("SRL E - cb 3b ");
SRL(Rgstr::E);
break;
case 0x3C:
// SRL H - cb 3c 
logger.debug("SRL H - cb 3c ");
SRL(Rgstr::H);
break;
case 0x3D:
// SRL L - cb 3d 
logger.debug("SRL L - cb 3d ");
SRL(Rgstr::L);
break;
case 0x3E:
// SRL (HL) - cb 3e 
logger.debug("SRL (HL) - cb 3e ");
SRL(MemoryAddress(RegisterPair::HL));
break;
case 0x3F:
// SRL A - cb 3f 
logger.debug("SRL A - cb 3f ");
SRL(Rgstr::A);
break;
case 0x40:
// BIT 0,B - cb 40 
logger.debug("BIT 0,B - cb 40 ");
BIT(0, Rgstr::B);
break;
case 0x41:
// BIT 0,C - cb 41 
logger.debug("BIT 0,C - cb 41 ");
BIT(0, Rgstr::C);
break;
case 0x42:
// BIT 0,D - cb 42 
logger.debug("BIT 0,D - cb 42 ");
BIT(0, Rgstr::D);
break;
case 0x43:
// BIT 0,E - cb 43 
logger.debug("BIT 0,E - cb 43 ");
BIT(0, Rgstr::E);
break;
case 0x44:
// BIT 0,H - cb 44 
logger.debug("BIT 0,H - cb 44 ");
BIT(0, Rgstr::H);
break;
case 0x45:
// BIT 0,L - cb 45 
logger.debug("BIT 0,L - cb 45 ");
BIT(0, Rgstr::L);
break;
case 0x46:
// BIT 0,(HL) - cb 46 
logger.debug("BIT 0,(HL) - cb 46 ");
BIT(0, MemoryAddress(RegisterPair::HL));
break;
case 0x47:
// BIT 0,A - cb 47 
logger.debug("BIT 0,A - cb 47 ");
BIT(0, Rgstr::A);
break;
case 0x48:
// BIT 1,B - cb 48 
logger.debug("BIT 1,B - cb 48 ");
BIT(1, Rgstr::B);
break;
case 0x49:
// BIT 1,C - cb 49 
logger.debug("BIT 1,C - cb 49 ");
BIT(1, Rgstr::C);
break;
case 0x4A:
// BIT 1,D - cb 4a 
logger.debug("BIT 1,D - cb 4a ");
BIT(1, Rgstr::D);
break;
case 0x4B:
// BIT 1,E - cb 4b 
logger.debug("BIT 1,E - cb 4b ");
BIT(1, Rgstr::E);
break;
case 0x4C:
// BIT 1,H - cb 4c 
logger.debug("BIT 1,H - cb 4c ");
BIT(1, Rgstr::H);
break;
case 0x4D:
// BIT 1,L - cb 4d 
logger.debug("BIT 1,L - cb 4d ");
BIT(1, Rgstr::L);
break;
case 0x4E:
// BIT 1,(HL) - cb 4e 
logger.debug("BIT 1,(HL) - cb 4e ");
BIT(1, MemoryAddress(RegisterPair::HL));
break;
case 0x4F:
// BIT 1,A - cb 4f 
logger.debug("BIT 1,A - cb 4f ");
BIT(1, Rgstr::A);
break;
case 0x50:
// BIT 2,B - cb 50 
logger.debug("BIT 2,B - cb 50 ");
BIT(2, Rgstr::B);
break;
case 0x51:
// BIT 2,C - cb 51 
logger.debug("BIT 2,C - cb 51 ");
BIT(2, Rgstr::C);
break;
case 0x52:
// BIT 2,D - cb 52 
logger.debug("BIT 2,D - cb 52 ");
BIT(2, Rgstr::D);
break;
case 0x53:
// BIT 2,E - cb 53 
logger.debug("BIT 2,E - cb 53 ");
BIT(2, Rgstr::E);
break;
case 0x54:
// BIT 2,H - cb 54 
logger.debug("BIT 2,H - cb 54 ");
BIT(2, Rgstr::H);
break;
case 0x55:
// BIT 2,L - cb 55 
logger.debug("BIT 2,L - cb 55 ");
BIT(2, Rgstr::L);
break;
case 0x56:
// BIT 2,(HL) - cb 56 
logger.debug("BIT 2,(HL) - cb 56 ");
BIT(2, MemoryAddress(RegisterPair::HL));
break;
case 0x57:
// BIT 2,A - cb 57 
logger.debug("BIT 2,A - cb 57 ");
BIT(2, Rgstr::A);
break;
case 0x58:
// BIT 3,B - cb 58 
logger.debug("BIT 3,B - cb 58 ");
BIT(3, Rgstr::B);
break;
case 0x59:
// BIT 3,C - cb 59 
logger.debug("BIT 3,C - cb 59 ");
BIT(3, Rgstr::C);
break;
case 0x5A:
// BIT 3,D - cb 5a 
logger.debug("BIT 3,D - cb 5a ");
BIT(3, Rgstr::D);
break;
case 0x5B:
// BIT 3,E - cb 5b 
logger.debug("BIT 3,E - cb 5b ");
BIT(3, Rgstr::E);
break;
case 0x5C:
// BIT 3,H - cb 5c 
logger.debug("BIT 3,H - cb 5c ");
BIT(3, Rgstr::H);
break;
case 0x5D:
// BIT 3,L - cb 5d 
logger.debug("BIT 3,L - cb 5d ");
BIT(3, Rgstr::L);
break;
case 0x5E:
// BIT 3,(HL) - cb 5e 
logger.debug("BIT 3,(HL) - cb 5e ");
BIT(3, MemoryAddress(RegisterPair::HL));
break;
case 0x5F:
// BIT 3,A - cb 5f 
logger.debug("BIT 3,A - cb 5f ");
BIT(3, Rgstr::A);
break;
case 0x60:
// BIT 4,B - cb 60 
logger.debug("BIT 4,B - cb 60 ");
BIT(4, Rgstr::B);
break;
case 0x61:
// BIT 4,C - cb 61 
logger.debug("BIT 4,C - cb 61 ");
BIT(4, Rgstr::C);
break;
case 0x62:
// BIT 4,D - cb 62 
logger.debug("BIT 4,D - cb 62 ");
BIT(4, Rgstr::D);
break;
case 0x63:
// BIT 4,E - cb 63 
logger.debug("BIT 4,E - cb 63 ");
BIT(4, Rgstr::E);
break;
case 0x64:
// BIT 4,H - cb 64 
logger.debug("BIT 4,H - cb 64 ");
BIT(4, Rgstr::H);
break;
case 0x65:
// BIT 4,L - cb 65 
logger.debug("BIT 4,L - cb 65 ");
BIT(4, Rgstr::L);
break;
case 0x66:
// BIT 4,(HL) - cb 66 
logger.debug("BIT 4,(HL) - cb 66 ");
BIT(4, MemoryAddress(RegisterPair::HL));
break;
case 0x67:
// BIT 4,A - cb 67 
logger.debug("BIT 4,A - cb 67 ");
BIT(4, Rgstr::A);
break;
case 0x68:
// BIT 5,B - cb 68 
logger.debug("BIT 5,B - cb 68 ");
BIT(5, Rgstr::B);
break;
case 0x69:
// BIT 5,C - cb 69 
logger.debug("BIT 5,C - cb 69 ");
BIT(5, Rgstr::C);
break;
case 0x6A:
// BIT 5,D - cb 6a 
logger.debug("BIT 5,D - cb 6a ");
BIT(5, Rgstr::D);
break;
case 0x6B:
// BIT 5,E - cb 6b 
logger.debug("BIT 5,E - cb 6b ");
BIT(5, Rgstr::E);
break;
case 0x6C:
// BIT 5,H - cb 6c 
logger.debug("BIT 5,H - cb 6c ");
BIT(5, Rgstr::H);
break;
case 0x6D:
// BIT 5,L - cb 6d 
logger.debug("BIT 5,L - cb 6d ");
BIT(5, Rgstr::L);
break;
case 0x6E:
// BIT 5,(HL) - cb 6e 
logger.debug("BIT 5,(HL) - cb 6e ");
BIT(5, MemoryAddress(RegisterPair::HL));
break;
case 0x6F:
// BIT 5,A - cb 6f 
logger.debug("BIT 5,A - cb 6f ");
BIT(5, Rgstr::A);
break;
case 0x70:
// BIT 6,B - cb 70 
logger.debug("BIT 6,B - cb 70 ");
BIT(6, Rgstr::B);
break;
case 0x71:
// BIT 6,C - cb 71 
logger.debug("BIT 6,C - cb 71 ");
BIT(6, Rgstr::C);
break;
case 0x72:
// BIT 6,D - cb 72 
logger.debug("BIT 6,D - cb 72 ");
BIT(6, Rgstr::D);
break;
case 0x73:
// BIT 6,E - cb 73 
logger.debug("BIT 6,E - cb 73 ");
BIT(6, Rgstr::E);
break;
case 0x74:
// BIT 6,H - cb 74 
logger.debug("BIT 6,H - cb 74 ");
BIT(6, Rgstr::H);
break;
case 0x75:
// BIT 6,L - cb 75 
logger.debug("BIT 6,L - cb 75 ");
BIT(6, Rgstr::L);
break;
case 0x76:
// BIT 6,(HL) - cb 76 
logger.debug("BIT 6,(HL) - cb 76 ");
BIT(6, MemoryAddress(RegisterPair::HL));
break;
case 0x77:
// BIT 6,A - cb 77 
logger.debug("BIT 6,A - cb 77 ");
BIT(6, Rgstr::A);
break;
case 0x78:
// BIT 7,B - cb 78 
logger.debug("BIT 7,B - cb 78 ");
BIT(7, Rgstr::B);
break;
case 0x79:
// BIT 7,C - cb 79 
logger.debug("BIT 7,C - cb 79 ");
BIT(7, Rgstr::C);
break;
case 0x7A:
// BIT 7,D - cb 7a 
logger.debug("BIT 7,D - cb 7a ");
BIT(7, Rgstr::D);
break;
case 0x7B:
// BIT 7,E - cb 7b 
logger.debug("BIT 7,E - cb 7b ");
BIT(7, Rgstr::E);
break;
case 0x7C:
// BIT 7,H - cb 7c 
logger.debug("BIT 7,H - cb 7c ");
BIT(7, Rgstr::H);
break;
case 0x7D:
// BIT 7,L - cb 7d 
logger.debug("BIT 7,L - cb 7d ");
BIT(7, Rgstr::L);
break;
case 0x7E:
// BIT 7,(HL) - cb 7e 
logger.debug("BIT 7,(HL) - cb 7e ");
BIT(7, MemoryAddress(RegisterPair::HL));
break;
case 0x7F:
// BIT 7,A - cb 7f 
logger.debug("BIT 7,A - cb 7f ");
BIT(7, Rgstr::A);
break;
case 0x80:
// RES 0,B - cb 80 
logger.debug("RES 0,B - cb 80 ");
RES(0, Rgstr::B);
break;
case 0x81:
// RES 0,C - cb 81 
logger.debug("RES 0,C - cb 81 ");
RES(0, Rgstr::C);
break;
case 0x82:
// RES 0,D - cb 82 
logger.debug("RES 0,D - cb 82 ");
RES(0, Rgstr::D);
break;
case 0x83:
// RES 0,E - cb 83 
logger.debug("RES 0,E - cb 83 ");
RES(0, Rgstr::E);
break;
case 0x84:
// RES 0,H - cb 84 
logger.debug("RES 0,H - cb 84 ");
RES(0, Rgstr::H);
break;
case 0x85:
// RES 0,L - cb 85 
logger.debug("RES 0,L - cb 85 ");
RES(0, Rgstr::L);
break;
case 0x86:
// RES 0,(HL) - cb 86 
logger.debug("RES 0,(HL) - cb 86 ");
RES(0, MemoryAddress(RegisterPair::HL));
break;
case 0x87:
// RES 0,A - cb 87 
logger.debug("RES 0,A - cb 87 ");
RES(0, Rgstr::A);
break;
case 0x88:
// RES 1,B - cb 88 
logger.debug("RES 1,B - cb 88 ");
RES(1, Rgstr::B);
break;
case 0x89:
// RES 1,C - cb 89 
logger.debug("RES 1,C - cb 89 ");
RES(1, Rgstr::C);
break;
case 0x8A:
// RES 1,D - cb 8a 
logger.debug("RES 1,D - cb 8a ");
RES(1, Rgstr::D);
break;
case 0x8B:
// RES 1,E - cb 8b 
logger.debug("RES 1,E - cb 8b ");
RES(1, Rgstr::E);
break;
case 0x8C:
// RES 1,H - cb 8c 
logger.debug("RES 1,H - cb 8c ");
RES(1, Rgstr::H);
break;
case 0x8D:
// RES 1,L - cb 8d 
logger.debug("RES 1,L - cb 8d ");
RES(1, Rgstr::L);
break;
case 0x8E:
// RES 1,(HL) - cb 8e 
logger.debug("RES 1,(HL) - cb 8e ");
RES(1, MemoryAddress(RegisterPair::HL));
break;
case 0x8F:
// RES 1,A - cb 8f 
logger.debug("RES 1,A - cb 8f ");
RES(1, Rgstr::A);
break;
case 0x90:
// RES 2,B - cb 90 
logger.debug("RES 2,B - cb 90 ");
RES(2, Rgstr::B);
break;
case 0x91:
// RES 2,C - cb 91 
logger.debug("RES 2,C - cb 91 ");
RES(2, Rgstr::C);
break;
case 0x92:
// RES 2,D - cb 92 
logger.debug("RES 2,D - cb 92 ");
RES(2, Rgstr::D);
break;
case 0x93:
// RES 2,E - cb 93 
logger.debug("RES 2,E - cb 93 ");
RES(2, Rgstr::E);
break;
case 0x94:
// RES 2,H - cb 94 
logger.debug("RES 2,H - cb 94 ");
RES(2, Rgstr::H);
break;
case 0x95:
// RES 2,L - cb 95 
logger.debug("RES 2,L - cb 95 ");
RES(2, Rgstr::L);
break;
case 0x96:
// RES 2,(HL) - cb 96 
logger.debug("RES 2,(HL) - cb 96 ");
RES(2, MemoryAddress(RegisterPair::HL));
break;
case 0x97:
// RES 2,A - cb 97 
logger.debug("RES 2,A - cb 97 ");
RES(2, Rgstr::A);
break;
case 0x98:
// RES 3,B - cb 98 
logger.debug("RES 3,B - cb 98 ");
RES(3, Rgstr::B);
break;
case 0x99:
// RES 3,C - cb 99 
logger.debug("RES 3,C - cb 99 ");
RES(3, Rgstr::C);
break;
case 0x9A:
// RES 3,D - cb 9a 
logger.debug("RES 3,D - cb 9a ");
RES(3, Rgstr::D);
break;
case 0x9B:
// RES 3,E - cb 9b 
logger.debug("RES 3,E - cb 9b ");
RES(3, Rgstr::E);
break;
case 0x9C:
// RES 3,H - cb 9c 
logger.debug("RES 3,H - cb 9c ");
RES(3, Rgstr::H);
break;
case 0x9D:
// RES 3,L - cb 9d 
logger.debug("RES 3,L - cb 9d ");
RES(3, Rgstr::L);
break;
case 0x9E:
// RES 3,(HL) - cb 9e 
logger.debug("RES 3,(HL) - cb 9e ");
RES(3, MemoryAddress(RegisterPair::HL));
break;
case 0x9F:
// RES 3,A - cb 9f 
logger.debug("RES 3,A - cb 9f ");
RES(3, Rgstr::A);
break;
case 0xA0:
// RES 4,B - cb a0 
logger.debug("RES 4,B - cb a0 ");
RES(4, Rgstr::B);
break;
case 0xA1:
// RES 4,C - cb a1 
logger.debug("RES 4,C - cb a1 ");
RES(4, Rgstr::C);
break;
case 0xA2:
// RES 4,D - cb a2 
logger.debug("RES 4,D - cb a2 ");
RES(4, Rgstr::D);
break;
case 0xA3:
// RES 4,E - cb a3 
logger.debug("RES 4,E - cb a3 ");
RES(4, Rgstr::E);
break;
case 0xA4:
// RES 4,H - cb a4 
logger.debug("RES 4,H - cb a4 ");
RES(4, Rgstr::H);
break;
case 0xA5:
// RES 4,L - cb a5 
logger.debug("RES 4,L - cb a5 ");
RES(4, Rgstr::L);
break;
case 0xA6:
// RES 4,(HL) - cb a6 
logger.debug("RES 4,(HL) - cb a6 ");
RES(4, MemoryAddress(RegisterPair::HL));
break;
case 0xA7:
// RES 4,A - cb a7 
logger.debug("RES 4,A - cb a7 ");
RES(4, Rgstr::A);
break;
case 0xA8:
// RES 5,B - cb a8 
logger.debug("RES 5,B - cb a8 ");
RES(5, Rgstr::B);
break;
case 0xA9:
// RES 5,C - cb a9 
logger.debug("RES 5,C - cb a9 ");
RES(5, Rgstr::C);
break;
case 0xAA:
// RES 5,D - cb aa 
logger.debug("RES 5,D - cb aa ");
RES(5, Rgstr::D);
break;
case 0xAB:
// RES 5,E - cb ab 
logger.debug("RES 5,E - cb ab ");
RES(5, Rgstr::E);
break;
case 0xAC:
// RES 5,H - cb ac 
logger.debug("RES 5,H - cb ac ");
RES(5, Rgstr::H);
break;
case 0xAD:
// RES 5,L - cb ad 
logger.debug("RES 5,L - cb ad ");
RES(5, Rgstr::L);
break;
case 0xAE:
// RES 5,(HL) - cb ae 
logger.debug("RES 5,(HL) - cb ae ");
RES(5, MemoryAddress(RegisterPair::HL));
break;
case 0xAF:
// RES 5,A - cb af 
logger.debug("RES 5,A - cb af ");
RES(5, Rgstr::A);
break;
case 0xB0:
// RES 6,B - cb b0 
logger.debug("RES 6,B - cb b0 ");
RES(6, Rgstr::B);
break;
case 0xB1:
// RES 6,C - cb b1 
logger.debug("RES 6,C - cb b1 ");
RES(6, Rgstr::C);
break;
case 0xB2:
// RES 6,D - cb b2 
logger.debug("RES 6,D - cb b2 ");
RES(6, Rgstr::D);
break;
case 0xB3:
// RES 6,E - cb b3 
logger.debug("RES 6,E - cb b3 ");
RES(6, Rgstr::E);
break;
case 0xB4:
// RES 6,H - cb b4 
logger.debug("RES 6,H - cb b4 ");
RES(6, Rgstr::H);
break;
case 0xB5:
// RES 6,L - cb b5 
logger.debug("RES 6,L - cb b5 ");
RES(6, Rgstr::L);
break;
case 0xB6:
// RES 6,(HL) - cb b6 
logger.debug("RES 6,(HL) - cb b6 ");
RES(6, MemoryAddress(RegisterPair::HL));
break;
case 0xB7:
// RES 6,A - cb b7 
logger.debug("RES 6,A - cb b7 ");
RES(6, Rgstr::A);
break;
case 0xB8:
// RES 7,B - cb b8 
logger.debug("RES 7,B - cb b8 ");
RES(7, Rgstr::B);
break;
case 0xB9:
// RES 7,C - cb b9 
logger.debug("RES 7,C - cb b9 ");
RES(7, Rgstr::C);
break;
case 0xBA:
// RES 7,D - cb ba 
logger.debug("RES 7,D - cb ba ");
RES(7, Rgstr::D);
break;
case 0xBB:
// RES 7,E - cb bb 
logger.debug("RES 7,E - cb bb ");
RES(7, Rgstr::E);
break;
case 0xBC:
// RES 7,H - cb bc 
logger.debug("RES 7,H - cb bc ");
RES(7, Rgstr::H);
break;
case 0xBD:
// RES 7,L - cb bd 
logger.debug("RES 7,L - cb bd ");
RES(7, Rgstr::L);
break;
case 0xBE:
// RES 7,(HL) - cb be 
logger.debug("RES 7,(HL) - cb be ");
RES(7, MemoryAddress(RegisterPair::HL));
break;
case 0xBF:
// RES 7,A - cb bf 
logger.debug("RES 7,A - cb bf ");
RES(7, Rgstr::A);
break;
case 0xC0:
// SET 0,B - cb c0 
logger.debug("SET 0,B - cb c0 ");
SET(0, Rgstr::B);
break;
case 0xC1:
// SET 0,C - cb c1 
logger.debug("SET 0,C - cb c1 ");
SET(0, Rgstr::C);
break;
case 0xC2:
// SET 0,D - cb c2 
logger.debug("SET 0,D - cb c2 ");
SET(0, Rgstr::D);
break;
case 0xC3:
// SET 0,E - cb c3 
logger.debug("SET 0,E - cb c3 ");
SET(0, Rgstr::E);
break;
case 0xC4:
// SET 0,H - cb c4 
logger.debug("SET 0,H - cb c4 ");
SET(0, Rgstr::H);
break;
case 0xC5:
// SET 0,L - cb c5 
logger.debug("SET 0,L - cb c5 ");
SET(0, Rgstr::L);
break;
case 0xC6:
// SET 0,(HL) - cb c6 
logger.debug("SET 0,(HL) - cb c6 ");
SET(0, MemoryAddress(RegisterPair::HL));
break;
case 0xC7:
// SET 0,A - cb c7 
logger.debug("SET 0,A - cb c7 ");
SET(0, Rgstr::A);
break;
case 0xC8:
// SET 1,B - cb c8 
logger.debug("SET 1,B - cb c8 ");
SET(1, Rgstr::B);
break;
case 0xC9:
// SET 1,C - cb c9 
logger.debug("SET 1,C - cb c9 ");
SET(1, Rgstr::C);
break;
case 0xCA:
// SET 1,D - cb ca 
logger.debug("SET 1,D - cb ca ");
SET(1, Rgstr::D);
break;
case 0xCB:
// SET 1,E - cb cb 
logger.debug("SET 1,E - cb cb ");
SET(1, Rgstr::E);
break;
case 0xCC:
// SET 1,H - cb cc 
logger.debug("SET 1,H - cb cc ");
SET(1, Rgstr::H);
break;
case 0xCD:
// SET 1,L - cb cd 
logger.debug("SET 1,L - cb cd ");
SET(1, Rgstr::L);
break;
case 0xCE:
// SET 1,(HL) - cb ce 
logger.debug("SET 1,(HL) - cb ce ");
SET(1, MemoryAddress(RegisterPair::HL));
break;
case 0xCF:
// SET 1,A - cb cf 
logger.debug("SET 1,A - cb cf ");
SET(1, Rgstr::A);
break;
case 0xD0:
// SET 2,B - cb d0 
logger.debug("SET 2,B - cb d0 ");
SET(2, Rgstr::B);
break;
case 0xD1:
// SET 2,C - cb d1 
logger.debug("SET 2,C - cb d1 ");
SET(2, Rgstr::C);
break;
case 0xD2:
// SET 2,D - cb d2 
logger.debug("SET 2,D - cb d2 ");
SET(2, Rgstr::D);
break;
case 0xD3:
// SET 2,E - cb d3 
logger.debug("SET 2,E - cb d3 ");
SET(2, Rgstr::E);
break;
case 0xD4:
// SET 2,H - cb d4 
logger.debug("SET 2,H - cb d4 ");
SET(2, Rgstr::H);
break;
case 0xD5:
// SET 2,L - cb d5 
logger.debug("SET 2,L - cb d5 ");
SET(2, Rgstr::L);
break;
case 0xD6:
// SET 2,(HL) - cb d6 
logger.debug("SET 2,(HL) - cb d6 ");
SET(2, MemoryAddress(RegisterPair::HL));
break;
case 0xD7:
// SET 2,A - cb d7 
logger.debug("SET 2,A - cb d7 ");
SET(2, Rgstr::A);
break;
case 0xD8:
// SET 3,B - cb d8 
logger.debug("SET 3,B - cb d8 ");
SET(3, Rgstr::B);
break;
case 0xD9:
// SET 3,C - cb d9 
logger.debug("SET 3,C - cb d9 ");
SET(3, Rgstr::C);
break;
case 0xDA:
// SET 3,D - cb da 
logger.debug("SET 3,D - cb da ");
SET(3, Rgstr::D);
break;
case 0xDB:
// SET 3,E - cb db 
logger.debug("SET 3,E - cb db ");
SET(3, Rgstr::E);
break;
case 0xDC:
// SET 3,H - cb dc 
logger.debug("SET 3,H - cb dc ");
SET(3, Rgstr::H);
break;
case 0xDD:
// SET 3,L - cb dd 
logger.debug("SET 3,L - cb dd ");
SET(3, Rgstr::L);
break;
case 0xDE:
// SET 3,(HL) - cb de 
logger.debug("SET 3,(HL) - cb de ");
SET(3, MemoryAddress(RegisterPair::HL));
break;
case 0xDF:
// SET 3,A - cb df 
logger.debug("SET 3,A - cb df ");
SET(3, Rgstr::A);
break;
case 0xE0:
// SET 4,B - cb e0 
logger.debug("SET 4,B - cb e0 ");
SET(4, Rgstr::B);
break;
case 0xE1:
// SET 4,C - cb e1 
logger.debug("SET 4,C - cb e1 ");
SET(4, Rgstr::C);
break;
case 0xE2:
// SET 4,D - cb e2 
logger.debug("SET 4,D - cb e2 ");
SET(4, Rgstr::D);
break;
case 0xE3:
// SET 4,E - cb e3 
logger.debug("SET 4,E - cb e3 ");
SET(4, Rgstr::E);
break;
case 0xE4:
// SET 4,H - cb e4 
logger.debug("SET 4,H - cb e4 ");
SET(4, Rgstr::H);
break;
case 0xE5:
// SET 4,L - cb e5 
logger.debug("SET 4,L - cb e5 ");
SET(4, Rgstr::L);
break;
case 0xE6:
// SET 4,(HL) - cb e6 
logger.debug("SET 4,(HL) - cb e6 ");
SET(4, MemoryAddress(RegisterPair::HL));
break;
case 0xE7:
// SET 4,A - cb e7 
logger.debug("SET 4,A - cb e7 ");
SET(4, Rgstr::A);
break;
case 0xE8:
// SET 5,B - cb e8 
logger.debug("SET 5,B - cb e8 ");
SET(5, Rgstr::B);
break;
case 0xE9:
// SET 5,C - cb e9 
logger.debug("SET 5,C - cb e9 ");
SET(5, Rgstr::C);
break;
case 0xEA:
// SET 5,D - cb ea 
logger.debug("SET 5,D - cb ea ");
SET(5, Rgstr::D);
break;
case 0xEB:
// SET 5,E - cb eb 
logger.debug("SET 5,E - cb eb ");
SET(5, Rgstr::E);
break;
case 0xEC:
// SET 5,H - cb ec 
logger.debug("SET 5,H - cb ec ");
SET(5, Rgstr::H);
break;
case 0xED:
// SET 5,L - cb ed 
logger.debug("SET 5,L - cb ed ");
SET(5, Rgstr::L);
break;
case 0xEE:
// SET 5,(HL) - cb ee 
logger.debug("SET 5,(HL) - cb ee ");
SET(5, MemoryAddress(RegisterPair::HL));
break;
case 0xEF:
// SET 5,A - cb ef 
logger.debug("SET 5,A - cb ef ");
SET(5, Rgstr::A);
break;
case 0xF0:
// SET 6,B - cb f0 
logger.debug("SET 6,B - cb f0 ");
SET(6, Rgstr::B);
break;
case 0xF1:
// SET 6,C - cb f1 
logger.debug("SET 6,C - cb f1 ");
SET(6, Rgstr::C);
break;
case 0xF2:
// SET 6,D - cb f2 
logger.debug("SET 6,D - cb f2 ");
SET(6, Rgstr::D);
break;
case 0xF3:
// SET 6,E - cb f3 
logger.debug("SET 6,E - cb f3 ");
SET(6, Rgstr::E);
break;
case 0xF4:
// SET 6,H - cb f4 
logger.debug("SET 6,H - cb f4 ");
SET(6, Rgstr::H);
break;
case 0xF5:
// SET 6,L - cb f5 
logger.debug("SET 6,L - cb f5 ");
SET(6, Rgstr::L);
break;
case 0xF6:
// SET 6,(HL) - cb f6 
logger.debug("SET 6,(HL) - cb f6 ");
SET(6, MemoryAddress(RegisterPair::HL));
break;
case 0xF7:
// SET 6,A - cb f7 
logger.debug("SET 6,A - cb f7 ");
SET(6, Rgstr::A);
break;
case 0xF8:
// SET 7,B - cb f8 
logger.debug("SET 7,B - cb f8 ");
SET(7, Rgstr::B);
break;
case 0xF9:
// SET 7,C - cb f9 
logger.debug("SET 7,C - cb f9 ");
SET(7, Rgstr::C);
break;
case 0xFA:
// SET 7,D - cb fa 
logger.debug("SET 7,D - cb fa ");
SET(7, Rgstr::D);
break;
case 0xFB:
// SET 7,E - cb fb 
logger.debug("SET 7,E - cb fb ");
SET(7, Rgstr::E);
break;
case 0xFC:
// SET 7,H - cb fc 
logger.debug("SET 7,H - cb fc ");
SET(7, Rgstr::H);
break;
case 0xFD:
// SET 7,L - cb fd 
logger.debug("SET 7,L - cb fd ");
SET(7, Rgstr::L);
break;
case 0xFE:
// SET 7,(HL) - cb fe 
logger.debug("SET 7,(HL) - cb fe ");
SET(7, MemoryAddress(RegisterPair::HL));
break;
case 0xFF:
// SET 7,A - cb ff 
logger.debug("SET 7,A - cb ff ");
SET(7, Rgstr::A);
break;
}
break;
case 0xCC:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL Z,(nn) - cc n n 
logger.debug("CALL Z,(nn) - cc n n ");
CALL(Condition::Z, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xCD:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL (nn) - cd n n 
logger.debug("CALL (nn) - cd n n ");
CALL(MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xCE:
//GetData
currentInstruction[1] = getNextByte();
// ADC A,n - ce n 
logger.debug("ADC A,n - ce n ");
ADC(Rgstr::A, currentInstruction[1]);
break;
case 0xCF:
// RST 8H - cf 
logger.debug("RST 8H - cf ");
RST(0x8);
break;
case 0xD0:
// RET NC - d0 
logger.debug("RET NC - d0 ");
RET(Condition::NC);
break;
case 0xD1:
// POP DE - d1 
logger.debug("POP DE - d1 ");
POP(RegisterPair::DE);
break;
case 0xD2:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP NC,(nn) - d2 n n 
logger.debug("JP NC,(nn) - d2 n n ");
JP(Condition::NC, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xD3:
//GetData
currentInstruction[1] = getNextByte();
// OUT (n),A - d3 n 
logger.debug("OUT (n),A - d3 n ");
out(MemoryAddress(currentInstruction[1]), Rgstr::A);
break;
case 0xD4:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL NC,(nn) - d4 n n 
logger.debug("CALL NC,(nn) - d4 n n ");
CALL(Condition::NC, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xD5:
// PUSH DE - d5 
logger.debug("PUSH DE - d5 ");
PUSH(RegisterPair::DE);
break;
case 0xD6:
//GetData
currentInstruction[1] = getNextByte();
// SUB n - d6 n 
logger.debug("SUB n - d6 n ");
SUB(currentInstruction[1]);
break;
case 0xD7:
// RST 10H - d7 
logger.debug("RST 10H - d7 ");
RST(0x10);
break;
case 0xD8:
// RET C - d8 
logger.debug("RET C - d8 ");
RET(Condition::C);
break;
case 0xD9:
// EXX - d9 
logger.debug("EXX - d9 ");
EXX();
break;
case 0xDA:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP C,(nn) - da n n 
logger.debug("JP C,(nn) - da n n ");
JP(Condition::C, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xDB:
//GetData
currentInstruction[1] = getNextByte();
// IN A,(n) - db n 
logger.debug("IN A,(n) - db n ");
in(Rgstr::A, MemoryAddress(currentInstruction[1]));
break;
case 0xDC:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL C,(nn) - dc n n 
logger.debug("CALL C,(nn) - dc n n ");
CALL(Condition::C, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xDD:
// get opcode
currentInstruction[1] = getNextByte();
switch (currentInstruction[1]) {
case 0x09:
// ADD IX,BC - dd 9 
logger.debug("ADD IX,BC - dd 9 ");
ADD(RegisterPair::IX, RegisterPair::BC);
break;
case 0x19:
// ADD IX,DE - dd 19 
logger.debug("ADD IX,DE - dd 19 ");
ADD(RegisterPair::IX, RegisterPair::DE);
break;
case 0x21:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD IX,nn - dd 21 n n 
logger.debug("LD IX,nn - dd 21 n n ");
LD(RegisterPair::IX, (currentInstruction[3] << 8) | currentInstruction[2]);
break;
case 0x22:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (nn),IX - dd 22 n n 
logger.debug("LD (nn),IX - dd 22 n n ");
LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::IX);
break;
case 0x23:
// INC IX - dd 23 
logger.debug("INC IX - dd 23 ");
INC(RegisterPair::IX);
break;
case 0x29:
// ADD IX,IX - dd 29 
logger.debug("ADD IX,IX - dd 29 ");
ADD(RegisterPair::IX, RegisterPair::IX);
break;
case 0x2A:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD IX,(nn) - dd 2a n n 
logger.debug("LD IX,(nn) - dd 2a n n ");
LD(RegisterPair::IX, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
break;
case 0x2B:
// DEC IX - dd 2b 
logger.debug("DEC IX - dd 2b ");
DEC(RegisterPair::IX);
break;
case 0x34:
//GetData
currentInstruction[2] = getNextByte();
// INC (IX+d) - dd 34 n 
logger.debug("INC (IX+d) - dd 34 n ");
INC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x35:
//GetData
currentInstruction[2] = getNextByte();
// DEC (IX+d) - dd 35 n 
logger.debug("DEC (IX+d) - dd 35 n ");
DEC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x36:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (IX+d),n - dd 36 n n 
logger.debug("LD (IX+d),n - dd 36 n n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), currentInstruction[3]);
break;
case 0x39:
// ADD IX,SP - dd 39 
logger.debug("ADD IX,SP - dd 39 ");
ADD(RegisterPair::IX, RegisterPair::SP);
break;
case 0x46:
//GetData
currentInstruction[2] = getNextByte();
// LD B,(IX+d) - dd 46 n 
logger.debug("LD B,(IX+d) - dd 46 n ");
LD(Rgstr::B, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x4E:
//GetData
currentInstruction[2] = getNextByte();
// LD C,(IX+d) - dd 4e n 
logger.debug("LD C,(IX+d) - dd 4e n ");
LD(Rgstr::C, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x56:
//GetData
currentInstruction[2] = getNextByte();
// LD D,(IX+d) - dd 56 n 
logger.debug("LD D,(IX+d) - dd 56 n ");
LD(Rgstr::D, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x5E:
//GetData
currentInstruction[2] = getNextByte();
// LD E,(IX+d) - dd 5e n 
logger.debug("LD E,(IX+d) - dd 5e n ");
LD(Rgstr::E, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x66:
//GetData
currentInstruction[2] = getNextByte();
// LD H,(IX+d) - dd 66 n 
logger.debug("LD H,(IX+d) - dd 66 n ");
LD(Rgstr::H, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x6E:
//GetData
currentInstruction[2] = getNextByte();
// LD L,(IX+d) - dd 6e n 
logger.debug("LD L,(IX+d) - dd 6e n ");
LD(Rgstr::L, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x70:
//GetData
currentInstruction[2] = getNextByte();
// LD (IX+d),B - dd 70 n 
logger.debug("LD (IX+d),B - dd 70 n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::B);
break;
case 0x71:
//GetData
currentInstruction[2] = getNextByte();
// LD (IX+d),C - dd 71 n 
logger.debug("LD (IX+d),C - dd 71 n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::C);
break;
case 0x72:
//GetData
currentInstruction[2] = getNextByte();
// LD (IX+d),D - dd 72 n 
logger.debug("LD (IX+d),D - dd 72 n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::D);
break;
case 0x73:
//GetData
currentInstruction[2] = getNextByte();
// LD (IX+d),E - dd 73 n 
logger.debug("LD (IX+d),E - dd 73 n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::E);
break;
case 0x74:
//GetData
currentInstruction[2] = getNextByte();
// LD (IX+d),H - dd 74 n 
logger.debug("LD (IX+d),H - dd 74 n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::H);
break;
case 0x75:
//GetData
currentInstruction[2] = getNextByte();
// LD (IX+d),L - dd 75 n 
logger.debug("LD (IX+d),L - dd 75 n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::L);
break;
case 0x77:
//GetData
currentInstruction[2] = getNextByte();
// LD (IX+d),A - dd 77 n 
logger.debug("LD (IX+d),A - dd 77 n ");
LD(MemoryAddress(RegisterPair::IX, currentInstruction[2]), Rgstr::A);
break;
case 0x7E:
//GetData
currentInstruction[2] = getNextByte();
// LD A,(IX+d) - dd 7e n 
logger.debug("LD A,(IX+d) - dd 7e n ");
LD(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x86:
//GetData
currentInstruction[2] = getNextByte();
// ADD A,(IX+d) - dd 86 n 
logger.debug("ADD A,(IX+d) - dd 86 n ");
ADD(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x8E:
//GetData
currentInstruction[2] = getNextByte();
// ADC A,(IX+d) - dd 8e n 
logger.debug("ADC A,(IX+d) - dd 8e n ");
ADC(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x96:
//GetData
currentInstruction[2] = getNextByte();
// SUB (IX+d) - dd 96 n 
logger.debug("SUB (IX+d) - dd 96 n ");
SUB(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x9E:
//GetData
currentInstruction[2] = getNextByte();
// SBC A,(IX+d) - dd 9e n 
logger.debug("SBC A,(IX+d) - dd 9e n ");
SBC(Rgstr::A, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xA6:
//GetData
currentInstruction[2] = getNextByte();
// AND (IX+d) - dd a6 n 
logger.debug("AND (IX+d) - dd a6 n ");
AND(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xAE:
//GetData
currentInstruction[2] = getNextByte();
// XOR (IX+d) - dd ae n 
logger.debug("XOR (IX+d) - dd ae n ");
XOR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xB6:
//GetData
currentInstruction[2] = getNextByte();
// OR (IX+d) - dd b6 n 
logger.debug("OR (IX+d) - dd b6 n ");
OR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xBE:
//GetData
currentInstruction[2] = getNextByte();
// CP (IX+d) - dd be n 
logger.debug("CP (IX+d) - dd be n ");
CP(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xCB:
//GetData
currentInstruction[2] = getNextByte();
// get opcode
currentInstruction[3] = getNextByte();
switch (currentInstruction[3]) {
case 0x06:
// RLC (IX+d) - dd cb n 6 
logger.debug("RLC (IX+d) - dd cb n 6 ");
RLC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x0E:
// RRC (IX+d) - dd cb n e 
logger.debug("RRC (IX+d) - dd cb n e ");
RRC(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x16:
// RL (IX+d) - dd cb n 16 
logger.debug("RL (IX+d) - dd cb n 16 ");
RL(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x1E:
// RR (IX+d) - dd cb n 1e 
logger.debug("RR (IX+d) - dd cb n 1e ");
RR(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x26:
// SLA (IX+d) - dd cb n 26 
logger.debug("SLA (IX+d) - dd cb n 26 ");
SLA(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x2E:
// SRA (IX+d) - dd cb n 2e 
logger.debug("SRA (IX+d) - dd cb n 2e ");
SRA(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x3E:
// SRL (IX+d) - dd cb n 3e 
logger.debug("SRL (IX+d) - dd cb n 3e ");
SRL(MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x46:
// BIT 0,(IX+d) - dd cb n 46 
logger.debug("BIT 0,(IX+d) - dd cb n 46 ");
BIT(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x4E:
// BIT 1,(IX+d) - dd cb n 4e 
logger.debug("BIT 1,(IX+d) - dd cb n 4e ");
BIT(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x56:
// BIT 2,(IX+d) - dd cb n 56 
logger.debug("BIT 2,(IX+d) - dd cb n 56 ");
BIT(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x5E:
// BIT 3,(IX+d) - dd cb n 5e 
logger.debug("BIT 3,(IX+d) - dd cb n 5e ");
BIT(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x66:
// BIT 4,(IX+d) - dd cb n 66 
logger.debug("BIT 4,(IX+d) - dd cb n 66 ");
BIT(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x6E:
// BIT 5,(IX+d) - dd cb n 6e 
logger.debug("BIT 5,(IX+d) - dd cb n 6e ");
BIT(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x76:
// BIT 6,(IX+d) - dd cb n 76 
logger.debug("BIT 6,(IX+d) - dd cb n 76 ");
BIT(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x7E:
// BIT 7,(IX+d) - dd cb n 7e 
logger.debug("BIT 7,(IX+d) - dd cb n 7e ");
BIT(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x86:
// RES 0,(IX+d) - dd cb n 86 
logger.debug("RES 0,(IX+d) - dd cb n 86 ");
RES(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x8E:
// RES 1,(IX+d) - dd cb n 8e 
logger.debug("RES 1,(IX+d) - dd cb n 8e ");
RES(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x96:
// RES 2,(IX+d) - dd cb n 96 
logger.debug("RES 2,(IX+d) - dd cb n 96 ");
RES(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0x9E:
// RES 3,(IX+d) - dd cb n 9e 
logger.debug("RES 3,(IX+d) - dd cb n 9e ");
RES(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xA6:
// RES 4,(IX+d) - dd cb n a6 
logger.debug("RES 4,(IX+d) - dd cb n a6 ");
RES(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xAE:
// RES 5,(IX+d) - dd cb n ae 
logger.debug("RES 5,(IX+d) - dd cb n ae ");
RES(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xB6:
// RES 6,(IX+d) - dd cb n b6 
logger.debug("RES 6,(IX+d) - dd cb n b6 ");
RES(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xBE:
// RES 7,(IX+d) - dd cb n be 
logger.debug("RES 7,(IX+d) - dd cb n be ");
RES(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xC6:
// SET 0,(IX+d) - dd cb n c6 
logger.debug("SET 0,(IX+d) - dd cb n c6 ");
SET(0, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xCE:
// SET 1,(IX+d) - dd cb n ce 
logger.debug("SET 1,(IX+d) - dd cb n ce ");
SET(1, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xD6:
// SET 2,(IX+d) - dd cb n d6 
logger.debug("SET 2,(IX+d) - dd cb n d6 ");
SET(2, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xDE:
// SET 3,(IX+d) - dd cb n de 
logger.debug("SET 3,(IX+d) - dd cb n de ");
SET(3, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xE6:
// SET 4,(IX+d) - dd cb n e6 
logger.debug("SET 4,(IX+d) - dd cb n e6 ");
SET(4, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xEE:
// SET 5,(IX+d) - dd cb n ee 
logger.debug("SET 5,(IX+d) - dd cb n ee ");
SET(5, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xF6:
// SET 6,(IX+d) - dd cb n f6 
logger.debug("SET 6,(IX+d) - dd cb n f6 ");
SET(6, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
case 0xFE:
// SET 7,(IX+d) - dd cb n fe 
logger.debug("SET 7,(IX+d) - dd cb n fe ");
SET(7, MemoryAddress(RegisterPair::IX, currentInstruction[2]));
break;
}
break;
case 0xE1:
// POP IX - dd e1 
logger.debug("POP IX - dd e1 ");
POP(RegisterPair::IX);
break;
case 0xE3:
// EX (SP),IX - dd e3 
logger.debug("EX (SP),IX - dd e3 ");
EX(MemoryAddress(RegisterPair::SP), RegisterPair::IX);
break;
case 0xE5:
// PUSH IX - dd e5 
logger.debug("PUSH IX - dd e5 ");
PUSH(RegisterPair::IX);
break;
case 0xE9:
// JP (IX) - dd e9 
logger.debug("JP (IX) - dd e9 ");
JP(MemoryAddress(RegisterPair::IX));
break;
case 0xF9:
// LD SP,IX - dd f9 
logger.debug("LD SP,IX - dd f9 ");
LD(RegisterPair::SP, RegisterPair::IX);
break;
}
break;
case 0xDE:
//GetData
currentInstruction[1] = getNextByte();
// SBC A,n - de n 
logger.debug("SBC A,n - de n ");
SBC(Rgstr::A, currentInstruction[1]);
break;
case 0xDF:
// RST 18H - df 
logger.debug("RST 18H - df ");
RST(0x18);
break;
case 0xE0:
// RET PO - e0 
logger.debug("RET PO - e0 ");
RET(Condition::PO);
break;
case 0xE1:
// POP HL - e1 
logger.debug("POP HL - e1 ");
POP(RegisterPair::HL);
break;
case 0xE2:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP PO,(nn) - e2 n n 
logger.debug("JP PO,(nn) - e2 n n ");
JP(Condition::PO, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xE3:
// EX (SP),HL - e3 
logger.debug("EX (SP),HL - e3 ");
EX(MemoryAddress(RegisterPair::SP), RegisterPair::HL);
break;
case 0xE4:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL PO,(nn) - e4 n n 
logger.debug("CALL PO,(nn) - e4 n n ");
CALL(Condition::PO, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xE5:
// PUSH HL - e5 
logger.debug("PUSH HL - e5 ");
PUSH(RegisterPair::HL);
break;
case 0xE6:
//GetData
currentInstruction[1] = getNextByte();
// AND n - e6 n 
logger.debug("AND n - e6 n ");
AND(currentInstruction[1]);
break;
case 0xE7:
// RST 20H - e7 
logger.debug("RST 20H - e7 ");
RST(0x20);
break;
case 0xE8:
// RET PE - e8 
logger.debug("RET PE - e8 ");
RET(Condition::PE);
break;
case 0xE9:
// JP (HL) - e9 
logger.debug("JP (HL) - e9 ");
JP(MemoryAddress(RegisterPair::HL));
break;
case 0xEA:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP PE,(nn) - ea n n 
logger.debug("JP PE,(nn) - ea n n ");
JP(Condition::PE, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xEB:
// EX DE,HL - eb 
logger.debug("EX DE,HL - eb ");
EX(RegisterPair::DE, RegisterPair::HL);
break;
case 0xEC:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL PE,(nn) - ec n n 
logger.debug("CALL PE,(nn) - ec n n ");
CALL(Condition::PE, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xED:
// get opcode
currentInstruction[1] = getNextByte();
switch (currentInstruction[1]) {
case 0x40:
// IN B,(C) - ed 40 
logger.debug("IN B,(C) - ed 40 ");
in(Rgstr::B, MemoryAddress(Rgstr::C));
break;
case 0x41:
// OUT (C),B - ed 41 
logger.debug("OUT (C),B - ed 41 ");
out(MemoryAddress(Rgstr::C), Rgstr::B);
break;
case 0x42:
// SBC HL,BC - ed 42 
logger.debug("SBC HL,BC - ed 42 ");
SBC(RegisterPair::HL, RegisterPair::BC);
break;
case 0x43:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (nn),BC - ed 43 n n 
logger.debug("LD (nn),BC - ed 43 n n ");
LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::BC);
break;
case 0x44:
// NEG - ed 44 
logger.debug("NEG - ed 44 ");
NEG();
break;
case 0x45:
// RETN - ed 45 
logger.debug("RETN - ed 45 ");
RETN();
break;
case 0x46:
// IM 0 - ed 46 
logger.debug("IM 0 - ed 46 ");
IM(0);
break;
case 0x47:
// LD I,A - ed 47 
logger.debug("LD I,A - ed 47 ");
LD(Rgstr::I, Rgstr::A);
break;
case 0x48:
// IN C,(C) - ed 48 
logger.debug("IN C,(C) - ed 48 ");
in(Rgstr::C, MemoryAddress(Rgstr::C));
break;
case 0x49:
// OUT (C),C - ed 49 
logger.debug("OUT (C),C - ed 49 ");
out(MemoryAddress(Rgstr::C), Rgstr::C);
break;
case 0x4A:
// ADC HL,BC - ed 4a 
logger.debug("ADC HL,BC - ed 4a ");
ADC(RegisterPair::HL, RegisterPair::BC);
break;
case 0x4B:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD BC,(nn) - ed 4b n n 
logger.debug("LD BC,(nn) - ed 4b n n ");
LD(RegisterPair::BC, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
break;
case 0x4D:
// RETI - ed 4d 
logger.debug("RETI - ed 4d ");
RETI();
break;
case 0x4F:
// LD R,A - ed 4f 
logger.debug("LD R,A - ed 4f ");
LD(Rgstr::R, Rgstr::A);
break;
case 0x50:
// IN D,(C) - ed 50 
logger.debug("IN D,(C) - ed 50 ");
in(Rgstr::D, MemoryAddress(Rgstr::C));
break;
case 0x51:
// OUT (C),D - ed 51 
logger.debug("OUT (C),D - ed 51 ");
out(MemoryAddress(Rgstr::C), Rgstr::D);
break;
case 0x52:
// SBC HL,DE - ed 52 
logger.debug("SBC HL,DE - ed 52 ");
SBC(RegisterPair::HL, RegisterPair::DE);
break;
case 0x53:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (nn),DE - ed 53 n n 
logger.debug("LD (nn),DE - ed 53 n n ");
LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::DE);
break;
case 0x56:
// IM 1 - ed 56 
logger.debug("IM 1 - ed 56 ");
IM(1);
break;
case 0x57:
// LD A,I - ed 57 
logger.debug("LD A,I - ed 57 ");
LD(Rgstr::A, Rgstr::I);
break;
case 0x58:
// IN E,(C) - ed 58 
logger.debug("IN E,(C) - ed 58 ");
in(Rgstr::E, MemoryAddress(Rgstr::C));
break;
case 0x59:
// OUT (C),E - ed 59 
logger.debug("OUT (C),E - ed 59 ");
out(MemoryAddress(Rgstr::C), Rgstr::E);
break;
case 0x5A:
// ADC HL,DE - ed 5a 
logger.debug("ADC HL,DE - ed 5a ");
ADC(RegisterPair::HL, RegisterPair::DE);
break;
case 0x5B:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD DE,(nn) - ed 5b n n 
logger.debug("LD DE,(nn) - ed 5b n n ");
LD(RegisterPair::DE, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
break;
case 0x5E:
// IM 2 - ed 5e 
logger.debug("IM 2 - ed 5e ");
IM(2);
break;
case 0x5F:
// LD A,R - ed 5f 
logger.debug("LD A,R - ed 5f ");
LD(Rgstr::A, Rgstr::R);
break;
case 0x60:
// IN H,(C) - ed 60 
logger.debug("IN H,(C) - ed 60 ");
in(Rgstr::H, MemoryAddress(Rgstr::C));
break;
case 0x61:
// OUT (C),H - ed 61 
logger.debug("OUT (C),H - ed 61 ");
out(MemoryAddress(Rgstr::C), Rgstr::H);
break;
case 0x62:
// SBC HL,HL - ed 62 
logger.debug("SBC HL,HL - ed 62 ");
SBC(RegisterPair::HL, RegisterPair::HL);
break;
case 0x63:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (nn),HL - ed 63 n n 
logger.debug("LD (nn),HL - ed 63 n n ");
LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::HL);
break;
case 0x67:
// RRD - ed 67 
logger.debug("RRD - ed 67 ");
RRD();
break;
case 0x68:
// IN L,(C) - ed 68 
logger.debug("IN L,(C) - ed 68 ");
in(Rgstr::L, MemoryAddress(Rgstr::C));
break;
case 0x69:
// OUT (C),L - ed 69 
logger.debug("OUT (C),L - ed 69 ");
out(MemoryAddress(Rgstr::C), Rgstr::L);
break;
case 0x6A:
// ADC HL,HL - ed 6a 
logger.debug("ADC HL,HL - ed 6a ");
ADC(RegisterPair::HL, RegisterPair::HL);
break;
case 0x6B:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD HL,(nn) - ed 6b n n 
logger.debug("LD HL,(nn) - ed 6b n n ");
LD(RegisterPair::HL, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
break;
case 0x6F:
// RLD - ed 6f 
logger.debug("RLD - ed 6f ");
RLD();
break;
case 0x72:
// SBC HL,SP - ed 72 
logger.debug("SBC HL,SP - ed 72 ");
SBC(RegisterPair::HL, RegisterPair::SP);
break;
case 0x73:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (nn),SP - ed 73 n n 
logger.debug("LD (nn),SP - ed 73 n n ");
LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::SP);
break;
case 0x78:
// IN A,(C) - ed 78 
logger.debug("IN A,(C) - ed 78 ");
in(Rgstr::A, MemoryAddress(Rgstr::C));
break;
case 0x79:
// OUT (C),A - ed 79 
logger.debug("OUT (C),A - ed 79 ");
out(MemoryAddress(Rgstr::C), Rgstr::A);
break;
case 0x7A:
// ADC HL,SP - ed 7a 
logger.debug("ADC HL,SP - ed 7a ");
ADC(RegisterPair::HL, RegisterPair::SP);
break;
case 0x7B:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD SP,(nn) - ed 7b n n 
logger.debug("LD SP,(nn) - ed 7b n n ");
LD(RegisterPair::SP, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
break;
case 0xA0:
// LDI - ed a0 
logger.debug("LDI - ed a0 ");
LDI();
break;
case 0xA1:
// CPI - ed a1 
logger.debug("CPI - ed a1 ");
CPI();
break;
case 0xA2:
// INI - ed a2 
logger.debug("INI - ed a2 ");
INI();
break;
case 0xA3:
// OUTI - ed a3 
logger.debug("OUTI - ed a3 ");
OUTI();
break;
case 0xA8:
// LDD - ed a8 
logger.debug("LDD - ed a8 ");
LDD();
break;
case 0xA9:
// CPD - ed a9 
logger.debug("CPD - ed a9 ");
CPD();
break;
case 0xAA:
// IND - ed aa 
logger.debug("IND - ed aa ");
IND();
break;
case 0xAB:
// OUTD - ed ab 
logger.debug("OUTD - ed ab ");
OUTD();
break;
case 0xB0:
// LDIR - ed b0 
logger.debug("LDIR - ed b0 ");
LDIR();
break;
case 0xB1:
// CPIR - ed b1 
logger.debug("CPIR - ed b1 ");
CPIR();
break;
case 0xB2:
// INIR - ed b2 
logger.debug("INIR - ed b2 ");
INIR();
break;
case 0xB3:
// OTIR - ed b3 
logger.debug("OTIR - ed b3 ");
OTIR();
break;
case 0xB8:
// LDDR - ed b8 
logger.debug("LDDR - ed b8 ");
LDDR();
break;
case 0xB9:
// CPDR - ed b9 
logger.debug("CPDR - ed b9 ");
CPDR();
break;
case 0xBA:
// INDR - ed ba 
logger.debug("INDR - ed ba ");
INDR();
break;
case 0xBB:
// OTDR - ed bb 
logger.debug("OTDR - ed bb ");
OTDR();
break;
}
break;
case 0xEE:
//GetData
currentInstruction[1] = getNextByte();
// XOR n - ee n 
logger.debug("XOR n - ee n ");
XOR(currentInstruction[1]);
break;
case 0xEF:
// RST 28H - ef 
logger.debug("RST 28H - ef ");
RST(0x28);
break;
case 0xF0:
// RET P - f0 
logger.debug("RET P - f0 ");
RET(Condition::P);
break;
case 0xF1:
// POP AF - f1 
logger.debug("POP AF - f1 ");
POP(RegisterPair::AF);
break;
case 0xF2:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP P,(nn) - f2 n n 
logger.debug("JP P,(nn) - f2 n n ");
JP(Condition::P, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xF3:
// DI - f3 
logger.debug("DI - f3 ");
DI();
break;
case 0xF4:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL P,(nn) - f4 n n 
logger.debug("CALL P,(nn) - f4 n n ");
CALL(Condition::P, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xF5:
// PUSH AF - f5 
logger.debug("PUSH AF - f5 ");
PUSH(RegisterPair::AF);
break;
case 0xF6:
//GetData
currentInstruction[1] = getNextByte();
// OR n - f6 n 
logger.debug("OR n - f6 n ");
OR(currentInstruction[1]);
break;
case 0xF7:
// RST 30H - f7 
logger.debug("RST 30H - f7 ");
RST(0x30);
break;
case 0xF8:
// RET M - f8 
logger.debug("RET M - f8 ");
RET(Condition::M);
break;
case 0xF9:
// LD SP,HL - f9 
logger.debug("LD SP,HL - f9 ");
LD(RegisterPair::SP, RegisterPair::HL);
break;
case 0xFA:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// JP M,(nn) - fa n n 
logger.debug("JP M,(nn) - fa n n ");
JP(Condition::M, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xFB:
// EI - fb 
logger.debug("EI - fb ");
EI();
break;
case 0xFC:
//GetData
currentInstruction[1] = getNextByte();
//GetData
currentInstruction[2] = getNextByte();
// CALL M,(nn) - fc n n 
logger.debug("CALL M,(nn) - fc n n ");
CALL(Condition::M, MemoryAddress((currentInstruction[2] << 8) | currentInstruction[1]));
break;
case 0xFD:
// get opcode
currentInstruction[1] = getNextByte();
switch (currentInstruction[1]) {
case 0x09:
// ADD IY,BC - fd 9 
logger.debug("ADD IY,BC - fd 9 ");
ADD(RegisterPair::IY, RegisterPair::BC);
break;
case 0x19:
// ADD IY,DE - fd 19 
logger.debug("ADD IY,DE - fd 19 ");
ADD(RegisterPair::IY, RegisterPair::DE);
break;
case 0x21:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD IY,nn - fd 21 n n 
logger.debug("LD IY,nn - fd 21 n n ");
LD(RegisterPair::IY, (currentInstruction[3] << 8) | currentInstruction[2]);
break;
case 0x22:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (nn),IY - fd 22 n n 
logger.debug("LD (nn),IY - fd 22 n n ");
LD(MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]), RegisterPair::IY);
break;
case 0x23:
// INC IY - fd 23 
logger.debug("INC IY - fd 23 ");
INC(RegisterPair::IY);
break;
case 0x29:
// ADD IY,IY - fd 29 
logger.debug("ADD IY,IY - fd 29 ");
ADD(RegisterPair::IY, RegisterPair::IY);
break;
case 0x2A:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD IY,(nn) - fd 2a n n 
logger.debug("LD IY,(nn) - fd 2a n n ");
LD(RegisterPair::IY, MemoryAddress((currentInstruction[3] << 8) | currentInstruction[2]));
break;
case 0x2B:
// DEC IY - fd 2b 
logger.debug("DEC IY - fd 2b ");
DEC(RegisterPair::IY);
break;
case 0x34:
//GetData
currentInstruction[2] = getNextByte();
// INC (IY+d) - fd 34 n 
logger.debug("INC (IY+d) - fd 34 n ");
INC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x35:
//GetData
currentInstruction[2] = getNextByte();
// DEC (IY+d) - fd 35 n 
logger.debug("DEC (IY+d) - fd 35 n ");
DEC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x36:
//GetData
currentInstruction[2] = getNextByte();
//GetData
currentInstruction[3] = getNextByte();
// LD (IY+d),n - fd 36 n n 
logger.debug("LD (IY+d),n - fd 36 n n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), currentInstruction[3]);
break;
case 0x39:
// ADD IY,SP - fd 39 
logger.debug("ADD IY,SP - fd 39 ");
ADD(RegisterPair::IY, RegisterPair::SP);
break;
case 0x46:
//GetData
currentInstruction[2] = getNextByte();
// LD B,(IY+d) - fd 46 n 
logger.debug("LD B,(IY+d) - fd 46 n ");
LD(Rgstr::B, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x4E:
//GetData
currentInstruction[2] = getNextByte();
// LD C,(IY+d) - fd 4e n 
logger.debug("LD C,(IY+d) - fd 4e n ");
LD(Rgstr::C, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x56:
//GetData
currentInstruction[2] = getNextByte();
// LD D,(IY+d) - fd 56 n 
logger.debug("LD D,(IY+d) - fd 56 n ");
LD(Rgstr::D, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x5E:
//GetData
currentInstruction[2] = getNextByte();
// LD E,(IY+d) - fd 5e n 
logger.debug("LD E,(IY+d) - fd 5e n ");
LD(Rgstr::E, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x66:
//GetData
currentInstruction[2] = getNextByte();
// LD H,(IY+d) - fd 66 n 
logger.debug("LD H,(IY+d) - fd 66 n ");
LD(Rgstr::H, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x6E:
//GetData
currentInstruction[2] = getNextByte();
// LD L,(IY+d) - fd 6e n 
logger.debug("LD L,(IY+d) - fd 6e n ");
LD(Rgstr::L, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x70:
//GetData
currentInstruction[2] = getNextByte();
// LD (IY+d),B - fd 70 n 
logger.debug("LD (IY+d),B - fd 70 n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::B);
break;
case 0x71:
//GetData
currentInstruction[2] = getNextByte();
// LD (IY+d),C - fd 71 n 
logger.debug("LD (IY+d),C - fd 71 n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::C);
break;
case 0x72:
//GetData
currentInstruction[2] = getNextByte();
// LD (IY+d),D - fd 72 n 
logger.debug("LD (IY+d),D - fd 72 n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::D);
break;
case 0x73:
//GetData
currentInstruction[2] = getNextByte();
// LD (IY+d),E - fd 73 n 
logger.debug("LD (IY+d),E - fd 73 n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::E);
break;
case 0x74:
//GetData
currentInstruction[2] = getNextByte();
// LD (IY+d),H - fd 74 n 
logger.debug("LD (IY+d),H - fd 74 n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::H);
break;
case 0x75:
//GetData
currentInstruction[2] = getNextByte();
// LD (IY+d),L - fd 75 n 
logger.debug("LD (IY+d),L - fd 75 n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::L);
break;
case 0x77:
//GetData
currentInstruction[2] = getNextByte();
// LD (IY+d),A - fd 77 n 
logger.debug("LD (IY+d),A - fd 77 n ");
LD(MemoryAddress(RegisterPair::IY, currentInstruction[2]), Rgstr::A);
break;
case 0x7E:
//GetData
currentInstruction[2] = getNextByte();
// LD A,(IY+d) - fd 7e n 
logger.debug("LD A,(IY+d) - fd 7e n ");
LD(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x86:
//GetData
currentInstruction[2] = getNextByte();
// ADD A,(IY+d) - fd 86 n 
logger.debug("ADD A,(IY+d) - fd 86 n ");
ADD(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x8E:
//GetData
currentInstruction[2] = getNextByte();
// ADC A,(IY+d) - fd 8e n 
logger.debug("ADC A,(IY+d) - fd 8e n ");
ADC(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x96:
//GetData
currentInstruction[2] = getNextByte();
// SUB (IY+d) - fd 96 n 
logger.debug("SUB (IY+d) - fd 96 n ");
SUB(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x9E:
//GetData
currentInstruction[2] = getNextByte();
// SBC A,(IY+d) - fd 9e n 
logger.debug("SBC A,(IY+d) - fd 9e n ");
SBC(Rgstr::A, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xA6:
//GetData
currentInstruction[2] = getNextByte();
// AND (IY+d) - fd a6 n 
logger.debug("AND (IY+d) - fd a6 n ");
AND(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xAE:
//GetData
currentInstruction[2] = getNextByte();
// XOR (IY+d) - fd ae n 
logger.debug("XOR (IY+d) - fd ae n ");
XOR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xB6:
//GetData
currentInstruction[2] = getNextByte();
// OR (IY+d) - fd b6 n 
logger.debug("OR (IY+d) - fd b6 n ");
OR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xBE:
//GetData
currentInstruction[2] = getNextByte();
// CP (IY+d) - fd be n 
logger.debug("CP (IY+d) - fd be n ");
CP(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xCB:
//GetData
currentInstruction[2] = getNextByte();
// get opcode
currentInstruction[3] = getNextByte();
switch (currentInstruction[3]) {
case 0x06:
// RLC (IY+d) - fd cb n 6 
logger.debug("RLC (IY+d) - fd cb n 6 ");
RLC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x0E:
// RRC (IY+d) - fd cb n e 
logger.debug("RRC (IY+d) - fd cb n e ");
RRC(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x16:
// RL (IY+d) - fd cb n 16 
logger.debug("RL (IY+d) - fd cb n 16 ");
RL(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x1E:
// RR (IY+d) - fd cb n 1e 
logger.debug("RR (IY+d) - fd cb n 1e ");
RR(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x26:
// SLA (IY+d) - fd cb n 26 
logger.debug("SLA (IY+d) - fd cb n 26 ");
SLA(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x2E:
// SRA (IY+d) - fd cb n 2e 
logger.debug("SRA (IY+d) - fd cb n 2e ");
SRA(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x3E:
// SRL (IY+d) - fd cb n 3e 
logger.debug("SRL (IY+d) - fd cb n 3e ");
SRL(MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x46:
// BIT 0,(IY+d) - fd cb n 46 
logger.debug("BIT 0,(IY+d) - fd cb n 46 ");
BIT(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x4E:
// BIT 1,(IY+d) - fd cb n 4e 
logger.debug("BIT 1,(IY+d) - fd cb n 4e ");
BIT(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x56:
// BIT 2,(IY+d) - fd cb n 56 
logger.debug("BIT 2,(IY+d) - fd cb n 56 ");
BIT(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x5E:
// BIT 3,(IY+d) - fd cb n 5e 
logger.debug("BIT 3,(IY+d) - fd cb n 5e ");
BIT(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x66:
// BIT 4,(IY+d) - fd cb n 66 
logger.debug("BIT 4,(IY+d) - fd cb n 66 ");
BIT(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x6E:
// BIT 5,(IY+d) - fd cb n 6e 
logger.debug("BIT 5,(IY+d) - fd cb n 6e ");
BIT(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x76:
// BIT 6,(IY+d) - fd cb n 76 
logger.debug("BIT 6,(IY+d) - fd cb n 76 ");
BIT(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x7E:
// BIT 7,(IY+d) - fd cb n 7e 
logger.debug("BIT 7,(IY+d) - fd cb n 7e ");
BIT(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x86:
// RES 0,(IY+d) - fd cb n 86 
logger.debug("RES 0,(IY+d) - fd cb n 86 ");
RES(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x8E:
// RES 1,(IY+d) - fd cb n 8e 
logger.debug("RES 1,(IY+d) - fd cb n 8e ");
RES(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x96:
// RES 2,(IY+d) - fd cb n 96 
logger.debug("RES 2,(IY+d) - fd cb n 96 ");
RES(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0x9E:
// RES 3,(IY+d) - fd cb n 9e 
logger.debug("RES 3,(IY+d) - fd cb n 9e ");
RES(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xA6:
// RES 4,(IY+d) - fd cb n a6 
logger.debug("RES 4,(IY+d) - fd cb n a6 ");
RES(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xAE:
// RES 5,(IY+d) - fd cb n ae 
logger.debug("RES 5,(IY+d) - fd cb n ae ");
RES(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xB6:
// RES 6,(IY+d) - fd cb n b6 
logger.debug("RES 6,(IY+d) - fd cb n b6 ");
RES(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xBE:
// RES 7,(IY+d) - fd cb n be 
logger.debug("RES 7,(IY+d) - fd cb n be ");
RES(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xC6:
// SET 0,(IY+d) - fd cb n c6 
logger.debug("SET 0,(IY+d) - fd cb n c6 ");
SET(0, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xCE:
// SET 1,(IY+d) - fd cb n ce 
logger.debug("SET 1,(IY+d) - fd cb n ce ");
SET(1, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xD6:
// SET 2,(IY+d) - fd cb n d6 
logger.debug("SET 2,(IY+d) - fd cb n d6 ");
SET(2, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xDE:
// SET 3,(IY+d) - fd cb n de 
logger.debug("SET 3,(IY+d) - fd cb n de ");
SET(3, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xE6:
// SET 4,(IY+d) - fd cb n e6 
logger.debug("SET 4,(IY+d) - fd cb n e6 ");
SET(4, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xEE:
// SET 5,(IY+d) - fd cb n ee 
logger.debug("SET 5,(IY+d) - fd cb n ee ");
SET(5, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xF6:
// SET 6,(IY+d) - fd cb n f6 
logger.debug("SET 6,(IY+d) - fd cb n f6 ");
SET(6, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
case 0xFE:
// SET 7,(IY+d) - fd cb n fe 
logger.debug("SET 7,(IY+d) - fd cb n fe ");
SET(7, MemoryAddress(RegisterPair::IY, currentInstruction[2]));
break;
}
break;
case 0xE1:
// POP IY - fd e1 
logger.debug("POP IY - fd e1 ");
POP(RegisterPair::IY);
break;
case 0xE3:
// EX (SP),IY - fd e3 
logger.debug("EX (SP),IY - fd e3 ");
EX(MemoryAddress(RegisterPair::SP), RegisterPair::IY);
break;
case 0xE5:
// PUSH IY - fd e5 
logger.debug("PUSH IY - fd e5 ");
PUSH(RegisterPair::IY);
break;
case 0xE9:
// JP (IY) - fd e9 
logger.debug("JP (IY) - fd e9 ");
JP(MemoryAddress(RegisterPair::IY));
break;
case 0xF9:
// LD SP,IY - fd f9 
logger.debug("LD SP,IY - fd f9 ");
LD(RegisterPair::SP, RegisterPair::IY);
break;
}
break;
case 0xFE:
//GetData
currentInstruction[1] = getNextByte();
// CP n - fe n 
logger.debug("CP n - fe n ");
CP(currentInstruction[1]);
break;
case 0xFF:
// RST 38H - ff 
logger.debug("RST 38H - ff ");
RST(0x38);
break;
}
//currentInstruction = ArrayUtils.subarray(currentInstruction, 0, instructionByteCount);
instructionByteCount = 0;
//return currentInstruction;
}
