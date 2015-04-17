// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/InstructionTableToCode.java

#pragma once

#include"tools/Switch.hpp"
#include"tools/Instruction.hpp"

class InstructionTableToCode
{

public:
    void main();

public:
    InstructionTableToCode();
    std::vector<Instruction> parse();
    Switch* groupOpcodes(std::vector<Instruction>* instructions);
private:
    void writeCode(Switch* rootSwitch);
    void writeHeader(std::ofstream* writer);
    void writeFooter(std::ofstream* writer);
};
