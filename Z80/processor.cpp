#include "Z80/processor.h"
#include "Z80/emu_alu.h"

#include <iostream>

Processor::Processor(Memory* memory, IO* io) :
io(io), memory(memory)
{
    //, Alu* alu, Registers* rgstrs
    std::cout << "Processor ctor" << std::endl;
    decoder = new Decoder();
    registers = new Registers();
    alu = new EmuAlu(memory, io, registers);
}

Processor::~Processor() {
//     delete &memory;
//     delete &io;
}

void Processor::process() {
//        if (halted) {
//            decode(); //NOP
//        } else {
    decoder->decode(*memory, *alu, registers->PC);
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

Alu* Processor::getAlu() {
    return alu;
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