#pragma once

#include "Switch.hpp"
#include "Instruction.hpp"

class InstructionTableToCode {
public:
  void main();

public:
  InstructionTableToCode();
  std::vector<Instruction> parse();
  Switch *groupOpcodes(std::vector<Instruction> *instructions);

private:
  void writeCode(Switch *rootSwitch);
  void writeHeader(std::ofstream *writer);
  void writeFooter(std::ofstream *writer);
};
