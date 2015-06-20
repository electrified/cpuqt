#include "BaseProcessor.h"
#include <iostream>

BaseProcessor::BaseProcessor(Memory& memory, IO& io) : io(io), memory(memory){
    PC = 0;
}

BaseProcessor::~BaseProcessor() {

}

void BaseProcessor::placeProgramCounterOnAddressBus() {
    addressBus = this->getPC();
    ++PC;
}

std::uint16_t BaseProcessor::getPC() {
    return PC;
}

void BaseProcessor::setPC(std::uint16_t pc) {
    PC = pc;
}

Memory& BaseProcessor::getMemory() {
    return memory;
}

IO& BaseProcessor::getIO() {
    return io;
}

std::uint8_t BaseProcessor::fetchInstruction() {
    return getMemory().read(addressBus);
}

std::uint8_t BaseProcessor::getNextByte() {
    ++instructionByteCount;
    placeProgramCounterOnAddressBus();
//     cout << "address bus " << addressBus << std::endl;

    return fetchInstruction();
}
