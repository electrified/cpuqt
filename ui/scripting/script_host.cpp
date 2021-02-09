#include "script_host.h"

#include <utility>
#include "computer/utils.h"

ScriptHost::ScriptHost(BadgerComputer *computer) {
  this->computer = computer;
  lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);
  lua["em"] = lua.create_table_with("brk", &ScriptHost::addBreakpoint, 
                     "step", &ScriptHost::step, 
                     "del", &ScriptHost::removeBreakpoint, 
                     "list", &ScriptHost::listBreakpoints, 
                     "peek", &ScriptHost::peek,
                     "poke", &ScriptHost::poke,
                     "loadrom", &ScriptHost::loadRom,
                     "loadsnap", &ScriptHost::loadSnapshot,
                     "run", &ScriptHost::run
                    );
}

void ScriptHost::executeScript(const std::string& path) { lua.script_file(path); }

void ScriptHost::runCommand(const std::string& command) {
  spdlog::get("console")->debug("Executing " + command);
  lua.script(command.c_str());
}

void ScriptHost::addBreakpoint(int memoryAddress) {
  spdlog::get("console")->debug("Adding breakpoint 0x{0:x}", memoryAddress);
  computer->addBreakpoint(memoryAddress);
}

void ScriptHost::removeBreakpoint(int memoryAddress) { computer->removeBreakpoint(memoryAddress); }

void ScriptHost::listBreakpoints() { computer->listBreakpoints(); }

void ScriptHost::poke(int memoryAddress, int value) { computer->memory->write(memoryAddress, value); }

int ScriptHost::peek(int memoryAddress) { return computer->memory->read(memoryAddress); }

void ScriptHost::step() { computer->step(); }

void ScriptHost::loadRom(std::string path) {
  auto data = ReadAllBytes(std::move(path));

  loadIntoMemory(data, computer->memory, 0);
}

void ScriptHost::loadSnapshot(std::string path) {
  auto data = ReadAllBytes(std::move(path));

  loadZ80Snapshot(data, computer->memory, computer->processor->getRegisters());
}

void ScriptHost::run() {
  computer->run();
}

void ScriptHost::reset() {
  computer->reset();
}
ScriptHost::~ScriptHost() = default;
