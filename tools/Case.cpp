// Generated from /org.maidavale.cpu/src/main/java/Case.java

using namespace std;
#include <fstream>

#include "tools/Case.hpp"

#include <tools/FinalNode.hpp>
#include <tools/Instruction.hpp>
#include <tools/Switch.hpp>

Case::Case(uint8_t opcode)
{
    this->opcode = opcode;
}

void Case::write(std::ofstream* writer)
{
    *writer << "case 0x%02X:\n" << this->opcode;
    for (auto const &node : this->nodes ) {
            node.second->write(writer);
    }
    if(this->instruction != nullptr) {
        instruction->write(writer);
    }
    if(this->theSwitch != nullptr) {
        this->theSwitch->write(writer);
    }
   *writer << "break;\n";
}

