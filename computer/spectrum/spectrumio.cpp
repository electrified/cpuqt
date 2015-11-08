#include "spectrumio.h"

#include "spdlog/spdlog.h"

SpectrumIO::SpectrumIO()
{   
    inputKeys.push_back(0xFEFE);
}

SpectrumIO::~SpectrumIO()
{

}

/*
 * The contents of register C are placed on the bottom half (A0 through A7) of
the address bus to select the I/O device at one of 256 possible ports. The
contents of Register B are placed on the top half (A8 through A15) of the
address bus at this time.
*/
std::uint8_t SpectrumIO::read(std::uint16_t address) {
    spdlog::get("console")->debug("address read {0:x}", address);
    if ((address & 0xFE) == 0xFE) {
        uint8_t lineScanned = address >> 8;
        
        spdlog::get("console")->debug("scanning line {0:x}", lineScanned);
        
        if (inputKeys.size() > 0) {
            uint16_t key = inputKeys.front();
            
            if (key >> 8 == lineScanned) {
//                 inputKeys.erase(inputKeys.begin());
                return key & 0xff;
            }
        }
    }
    return 0;
}

void SpectrumIO::write(std::uint16_t address, std::uint8_t value) {
    
}