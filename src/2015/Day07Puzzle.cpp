#include <2015/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>

#define TOKEN_NOT "NOT"
#define TOKEN_AND "AND"
#define TOKEN_OR "OR"
#define TOKEN_LSHIFT "LSHIFT"
#define TOKEN_RSHIFT "RSHIFT"
#define TOKEN_ASSIGN "->"

namespace TwentyFifteen {


	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Some Assembly Required", 2015, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void  Day07Puzzle::compileAssignInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr) {
		_computer.p.emplace(_instr.output, [_instr]() -> InstructionDataType {
			//std::cout << "Executing " << _instr.input1Int << " -> " << _instr.output << std::endl;
			return _instr.input1Int; 
		});
	}
	void Day07Puzzle::compileAndInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr) {
		_computer.p.emplace(_instr.output, [_instr, &_computer]() -> InstructionDataType {
			if (_instr.input1.empty()) {
				if (_computer.memoizedValues.count(_instr.output) > 0) {
					return _computer.memoizedValues[_instr.output];
				}
				//std::cout << "Executing " << _instr.input1Int << " AND " << _instr.input2 << " -> " << _instr.output << std::endl;
				const auto& i1 = _instr.input1Int;
				const auto& i2 = _computer.p[_instr.input2]();
				const auto res = i1 & i2;
				_computer.memoizedValues[_instr.output] = res;
				return res;
			} else {
				if (_computer.memoizedValues.count(_instr.output) > 0) {
					return _computer.memoizedValues[_instr.output];
				}
				//std::cout << "Executing " << _instr.input1 << " AND " << _instr.input2 << " -> " << _instr.output << std::endl;
				const auto& i1 = _computer.p[_instr.input1]();
				const auto& i2 = _computer.p[_instr.input2]();
				const auto res = i1 & i2;
				_computer.memoizedValues[_instr.output] = res;
				return res;
			}
		});
	}
	void Day07Puzzle::compileOrInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr) {
		_computer.p.emplace(_instr.output, [_instr, &_computer]() -> InstructionDataType {
			if (_computer.memoizedValues.count(_instr.output) > 0) {
				return _computer.memoizedValues[_instr.output];
			}
			//std::cout << "Executing " << _instr.input1 << " OR " << _instr.input2 << " -> " << _instr.output << std::endl;
			const auto& i1 = _computer.p[_instr.input1]();
			const auto& i2 = _computer.p[_instr.input2]();
			const auto res = i1 | i2;
			_computer.memoizedValues[_instr.output] = res;
			return res;
		});
	}
	void Day07Puzzle::compileLeftShiftInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr) {
		_computer.p.emplace(_instr.output, [_instr, &_computer]() -> InstructionDataType {
			if (_computer.memoizedValues.count(_instr.output) > 0) {
				return _computer.memoizedValues[_instr.output];
			}
			//std::cout << "Executing " << _instr.input1 << " LSHIFT " << _instr.input2Int << " -> " << _instr.output << std::endl;
			const auto& i1 = _computer.p[_instr.input1]();
			const auto& i2 = _instr.input2Int;
			const auto res = i1 << i2;
			_computer.memoizedValues[_instr.output] = res;
			return res;
		});
	}
	void Day07Puzzle::compileRightShiftInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr) {
		_computer.p.emplace(_instr.output, [_instr, &_computer]() -> InstructionDataType {
			if (_computer.memoizedValues.count(_instr.output) > 0) {
				return _computer.memoizedValues[_instr.output];
			}
			//std::cout << "Executing " << _instr.input1 << " RSHIFT " << _instr.input2Int << " -> " << _instr.output << std::endl;
			const auto& i1 = _computer.p[_instr.input1]();
			const auto& i2 = _instr.input2Int;
			const auto res = i1 >> i2;
			_computer.memoizedValues[_instr.output] = res;
			return res;
		});
	}
	void Day07Puzzle::compileNotInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr) {
		_computer.p.emplace(_instr.output, [_instr, &_computer]() -> InstructionDataType {
			if (_computer.memoizedValues.count(_instr.output) > 0) {
				return _computer.memoizedValues[_instr.output];
			}
			//std::cout << "Executing NOT " << _instr.input1 << " -> " << _instr.output << std::endl;
			const auto& i1 = _computer.p[_instr.input1]();
			const auto res = ~i1 & 0xffff;
			_computer.memoizedValues[_instr.output] = res;
			return res;
		});
	}
	void Day07Puzzle::compileNoOpInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr) {
		_computer.p.emplace(_instr.output, [_instr, &_computer]() -> InstructionDataType {
			if (_computer.memoizedValues.count(_instr.output) > 0) {
				return _computer.memoizedValues[_instr.output];
			}
			//std::cout << "Executing " << _instr.input1 << " -> " << _instr.output << std::endl;
			const auto& i1 = _computer.p[_instr.input1]();
			const auto res = i1;
			_computer.memoizedValues[_instr.output] = res;
			return res;
		});
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		InstructionDataType part1;
		
		{
			Computer computer;

			std::vector<ParsedInstruction> instructions;
			for (const auto& l : m_InputLines) {
				const auto& instr = parseInstruction(l);
				switch (instr.type) {
				case ParsedInstruction::OperatorType::ASSIGN:
					compileAssignInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::AND:
					compileAndInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::OR:
					compileOrInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::LSHIFT:
					compileLeftShiftInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::RSHIFT:
					compileRightShiftInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::NOT:
					compileNotInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::NOOP:
					compileNoOpInstruction(computer, instr);
					break;
				}
			}


			auto fxn = computer.p[desiredoutput];
			const auto res = fxn();
			part1 = res;
		}

		if (desiredoutput == "a") {
			Computer computer;

			std::vector<ParsedInstruction> instructions;
			for (const auto& l : m_InputLines) {
				auto instr = parseInstruction(l);
				if (instr.output == "b") {
					instr.input1Int = part1;
					instr.input1 = "";
					instr.type = ParsedInstruction::OperatorType::ASSIGN;
				}
				switch (instr.type) {
				case ParsedInstruction::OperatorType::ASSIGN:
					compileAssignInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::AND:
					compileAndInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::OR:
					compileOrInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::LSHIFT:
					compileLeftShiftInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::RSHIFT:
					compileRightShiftInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::NOT:
					compileNotInstruction(computer, instr);
					break;
				case ParsedInstruction::OperatorType::NOOP:
					compileNoOpInstruction(computer, instr);
					break;
				}
			}


			auto fxn = computer.p[desiredoutput];
			const auto res = fxn();
			return { std::to_string(part1), std::to_string(res) };
		}
					   
		return { std::to_string(part1), "Part 2" };
	}

	Day07Puzzle::ParsedInstruction Day07Puzzle::parseInstruction(const std::string& _line) {
		ParsedInstruction instr{};
		const auto& parts = core::StringExtensions::splitStringByDelimeter(_line, " ");
		if (parts[0] == TOKEN_NOT) {
			instr.type = ParsedInstruction::OperatorType::NOT;
			instr.input1 = parts[1];
			instr.output = parts[3];
		}
		else if (parts[1] == TOKEN_AND) {
			instr.type = ParsedInstruction::OperatorType::AND;

			if (std::isalpha(parts[0][0])) {
				instr.input1 = parts[0];
			} else {
				instr.input1Int = std::stoi(parts[0]);
			}
			instr.input2 = parts[2];
			instr.output = parts[4];
		}
		else if (parts[1] == TOKEN_OR) {
			instr.type = ParsedInstruction::OperatorType::OR;
			instr.input1 = parts[0];
			instr.input2 = parts[2];
			instr.output = parts[4];
		}
		else if (parts[1] == TOKEN_LSHIFT) {
			instr.type = ParsedInstruction::OperatorType::LSHIFT;
			instr.input1 = parts[0];
			instr.input2Int = std::stoi(parts[2]);
			instr.output = parts[4];
		}
		else if (parts[1] == TOKEN_RSHIFT) {
			instr.type = ParsedInstruction::OperatorType::RSHIFT;
			instr.input1 = parts[0];
			instr.input2Int = std::stoi(parts[2]);
			instr.output = parts[4];
		}
		else if (parts.size() == 3) {
			if (std::isalpha(parts[0][0])) {
				instr.type = ParsedInstruction::OperatorType::NOOP;
				instr.input1 = parts[0];
				instr.output = parts[2];
			}
			else {
				instr.type = ParsedInstruction::OperatorType::ASSIGN;
				instr.input1Int = std::stoi(parts[0]);
				instr.output = parts[2];
			}
		} else {
			instr.type = ParsedInstruction::OperatorType::INVALID;
			return instr;
		}
		return instr;
	}
}
