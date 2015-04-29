#include <tools/InstructionTableToCode.hpp>

#include "tools/Case.hpp"
#include "tools/FinalNode.hpp"
#include "tools/GetData.hpp"
// #include "tools/Instruction.hpp"

#include<string>
#include<fstream>
#include<vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>

using namespace std;

int main(int argc, char** argv)
{
    InstructionTableToCode parser;
    parser.main();
    return 0;
}



void InstructionTableToCode::main() {
    auto instructions = this->parse();
    cout << "grouping" <<endl;
    auto s = this->groupOpcodes(&instructions);
    cout << "writing code" <<endl;
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
//             cout <<"Skipping line" << endl;
        }

        while ( getline (file,line) )
        {
            std::vector<std::string> split;
            boost::split_regex(split, line, boost::regex("\\s{2,}|\\t+"));

            if(split.size() < 2) {
                continue;
            }

            string mnemonic = split[1];

            boost::trim(mnemonic);
            bool endsWith = boost::ends_with(mnemonic, "*");
            
	    if(endsWith) {
                continue;
            }

//             cout << "full line: \"" << line<< "\" opcode:\"" << split[0] << "\"" << endl;
	    
            auto instruction = new Instruction();

            instruction->setMnemonic(mnemonic);
            // 2 letter word or word boundary, word, word boundary
            auto pattern = boost::regex("([0-9A-F]{2})|([dne])");
//             boost::cmatch matches;

            boost::sregex_iterator res(split[0].begin(),split[0].end(),pattern);
            boost::sregex_iterator end;
            vector<int> intOpcodes;

            for (; res != end; ++res) {
//                 std::cout << (*res)[0] << std::endl;
                string match = (*res)[0];

                if (match == "n" || match == "d" || match == "e") {
                    intOpcodes.push_back(-1);
                } else {
                    intOpcodes.push_back((int)stoul(match,nullptr, 16));
                }
            }
            instruction->setOpcodes(intOpcodes);
            theInstructions.push_back(*instruction);
        }
        file.close();
    }
// cout << "Sorting " << endl;
    std::sort(theInstructions.begin(), theInstructions.end());
    return theInstructions;
}

void InstructionTableToCode::writeCode(
    Switch* rootSwitch)
{
    string javaPath = "InstructionDecoderGenerated.cpp";
    if (boost::filesystem::exists(javaPath)) {
        boost::filesystem::remove(javaPath);
    }
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
        *writer << "#include \"Z80/InstructionDecoderGenerated.h\"" << endl;
    *writer << "#include \"Z80/MemoryAddress.h\"" << endl;
    *writer << "#include \"Z80/Register.hpp\"" << endl;
    *writer << "#include \"Z80/RegisterPair.hpp\"" << endl;
    *writer << "#include \"Z80/Condition.hpp\"" << endl;

    *writer << "void InstructionDecoderGenerated::decode() {" << endl;
    *writer << "int currentInstruction[4];" << endl;
}

void InstructionTableToCode::writeFooter(
    std::ofstream* writer)
{
    *writer << "currentInstruction = ArrayUtils.subarray(currentInstruction, 0, instructionByteCount);" << endl;
    *writer << "instructionByteCount = 0;" << endl;
    *writer << "//return currentInstruction;" << endl;
    *writer << "}\n";
}

Switch* InstructionTableToCode::groupOpcodes(std::vector<Instruction>* instructions) {
//     cout << "grouping opcodes" << endl;
    Switch* rootLevel = new Switch(0);

    for (auto instruction : *instructions) {
        cout << instruction.getMnemonic() << endl;
        uint8_t depth =0;
        FinalNode* currentCase = nullptr;
        for (uint8_t opcode : instruction.getOpcodes()) {        
//             cout << to_string(opcode) << endl;
            if (opcode < 0) {
                auto dataSearch = currentCase->getDatas.find(depth);
                if (dataSearch == currentCase->getDatas.end()) {
                    auto data = new GetData(depth);
                    currentCase->getDatas.insert(make_pair(depth,data));
                }
            } else {
                if (currentCase == nullptr) {
                    auto caseSearch = rootLevel->cases.find(opcode);
                    if (caseSearch != rootLevel->cases.end()) {
                        currentCase = caseSearch->second;
                    } else {
                        currentCase = new Case(opcode);
                        rootLevel->cases.insert(make_pair(opcode, (Case*)currentCase));
                    }
                } else {
                    if (currentCase->theSwitch.level < 0) {
                        currentCase->theSwitch.level = depth;
                    }
                    auto caseSearch = currentCase->theSwitch.cases.find(opcode);
                    if (caseSearch != currentCase->theSwitch.cases.end()) {
                        currentCase = caseSearch->second;
                    } else {
                        auto c = new Case(opcode);
                        currentCase->theSwitch.cases.insert(make_pair(opcode, c));
                        currentCase = c;
                    }
                }
            }

            if (depth == instruction.getIndexOfLastOpcode()) {
                cout << "hello" <<endl;
                currentCase->instruction = instruction;                
                cout << "hello2" <<endl;
            }
            depth++;
        }
    }
    cout << "returning cropuped" <<endl;
    return rootLevel;
}
