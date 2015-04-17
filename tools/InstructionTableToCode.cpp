#include <tools/InstructionTableToCode.hpp>

#include "tools/Case.hpp"
#include "tools/FinalNode.hpp"
#include"tools/GetData.hpp"

#include<string>
#include<fstream>
#include<vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

int main(int argc, char** argv)
{
      InstructionTableToCode parser;

    parser.main();
    
    return 0;
}



void InstructionTableToCode::main() {

    auto instructions = this->parse();
    auto s = this->groupOpcodes(&instructions);
    this->writeCode(s);

}

InstructionTableToCode::InstructionTableToCode() {
  
}

std::vector<Instruction> InstructionTableToCode::parse()
{
    std::vector<Instruction> theInstructions;
    string line;
    ifstream file ("z80sean.txt");
    if (file.is_open()) {
        for (int i = 0; i < 33; i++) {
            getline (file,line);
            cout <<"Skipping line" << endl;
        }

        while ( getline (file,line) )
        {
	    std::vector<std::string> split;
	    boost::split(split, line, boost::is_any_of("\t ")); //"\\s{2,}|\\t+"
	  
// 	    if(split.size() < 2 || split.at(1).trim()->endsWith("*")) {
// 	      continue;
// 	    }
	    
            cout << line << '\n';
        }
        file.close();
    }
//     string* line;
//     while ((line = npc(reader)->readLine()) != nullptr) {
//         auto split = npc(line)->split(u"\\s{2,}|\\t+"_j);
//         if(npc(split)->length < 2 || npc(npc((*split)[int32_t(1)])->trim())->endsWith(u"*"_j)) {
//             continue;
//         }
//         split->set(int32_t(1), npc(npc((*split)[int32_t(1)])->trim())->replace(static_cast< ::java::lang::CharSequence* >(u"*"_j), static_cast< ::java::lang::CharSequence* >(u""_j)));
//         auto instruction = new Instruction();
//         npc(instruction)->setMnemonic(npc((*split)[int32_t(1)])->trim());
//         auto pattern = ::java::util::regex::Pattern::compile(u"(\\w{2})|\\b(\\w+)\\b"_j);
//         auto matcher = npc(pattern)->matcher((*split)[int32_t(0)]);
//         ::java::util::List* opcodeparts = new ::java::util::ArrayList();
//         while (npc(matcher)->find()) {
//             npc(opcodeparts)->add(static_cast< ::java::lang::Object* >(npc(matcher)->group()));
//         }
//         ::java::util::List* intOpcodes = new ::java::util::ArrayList();
//         for (auto _i = npc(opcodeparts)->iterator(); _i->hasNext(); ) {
//             ::java::lang::String* op = java_cast< ::java::lang::String* >(_i->next());
//             {
//                 if(npc(op)->equals(static_cast< ::java::lang::Object* >(u"n"_j)) || npc(op)->equals(static_cast< ::java::lang::Object* >(u"d"_j)) || npc(op)->equals(static_cast< ::java::lang::Object* >(u"e"_j))) {
//                     npc(intOpcodes)->add(::java::lang::Integer::valueOf(Instruction::N));
//                 } else {
//                     npc(intOpcodes)->add(::java::lang::Integer::valueOf(::java::lang::Integer::parseUnsignedInt(op, 16)));
//                 }
//             }
//         }
//         npc(instruction)->setOpcodes(java_cast< ::java::lang::IntegerArray* >(npc(intOpcodes)->toArray_(static_cast< ::java::lang::ObjectArray* >(new ::java::lang::IntegerArray(npc(intOpcodes)->size())))));
//         npc(::java::lang::System::out())->println(static_cast< ::java::lang::Object* >(instruction));
//         npc(theInstructions)->add(static_cast< ::java::lang::Object* >(instruction));
//     }
// }
// catch (::java::io::IOException* x) {
//     npc(x)->printStackTrace();
// }
// ::java::util::Collections::sort(theInstructions);
    return theInstructions;
}

void InstructionTableToCode::writeCode(
    Switch* rootSwitch)
{
    string javaPath = "InstructionDecoderGenerated.cpp";
//     if (::java::nio::file::Files::exists(javaPath,
//                                          new ::java::nio::file::LinkOptionArray())) {
//         ::java::nio::file::Files::delete_ (javaPath);
//     }
    ofstream writer (javaPath);
    if (writer.is_open())
    {
        writeHeader(&writer);
        rootSwitch->write(&writer);
        writeFooter(&writer);
    }

}

void InstructionTableToCode::writeHeader(
    std::ofstream* writer)
{
           *writer << "public class InstructionDecoderGenerated extends BaseInstructionDecoder {\n";
          *writer << u"    public int[] decode() {\n";
           *writer << u"int[] currentInstruction = new int[4];\n";
}

       void InstructionTableToCode::writeFooter(
           std::ofstream* writer)
{
    *writer << u"currentInstruction = ArrayUtils.subarray(currentInstruction, 0, instructionByteCount);\n";
    *writer << u"instructionByteCount = 0;\n";
    *writer << u"return currentInstruction;\n";
    *writer << u"    }\n";
    *writer << u"}\n";
}

Switch* InstructionTableToCode::groupOpcodes(std::vector<Instruction>* instructions) {
    auto rootLevel = new Switch(0);

//         for (auto _i = npc(instructions)->iterator(); _i->hasNext();) {
//             Instruction* instruction = java_cast<Instruction*>(_i->next());
//             {
//                 ::java::lang::Integer* depth = ::java::lang::Integer::valueOf(int32_t(0));
//                 FinalNode* currentCase = nullptr;
//                 for (auto opcode : *npc(npc(instruction)->getOpcodes())) {
//                     if ((npc(opcode))->intValue() == Instruction::N) {
//                         if (!npc(npc(currentCase)->getDatas)->containsKey(depth)) {
//                             auto data = new GetData(depth);
//                             npc(npc(currentCase)->getDatas)->put(depth, data);
//                         }
//                     } else {
//                         if (currentCase == nullptr) {
//                             currentCase = java_cast<FinalNode*>(
//                                               npc(npc(rootLevel)->nodes)->get(opcode));
//                             if (currentCase == nullptr) {
//                                 currentCase = new Case(opcode);
//                                 npc(npc(rootLevel)->nodes)->put(opcode, currentCase);
//                             }
//                         } else {
//                             if (npc(currentCase)->theSwitch == nullptr) {
//                                 npc(currentCase)->theSwitch = new Switch(depth);
//                             }
//                             if (npc(npc(npc(currentCase)->theSwitch)->nodes)->containsKey(
//                             opcode)) {
//                                 currentCase = java_cast<FinalNode*>(
//                                                   npc(npc(npc(currentCase)->theSwitch)->nodes)->get(
//                                                       opcode));
//                             } else {
//                                 auto c = new Case(opcode);
//                                 npc(npc(npc(currentCase)->theSwitch)->nodes)->put(opcode, c);
//                                 currentCase = c;
//                             }
//                         }
//                     }
//                     if (depth == instruction->getIndexOfLastOpcode()) {
//                         currentCase->instruction = instruction;
//                     }
//                     depth->intValue()++;
//                 }
//             }
//         }
    return rootLevel;
}
