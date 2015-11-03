#include "script_host.h"

#include <iostream>

ScriptHost::ScriptHost(BadgerComputer* computer) {
    this->computer = computer;
    sel::State state{true};
    
    state["em"].SetObj(*this,
        "break", &ScriptHost::addBreakpoint,
        "step", &ScriptHost::step);
}

void ScriptHost::executeScript(std::string path) {
     state.Load(path);
}

void ScriptHost::runCommand(std::string command) {
    state(command.c_str());
}

void ScriptHost::addBreakpoint(int memoryAddress) {
    computer->addBreakpoint(memoryAddress);
}

void ScriptHost::step() {
    computer->step();
}
