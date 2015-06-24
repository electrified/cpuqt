#include "registers.h"

Registers::Registers()
{

}


std::uint16_t Registers::getPC() {
    return PC;
}

void Registers::setPC(std::uint16_t pc) {
    PC = pc;
}


std::uint8_t Registers::getA() {
    return A;
}

void Registers::setA(std::uint8_t a) {
    A = a;
}

std::uint16_t Registers::getAF() {
    return (getA() << 8) | getF();
}

void Registers::setAF(std::uint16_t value) {
    setA((value >> 8) & 0xff);
    setF(value & 0xff);
}

std::uint16_t Registers::getAF_alt() {
    return (getA_alt() << 8) | getF_alt();
}

void Registers::setAF_alt(std::uint16_t value) {
    setA_alt((value >> 8) & 0xff);
    setF_alt(value & 0xff);
}

std::uint8_t Registers::getA_alt() {
    return A_alt;
}

void Registers::setA_alt(std::uint8_t a_alt) {
    A_alt = a_alt;
}

std::uint8_t Registers::getB() {
    return B;
}

void Registers::setB(std::uint8_t b) {
    this->B = b;
}

std::uint16_t Registers::getBC() {
    return (B << 8) | C;
}

void Registers::setBC(std::uint16_t value) {
    setB((value >> 8) & 0xff);
    setC(value & 0xff);
}

std::uint16_t Registers::getBC_alt() {
    return (B_alt << 8) | C_alt;
}

void Registers::setBC_alt(std::uint16_t value) {
    setB_alt((value >> 8) & 0xff);
    setC_alt(value & 0xff);
}

std::uint8_t Registers::getB_alt() {
    return B_alt;
}

void Registers::setB_alt(std::uint8_t b_alt) {
    B_alt = b_alt;
}

std::uint8_t Registers::getC() {
    return C;
}

void Registers::setC(std::uint8_t c) {
    this->C = c;
}

bool Registers::getCFlag() {
    return (F & BOOST_BINARY(1)) == BOOST_BINARY(1);
}

void Registers::setCFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(1);
    } else {
        F &= ~BOOST_BINARY(1);
    }
}

std::uint8_t Registers::getC_alt() {
    return C_alt;
}

void Registers::setC_alt(std::uint8_t c_alt) {
    C_alt = c_alt;
}

std::uint8_t Registers::getD() {
    return D;
}

void Registers::setD(std::uint8_t d) {
    this->D = d;
}

std::uint16_t Registers::getDE() {
    return (D << 8) | E;
}

void Registers::setDE(std::uint16_t value) {
    setD((value >> 8) & 0xff);
    setE(value & 0xff);
}

std::uint16_t Registers::getDE_alt() {
    return (D_alt << 8) | E_alt;
}

void Registers::setDE_alt(std::uint16_t value) {
    setD_alt((value >> 8) & 0xff);
    setE_alt(value & 0xff);
}

std::uint8_t Registers::getD_alt() {
    return D_alt;
}

void Registers::setD_alt(std::uint8_t d_alt) {
    D_alt = d_alt;
}

std::uint8_t Registers::getE() {
    return E;
}

void Registers::setE(std::uint8_t e) {
    this->E = e;
}

std::uint8_t Registers::getE_alt() {
    return E_alt;
}

void Registers::setE_alt(std::uint8_t e_alt) {
    E_alt = e_alt;
}

std::uint8_t Registers::getF() {
    return F;
}

void Registers::setF(std::uint8_t f) {
    this->F = f;
}

std::uint8_t Registers::getF_alt() {
    return F_alt;
}

void Registers::setF_alt(std::uint8_t f_alt) {
    F_alt = f_alt;
}

std::uint8_t Registers::getH() {
    return H;
}

void Registers::setH(std::uint8_t h) {
    this->H = h;
}

bool Registers::getHFlag() {
    return (F & BOOST_BINARY(100000)) == BOOST_BINARY(100000);
}

void Registers::setHFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(100000);
    } else {
        F &= ~BOOST_BINARY(100000);
    }
}

std::uint16_t Registers::getHL() {
    return (getH() << 8) | getL();
}

void Registers::setHL(std::uint16_t value) {
    setH((value >> 8) & 0xff);
    setL(value & 0xff);
}

std::uint16_t Registers::getHL_alt() {
    return (H_alt << 8) | L_alt;
}

void Registers::setHL_alt(std::uint16_t value) {
    setH_alt((value >> 8) & 0xff);
    setL_alt(value & 0xff);
}

std::uint8_t Registers::getH_alt() {
    return H_alt;
}

void Registers::setH_alt(std::uint8_t h_alt) {
    H_alt = h_alt;
}

std::uint8_t Registers::getI() {
    return I;
}

void Registers::setI(std::uint8_t i) {
    I = i;
}

void Registers::setIM(std::uint8_t im) {
    _IM = im;
}

std::uint8_t Registers::getIM() {
    return _IM;
}

std::uint16_t Registers::getIX() {
    return IX;
}

void Registers::setIX(std::uint16_t iX) {
    IX = iX;
}

std::uint8_t Registers::getIXH() {
    return IX >> 8;
}

std::uint8_t Registers::getIXL() {
    return IX & 0xff;
}

std::uint16_t Registers::getIY() {
    return IY;
}

void Registers::setIY(std::uint16_t iY) {
    IY = iY;
}

std::uint8_t Registers::getIYH() {
    return IY >> 8;
}

std::uint8_t Registers::getIYL() {
    return IY & BOOST_BINARY(11111111);
}

std::uint8_t Registers::getL() {
    return L;
}

void Registers::setL(std::uint8_t l) {
    L = l;
}

std::uint8_t Registers::getL_alt() {
    return L_alt;
}

void Registers::setL_alt(std::uint8_t l_alt) {
    L_alt = l_alt;
}

bool Registers::getNFlag() {
    return (F & BOOST_BINARY(10000)) == BOOST_BINARY(10000);
}

void Registers::setNFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(10000);
    } else {
        F &= ~BOOST_BINARY(10000);
    }
}

bool Registers::getParityOverflowFlag() {
    return (F & BOOST_BINARY(100)) == BOOST_BINARY(100);
}

void Registers::setParityOverflowFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(100);
    } else {
        F &= ~BOOST_BINARY(100);
    }
}

std::uint8_t Registers::getR() {
    return R;
}

void Registers::setR(std::uint8_t r) {
    R = r;
}

std::uint16_t Registers::getRegisterPairValue(RegisterPair rgstr) {
//		logger.debug("Getting value for rgstr " + rgstr);
    switch (rgstr) {
        case RegisterPair::BC:
        return getBC();
    case RegisterPair::DE:
        return getDE();
    case RegisterPair::HL:
        return getHL();
    case RegisterPair::SP:
        return getSP();
    case RegisterPair::AF:
        return getAF();
    case RegisterPair::IX:
        return getIX();
    case RegisterPair::IY:
        return getIY();
    case RegisterPair::PC:
        return getPC();
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

std::uint8_t Registers::getRegisterValue(Rgstr rgstr) {
//		logger.debug("Getting value for rgstr " + rgstr);
    switch (rgstr) {
        case Rgstr::A:
        return getA();
    case Rgstr::B:
        return getB();
    case Rgstr::C:
        return getC();
    case Rgstr::D:
        return getD();
    case Rgstr::E:
        return getE();
    case Rgstr::H:
        return getH();
    case Rgstr::L:
        return getL();
    case Rgstr::IXL:
        return getIXL();
    case Rgstr::IXH:
        return getIXH();
    case Rgstr::R:
        return getR();
    case Rgstr::I:
        return getI();
    default:
//         logger.debug("Unknnown rgstr " + rgstr);
        throw UnknownRegisterPairException();
    }
}

std::uint16_t Registers::getSP() {
    return SP;
}

void Registers::setSP(std::uint16_t sP) {
    SP = sP;
}

bool Registers::getSignFlag() {
    return (F & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000);
}

void Registers::setSignFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(10000000);
    } else {
        F &= ~BOOST_BINARY(10000000);
    }
}

bool Registers::getZeroFlag() {
    return (F & BOOST_BINARY(1000000)) == BOOST_BINARY(1000000);
}

void Registers::setZeroFlag(bool flag) {
    if (flag) {
        F |= BOOST_BINARY(1000000);
    } else {
        F &= ~BOOST_BINARY(1000000);
    }
}

void Registers::setRegister(Rgstr rgstr, std::uint8_t value) {
//    logger.debug("Setting value 0x" + value + " for rgstr " + rgstr);
    switch (rgstr) {
        case Rgstr::A:
        setA(value);
        break;
    case Rgstr::B:
        setB(value);
        break;
    case Rgstr::C:
        setC(value);
        break;
    case Rgstr::D:
        setD(value);
        break;
    case Rgstr::E:
        setE(value);
        break;
    case Rgstr::H:
        setH(value);
        break;
    case Rgstr::L:
        setL(value);
        break;
    case Rgstr::R:
        setR(value);
        break;
    case Rgstr::I:
        setI(value);
        break;
    default:
        throw UnknownRegisterException();
    }
}

void Registers::setRegisterPair(RegisterPair rgstr, std::uint16_t sixteenBit) {
    setRegisterPair(rgstr, sixteenBit & 0xff, ((sixteenBit >> 8) & 0xff));
}

void Registers::setRegisterPair(RegisterPair rgstr, std::uint8_t lowOrder, std::uint8_t highOrder) {
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

bool Registers::isIFF1() {
    return IFF1;
}

void Registers::setIFF1(bool iFF1) {
    IFF1 = iFF1;
}

bool Registers::isIFF2() {
    return IFF2;
}

void Registers::setIFF2(bool iFF2) {
    IFF2 = iFF2;
}

bool Registers::isHalted() {
    return halted;
}

void Registers::setHalted(bool val) {
    halted = val;
}
