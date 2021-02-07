#pragma once

#include <string>
#include "../badgercomputer.h"
#include "spdlog/spdlog.h"
#include "sol/sol.hpp"

class ScriptHost {
private:
  sol::state lua;
  BadgerComputer *computer;

public:
  ScriptHost(BadgerComputer *computer);
  ~ScriptHost();
  void executeScript(std::string path);
  void runCommand(std::string command);
  void addBreakpoint(int memoryAddress);
  void removeBreakpoint(int memoryAddress);
  void listBreakpoints();
  void poke(int memoryAddress, int value);
  int peek(int memoryAddress);
  void step();
  void loadRom(std::string path);
  void loadSnapshot(std::string path);
  void run();
  void reset();
};
