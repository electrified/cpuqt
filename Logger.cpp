#include "Logger.h"
#include <iostream>
Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::debug(const std::string toLog)
{
//    if (loglevel == LogLevel::debug) {
//        std::cout << "DEBUG: " << toLog << std::endl;
//    }
}

void Logger::info(const std::string toLog)
{
    if (loglevel == LogLevel::info || loglevel == LogLevel::debug) {
        std::cout << "INFO: " << toLog << std::endl;
    }
}
