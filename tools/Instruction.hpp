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

    static constexpr uint8_t N { 255 };

private:
//    static ::std::stringArray* useCondition_;
    std::string mnemonic {  };
    std::int32_t* size {  };
    std::vector<int> opcodes {  };
    std::vector<uint8_t>* clocks {  };
    std::string* flags {  };
    std::string* effect {  };

public:
    Instruction();
    uint32_t getScore() const;
    virtual ::std::string getMnemonic() const;
    virtual void setMnemonic(::std::string mnemonic);
    virtual int32_t* getSize();
    virtual void setSize(int32_t* size);
    virtual std::vector<int> getOpcodes() const;
    virtual void setOpcodes(std::vector<int> opcodes);
    virtual std::vector<uint8_t>* getClock();
    virtual void setClock(std::vector<uint8_t>* clock);
    virtual ::std::string* getFlags();
    virtual void setFlags(::std::string* flags);
    virtual ::std::string* getEffect();
    virtual void setEffect(::std::string* effect);
    virtual ::std::string* getFunctionisedMethodName();
    virtual std::vector<std::string>* getMethodParams();

private:
    ::std::string* getParam(::std::string* part, bool indirect, uint32_t dataParamsUsed, std::vector<u_int32_t>* dataParams);
    int32_t paramsRequired(::std::string* part);
    std::vector<uint32_t>* dataParams();

public:
    virtual ::std::string* getFunctionCall();
    virtual int32_t getIndexOfLastOpcode();
    virtual ::std::string* getOpcodesAsHex();
    virtual void write(std::ofstream* writer);

public:
    static void clinit();

//public: /* package */
//    static ::std::stringArray*& useCondition();
};
