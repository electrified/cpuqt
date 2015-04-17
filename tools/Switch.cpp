// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/Switch.java
#include <fstream>

#include "tools/Switch.hpp"
#include "tools/FinalNode.hpp"

Switch::Switch(int32_t level)
{
    this->level = level;
}

/**
 *
 */
void Switch::write(std::ofstream* writer)
{
    *writer << "// get opcode";
    *writer << "currentInstruction[" <<  this->level << "] = getNextByte();\n";
    *writer << "switch (currentInstruction["<< this->level << "]) {\n";
    for (auto node : this->nodes ) {
            node.second->write(writer);
    }
    *writer << "}";
}

