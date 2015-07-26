#pragma once
#include <exception>
#include <string>

class UnknownRegisterPairException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Unknown register pair used!";
    }
};

enum class RegisterPair {
    unknown,
    AF,
    AF_prime,
    BC,
    BC_prime,
    DE,
    DE_prime,
    HL,
    HL_prime,
    IX,
    IY,
    PC,
    SP,
};

namespace registers {
    std::string toString(RegisterPair c);
}