// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/InstructionTableToCode.java

#pragma once

#include<string>
#include<fstream>
#include<vector>

#include"tools/Switch.hpp"
#include"tools/Instruction.hpp"

class InstructionTableToCode
{

public:
    static void main(std::vector<string>* args);
protected:
    void ctor();

public:
    virtual std::vector<Instruction> parse();

private:
    void writeCode(Switch* rootSwitch);
    void writeHeader(std::ofstream* writer);
    void writeFooter(std::ofstream* writer);

public:
    virtual Switch* groupOpcodes(std::vector<Instruction>* instructions);
public:
    InstructionTableToCode();
};
