/*
 * Copyright (c) 2015, <copyright holder> <email>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "BaseProcessor.h"
//#include <cstdint>

BaseProcessor::BaseProcessor(Memory& memory, IO& io) : io(io), memory(memory){
    PC = 0;
//     this->io = io;
//     this->memory = memory;
}

BaseProcessor::~BaseProcessor() {

}

void BaseProcessor::placeProgramCounterOnAddressBus() {
    addressBus = this->getPC();
    PC++;
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

void BaseProcessor::setMemory(Memory& memory) {
    this->memory = memory;
}

IO& BaseProcessor::getIO() {
    return io;
}

void BaseProcessor::setIO(IO& io) {
    this->io = io;
}

std::uint8_t BaseProcessor::fetchInstruction() {
    return getMemory().read(addressBus);
}

std::uint8_t BaseProcessor::getNextByte() {
    instructionByteCount++;
    placeProgramCounterOnAddressBus();
    return fetchInstruction();
}

