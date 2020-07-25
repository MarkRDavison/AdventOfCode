#include <2015/Day23Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <functional>
#include <cassert>
namespace TwentyFifteen {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Opening the Turing Lock", 2015, 23) {

	}
	Day23Puzzle::~Day23Puzzle() {

	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		using RegisterValue = long long;
		using RegisterName = int;
		struct Instruction {
			enum class Type {
				HLF,
				TPL,
				INC,
				JMP,
				JIE,
				JIO
			} type;

			RegisterName reg;
			RegisterValue offset;
		};

		using Operation = std::function<void(const Instruction&, RegisterValue*, RegisterValue& _pc)>;
		using OperationMap = std::unordered_map<Instruction::Type, Operation>;

		OperationMap map;
		map[Instruction::Type::HLF] = [](const Instruction& _instr, RegisterValue *_register, RegisterValue& _pc) -> void { _register[_instr.reg] /= 2; _pc++; };
		map[Instruction::Type::TPL] = [](const Instruction& _instr, RegisterValue *_register, RegisterValue& _pc) -> void { _register[_instr.reg] *= 3; _pc++; };
		map[Instruction::Type::INC] = [](const Instruction& _instr, RegisterValue *_register, RegisterValue& _pc) -> void { _register[_instr.reg] += 1; _pc++; };
		map[Instruction::Type::JMP] = [](const Instruction& _instr, RegisterValue *_register, RegisterValue& _pc) -> void { _pc += _instr.offset; };
		map[Instruction::Type::JIE] = [](const Instruction& _instr, RegisterValue *_register, RegisterValue& _pc) -> void { _pc += (_register[_instr.reg] % 2 == 0 ? _instr.offset : 1); };
		map[Instruction::Type::JIO] = [](const Instruction& _instr, RegisterValue *_register, RegisterValue& _pc) -> void { _pc += (_register[_instr.reg] == 1 ? _instr.offset : 1); };
		std::vector<Instruction> instructions;
		for (const auto& i : m_InputLines) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, " ,");
			Instruction& instr = instructions.emplace_back();

			if (s[0] == "hlf") {
				instr.type = Instruction::Type::HLF;
			} else if (s[0] == "tpl") {
				instr.type = Instruction::Type::TPL;
			} else if (s[0] == "inc") {
				instr.type = Instruction::Type::INC;
			} else if (s[0] == "jmp") {
				instr.type = Instruction::Type::JMP;
			} else if (s[0] == "jie") {
				instr.type = Instruction::Type::JIE;
			} else if (s[0] == "jio") {
				instr.type = Instruction::Type::JIO;
			}
			else {
				assert(false);
			}

			switch (instr.type) {
			case Instruction::Type::HLF:
			case Instruction::Type::TPL:
			case Instruction::Type::INC:
				assert(s.size() == 2);
				assert(s[1].size() == 1);
				instr.reg = s[1][0] - 'a';
				break;
			case Instruction::Type::JIE:
			case Instruction::Type::JIO:
				assert(s.size() == 3);
				assert(s[1].size() == 1);
				instr.reg = s[1][0] - 'a';
				instr.offset = stoi(s[2]);
				break;
			case Instruction::Type::JMP:
				assert(s.size() == 2);
				instr.offset = stoi(s[1]);
				break;
			}
		}


		const auto runProgram = [&instructions, &map](RegisterValue _aStart) -> RegisterValue {
			RegisterValue registers[2] = { _aStart, 0 };
			RegisterValue pc = 0;

			while (0 <= pc && pc < (RegisterValue)instructions.size()) {
				const Instruction& instr = instructions[pc];
				const Operation& op = map[instr.type];
				op(instr, registers, pc);
			}
			return registers[1];
		};


		return { std::to_string(runProgram(0)), std::to_string(runProgram(1)) };
	}
}
