#include "Instruction.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>

using namespace std;

const string Instruction::useCondition[useConditionCount] = {"JP", "RET", "CALL", "JR"};

const string Instruction::registers[registerCount] = {"A",   "B",   "C",   "D",   "E", "H", "I",
                                                      "IXH", "IXL", "IYH", "IYL", "L", "R"};

const string Instruction::registerpairs[registerPairCount] = {"AF", "AF_prime", "BC", "BC_prime", "DE", "DE_prime",
                                                              "HL", "HL_prime", "IX", "IY",       "PC", "SP"};

const string Instruction::conditions[conditionCount] = {
    "C", "M", "NC", "NZ", "P", "PE", "PO", "Z",
};

Instruction::Instruction() {}

unsigned long long Instruction::getScore() const {
  cout << getMnemonic() << endl;
  string thisScore = "";
  for (unsigned long i = 0; i < 4; i++) {
    //         cout << "loopinng " << thisScore <<endl;
    if (i < getOpcodes().size() && (getOpcodes().at(i) >= 0)) {
      thisScore = thisScore + to_string(getOpcodes().at(i));
    } else {
      thisScore = thisScore + "000";
    }
  }
  //     cout << "stringscore " << thisScore <<endl;
  return stoull(thisScore);
}

string Instruction::getMnemonic() const { return mnemonic; }

void Instruction::setMnemonic(string mnemonic) { this->mnemonic = mnemonic; }

vector<int> Instruction::getOpcodes() const { return opcodes; }

void Instruction::setOpcodes(vector<int> opcodes) { this->opcodes = opcodes; }

std::string Instruction::getFunctionisedMethodName() {
  vector<string> details;
  string str = this->getMnemonic();
  boost::split(details, str, boost::is_any_of(" "));
  return details.at(0);
}

vector<string> Instruction::getMethodParams() {
  int dataParamsUsed = 0;
  auto dataParams = this->dataParams();

  vector<string> parameters;
  vector<string> parts;

  string str = this->getMnemonic();
  boost::split(parts, str, boost::is_any_of(" ,"));

  if (parts.size() > 1) {
    for (std::uint16_t i = 1; i < parts.size(); i++) {
      string part = parts[i];
      if (boost::starts_with(part, "(")) {
        stringstream paramStream;

        paramStream << "MemoryAddress(";

        part = part.substr(1, part.size() - 2);

        if (part.find("+") != std::string::npos) {
          vector<string> innerParts;
          boost::split(innerParts, part, boost::is_any_of("+"));
          for (std::uint16_t j = 0; j < innerParts.size(); j++) {
            string innerPart = innerParts.at(j);
            paramStream << getParam(innerPart, true, dataParamsUsed, dataParams);
            dataParamsUsed += paramsRequired(innerPart);
            if (j != innerParts.size() - 1) {
              paramStream << ", ";
            }
          }
        } else {
          paramStream << getParam(part, true, dataParamsUsed, dataParams);
          dataParamsUsed += paramsRequired(part);
        }
        paramStream << ")";
        parameters.push_back(paramStream.str());
      } else {
        auto param = getParam(part, false, dataParamsUsed, dataParams);
        dataParamsUsed += paramsRequired(part);
        parameters.push_back(param);
      }
    }
  }
  return parameters;
}

string Instruction::getParam(string part, bool indirect, uint32_t dataParamsUsed, vector<uint32_t> dataParams) {
  stringstream param;
  boost::replace_all(part, "'", "_prime");
  if (boost::regex_match(part, boost::regex("[A-Z]*")) || boost::ends_with(part, "_prime")) {
    if (contains(part, registers, registerCount) &&
        !contains(getFunctionisedMethodName(), useCondition, useConditionCount)) {
      param << "Rgstr::" << part;
    } else if (contains(part, registerpairs, registerPairCount)) {
      param << "RegisterPair::" << part;
    } else if (contains(part, conditions, conditionCount)) {
      param << "Condition::" << part;
    }
  } else if (boost::regex_match(part, boost::regex("[0-9]*"))) {
    param << part;
  } else if (part == "nn") {
    param << boost::format("(currentInstruction[%d] << 8) | currentInstruction[%d]") % dataParams[dataParamsUsed + 1] %
                 dataParams[dataParamsUsed];
  } else if (part == "n" || part == "e" || part == "d") {
    param << boost::format("currentInstruction[%d]") % dataParams[dataParamsUsed];
  } else if (boost::regex_match(part, boost::regex("[0-9a-fA-F]+H"))) {
    param << "0x" << part.substr(0, part.size() - 1);
  }
  return param.str();
}

bool Instruction::contains(std::string testString, const string possibles[], const int itemCount) {
  for (int i = 0; i < itemCount; i++) {
    //         cout << "possible match: " << possibles[i] << endl;
    if (testString == possibles[i]) {
      //             cout << "found!!!!" << endl;
      return true;
    }
  }
  return false;
}

int32_t Instruction::paramsRequired(string part) {
  if (part == "nn") {
    return 2;
  } else if (part == "n" || part == "e" || part == "d") {
    return 1;
  }
  return 0;
}

vector<uint32_t> Instruction::dataParams() {
  vector<uint32_t> data;
  for (unsigned long i = 0; i < opcodes.size(); i++) {
    if (opcodes.at(i) < 0) {
      data.push_back(i);
    }
  }
  return data;
}

std::string Instruction::getFunctionCall() {
  std::stringstream stream;
  stream << getFunctionisedMethodName() << "(";
  auto params = getMethodParams();
  for (unsigned long i = 0; i < params.size(); i++) {
    stream << params.at(i);
    if (i != params.size() - 1) {
      stream << ", ";
    }
  }
  stream << ")";
  return stream.str();
}

int Instruction::getIndexOfLastOpcode() {
  int returnInt = 0;
  for (unsigned long i = 0; i < opcodes.size(); i++) {
    if (opcodes.at(i) >= 0) {
      returnInt = i;
    }
  }
  return returnInt;
}

std::string Instruction::getOpcodesAsHex() {
  std::stringstream stream;
  for (auto i : opcodes) {
    if (i >= 0) {
      stream << std::hex << i << " ";
    } else {
      stream << "n ";
    }
  }
  return stream.str();
}

void Instruction::write(std::ofstream *writer) {
  *writer << boost::format("logger.debug(\"%s - %s\");") % this->getMnemonic() % this->getOpcodesAsHex() << endl;
  *writer << boost::format("processor.%s;") % this->getFunctionCall() << endl;
}
