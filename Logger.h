#ifndef LOGGER_H
#define LOGGER_H

#include <string>

enum class LogLevel {
    debug,
    info,
    error
};

class Logger
{
    const static LogLevel loglevel = LogLevel::info;
public:
    Logger();
    ~Logger();
    void debug(const std::string& toLog);
    void info(const std::string& toLog);
};

#endif // LOGGER_H
