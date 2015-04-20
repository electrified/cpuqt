// Generated from /org.maidavale.cpu/src/main/java/Instruction.java

#include <tools/Instruction.hpp>
#include <string>

#include <Z80/Condition.hpp>
#include <Z80/Register.hpp>
#include <Z80/RegisterPair.hpp>

constexpr uint8_t Instruction::N;

Instruction::Instruction() {
}

// vector<string>* Instruction::useCondition()
// {
//     clinit();
//     return useCondition_;
// } 


int32_t Instruction::getScore() const
{
    string thisScore = "0";
    for (auto i = 0; i < 4; i++) {
        if(i < getOpcodes()->size() && (getOpcodes()->at(i) != NULL)) {
            thisScore = thisScore + to_string(getOpcodes()->at(i));
        } else {
            thisScore = thisScore + "000";
        }
    }
    return stoi(thisScore);
}

std::string* Instruction::getMnemonic()
{
    return mnemonic;
}

void Instruction::setMnemonic(::std::string* mnemonic)
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

vector<uint8_t>* Instruction::getOpcodes() const
{
    return opcodes;
}

void Instruction::setOpcodes(vector<uint8_t>* opcodes)
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
//
//std::string* Instruction::toString()
//{
//    return ::std::stringBuilder().append(::std::stringBuilder().append(u"Opcode{"_j)->append(u"mnemonic='"_j)->toString())->append(mnemonic)
//        ->append(u'\'')
//        ->append(u", size="_j)
//        ->append(static_cast< ::java::lang::Object* >(size))
//        ->append(u", opcodes="_j)
//        ->append(::java::util::Arrays::toString(static_cast< ::java::lang::ObjectArray* >(opcodes)))
//        ->append(u", clocks="_j)
//        ->append(::java::util::Arrays::toString(static_cast< ::java::lang::ObjectArray* >(clocks)))
//        ->append(u", flags='"_j)
//        ->append(flags)
//        ->append(u'\'')
//        ->append(u", effect='"_j)
//        ->append(effect)
//        ->append(u'\'')
//        ->append(u'}')->toString();
//}

std::string* Instruction::getFunctionisedMethodName()
{
//     return this->getMnemonic()->split(u"\\s"_j);
}

std::vector<std::string>* Instruction::getMethodParams()
{
    auto dataParamsUsed = int32_t(0);
    auto dataParams = this->dataParams();
    std::vector<std::string>* parameters;// = new ::java::util::ArrayList();
//     auto parts = this->getMnemonic()->split(u"\\s|,"_j);
//     if(parts->length > 1) {
//         for (auto i = int32_t(1); i < parts.size(); i++) {
//             auto part = (*parts)[i];
//             if(part)->startsWith(u"("_j)) {
//                 auto param = u"new MemoryAddress("_j;
//                 part = part)->substring(1, part)->length() - int32_t(1));
//                 if(part)->contains(u"+"_j)) {
//                     auto innerParts = part)->split(u"\\+"_j);
//                     for(auto innerPart : *innerParts)) {
//                         param = ::std::stringBuilder().append(param)->append(getParam(innerPart, true, dataParamsUsed, dataParams))
//                             ->append(u", "_j)->toString();
//                         dataParamsUsed += paramsRequired(innerPart);
//                     }
//                     param = param)->substring(0, param)->length() - int32_t(2));
//                 } else {
//                     param = ::std::stringBuilder().append(param)->append(getParam(part, true, dataParamsUsed, dataParams))->toString();
//                     dataParamsUsed += paramsRequired(part);
//                 }
//                 param = ::std::stringBuilder().append(param)->append(u")"_j)->toString();
//                 parameters)->add(static_cast< ::java::lang::Object* >(param));
//             } else {
//                 auto param = getParam(part, false, dataParamsUsed, dataParams);
//                 dataParamsUsed += paramsRequired(part);
//                 parameters)->add(static_cast< ::java::lang::Object* >(param));
//             }
//         }
//     }
    return parameters;
}

std::string* Instruction::getParam(::std::string* part, bool indirect, uint32_t dataParamsUsed, vector<uint32_t>* dataParams)
{
    string param = ""; //_j;
//     part = part)->replace(static_cast< ::java::lang::CharSequence* >(u"'"_j), static_cast< ::java::lang::CharSequence* >(u"_prime"_j));
//     if(::org::apache::commons::lang3::StringUtils::isAllUpperCase(part) || part)->endsWith(u"_prime"_j)) {
//         if(::org::apache::commons::lang3::ArrayUtils::contains(static_cast< ::java::lang::ObjectArray* >(::org::maidavale::cpu::Register::names()), static_cast< ::java::lang::Object* >(part)) && !::org::apache::commons::lang3::ArrayUtils::contains(static_cast< ::java::lang::ObjectArray* >(useCondition_), static_cast< ::java::lang::Object* >(getFunctionisedMethodName()))) {
//             param = ::std::stringBuilder().append(u"Register."_j)->append(part)->toString();
//         } else if(::org::apache::commons::lang3::ArrayUtils::contains(static_cast< ::java::lang::ObjectArray* >(::org::maidavale::cpu::RegisterPair::names()), static_cast< ::java::lang::Object* >(part))) {
//             param = ::std::stringBuilder().append(u"RegisterPair."_j)->append(part)->toString();
//         } else if(::org::apache::commons::lang3::ArrayUtils::contains(static_cast< ::java::lang::ObjectArray* >(::org::maidavale::cpu::Condition::names()), static_cast< ::java::lang::Object* >(part))) {
//             param = ::std::stringBuilder().append(u"Condition."_j)->append(part)->toString();
//         }
//     } else if(::org::apache::commons::lang3::StringUtils::isNumeric(part)) {
//         param = part;
//     } else if(part)->equals(static_cast< ::java::lang::Object* >(u"nn"_j))) {
//         param = ::std::string::format(u"(currentInstruction[%d] << 8) | currentInstruction[%d]"_j, new ::java::lang::ObjectArray({static_cast< ::java::lang::Object* >((*dataParams)[dataParamsUsed + int32_t(1)]), static_cast< ::java::lang::Object* >((*dataParams)[dataParamsUsed])}));
//     } else if(part)->equals(static_cast< ::java::lang::Object* >(u"n"_j)) || part)->equals(static_cast< ::java::lang::Object* >(u"e"_j)) || part)->equals(static_cast< ::java::lang::Object* >(u"d"_j))) {
//         param = ::std::string::format(u"currentInstruction[%d]"_j, new ::java::lang::ObjectArray({static_cast< ::java::lang::Object* >((*dataParams)[dataParamsUsed])}));
//     } else if(part)->matches(u"[0-9a-fA-F]+H"_j)) {
//         param = ::std::stringBuilder().append(u"0x"_j)->append(part)->substring(0, part)->length() - int32_t(1)))->toString();
//     }
    return &param;
}

int32_t Instruction::paramsRequired(::std::string* part)
{
//     if(part)->equals(static_cast< ::java::lang::Object* >(u"nn"_j))) {
//         return 2;
//     } else if(part)->equals(static_cast< ::java::lang::Object* >(u"n"_j)) || part)->equals(static_cast< ::java::lang::Object* >(u"e"_j)) || part)->equals(static_cast< ::java::lang::Object* >(u"d"_j))) {
//         return 1;
//     }
    return 0;
}

vector<uint32_t>* Instruction::dataParams()
{
//     ::java::util::List* data = new ::java::util::ArrayList();
//     for (auto i = int32_t(0); i < opcodes)->length; i++) {
//         if(((*opcodes)[i]))->intValue() == N) {
//             data)->add(::java::lang::Integer::valueOf(i));
//         }
//     }
//     return java_cast< ::java::lang::IntegerArray* >(data)->toArray_(static_cast< ::java::lang::ObjectArray* >(new ::java::lang::IntegerArray(data)->size()))));
}

std::string* Instruction::getFunctionCall()
{
//     return ::std::stringBuilder().append(getFunctionisedMethodName())->append(u"("_j)
//         ->append(::std::string::join(static_cast< ::java::lang::CharSequence* >(u", "_j), static_cast< ::java::lang::CharSequenceArray* >(getMethodParams())))
//         ->append(u")"_j)->toString();
}

int32_t Instruction::getIndexOfLastOpcode()
{
//     auto returnInt = int32_t(0);
//     for (auto i = int32_t(0); i < opcodes->size(); i++) {
//         if((*opcodes)[i] != nullptr) {
//             returnInt = i;
//         }
//     }
//     return returnInt;
}

std::string* Instruction::getOpcodesAsHex()
{
//     auto blah = u""_j;
//     for(auto i : *opcodes) {
//         if(i != nullptr && (i))->intValue() != N) {
//             blah = ::std::stringBuilder().append(blah)->append(::java::lang::Integer::toHexString((i))->intValue()))
//                 ->append(u" "_j)->toString();
//         } else {
//             blah = ::std::stringBuilder().append(blah)->append(u"n "_j)->toString();
//         }
//     }
//     return blah;
}

void Instruction::write(std::ofstream* writer) /* throws(IOException) */
{
//     writer << "// %s - %s\n" << this->getMnemonic() << this->getOpcodesAsHex();
//     writer << "logger.debug(\"%s - %s\");\n" << this->getMnemonic() << this->getOpcodesAsHex();
//     writer << "getProcessor().%s;\n" << this->getFunctionCall();
}


void Instruction::clinit()
{
//         useCondition_ = (new ::std::stringArray({
//             u"JP"_j
//             , u"RET"_j
//             , u"CALL"_j
//             , u"JR"_j
//         }));
}

