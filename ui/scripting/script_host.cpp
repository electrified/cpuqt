#include "script_host.h"
#include "computer/utils.h"

ScriptHost::ScriptHost(BadgerComputer *computer) {
  this->computer = computer;

  state["em"].SetObj(*this, "brk", &ScriptHost::addBreakpoint, 
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

void ScriptHost::executeScript(std::string path) { state.Load(path); }

void ScriptHost::runCommand(std::string command) {
  spdlog::get("console")->debug("Executing " + command);
  state(command.c_str());
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
  auto data = ReadAllBytes(path);

  loadIntoMemory(data, computer->memory, 0);
}

void ScriptHost::loadSnapshot(std::string path) {
  auto data = ReadAllBytes(path);

  loadZ80Snapshot(data, computer->memory, computer->processor->getRegisters());
}

void ScriptHost::run() {
  // need to move timer stuff out of main_window
}

void ScriptHost::reset() {
  computer->reset();
}
