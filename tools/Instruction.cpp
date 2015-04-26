#include <tools/Instruction.hpp>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

#include<boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>

#include "Z80/Condition.hpp"
#include "Z80/Register.hpp"
#include "Z80/RegisterPair.hpp"

using namespace std;

    vector<string> Instruction::useCondition_;
    vector<string> Instruction::registers;
    vector<string> Instruction::registerpairs;

Instruction::Instruction() {
}

uint32_t Instruction::getScore() const
{
    std::cout << getMnemonic() << endl;
    string thisScore = "";
    for (auto i = 0; i < 4; i++) {
        std::cout << "loopinng " << thisScore <<endl;
        if(i < getOpcodes().size() && (getOpcodes().at(i) >= 0)) {
            thisScore = thisScore + to_string(getOpcodes().at(i));
        } else {
            thisScore = thisScore + "000";
        }
    }
    std::cout << "stringscore " << thisScore <<endl;
    return stoul(thisScore);
}

std::string Instruction::getMnemonic() const
{
    return mnemonic;
}

void Instruction::setMnemonic(string mnemonic)
{
    this->mnemonic = mnemonic;
}

int32_t* Instruction::getSize()
{
    return size;
}

void Instruction::setSize(int32_t* size)
{
    this->size = size;
}

vector<int> Instruction::getOpcodes() const
{
    return opcodes;
}

void Instruction::setOpcodes(vector<int> opcodes)
{
    this->opcodes = opcodes;
}

vector<uint8_t>* Instruction::getClock()
{
    return clocks;
}

void Instruction::setClock(vector<uint8_t>* clock)
{
    this->clocks = clock;
}

std::string* Instruction::getFlags()
{
    return flags;
}

void Instruction::setFlags(::std::string* flags)
{
    this->flags = flags;
}

std::string* Instruction::getEffect()
{
    return effect;
}

void Instruction::setEffect(::std::string* effect)
{
    this->effect = effect;
}

std::string Instruction::getFunctionisedMethodName()
{
    vector<string> details;
    string str = this->getMnemonic();
    boost::split(details, str, boost::is_any_of(" "));
    return details.at(0);
}

vector<string> Instruction::getMethodParams()
{
    auto dataParamsUsed = int32_t(0);
    auto dataParams = this->dataParams();
    vector<string> parameters;
    vector<string> parts;
    string str = this->getMnemonic();
    boost::split(parts, str, boost::is_any_of(" ,"));

    if(parts.size() > 1) {
        for (string part : parts) {
            if(boost::starts_with(part,"(")) {
                stringstream paramStream;

                paramStream << "new MemoryAddress(";
                part = part.substr(1, part.size() - 1);
                if(part.find("+") != string::npos) {
                    vector<string>  innerParts;
                    boost::split(innerParts, part, boost::is_any_of("+"));
                    for(string innerPart : innerParts) {
                        paramStream << getParam(innerPart, true, dataParamsUsed, dataParams) << ", ";
                        dataParamsUsed += paramsRequired(innerPart);
                    }
//                     param = paramStream.str().substr(0, param.size() - 2);
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

string Instruction::getParam(string part, bool indirect, uint32_t dataParamsUsed, vector<uint32_t> dataParams)
{
    stringstream param;
    boost::replace_all(part, "'", "_prime");
    if( boost::regex_match(part, boost::regex("[A-Z]*")) || boost::ends_with(part, "_prime")) {
        if(contains(part, registers) && !contains(getFunctionisedMethodName(), useCondition_)) {
        param << "Register." << part;
    } else if(contains(part, registerpairs)) {
        param << "RegisterPair." << part;
    } else if(contains(part, useCondition_)) {
        param << "Condition." << part;
    }
} else if( boost::regex_match(part, boost::regex("[0-9]*"))) {
        param << part;
    } else if(part == "nn") {
        param << boost::format("(currentInstruction[%d] << 8) | currentInstruction[%d]") % dataParams[dataParamsUsed + 1] % dataParams[dataParamsUsed];
    } else if(part =="n" || part== "e" || part == "d") {
        param << boost::format("currentInstruction[%d]") % dataParams[dataParamsUsed];
    } else if(boost::regex_match(part, boost::regex("[0-9a-fA-F]+H"))) {
        param <<"0x" << part.substr(0, part.size() - 1);
    }
    return "";
}

bool Instruction::contains(string testString, vector<string> possibles) {

    for (string test : possibles) {
        if (testString.find(test) != std::string::npos) {
            return true;
        }
    }
    return false;
}

int32_t Instruction::paramsRequired(string part)
{
    if(part == "nn") {
        return 2;
    } else if(part =="n" || part == "e" || part == "d") {
        return 1;
    }
    return 0;
}

vector<uint32_t> Instruction::dataParams()
{
    vector<uint32_t> data;
    for (auto i = 0; i < opcodes.size(); i++) {
        if(opcodes.at(i) >= 0) {
            data.push_back(i);
        }
    }
    return data;
}

std::string Instruction::getFunctionCall()
{
    std::stringstream stream;
    stream << getFunctionisedMethodName() << "(";
    auto params = getMethodParams();
    for(int i = 0; i < params.size(); i++) {
        stream << params.at(i);
        if (i != params.size() -1) {
            stream << ", ";

        }
    }
    stream  << ")";
    return stream.str();
}

int Instruction::getIndexOfLastOpcode()
{
    int returnInt = 0;
    for (int i = 0; i < opcodes.size(); i++) {
        if(opcodes.at(i) >= 0) {
            returnInt = i;
        }
    }
    return returnInt;
}

std::string Instruction::getOpcodesAsHex()
{
    std::stringstream stream;
    for(auto i : opcodes) {
        if( i >= 0) {
            stream << std::hex << i << " ";
        } else {
            stream << "n ";
        }
    }
    return stream.str();
}

void Instruction::write(std::ofstream* writer)
{
    *writer << boost::format("// %s - %s") % this->getMnemonic() % this->getOpcodesAsHex() << endl;
    *writer << boost::format("logger.debug(\"%s - %s\");") % this->getMnemonic() % this->getOpcodesAsHex()<< endl;
    *writer << boost::format("getProcessor().%s;") % this->getFunctionCall()<< endl;
}


void Instruction::clinit()
{
    useCondition_.push_back("JP");
    useCondition_.push_back("RET");
    useCondition_.push_back("CALL");
    useCondition_.push_back("JR");
}

