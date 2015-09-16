#include "disassembler.h"
#include <iostream>
#include <boost/format.hpp>
#include "utils.h"

using namespace registers;

Disassembler::Disassembler(Memory *memory) {
    decoder = new Decoder();
    this->memory = memory;
    results.resize(memory->size());
}

Disassembler::~Disassembler() {

}

void Disassembler::disassemble() {

    disassemble(0, this->results.size());
}

std::string Disassembler::getDisassembly(std::uint16_t index) {
    return this->results.at(index);
}

void Disassembler::disassemble(const std::uint16_t start, const std::uint16_t end) {
    std::uint16_t fakePC = start;

    while (fakePC < end) {
        programCounterAtStartOfInstructionExecution = fakePC;
        decoder->decode(*memory, *this, fakePC);
    }
}

void Disassembler::add(std::string mnemonic) {
    results.at(programCounterAtStartOfInstructionExecution) = mnemonic;
}

void Disassembler::ADC(const RegisterPair rp1, const RegisterPair rp2) {
    add(boost::str(boost::format("ADC %s, %s") % registers::toString(rp1) % registers::toString(rp2)));
}

void Disassembler::ADC(const Rgstr r1, const Rgstr r2) {
    add(boost::str(boost::format("ADC %s, %s") % registers::toString(r1) % registers::toString(r2)));
}

void Disassembler::ADC(const Rgstr r, const std::uint8_t i) {
    add(boost::str(boost::format("ADC %s, %s") % registers::toString(r) % utils::int_to_hex(i)));
}

void Disassembler::ADC(const Rgstr r, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("ADC %s, %s") % registers::toString(r) % memoryAddress.toString()));
}

void Disassembler::ADD(const RegisterPair destination, const RegisterPair registerPair) {
    add(boost::str(boost::format("ADD %s, %s")% registers::toString(destination) % registers::toString(registerPair)));
}

void Disassembler::ADD(const Rgstr r, const std::uint8_t nextByte) {
    add(boost::str(boost::format("ADD %s, %s") % registers::toString(r) % utils::int_to_hex(nextByte)));
}

void Disassembler::ADD(const Rgstr r1, const Rgstr r2) {
    add(boost::str(boost::format("ADD %s, %s") % registers::toString(r1) % registers::toString(r2)));
}

void Disassembler::ADD(const Rgstr r, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("ADD %s, %s") % registers::toString(r) % memoryAddress.toString()));
}

void Disassembler::AND(const Rgstr r) {
    add(boost::str(boost::format("AND %s") % registers::toString(r)));
}

void Disassembler::AND(const std::uint8_t i) {
    add(boost::str(boost::format("AND %s") % utils::int_to_hex(i)));
}

void Disassembler::AND(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("AND %s") % memoryAddress.toString()));
}

void Disassembler::BIT(const std::uint8_t i, const Rgstr r) {
    add(boost::str(boost::format("BIT %d, %s") % i % registers::toString(r)));
}

void Disassembler::BIT(const std::uint8_t i, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("BIT %d, %s") % i % memoryAddress.toString()));
}

void Disassembler::CALL(const Condition c, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("CALL %s, %s") % registers::toString(c) % memoryAddress.toString()));
}

void Disassembler::CALL(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("CALL %s") % memoryAddress.toString()));
}

void Disassembler::CCF() {
    add("CCF");
}

void Disassembler::CP(const std::uint8_t val) {
    add(boost::str(boost::format("CP %s") % utils::int_to_hex(val)));
}

void Disassembler::CP(const Rgstr val) {
    add(boost::str(boost::format("CP %s") % registers::toString(val)));
}

void Disassembler::CP(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("CP %s") % memoryAddress.toString()));
}

void Disassembler::CPD() {
    add("CPD");
}

void Disassembler::CPDR() {
    add("CPDR");
}

void Disassembler::CPI() {
    add("CPI");
}

void Disassembler::CPIR() {
    add("CPIR");
}

void Disassembler::CPL() {
    add("CPL");
}

void Disassembler::DAA() {
    add("DAA");
}

void Disassembler::DEC(const Rgstr r) {
    add(boost::str(boost::format("DEC %s") % registers::toString(r)));
}

void Disassembler::DEC(const RegisterPair r) {
    add(boost::str(boost::format("DEC %s") % registers::toString(r)));
}

void Disassembler::DEC(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("DEC %s") % memoryAddress.toString()));
}

void Disassembler::DI() {
    add("DI");
}

void Disassembler::DJNZ(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("DJNZ %s") % memoryAddress.toString()));
}

void Disassembler::EI() {
    add("EI");
}

void Disassembler::EX(const RegisterPair rp1, const RegisterPair rp2) {
    add(boost::str(boost::format("EX %s, %s") % registers::toString(rp1) % registers::toString(rp2)));
}

void Disassembler::EX(const MemoryAddress memoryAddress, const RegisterPair rp) {
    add(boost::str(boost::format("EX %s, %s") % memoryAddress.toString() % registers::toString(rp)));
}

void Disassembler::EXX() {
    add("EXX");
}

void Disassembler::HALT() {
    add("HALT");
}

void Disassembler::IM(const std::uint8_t im) {
    add(boost::str(boost::format("IM %s") % utils::int_to_hex(im)));
}

void Disassembler::in(const Rgstr r, const MemoryAddress &memoryAddress) {
    add(boost::str(boost::format("IN %s, %s") % registers::toString(r) % memoryAddress.toString()));
}

void Disassembler::INC(const Rgstr r) {
    add(boost::str(boost::format("INC %s") % registers::toString(r)));
}

void Disassembler::INC(const RegisterPair r) {
    add(boost::str(boost::format("INC %s") % registers::toString(r)));
}

void Disassembler::INC(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("INC %s") % memoryAddress.toString()));
}

void Disassembler::IND() {
    add("IND");
}

void Disassembler::INDR() {
    add("INDR");
}

void Disassembler::INI() {
    add("INI");
}

void Disassembler::INIR() {
    add("INIR");
}

void Disassembler::JP(const Condition c, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("JP %s %s") % registers::toString(c) % memoryAddress.toString()));
}

void Disassembler::JP(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("JP %s") % memoryAddress.toString()));
}

void Disassembler::JR(const Condition c, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("JR %s %s") % registers::toString(c) % memoryAddress.toString()));
}

void Disassembler::JR(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("JR %s") % memoryAddress.toString()));
}

void Disassembler::LD(const Rgstr r, const std::uint8_t i) {
    add(boost::str(boost::format("LD %s, %s") % registers::toString(r) % utils::int_to_hex(i)));
}

void Disassembler::LD(const Rgstr r1, const Rgstr r2) {
    add(boost::str(boost::format("LD %s, %s") % registers::toString(r1) % registers::toString(r2)));
}

void Disassembler::LD(const RegisterPair r1, const RegisterPair r2) {
    add(boost::str(boost::format("LD %s, %s")% registers::toString(r1)% registers::toString(r2)));
}

void Disassembler::LD(const RegisterPair rp, const std::uint16_t immediateValue) {
    add(boost::str(boost::format("LD %s, %d") % registers::toString(rp) % utils::int_to_hex(immediateValue)));
}

void Disassembler::LD(const MemoryAddress memoryAddress, const Rgstr r) {
    add(boost::str(boost::format("LD %s, %s") % memoryAddress.toString() % registers::toString(r)));
}

void Disassembler::LD(const Rgstr r, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("LD %s, %s") % registers::toString(r) % memoryAddress.toString()));
}

void Disassembler::LD(const MemoryAddress memoryAddress, const RegisterPair r) {
    add(boost::str(boost::format("LD %s, %s") % memoryAddress.toString() % registers::toString(r)));
}

void Disassembler::LD(const RegisterPair r, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("LD %s, %s") % registers::toString(r) % memoryAddress.toString()));
}

void Disassembler::LD(const MemoryAddress memoryAddress, const std::uint8_t i) {
    add(boost::str(boost::format("LD %s, %s") % memoryAddress.toString() % utils::int_to_hex(i)));
}

void Disassembler::LDD() {
    add("LDD");
}

void Disassembler::LDDR() {
    add("LDDR");
}

void Disassembler::LDI() {
    add("LDI");
}

void Disassembler::LDIR() {
    add("LDIR");
}

void Disassembler::NEG() {
    add("NEG");
}

void Disassembler::NOP() {
    add("NOP");
}

void Disassembler::OR(const Rgstr r) {
    add(boost::str(boost::format("OR %s") % registers::toString(r)));
}

void Disassembler::OR(const std::uint8_t immediateValue) {
    add(boost::str(boost::format("OR %s") % utils::int_to_hex(immediateValue)));
}

void Disassembler::OR(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("OR %s") % memoryAddress.toString()));
}

void Disassembler::OTDR() {
    add("OTDR");
}

void Disassembler::OTIR() {
    add("OTIR");
}

void Disassembler::out(const MemoryAddress memoryAddress, const Rgstr r) {
    add(boost::str(boost::format("OUT %s, %s") % memoryAddress.toString() % registers::toString(r)));
}

void Disassembler::OUTD() {
    add("OUTD");
}

void Disassembler::OUTI() {
    add("OUTI");
}

void Disassembler::POP(const RegisterPair r) {
    add(boost::str(boost::format("POP %s") % registers::toString(r)));
}

void Disassembler::PUSH(const RegisterPair r) {
    add(boost::str(boost::format("PUSH %s") % registers::toString(r)));
}

void Disassembler::RES(const std::uint8_t i, const Rgstr r) {
    add(boost::str(boost::format("RES %d %s") % i % registers::toString(r)));
}

void Disassembler::RES(const std::uint8_t i, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("RES %d %s") % i % memoryAddress.toString()));
}

void Disassembler::RET(const Condition c) {
    add(boost::str(boost::format("RET %s") % registers::toString(c)));
}

void Disassembler::RET() {
    add("RET");
}

void Disassembler::RETI() {
    add("RETI");
}

void Disassembler::RETN() {
    add("RETN");
}

void Disassembler::RL(const Rgstr r) {
    add(boost::str(boost::format("RL %s") % registers::toString(r)));
}

void Disassembler::RL(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("RL %s") % memoryAddress.toString()));
}

void Disassembler::RLA() {
    add("RLA");
}

void Disassembler::RLC(const Rgstr r) {
    add(boost::str(boost::format("RLC %s") % registers::toString(r)));
}

void Disassembler::RLC(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("RLC %s") % memoryAddress.toString()));
}

void Disassembler::RLCA() {
    add("RLCA");
}

void Disassembler::RLD() {
    add("RLD");
}

void Disassembler::RR(const Rgstr r) {
    add(boost::str(boost::format("RR %s") % registers::toString(r)));
}

void Disassembler::RR(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("RR %s") % memoryAddress.toString()));
}

void Disassembler::RRA() {
    add("RRA");
}

void Disassembler::RRC(const Rgstr r) {
    add(boost::str(boost::format("RRC %s") % registers::toString(r)));
}

void Disassembler::RRC(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("RRC %s") % memoryAddress.toString()));
}

void Disassembler::RRCA() {
    add("RRCA");
}

void Disassembler::RRD() {
    add("RRD");
}

void Disassembler::RST(const std::uint8_t i) {
    add(boost::str(boost::format("RST %s") % utils::int_to_hex(i)));
}

void Disassembler::SBC(const Rgstr r, const std::uint8_t nextByte) {
    add(boost::str(boost::format("SBC %s, %s") % registers::toString(r) % utils::int_to_hex(nextByte)));
}

void Disassembler::SBC(const Rgstr r1, const Rgstr r2) {
    add(boost::str(boost::format("SBC %s, %s") % registers::toString(r1) % registers::toString(r2)));
}

void Disassembler::SBC(const RegisterPair rp1, const RegisterPair rp2) {
    add(boost::str(boost::format("SBC %s, %s") % registers::toString(rp1) % registers::toString(rp2)));
}

void Disassembler::SBC(const Rgstr r, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("SBC %s, %s") % registers::toString(r) % memoryAddress.toString()));
}

void Disassembler::SCF() {
    add("SCF");
}

void Disassembler::SET(const std::uint8_t i, const Rgstr r) {
    add(boost::str(boost::format("SET %d, %s") % i % registers::toString(r)));
}

void Disassembler::SET(const std::uint8_t i, const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("SET %d, %s") % i % memoryAddress.toString()));
}

void Disassembler::SLA(const Rgstr r) {
    add(boost::str(boost::format("SLA %s") % registers::toString(r)));
}

void Disassembler::SLA(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("SLA %s") % memoryAddress.toString()));
}

void Disassembler::SRA(const Rgstr r) {
    add(boost::str(boost::format("SRA %s") % registers::toString(r)));
}

void Disassembler::SRA(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("SRA %s") % memoryAddress.toString()));
}

void Disassembler::SRL(const Rgstr r) {
    add(boost::str(boost::format("SRL %s") % registers::toString(r)));
}

void Disassembler::SRL(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("SRL %s") % memoryAddress.toString()));
}

void Disassembler::SUB(const Rgstr r) {
    add(boost::str(boost::format("SUB %s") % registers::toString(r)));
}

void Disassembler::SUB(const std::uint8_t i) {
    add(boost::str(boost::format("SUB %s") % utils::int_to_hex(i)));
}

void Disassembler::SUB(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("SUB %s") % memoryAddress.toString()));
}

void Disassembler::XOR(const Rgstr r) {
    add(boost::str(boost::format("XOR %s") % registers::toString(r)));
}

void Disassembler::XOR(const std::uint8_t i) {
    add(boost::str(boost::format("XOR %s") % utils::int_to_hex(i)));
}

void Disassembler::XOR(const MemoryAddress memoryAddress) {
    add(boost::str(boost::format("XOR %s") % memoryAddress.toString()));
}
