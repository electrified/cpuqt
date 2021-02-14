#include "script_host.h"

#include "computer/utils.h"
#include "spdlog/spdlog.h"
#include <utility>

ScriptHost::ScriptHost(BadgerComputer *computer) {
  this->computer = computer;
  lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);
  lua.set_function("brk", &ScriptHost::addBreakpoint, this);
  lua.set_function("step", &ScriptHost::step, this);
  lua.set_function("del", &ScriptHost::removeBreakpoint, this);
  lua.set_function("list", &ScriptHost::listBreakpoints, this);
  lua.set_function("peek", &ScriptHost::peek, this);
  lua.set_function("poke", &ScriptHost::poke, this);
  lua.set_function("loadrom", &ScriptHost::loadRom, this);
  lua.set_function("loadsnap", &ScriptHost::loadSnapshot, this);
  lua.set_function("run", &ScriptHost::run, this);
}

void ScriptHost::executeScript(const std::string &path) { lua.script_file(path); }

void ScriptHost::runCommand(const std::string &command) {
  try {
    spdlog::get("general")->debug("Executing " + command);
    lua.script(command.c_str());
  } catch (sol::error &error) {
    cout << error.what();
  }
}

void ScriptHost::addBreakpoint(int memoryAddress) {
  spdlog::get("general")->debug("Adding breakpoint 0x{0:x}", memoryAddress);
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

void ScriptHost::run() { computer->run(); }

void ScriptHost::reset() { computer->reset(); }
ScriptHost::~ScriptHost() = default;
