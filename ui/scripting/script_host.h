#ifndef SCRIPT_HOST_H
#define SCRIPT_HOST_H

#include <string>
#include "Logger.h"
#include "../badgercomputer.h"

class ScriptHost {
    Logger l;
    BadgerComputer* computer;
public:
    ScriptHost();
    ScriptHost(BadgerComputer* computer);
    ~ScriptHost();
    void executeScript(std::string path);
    void runCommand(std::string command);
    void addBreakpoint(int memoryAddress);
    void removeBreakpoint(int memoryAddress);
    void listBreakpoints();
    void poke(int memoryAddress, int value);
    int peek(int memoryAddress);
    void step();
};
#endif