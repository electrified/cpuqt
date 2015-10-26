#ifndef SPECTRUMIO_H
#define SPECTRUMIO_H


#include "Z80/IO.h"

class SpectrumIO  : public IO
{
public:
    SpectrumIO();
    ~SpectrumIO();
    std::uint8_t read(std::uint16_t address);
    void write(std::uint16_t address, std::uint8_t value);
};

#endif // SPECTRUMIO_H
