// Generated from /org.maidavale.cpu/src/main/java/InstructionTableToCode.java
#include <tools/InstructionTableToCode.hpp>

#include <tools/Case.hpp>
#include <tools/FinalNode.hpp>
#include <tools/GetData.hpp>
#include <tools/Instruction.hpp>
#include <tools/Switch.hpp>

InstructionTableToCode::InstructionTableToCode() :
		InstructionTableToCode(*static_cast<::default_init_tag*>(0)) {
	ctor();
}

void InstructionTableToCode::main(
		vector<string>* args) {
	auto parser = new InstructionTableToCode();

	auto instructions = parser->parse();
	auto s = parser->groupOpcodes(instructions);
	parser->writeCode(s);

}

std::vector<Instruction> instructions* InstructionTableToCode::parse() /* throws(URISyntaxException) */
{
	auto theInstructions = new ::java::util::ArrayList();
	auto opcodeList = ::java::nio::file::Paths::get(npc(::java::lang::ClassLoader::getSystemResource(u"z80sean.txt"_j))->toURI());
	try (auto *const reader = ::java::nio::file::Files::newBufferedReader(opcodeList, charset)) {
		for (auto i = int32_t(0); i < 33; i++) {
			npc(reader)->readLine();
			npc(::java::lang::System::out())->print(u"Skipping line"_j);
		}
		::java::lang::String* line;
		while ((line = npc(reader)->readLine()) != nullptr) {
			auto split = npc(line)->split(u"\\s{2,}|\\t+"_j);
			if(npc(split)->length < 2 || npc(npc((*split)[int32_t(1)])->trim())->endsWith(u"*"_j)) {
				continue;
			}
			split->set(int32_t(1), npc(npc((*split)[int32_t(1)])->trim())->replace(static_cast< ::java::lang::CharSequence* >(u"*"_j), static_cast< ::java::lang::CharSequence* >(u""_j)));
			auto instruction = new Instruction();
			npc(instruction)->setMnemonic(npc((*split)[int32_t(1)])->trim());
			auto pattern = ::java::util::regex::Pattern::compile(u"(\\w{2})|\\b(\\w+)\\b"_j);
			auto matcher = npc(pattern)->matcher((*split)[int32_t(0)]);
			::java::util::List* opcodeparts = new ::java::util::ArrayList();
			while (npc(matcher)->find()) {
				npc(opcodeparts)->add(static_cast< ::java::lang::Object* >(npc(matcher)->group()));
			}
			::java::util::List* intOpcodes = new ::java::util::ArrayList();
			for (auto _i = npc(opcodeparts)->iterator(); _i->hasNext(); ) {
				::java::lang::String* op = java_cast< ::java::lang::String* >(_i->next());
				{
					if(npc(op)->equals(static_cast< ::java::lang::Object* >(u"n"_j)) || npc(op)->equals(static_cast< ::java::lang::Object* >(u"d"_j)) || npc(op)->equals(static_cast< ::java::lang::Object* >(u"e"_j))) {
						npc(intOpcodes)->add(::java::lang::Integer::valueOf(Instruction::N));
					} else {
						npc(intOpcodes)->add(::java::lang::Integer::valueOf(::java::lang::Integer::parseUnsignedInt(op, 16)));
					}
				}
			}
			npc(instruction)->setOpcodes(java_cast< ::java::lang::IntegerArray* >(npc(intOpcodes)->toArray_(static_cast< ::java::lang::ObjectArray* >(new ::java::lang::IntegerArray(npc(intOpcodes)->size())))));
			npc(::java::lang::System::out())->println(static_cast< ::java::lang::Object* >(instruction));
			npc(theInstructions)->add(static_cast< ::java::lang::Object* >(instruction));
		}
	} catch (::java::io::IOException* x) {
		npc(x)->printStackTrace();
	}
	::java::util::Collections::sort(theInstructions);
	return theInstructions;
}

void InstructionTableToCode::writeCode(
		Switch* rootSwitch) /* throws(IOException) */
		{
	auto javaPath = npc(::java::nio::file::FileSystems::getDefault())->getPath(u"./src/main/java/InstructionDecoderGenerated.java"_j, new ::java::lang::StringArray());
	if (::java::nio::file::Files::exists(javaPath,
			new ::java::nio::file::LinkOptionArray())) {
		::java::nio::file::Files::delete_ (javaPath);
	}
try (auto *const writer = ::java::nio::file::Files::newBufferedWriter(javaPath, charset, new ::java::nio::file::OpenOptionArray())) {
	writeHeader(writer);
	rootSwitch->write(writer);
	writeFooter(writer);
}

void InstructionTableToCode::writeHeader(
	std::ofstream* writer) /* throws(IOException) */
	{
writer << u"package org.maidavale.cpu.tools;\n"_j)writer << u"\n"_j)
	writer << u"import java.util.ArrayList;\n"_j)
	writer << u"import java.util.List;\n"_j)
	writer << u"import org.slf4j.Logger;\n"_j)
	writer << u"import org.slf4j.LoggerFactory;\n"_j)
	writer << u"import org.apache.commons.lang3.ArrayUtils;\n"_j)
	writer << u"import org.maidavale.cpu.Processor;\n"_j)
	writer << u"import org.maidavale.cpu.InstructionDecoder;\n"_j)
	writer << u"import org.maidavale.cpu.BaseInstructionDecoder;\n"_j)
	writer << u"import org.maidavale.cpu.Register;\n"_j)
	writer << u"import org.maidavale.cpu.RegisterPair;\n"_j)
	writer << u"import org.maidavale.cpu.Condition;\n"_j)
	writer << u"import org.maidavale.cpu.MemoryAddress;\n"_j)
	writer << u"/**\n"_j)
	writer << u" * Created by ed on 01/02/15.\n"_j)
	writer << u" */\n"_j)
	writer << u"public class InstructionDecoderGenerated extends BaseInstructionDecoder {\n"_j)
	writer << u"final Logger logger = LoggerFactory.getLogger(InstructionDecoderGenerated.class);\n"_j)
	writer << u"    @Override\n"_j)
	writer << u"    public int[] decode() {\n"_j)
	writer << u"int[] currentInstruction = new int[4];\n"_j)
	writer << u"\n"_j)->toString());
}

void InstructionTableToCode::writeFooter(
std::ofstream* writer) /* throws(IOException) */
{
writer << u"currentInstruction = ArrayUtils.subarray(currentInstruction, 0, instructionByteCount);\n"_j)writer << u"instructionByteCount = 0;\n"_j)
writer << u"return currentInstruction;\n"_j)
writer << u"    }\n"_j)
writer << u"}\n"_j)->toString());
}

Switch* InstructionTableToCode::groupOpcodes(
std::vector<Instruction> instructions) {
auto rootLevel = new Switch(0);

for (auto _i = npc(instructions)->iterator(); _i->hasNext();) {
Instruction* instruction = java_cast<Instruction*>(_i->next());
{
::java::lang::Integer* depth = ::java::lang::Integer::valueOf(int32_t(0));
FinalNode* currentCase = nullptr;
for (auto opcode : *npc(npc(instruction)->getOpcodes())) {
	if ((npc(opcode))->intValue() == Instruction::N) {
		if (!npc(npc(currentCase)->getDatas)->containsKey(depth)) {
			auto data = new GetData(depth);
			npc(npc(currentCase)->getDatas)->put(depth, data);
		}
	} else {
		if (currentCase == nullptr) {
			currentCase = java_cast<FinalNode*>(
					npc(npc(rootLevel)->nodes)->get(opcode));
			if (currentCase == nullptr) {
				currentCase = new Case(opcode);
				npc(npc(rootLevel)->nodes)->put(opcode, currentCase);
			}
		} else {
			if (npc(currentCase)->theSwitch == nullptr) {
				npc(currentCase)->theSwitch = new Switch(depth);
			}
			if (npc(npc(npc(currentCase)->theSwitch)->nodes)->containsKey(
					opcode)) {
				currentCase = java_cast<FinalNode*>(
						npc(npc(npc(currentCase)->theSwitch)->nodes)->get(
								opcode));
			} else {
				auto c = new Case(opcode);
				npc(npc(npc(currentCase)->theSwitch)->nodes)->put(opcode, c);
				currentCase = c;
			}
		}
	}
	if (depth == npc(instruction)->getIndexOfLastOpcode()) {
		npc(currentCase)->instruction = instruction;
	}
	(npc(depth))->intValue()++;}
}
}
return rootLevel;
}
