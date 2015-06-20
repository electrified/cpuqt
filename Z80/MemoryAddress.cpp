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
