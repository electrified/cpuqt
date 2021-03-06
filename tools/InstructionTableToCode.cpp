#include "InstructionTableToCode.hpp"

#include "Case.hpp"
#include "GetData.hpp"

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char **argv) {
  std::cout << "Instruction decoder generator v2" << std::endl;
  InstructionTableToCode parser;
  parser.main();
  return 0;
}

void InstructionTableToCode::main() {
  auto instructions = this->parse();
  std::cout << "grouping" << std::endl;
  auto s = this->groupOpcodes(&instructions);
  std::cout << "writing code" << std::endl;
  this->writeCode(s);
}

InstructionTableToCode::InstructionTableToCode() {}

std::vector<Instruction> InstructionTableToCode::parse() {
  std::vector<Instruction> theInstructions;
  std::string line;
  ifstream file("z80sean.txt");
  if (file.is_open()) {
    for (int i = 0; i < 33; i++) {
      getline(file, line);
      //             cout <<"Skipping line" << endl;
    }

    while (getline(file, line)) {
      std::vector<std::string> split;
      boost::split_regex(split, line, boost::regex("\\s{2,}|\\t+"));

      if (split.size() < 2) {
        continue;
      }

      string mnemonic = split[1];

      boost::trim(mnemonic);
      bool endsWith = boost::ends_with(mnemonic, "*");

      if (endsWith) {
        continue;
      }

      //             cout << "full line: \"" << line<< "\" opcode:\"" << split[0] << "\"" << endl;

      auto instruction = new Instruction();

      instruction->setMnemonic(mnemonic);
      // 2 letter word or word boundary, word, word boundary
      auto pattern = boost::regex("([0-9A-F]{2})|([dne])");
      //             boost::cmatch matches;

      boost::sregex_iterator res(split[0].begin(), split[0].end(), pattern);
      boost::sregex_iterator end;
      vector<int> intOpcodes;

      for (; res != end; ++res) {
        //                 std::cout << (*res)[0] << std::endl;
        string match = (*res)[0];

        if (match == "n" || match == "d" || match == "e") {
          intOpcodes.push_back(-1);
        } else {
          intOpcodes.push_back((int)stoul(match, nullptr, 16));
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

void InstructionTableToCode::writeCode(Switch *rootSwitch) {
  string javaPath = "baseprocessordecoder.cpp";
  if (boost::filesystem::exists(javaPath)) {
    boost::filesystem::remove(javaPath);
  }
  ofstream writer(javaPath);
  if (writer.is_open()) {
    writeHeader(&writer);
    rootSwitch->write(&writer);
    writeFooter(&writer);
  }
}

void InstructionTableToCode::writeHeader(std::ofstream *writer) {
  *writer << "#include \"Z80/baseprocessordecoder.h\"" << endl;

  *writer << "void BaseProcessorDecoder::decode() {" << endl;
  *writer << "std::uint8_t currentInstruction[4];" << endl;
}

void InstructionTableToCode::writeFooter(std::ofstream *writer) {
  *writer << "//currentInstruction = ArrayUtils.subarray(currentInstruction, 0, instructionByteCount);" << endl;
  *writer << "instructionByteCount = 0;" << endl;
  *writer << "//return currentInstruction;" << endl;
  *writer << "}\n";
}

Switch *InstructionTableToCode::groupOpcodes(std::vector<Instruction> *instructions) {
  //     cout << "grouping opcodes" << endl;
  Switch *rootLevel = new Switch(0);

  for (auto instruction : *instructions) {
    cout << instruction.getMnemonic() << endl;
    uint8_t depth = 0;
    FinalNode *currentNode = nullptr;
    for (int opcode : instruction.getOpcodes()) {
      //             cout << to_string(opcode) << endl;
      if (opcode < 0) {
        auto dataSearch = currentNode->getDatas.find(depth);
        if (dataSearch == currentNode->getDatas.end()) {
          auto data = new GetData(depth);
          currentNode->getDatas.insert(make_pair(depth, data));
        }
      } else {
        if (currentNode == nullptr) {
          auto caseSearch = rootLevel->cases.find(opcode);
          if (caseSearch != rootLevel->cases.end()) {
            currentNode = caseSearch->second;
          } else {
            currentNode = new Case(opcode);
            rootLevel->cases.insert(make_pair(opcode, (Case *)currentNode));
          }
        } else {
          if (currentNode->theSwitch.level < 0) {
            currentNode->theSwitch.level = depth;
          }
          auto caseSearch = currentNode->theSwitch.cases.find(opcode);
          if (caseSearch != currentNode->theSwitch.cases.end()) {
            currentNode = caseSearch->second;
          } else {
            auto c = new Case(opcode);
            currentNode->theSwitch.cases.insert(make_pair(opcode, c));
            currentNode = c;
          }
        }
      }

      if (depth == instruction.getIndexOfLastOpcode()) {
        currentNode->instruction = instruction;
      }
      depth++;
    }
  }
  cout << "returning grouped" << endl;
  return rootLevel;
}
