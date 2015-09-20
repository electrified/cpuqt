#include "RegisterPair.hpp"

std::string registers::toString(RegisterPair c) {
    switch(c) {
        case RegisterPair::unknown: return "unknown";
        case RegisterPair::AF: return "AF";
        case RegisterPair::AF_prime: return "AF'";
        case RegisterPair::BC: return "BC";
        case RegisterPair::BC_prime: return "BC'";
        case RegisterPair::DE: return "DE";
        case RegisterPair::DE_prime: return "DE'";
        case RegisterPair::HL: return "HL";
        case RegisterPair::HL_prime: return "HL'";
        case RegisterPair::IX: return "IX";
        case RegisterPair::IY: return "IY";
        case RegisterPair::PC: return "PC";
        case RegisterPair::SP: return "SP";
        default: return "UNKNOWN";
    }
}
