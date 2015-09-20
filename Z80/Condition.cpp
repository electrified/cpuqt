#include "Condition.hpp"

std::string registers::toString(Condition c) {
    switch(c) {
        case Condition::C: return "C";
        case Condition::M: return "M";
        case Condition::NC: return "NC";
        case Condition::NZ: return "NZ";
        case Condition::P: return "P";
        case Condition::PE: return "PE";
        case Condition::PO: return "PO";
        case Condition::Z: return "Z";
        default: return "UNKNOWN";
    }
}
