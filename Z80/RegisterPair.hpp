#pragma once
#include <exception>

class UnknownRegisterPairException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "My exception happened";
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
