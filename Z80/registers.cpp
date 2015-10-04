#include "registers.h"

Registers::Registers()
{
    IX.all = 0;
    IY.all = 0;
    SP.all = 0;
    IR.all = 0;
    
    AF.all = 0;
    BC.all = 0;
    DE.all = 0;
    HL.all = 0;
    
    AF_alt.all = 0;
    BC_alt.all = 0;
    DE_alt.all = 0;
    HL_alt.all = 0;
}

std::uint16_t Registers::getPC() {
    return PC;
}

void Registers::setPC(std::uint16_t pc) {
    PC = pc;
}

std::uint8_t Registers::getA() {
    return AF.byte[1];
}

void Registers::setA(std::uint8_t a) {
    AF.byte[1] = a;
}

std::uint16_t Registers::getAF() {
    return AF.all;
}

void Registers::setAF(std::uint16_t value) {
    AF.all = value;
}

std::uint16_t Registers::getAF_alt() {
    return AF_alt.all;
}

void Registers::setAF_alt(std::uint16_t value) {
    AF_alt.all = value;
}

std::uint8_t Registers::getA_alt() {
    return AF_alt.byte[1];
}

void Registers::setA_alt(std::uint8_t a_alt) {
    AF_alt.byte[1] = a_alt;
}

std::uint8_t Registers::getB() {
    return BC.byte[1];
}

void Registers::setB(std::uint8_t b) {
    BC.byte[1] = b;
}

std::uint16_t Registers::getBC() {
    return BC.all;
}

void Registers::setBC(std::uint16_t value) {
    BC.all = value;
}

std::uint16_t Registers::getBC_alt() {
    return BC_alt.all;
}

void Registers::setBC_alt(std::uint16_t value) {
    BC_alt.all = value;
}

std::uint8_t Registers::getB_alt() {
    return BC_alt.byte[1];
}

void Registers::setB_alt(std::uint8_t b_alt) {
    BC_alt.byte[1] = b_alt;
}

std::uint8_t Registers::getC() {
    return BC.byte[0];
}

void Registers::setC(std::uint8_t c) {
    BC.byte[0] = c;
}

bool Registers::getCFlag() {
    return (getF() & BOOST_BINARY(1)) == BOOST_BINARY(1);
}

void Registers::setCFlag(bool flag) {
    if (flag) {
        AF.byte[0] |= BOOST_BINARY(1);
    } else {
        AF.byte[0] &= ~BOOST_BINARY(1);
    }
}

std::uint8_t Registers::getC_alt() {
    return BC_alt.byte[0];
}

void Registers::setC_alt(std::uint8_t c_alt) {
    BC_alt.byte[0] = c_alt;
}

std::uint8_t Registers::getD() {
    return DE.byte[1];
}

void Registers::setD(std::uint8_t d) {
    this->DE.byte[1] = d;
}

std::uint16_t Registers::getDE() {
    return DE.all;
}

void Registers::setDE(std::uint16_t value) {
    DE.all = value;
}

std::uint16_t Registers::getDE_alt() {
    return DE_alt.all;
}

void Registers::setDE_alt(std::uint16_t value) {
    DE_alt.all = value;
}

std::uint8_t Registers::getD_alt() {
    return DE_alt.byte[1];
}

void Registers::setD_alt(std::uint8_t d_alt) {
    DE_alt.byte[1] = d_alt;
}

std::uint8_t Registers::getE() {
    return DE.byte[0];
}

void Registers::setE(std::uint8_t e) {
    DE.byte[0] = e;
}

std::uint8_t Registers::getE_alt() {
    return DE_alt.byte[0];
}

void Registers::setE_alt(std::uint8_t e_alt) {
    DE_alt.byte[0] = e_alt;
}

std::uint8_t Registers::getF() {
    return AF.byte[0];
}

void Registers::setF(std::uint8_t f) {
    AF.byte[0] = f;
}

std::uint8_t Registers::getF_alt() {
    return AF_alt.byte[0];
}

void Registers::setF_alt(std::uint8_t f_alt) {
     AF_alt.byte[0] = f_alt;
}

std::uint8_t Registers::getH() {return HL.byte[1];}
void Registers::setH(std::uint8_t h) {HL.byte[1] = h;}

std::uint8_t Registers::getL() {return HL.byte[0];}
void Registers::setL(std::uint8_t l) {HL.byte[0] = l;}

std::uint16_t Registers::getHL() {
    return HL.all;
}

void Registers::setHL(std::uint16_t value) {
    HL.all = value;
}

bool Registers::getHFlag() {
    return (AF.byte[0] & BOOST_BINARY(100000)) == BOOST_BINARY(100000);
}

void Registers::setHFlag(bool flag) {
    if (flag) {
        AF.byte[0] |= BOOST_BINARY(100000);
    } else {
        AF.byte[0] &= ~BOOST_BINARY(100000);
    }
}

std::uint16_t Registers::getHL_alt() {
    return HL_alt.all;
}

void Registers::setHL_alt(std::uint16_t value) {
    HL_alt.all = value;
}

std::uint8_t Registers::getH_alt() {
    return HL_alt.byte[1];
}

void Registers::setH_alt(std::uint8_t h_alt) {
    HL_alt.byte[1] = h_alt;
}

std::uint8_t Registers::getI() {
    return IR.byte[1];
}

void Registers::setI(std::uint8_t i) {
    IR.byte[1] = i;
}

void Registers::setIM(std::uint8_t im) {
    _IM = im;
}

std::uint8_t Registers::getIM() {
    return _IM;
}

std::uint16_t Registers::getIX() {
    return IX.all;
}

void Registers::setIX(std::uint16_t ix) {
    IX.all = ix;
}

std::uint8_t Registers::getIXH() {
    return IX.byte[1];
}

std::uint8_t Registers::getIXL() {
    return IX.byte[0];
}

std::uint16_t Registers::getIY() {
    return IY.all;
}

void Registers::setIY(std::uint16_t iy) {
    IY.all = iy;
}

std::uint8_t Registers::getIYH() {
    return IY.byte[1];
}

std::uint8_t Registers::getIYL() {
    return IY.byte[0];
}

std::uint8_t Registers::getL_alt() {
    return HL_alt.byte[0];
}

void Registers::setL_alt(std::uint8_t l_alt) {
    HL_alt.byte[0] = l_alt;
}

bool Registers::getNFlag() {
    return (AF.byte[0] & BOOST_BINARY(10000)) == BOOST_BINARY(10000);
}

void Registers::setNFlag(bool flag) {
    if (flag) {
        AF.byte[0] |= BOOST_BINARY(10000);
    } else {
        AF.byte[0] &= ~BOOST_BINARY(10000);
    }
}

bool Registers::getParityOverflowFlag() {
    return (AF.byte[0] & BOOST_BINARY(100)) == BOOST_BINARY(100);
}

void Registers::setParityOverflowFlag(bool flag) {
    if (flag) {
        AF.byte[0] |= BOOST_BINARY(100);
    } else {
        AF.byte[0] &= ~BOOST_BINARY(100);
    }
}

std::uint8_t Registers::getR() {
    return IR.byte[0];
}

void Registers::setR(std::uint8_t r) {
    IR.byte[0] = r;
}

std::uint16_t Registers::getRegisterPairValue(RegisterPair rgstr) {
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
        throw UnknownRegisterPairException();
    }
}

std::uint8_t Registers::getRegisterValue(Rgstr rgstr) {
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
        throw UnknownRegisterPairException();
    }
}

std::uint16_t Registers::getSP() {
    return SP.all;
}

void Registers::setSP(std::uint16_t sp) {
    SP.all = sp;
}

bool Registers::getSignFlag() {
    return (AF.byte[0] & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000);
}

void Registers::setSignFlag(bool flag) {
    if (flag) {
        AF.byte[0] |= BOOST_BINARY(10000000);
    } else {
        AF.byte[0] &= ~BOOST_BINARY(10000000);
    }
}

bool Registers::getZeroFlag() {
    return (AF.byte[0] & BOOST_BINARY(1000000)) == BOOST_BINARY(1000000);
}

void Registers::setZeroFlag(bool flag) {
    if (flag) {
        AF.byte[0] |= BOOST_BINARY(1000000);
    } else {
        AF.byte[0] &= ~BOOST_BINARY(1000000);
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
    switch (rgstr) {
        case RegisterPair::BC:
        setBC(sixteenBit);
        break;
    case RegisterPair::BC_prime:
        setBC_alt(sixteenBit);
        break;
    case RegisterPair::DE:
        setDE(sixteenBit);
        break;
    case RegisterPair::DE_prime:
        setDE_alt(sixteenBit);
        break;
    case RegisterPair::HL:
        setHL(sixteenBit);
        break;
    case RegisterPair::HL_prime:
        setHL_alt(sixteenBit);
        break;
    case RegisterPair::SP:
        setSP(sixteenBit);
        break;
    case RegisterPair::AF:
        setAF(sixteenBit);
        break;
    case RegisterPair::AF_prime:
        setAF_alt(sixteenBit);
        break;
    case RegisterPair::IX:
        setIX(sixteenBit);
        break;
    case RegisterPair::IY:
        setIY(sixteenBit);
        break;
    default:
        logger.debug("unknown rgstr pair");
    }
}

void Registers::setRegisterPair(RegisterPair rgstr, std::uint8_t lowOrder, std::uint8_t highOrder) {
    switch (rgstr) {
        case RegisterPair::BC:
        setB(highOrder);
        setC(lowOrder);
        break;
    case RegisterPair::BC_prime:
        setB_alt(highOrder);
        setC_alt(lowOrder);
        break;
    case RegisterPair::DE:
        setD(highOrder);
        setE(lowOrder);
        break;
    case RegisterPair::DE_prime:
        setD_alt(highOrder);
        setE_alt(lowOrder);
        break;
    case RegisterPair::HL:
        setH(highOrder);
        setL(lowOrder);
        break;
    case RegisterPair::HL_prime:
        setH_alt(highOrder);
        setL_alt(lowOrder);
        break;
    case RegisterPair::SP:
        this->SP.byte[1] = highOrder;
        this->SP.byte[0] = lowOrder;
        break;
    case RegisterPair::AF:
        setA(highOrder);
        setF(lowOrder);
        break;
    case RegisterPair::AF_prime:
        setA_alt(highOrder);
        setF_alt(lowOrder);
        break;
    case RegisterPair::IX:
        this->IX.byte[1] = highOrder;
        this->IX.byte[0] = lowOrder;
        break;
    case RegisterPair::IY:
        this->IY.byte[1] = highOrder;
        this->IY.byte[0] = lowOrder;
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
