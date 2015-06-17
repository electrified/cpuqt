#include <fstream>
#include<boost/format.hpp>

#include "tools/Case.hpp"

//#include <tools/FinalNode.hpp>
//#include <tools/Instruction.hpp>
//#include <tools/Switch.hpp>
#include <tools/GetData.hpp>

Case::Case()
{
    this->opcode = -1;
}

Case::Case(int opcode)
{
    this->opcode = opcode;
}

void Case::write(std::ofstream* writer)
{
    *writer << boost::format("case 0x%02X:") % this->opcode << endl;
    for (auto const &node : this->getDatas ) {
            node.second->write(writer);
    }
    if(this->instruction.getOpcodes().size() > 0) {
        instruction.write(writer);
    }
    if(this->theSwitch.cases.size() > 0) {
        this->theSwitch.write(writer);
    }
   *writer << "break;" << endl;
}

