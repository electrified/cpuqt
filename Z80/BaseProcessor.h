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

#ifndef BASEPROCESSOR_H
#define BASEPROCESSOR_H

#include <cstdint>

#include "Z80/Memory.h"
#include "Z80/Processor.h"
#include "Z80/InstructionDecoder.h"

class BaseProcessor : public Processor
{
protected:
    InstructionDecoder* instructionDecoder;
    Memory* memory;
    std::uint16_t addressBus;

    /*
 * Program Counter (PC) The program counter holds the 16-bit address of the
 * current instruction being fetched from memory. The PC is automatically
 * incremented after its contents have been transferred to the address
 * lines. When a program jump occurs, the new value is automatically placed
 * in the PC, overriding the incrementer.
 */
    std::uint16_t PC;
public:
    void placeProgramCounterOnAddressBus();
    std::uint16_t getPC();
    void setPC(std::uint16_t pC);
    Memory* getMemory();
    void setMemory(std::uint8_t memory[]);
    void setMemory(Memory* memory);
    std::uint8_t fetchInstruction();
};

#endif // BASEPROCESSOR_H
