// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/Switch.java
#include <fstream>

#include "tools/Switch.hpp"
#include "tools/FinalNode.hpp"

Switch::Switch(int32_t* level)
{
    this->level = level;
}

/**
 *
 */
void Switch::write(std::ofstream* writer)
{
    writer << u"// get opcode";
    writer << u"currentInstruction[" <<  this->level << "] = getNextByte();\n";
    writer << u"switch (currentInstruction["<< this->level << "]) {\n";
    for (auto FinalNode& node : this->nodes->values() ) {
            c->write(writer);
    }
    writer << u"}";
}

