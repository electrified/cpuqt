#include <fstream>

#include "tools/Switch.hpp"
#include "tools/Case.hpp"

Switch::Switch() {
    this->level = -1;
}

Switch::Switch(int level)
{
    this->level = level;
}

void Switch::write(std::ofstream* writer)
{
    *writer << "// get opcode"<< endl;
    *writer << "currentInstruction[" <<  this->level << "] = memory.read(++pc);"<< endl;
    *writer << "switch (currentInstruction["<< this->level << "]) {"<< endl;
    for (auto node : this->cases ) {
        node.second->write(writer);
    }
    *writer << "}"<< endl;
}

