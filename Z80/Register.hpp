#pragma once

#include <exception>

class UnknownRegisterException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Unknown register pair used!";
    }
};

enum class Rgstr {
    unknown,
    A,
    B,
    C,
    D,
    E,
    H,
    I,
    IXH,
    IXL,
    IYH,
    IYL,
    L,
    R,
};
