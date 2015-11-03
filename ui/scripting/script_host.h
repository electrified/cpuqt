#pragma once

#include <string>
#include "ui/badgercomputer.h"
#include "selene.h"

class ScriptHost {
    sel::State state{true};
    BadgerComputer* computer;
public:
    ScriptHost(BadgerComputer* computer);
    ~ScriptHost();
    void executeScript(std::string path);
    void runCommand(std::string command);
    void addBreakpoint(int memoryAddress);
    void step();
};
