#include "badgerio.h"
#include <boost/utility/binary.hpp>

BadgerIO::BadgerIO()
{

}

std::uint8_t BadgerIO::read(std::uint16_t address) {
    int returnValue = 0;
    if ((address & UART_PORT) == UART_PORT) {
//             logger.debug("UART read!!!!");
        switch (address) {
        case BadgerIO::UART_DLL: //case UART_PORT:
//                    returnValue = DLL;
            returnValue = key;
            break;
        case BadgerIO::UART_DLM:
            returnValue = DLM;
            break;
        case BadgerIO::UART_FCR:
            returnValue = FCR;
            break;
//				case UART_IER:
//					break;
        case BadgerIO::UART_LCR:
            returnValue = LCR;
            break;
        case BadgerIO::UART_MCR:
            returnValue = MCR;
            break;
        case BadgerIO::UART_LSR:
            key = 0;
            if (keyboardBuffer.size() > 1) {
                key = keyboardBuffer.at(0);
                keyboardBuffer.erase(keyboardBuffer.begin());
            }

            returnValue = BOOST_BINARY(1000000) | (key != 0 ? 1 : 0); //transmitted!
            break;
        }
    } else {
        returnValue = memory[address];
    }
//      logger.debug(String.format("read address: 0x%s value: 0x%s 0b%s", Integer.toHexString(address), Integer.toHexString(returnValue), Integer.toBinaryString(returnValue)));
    return returnValue;
}

void BadgerIO::write(std::uint16_t address, std::uint8_t value) {
//         logger.debug("write address: 0x" + Integer.toHexString(address));
    if ((address & UART_PORT) == UART_PORT) {
//             logger.debug("UART write!!!!");
        switch (address) {
        case UART_DLL:
            DLL = value;
//                     screenOutputPrintStream.write(value);
            emit consoleTextOutput(value);
            break;
        case UART_DLM:
            DLM = value;
            break;
        case UART_FCR:
            FCR = value;
            break;
//				case UART_IER:
//					break;
        case UART_LCR:
            LCR = value;
            break;
        case UART_MCR:
            MCR = value;
            break;
        case UART_LSR:
            break;
        }
    }
    memory[address] = value;
}
