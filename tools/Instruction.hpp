// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/Instruction.java

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
    string mnemonic {  };
    int32_t* size {  };
    vector<int> opcodes {  };
    vector<uint8_t>* clocks {  };
    string* flags {  };
    string* effect {  };
    static vector<string> useCondition_;
    static vector<string> registers;
    static vector<string> registerpairs;

public:
    Instruction();
    uint32_t getScore() const;
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

private:
    string getParam(string part, bool indirect, uint32_t dataParamsUsed, vector< uint32_t > dataParams);
    int32_t paramsRequired(string part);
    vector< uint32_t > dataParams();
    bool contains(string test, vector<string> arg2);

public:
    virtual string getFunctionCall();
    virtual int getIndexOfLastOpcode();
    virtual string getOpcodesAsHex();
    virtual void write(ofstream* writer);

public:
    static void clinit();
};
