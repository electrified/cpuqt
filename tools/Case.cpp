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
   /* writer << u"case 0x%02X:\n" << this->opcode;
    for (auto FinalNode& node : this->nodes->values() ) {
            c->write(writer);
    }*/
    if(this->instruction != nullptr) {
        instruction->write(writer);
    }
    if(this->theSwitch != nullptr) {
        this->theSwitch->write(writer);
    }
//    writer << u"break;\n";
}

