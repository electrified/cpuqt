#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"
#include <boost/utility/binary.hpp>
#include "Logger.h"

class Registers {
        
public:
    Logger logger;
    std::uint8_t A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, H = 0, L = 0, I = 0, R = 0;
    std::uint16_t IX = 0, IY = 0, SP = 0;
    std::uint8_t A_alt = 0, B_alt = 0, C_alt = 0, D_alt = 0, E_alt = 0, F_alt = 0, H_alt = 0, L_alt = 0;
    //interrupt enable flip flops
    bool IFF1 = false;
    bool IFF2 = false;
    bool halted = false;
    //interrupt mode
    std::uint8_t _IM = 0;
    std::uint16_t addressBus = 0;

inline std::uint16_t getAF() {
    return (A << 8) | F;
}

inline void setAF(std::uint16_t value) {
    A = (value >> 8) & 0xff;
    F = value & 0xff;
}

inline std::uint16_t getAF_alt() {
    return (A_alt << 8) | F_alt;
}

inline void setAF_alt(std::uint16_t value) {
    A_alt=(value >> 8) & 0xff;
    F_alt=(value & 0xff);
}

inline std::uint16_t getBC() {
    return (B << 8) | C;
}

inline void setBC(std::uint16_t value) {
    B=(value >> 8) & 0xff;
    C=value & 0xff;
}

inline std::uint16_t getBC_alt() {
    return (B_alt << 8) | C_alt;
}

inline void setBC_alt(std::uint16_t value) {
    B_alt=(value >> 8) & 0xff;
    C_alt=value & 0xff;
}

inline bool getCFlag() {
    return (F & BOOST_BINARY(1)) == BOOST_BINARY(1);
}

inline void setCFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(1);
    } else {
        F &= ~BOOST_BINARY(1);
    }
}

inline std::uint16_t getDE() {
    return (D << 8) | E;
}

inline void setDE(std::uint16_t value) {
    D=(value >> 8) & 0xff;
    E=value & 0xff;
}

inline std::uint16_t getDE_alt() {
    return (D_alt << 8) | E_alt;
}

inline void setDE_alt(std::uint16_t value) {
    D_alt=(value >> 8) & 0xff;
    E_alt=value & 0xff;
}

inline bool getHFlag() {
    return (F & BOOST_BINARY(100000)) == BOOST_BINARY(100000);
}

inline void setHFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(100000);
    } else {
        F &= ~BOOST_BINARY(100000);
    }
}

inline std::uint16_t getHL() {
    return (H << 8) | L;
}

inline void setHL(std::uint16_t value) {
    H =(value >> 8) & 0xff;
    L = value & 0xff;
}

inline std::uint16_t getHL_alt() {
    return (H_alt << 8) | L_alt;
}

inline void setHL_alt(std::uint16_t value) {
    H_alt=(value >> 8) & 0xff;
    L_alt=value & 0xff;
}

inline std::uint8_t getIXH() {
    return IX >> 8;
}

inline std::uint8_t getIXL() {
    return IX & 0xff;
}

inline std::uint8_t getIYH() {
    return IY >> 8;
}

inline std::uint8_t getIYL() {
    return IY & BOOST_BINARY(11111111);
}

inline bool getNFlag() {
    return (F & BOOST_BINARY(10000)) == BOOST_BINARY(10000);
}

inline void setNFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(10000);
    } else {
        F &= ~BOOST_BINARY(10000);
    }
}

inline bool getParityOverflowFlag() {
    return (F & BOOST_BINARY(100)) == BOOST_BINARY(100);
}

inline void setParityOverflowFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(100);
    } else {
        F &= ~BOOST_BINARY(100);
    }
}

inline std::uint16_t getRegisterPairValue(RegisterPair rgstr) {
//		logger.debug("Getting value for rgstr " + rgstr);
    switch (rgstr) {
        case RegisterPair::BC:
        return getBC();
    case RegisterPair::DE:
        return getDE();
    case RegisterPair::HL:
        return getHL();
    case RegisterPair::SP:
        return SP;
    case RegisterPair::AF:
        return getAF();
    case RegisterPair::IX:
        return IX;
    case RegisterPair::IY:
        return IY;
    case RegisterPair::PC:
        return PC;
    case RegisterPair::BC_prime:
        return getBC_alt();
    case RegisterPair::DE_prime:
        return getDE_alt();
    case RegisterPair::HL_prime:
        return getHL_alt();
    case RegisterPair::AF_prime:
        return getAF_alt();
    default:
//         logger.debug("Unknnown rgstr " + rgstr);
        throw UnknownRegisterPairException();
    }
}

inline std::uint8_t getRegisterValue(Rgstr rgstr) {
//		logger.debug("Getting value for rgstr " + rgstr);
    switch (rgstr) {
        case Rgstr::A:
        return A;
    case Rgstr::B:
        return B;
    case Rgstr::C:
        return C;
    case Rgstr::D:
        return D;
    case Rgstr::E:
        return E;
    case Rgstr::H:
        return H;
    case Rgstr::L:
        return L;
    case Rgstr::IXL:
        return getIXL();
    case Rgstr::IXH:
        return getIXH();
    case Rgstr::R:
        return R;
    case Rgstr::I:
        return I;
    default:
//         logger.debug("Unknnown rgstr " + rgstr);
        throw UnknownRegisterPairException();
    }
}

inline bool getSignFlag() {
    return (F & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000);
}

inline void setSignFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(10000000);
    } else {
        F &= ~BOOST_BINARY(10000000);
    }
}

inline bool getZeroFlag() {
    return (F & BOOST_BINARY(1000000)) == BOOST_BINARY(1000000);
}

inline void setZeroFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(1000000);
    } else {
        F &= ~BOOST_BINARY(1000000);
    }
}

inline void setRegister(Rgstr rgstr, std::uint8_t value) {
//    logger.debug("Setting value 0x" + value + " for rgstr " + rgstr);
    switch (rgstr) {
        case Rgstr::A:
        A = value;
        break;
    case Rgstr::B:
        B=value;
        break;
    case Rgstr::C:
        C=value;
        break;
    case Rgstr::D:
        D=value;
        break;
    case Rgstr::E:
        E=value;
        break;
    case Rgstr::H:
        H=value;
        break;
    case Rgstr::L:
        L=value;
        break;
    case Rgstr::R:
        R=value;
        break;
    case Rgstr::I:
        I=value;
        break;
    default:
        throw UnknownRegisterException();
    }
}

inline void setRegisterPair(RegisterPair rgstr, std::uint16_t sixteenBit) {
    setRegisterPair(rgstr, sixteenBit & 0xff, ((sixteenBit >> 8) & 0xff));
}

inline void setRegisterPair(RegisterPair rgstr, std::uint8_t lowOrder, std::uint8_t highOrder) {
    switch (rgstr) {
        case RegisterPair::BC:
        this->B = highOrder;
        this->C = lowOrder;
        break;
    case RegisterPair::BC_prime:
        this->B_alt = highOrder;
        this->C_alt = lowOrder;
        break;
    case RegisterPair::DE:
        this->D = highOrder;
        this->E = lowOrder;
        break;
    case RegisterPair::DE_prime:
        this->D_alt = highOrder;
        this->E_alt = lowOrder;
        break;
    case RegisterPair::HL:
        this->H = highOrder;
        this->L = lowOrder;
        break;
    case RegisterPair::HL_prime:
        this->H_alt = highOrder;
        this->L_alt = lowOrder;
        break;
    case RegisterPair::SP:
        this->SP = highOrder << 8 | lowOrder;
        break;
    case RegisterPair::AF:
        this->A = highOrder;
        this->F = lowOrder;
        break;
    case RegisterPair::AF_prime:
        this->A_alt = highOrder;
        this->F_alt = lowOrder;
        break;
    case RegisterPair::IX:
        this->IX = highOrder << 8 | lowOrder;
        break;
    case RegisterPair::IY:
        this->IY = highOrder << 8 | lowOrder;
        break;
    default:
        logger.debug("unknown rgstr pair");
    }
}
    /*
* Program Counter (PC) The program counter holds the 16-bit address of the
* current instruction being fetched from memory. The PC is automatically
* incremented after its contents have been transferred to the address
* lines. When a program jump occurs, the new value is automatically placed
* in the PC, overriding the incrementer.
*/
    std::uint16_t PC = 0;
    Registers();
};

#endif // REGISTERS_H
