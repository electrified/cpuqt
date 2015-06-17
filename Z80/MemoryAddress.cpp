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
#include<string>
#include "Z80/MemoryAddress.h"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"

MemoryAddress::MemoryAddress() {
    memoryAddress = 0;
    offset = 0;
    registerPair = RegisterPair::unknown;
    rgstr = Rgstr::unknown;
}

MemoryAddress::MemoryAddress(const std::uint16_t  memoryAddress) : MemoryAddress() {
    this->memoryAddress = memoryAddress;
}

MemoryAddress::MemoryAddress(const Rgstr rgstr) : MemoryAddress() {
    this->rgstr = rgstr;
}

MemoryAddress::MemoryAddress(const RegisterPair rgstrPair) : MemoryAddress() {
    this->registerPair = rgstrPair;
}

MemoryAddress::MemoryAddress(const RegisterPair rgstrPair, const std::uint8_t offset) : MemoryAddress() {
    this->registerPair = rgstrPair;
    this->offset = offset;
}

const std::uint16_t  MemoryAddress::getMemoryAddress() {
    return memoryAddress;
}

const std::uint8_t  MemoryAddress::getOffset() {
    return offset;
}

const Rgstr MemoryAddress::getRegister() {
    return rgstr;
}

const RegisterPair MemoryAddress::getRegisterPair() {
    return registerPair;
}

const std::string MemoryAddress::toString() {
         string address = "";
//         if(getRegister() != null) {
//             address = getRegister().name();
//             if (getOffset() != null) {
//                 address = address + "+" + "0x" + Integer.toHexString(getOffset());
//             }
//         } else if (getRegisterPair() != null) {
//             address = getRegisterPair().name();
//             if (getOffset() != null) {
//                 address = address + "+" + "0x" + Integer.toHexString(getOffset());
//             }
//         } else if (getMemoryAddress() != null) {
//             address = "0x" + Integer.toHexString(getMemoryAddress());
//         }

         return address;
}
