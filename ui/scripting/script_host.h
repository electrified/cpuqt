#pragma once

#include <string>
#include "../badgercomputer.h"

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class ScriptHost {
private:
  sol::state lua;
  BadgerComputer *computer;

public:
  explicit ScriptHost(BadgerComputer *computer);
  ~ScriptHost();
  void executeScript(const std::string& path);
  void runCommand(const std::string& command);
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
