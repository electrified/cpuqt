// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/tools/Instruction.java

#pragma once
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

class Instruction
{

public:
    static constexpr int32_t N { int32_t(1000) };

private:
//    static ::std::stringArray* useCondition_;
    std::string* mnemonic {  };
    std::int32_t* size {  };
    std::vector<int32_t>* opcodes {  };
    std::vector<int32_t>* clocks {  };
    std::string* flags {  };
    std::string* effect {  };

public:
    static int32_t* getScore(Instruction* o);
    virtual ::std::string* getMnemonic();
    virtual void setMnemonic(::std::string* mnemonic);
    virtual int32_t* getSize();
    virtual void setSize(int32_t* size);
    virtual std::vector<int32_t>* getOpcodes();
    virtual void setOpcodes(std::vector<int32_t>* opcodes);
    virtual std::vector<int32_t>* getClock();
    virtual void setClock(std::vector<int32_t>* clock);
    virtual ::std::string* getFlags();
    virtual void setFlags(::std::string* flags);
    virtual ::std::string* getEffect();
    virtual void setEffect(::std::string* effect);
    virtual int32_t compareTo(Instruction* o);
    virtual ::std::string* getFunctionisedMethodName();
    virtual std::vector<std::string>* getMethodParams();

private:
    ::std::string* getParam(::std::string* part, bool indirect, uint32_t dataParamsUsed, std::vector<u_int32_t>* dataParams);
    int32_t paramsRequired(::std::string* part);
    std::vector<uint32_t>* dataParams();

public:
    virtual ::std::string* getFunctionCall();
    virtual int32_t* getIndexOfLastOpcode();
    virtual ::std::string* getOpcodesAsHex();
    virtual void write(std::ofstream* writer);

    // Generated
    Instruction();

public:
    static void clinit();
//    virtual int32_t compareTo(::java::lang::Object* o) override;
//
//public: /* package */
//    static ::std::stringArray*& useCondition();
};
