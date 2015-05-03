#pragma once
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

class Instruction
{
public:
    bool operator < (const Instruction& instr) const
    {
        return (getScore() < instr.getScore());
    }

private:
    string mnemonic;
    int32_t* size;
    vector<int> opcodes;
    vector<uint8_t>* clocks;
    string* flags;
    string* effect;

public:
    Instruction();
    unsigned long long getScore() const;
    virtual string getMnemonic() const;
    virtual void setMnemonic(string mnemonic);
    virtual int32_t* getSize();
    virtual void setSize(int32_t* size);
    virtual vector<int> getOpcodes() const;
    virtual void setOpcodes(vector<int> opcodes);
    virtual vector<uint8_t>* getClock();
    virtual void setClock(vector<uint8_t>* clock);
    virtual string* getFlags();
    virtual void setFlags(string* flags);
    virtual string* getEffect();
    virtual void setEffect(string* effect);
    virtual string getFunctionisedMethodName();
    vector<string> getMethodParams();
    
    static const string useCondition[];
    static const string registers[];
    static const string registerpairs[];
    static const string conditions[];
    bool contains(string test, const string arg2[], const int itemCount);
private:
    string getParam(string part, bool indirect, uint32_t dataParamsUsed, vector< uint32_t > dataParams);
    int32_t paramsRequired(string part);
    vector< uint32_t > dataParams();


public:
    virtual string getFunctionCall();
    virtual int getIndexOfLastOpcode();
    virtual string getOpcodesAsHex();
    virtual void write(ofstream* writer);
};

const int useConditionCount = 4;
const int registerCount = 13;
const int registerPairCount = 12;
const int conditionCount = 8;
