#include "script_host.h"

#include <iostream>
#include "selene.h"
#include "spdlog/spdlog.h"

sel::State state{true};
/*
auto print = [](std::string str) {
                spdlog::get("console_log")->info(str);
            };
            this->state["print"] = print;*/

// print(string.format("%x",em.peek(0)))
// em.poke(0, 255)
// print(string.format("%x",em.peek(0)))

ScriptHost::ScriptHost() {
}

ScriptHost::ScriptHost(BadgerComputer* computer) {
    this->computer = computer;
    
    state["em"].SetObj(*this,
        "break", &ScriptHost::addBreakpoint,
        "step", &ScriptHost::step,
        "del", &ScriptHost::removeBreakpoint,
        "list", &ScriptHost::listBreakpoints,
        "peek", &ScriptHost::peek,
        "poke", &ScriptHost::poke);
}

void ScriptHost::executeScript(std::string path) {
     state.Load(path);
}

void ScriptHost::runCommand(std::string command) {
    spdlog::get("console")->debug("Executing " + command);
    state(command.c_str());
}

void ScriptHost::addBreakpoint(int memoryAddress) {
    spdlog::get("console")->debug("Adding breakpoint 0x{0:x}", memoryAddress);
    computer->addBreakpoint(memoryAddress);
}

void ScriptHost::removeBreakpoint(int memoryAddress) {
    computer->removeBreakpoint(memoryAddress);
}

void ScriptHost::listBreakpoints() {
    computer->listBreakpoints();
}

void ScriptHost::poke(int memoryAddress, int value) {
    computer->memory->write(memoryAddress, value);
}

int ScriptHost::peek(int memoryAddress) {
    return computer->memory->read(memoryAddress);
}

void ScriptHost::step() {
    computer->step();
}
