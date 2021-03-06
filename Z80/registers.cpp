#include "registers.h"

Registers::Registers() {
  IX.all = 0;
  IY.all = 0;
  SP.all = 0;
  IR.all = 0;

  AF.all = 0;
  AF.all = 0;
  BC.all = 0;
  DE.all = 0;
  HL.all = 0;

  AF_alt.all = 0;
  BC_alt.all = 0;
  DE_alt.all = 0;
  HL_alt.all = 0;
}

std::uint16_t Registers::getPC() const { return PC; }

void Registers::setPC(std::uint16_t pc) { PC = pc; }

std::uint8_t Registers::getA() const { return AF.bytes.high; }

void Registers::setA(std::uint8_t a) { AF.bytes.high = a; }

std::uint16_t Registers::getAF() const { return AF.all; }

void Registers::setAF(std::uint16_t value) { AF.all = value; }

std::uint16_t Registers::getAF_alt() const { return AF_alt.all; }

void Registers::setAF_alt(std::uint16_t value) { AF_alt.all = value; }

std::uint8_t Registers::getA_alt() const { return AF_alt.bytes.high; }

void Registers::setA_alt(std::uint8_t a_alt) { AF_alt.bytes.high = a_alt; }

std::uint8_t Registers::getB() const { return BC.bytes.high; }

void Registers::setB(std::uint8_t b) { BC.bytes.high = b; }

std::uint16_t Registers::getBC() const { return BC.all; }

void Registers::setBC(std::uint16_t value) { BC.all = value; }

std::uint16_t Registers::getBC_alt() const { return BC_alt.all; }

void Registers::setBC_alt(std::uint16_t value) { BC_alt.all = value; }

std::uint8_t Registers::getB_alt() const { return BC_alt.bytes.high; }

void Registers::setB_alt(std::uint8_t b_alt) { BC_alt.bytes.high = b_alt; }

std::uint8_t Registers::getC() const { return BC.bytes.low; }

void Registers::setC(std::uint8_t c) { BC.bytes.low = c; }

bool Registers::getCFlag() { return (getF() & BOOST_BINARY(1)) == BOOST_BINARY(1); }

void Registers::setCFlag(bool flag) {
  if (flag) {
    AF.bytes.low |= BOOST_BINARY(1);
  } else {
    AF.bytes.low &= ~BOOST_BINARY(1);
  }
}

std::uint8_t Registers::getC_alt() const { return BC_alt.bytes.low; }

void Registers::setC_alt(std::uint8_t c_alt) { BC_alt.bytes.low = c_alt; }

std::uint8_t Registers::getD() const { return DE.bytes.high; }

void Registers::setD(std::uint8_t d) { this->DE.bytes.high = d; }

std::uint16_t Registers::getDE() const { return DE.all; }

void Registers::setDE(std::uint16_t value) { DE.all = value; }

std::uint16_t Registers::getDE_alt() const { return DE_alt.all; }

void Registers::setDE_alt(std::uint16_t value) { DE_alt.all = value; }

std::uint8_t Registers::getD_alt() const { return DE_alt.bytes.high; }

void Registers::setD_alt(std::uint8_t d_alt) { DE_alt.bytes.high = d_alt; }

std::uint8_t Registers::getE() const { return DE.bytes.low; }

void Registers::setE(std::uint8_t e) { DE.bytes.low = e; }

std::uint8_t Registers::getE_alt() const { return DE_alt.bytes.low; }

void Registers::setE_alt(std::uint8_t e_alt) { DE_alt.bytes.low = e_alt; }

std::uint8_t Registers::getF() const { return AF.bytes.low; }

void Registers::setF(std::uint8_t f) { AF.bytes.low = f; }

std::uint8_t Registers::getF_alt() const { return AF_alt.bytes.low; }

void Registers::setF_alt(std::uint8_t f_alt) { AF_alt.bytes.low = f_alt; }

std::uint8_t Registers::getH() const { return HL.bytes.high; }
void Registers::setH(std::uint8_t h) { HL.bytes.high = h; }

std::uint8_t Registers::getL() const { return HL.bytes.low; }
void Registers::setL(std::uint8_t l) { HL.bytes.low = l; }

std::uint16_t Registers::getHL() const { return HL.all; }

void Registers::setHL(std::uint16_t value) { HL.all = value; }

bool Registers::getHFlag() const { return (AF.bytes.low & BOOST_BINARY(10000)) == BOOST_BINARY(10000); }

void Registers::setHFlag(bool flag) {
  if (flag) {
    AF.bytes.low |= BOOST_BINARY(10000);
  } else {
    AF.bytes.low &= ~BOOST_BINARY(10000);
  }
}

std::uint16_t Registers::getHL_alt() const { return HL_alt.all; }

void Registers::setHL_alt(std::uint16_t value) { HL_alt.all = value; }

std::uint8_t Registers::getH_alt() const { return HL_alt.bytes.high; }

void Registers::setH_alt(std::uint8_t h_alt) { HL_alt.bytes.high = h_alt; }

std::uint8_t Registers::getI() const { return IR.bytes.high; }

void Registers::setI(std::uint8_t i) { IR.bytes.high = i; }

void Registers::setIM(std::uint8_t im) { _IM = im; }

std::uint8_t Registers::getIM() const { return _IM; }

std::uint16_t Registers::getIX() const { return IX.all; }

void Registers::setIX(std::uint16_t ix) { IX.all = ix; }

std::uint8_t Registers::getIXH() const { return IX.bytes.high; }

std::uint8_t Registers::getIXL() const { return IX.bytes.low; }

std::uint16_t Registers::getIY() const { return IY.all; }

void Registers::setIY(std::uint16_t iy) { IY.all = iy; }

std::uint8_t Registers::getIYH() const { return IY.bytes.high; }

std::uint8_t Registers::getIYL() const { return IY.bytes.low; }

std::uint8_t Registers::getL_alt() const { return HL_alt.bytes.low; }

void Registers::setL_alt(std::uint8_t l_alt) { HL_alt.bytes.low = l_alt; }

bool Registers::getNFlag() const { return (AF.bytes.low & BOOST_BINARY(10)) == BOOST_BINARY(10); }

void Registers::setNFlag(bool flag) {
  if (flag) {
    AF.bytes.low |= BOOST_BINARY(10);
  } else {
    AF.bytes.low &= ~BOOST_BINARY(10);
  }
}

bool Registers::getPVFlag() const { return (AF.bytes.low & BOOST_BINARY(100)) == BOOST_BINARY(100); }

void Registers::setPVFlag(bool flag) {
  if (flag) {
    AF.bytes.low |= BOOST_BINARY(100);
  } else {
    AF.bytes.low &= ~BOOST_BINARY(100);
  }
}

std::uint8_t Registers::getR() const { return IR.bytes.low; }

void Registers::setR(std::uint8_t r) { IR.bytes.low = r; }

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

std::uint16_t Registers::getSP() const { return SP.all; }

void Registers::setSP(std::uint16_t sp) { SP.all = sp; }

bool Registers::getSignFlag() const { return (AF.bytes.low & BOOST_BINARY(10000000)) == BOOST_BINARY(10000000); }

void Registers::setSignFlag(bool flag) {
  if (flag) {
    AF.bytes.low |= BOOST_BINARY(10000000);
  } else {
    AF.bytes.low &= ~BOOST_BINARY(10000000);
  }
}

bool Registers::getZeroFlag() const { return (AF.bytes.low & BOOST_BINARY(1000000)) == BOOST_BINARY(1000000); }

void Registers::setZeroFlag(bool flag) {
  if (flag) {
    AF.bytes.low |= BOOST_BINARY(1000000);
  } else {
    AF.bytes.low &= ~BOOST_BINARY(1000000);
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
    throw UnknownRegisterException();
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
    this->SP.bytes.high = highOrder;
    this->SP.bytes.low = lowOrder;
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
    this->IX.bytes.high = highOrder;
    this->IX.bytes.low = lowOrder;
    break;
  case RegisterPair::IY:
    this->IY.bytes.high = highOrder;
    this->IY.bytes.low = lowOrder;
    break;
  default:
    throw UnknownRegisterException();
  }
}

bool Registers::isIFF1() const { return IFF1; }

void Registers::setIFF1(bool iFF1) { IFF1 = iFF1; }

bool Registers::isIFF2() const { return IFF2; }

void Registers::setIFF2(bool iFF2) { IFF2 = iFF2; }

bool Registers::isHalted() const { return halted; }

void Registers::setHalted(bool val) { halted = val; }
