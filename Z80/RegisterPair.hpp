//// Generated from /org.maidavale.cpu/src/main/java/org/maidavale/cpu/RegisterPair.java
//
//#pragma once
//
//#include <java/io/fwd-org.maidavale.cpu.hpp>
//#include <java/lang/fwd-org.maidavale.cpu.hpp>
//#include <org/maidavale/cpu/fwd-org.maidavale.cpu.hpp>
//#include <java/lang/Enum.hpp>
//
//template<typename ComponentType, typename... Bases> struct SubArray;
//namespace java
//{
//    namespace io
//    {
//typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
//    } // io
//
//    namespace lang
//    {
//typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
//typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
//typedef ::SubArray< ::java::lang::Enum, ObjectArray, ComparableArray, ::java::io::SerializableArray > EnumArray;
//typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
//    } // lang
//} // java
//
//namespace org
//{
//    namespace maidavale
//    {
//        namespace cpu
//        {
//typedef ::SubArray< ::org::maidavale::cpu::RegisterPair, ::java::lang::EnumArray > RegisterPairArray;
//        } // cpu
//    } // maidavale
//} // org
//
//struct default_init_tag;
//
//class org::maidavale::cpu::RegisterPair final
//    : public ::java::lang::Enum
//{
//
//public:
//    typedef ::java::lang::Enum super;
//
//public: /* package */
//    static RegisterPair *BC;
//    static RegisterPair *DE;
//    static RegisterPair *HL;
//    static RegisterPair *SP;
//    static RegisterPair *AF;
//    static RegisterPair *IX;
//    static RegisterPair *IY;
//    static RegisterPair *PC;
//    static RegisterPair *AF_prime;
//    static RegisterPair *BC_prime;
//    static RegisterPair *DE_prime;
//    static RegisterPair *HL_prime;
//
//public:
//    static ::java::lang::StringArray* names();
//
//    // Generated
//    RegisterPair(::java::lang::String* name, int ordinal);
//protected:
//    RegisterPair(const ::default_init_tag&);
//
//
//public:
//    static ::java::lang::Class *class_();
//    static RegisterPair* valueOf(::java::lang::String* a0);
//    static RegisterPairArray* values();
//
//private:
//    virtual ::java::lang::Class* getClass0();
//};
