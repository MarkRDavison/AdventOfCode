#include <2015/Day07Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <cassert>

namespace TwentyFifteen {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Some Assembly Required", 2015, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		ResolvedMap resolvedValuesPart1;
		runLogic(m_InputLines, resolvedValuesPart1);

		ResolvedMap resolvedValuesPart2;
		resolvedValuesPart2["b"] = resolvedValuesPart1.at("a");
		runLogic(m_InputLines, resolvedValuesPart2);

		return { 
			std::to_string(resolvedValuesPart1.at("a")),
			std::to_string(resolvedValuesPart2.at("a"))
		};
	}

	inline bool isConstant(const std::string& _input) {
		return '0' <= _input[0] && _input[0] <= '9';
	}

	Day07ParsedLine Day07Puzzle::parseLine(const std::string& _input) {
		const auto& s = ze::StringExtensions::splitStringByDelimeter(_input, " ");

		Day07ParsedLine line;

		if (s.size() == 3) {
			line.type = InstructionType::INPUT;
			line.wireOutput = s[2];
			if (isConstant(s[0])) {
				line.signalTypeInput1 = SignalType::Constant;
				line.constantInput1 = std::stoi(s[0]);
			} else {
				line.signalTypeInput1 = SignalType::Wire;
				line.wireInput1 = s[0];
			}
		}
		else if (s[0] == "NOT") {
			line.type = InstructionType::NOT;
			line.wireOutput = s[3];
			if (isConstant(s[1])) {
				line.signalTypeInput1 = SignalType::Constant;
				line.constantInput1 = std::stoi(s[1]);
			} else {
				line.signalTypeInput1 = SignalType::Wire;
				line.wireInput1 = s[1];
			}
		}
		else if (s[1] == "AND") {
			line.type = InstructionType::AND;
			line.wireOutput = s[4];
			if (isConstant(s[0])) {
				line.signalTypeInput1 = SignalType::Constant;
				line.constantInput1 = std::stoi(s[0]);
			} else {
				line.signalTypeInput1 = SignalType::Wire;
				line.wireInput1 = s[0];
			}
			if (isConstant(s[2])) {
				line.signalTypeInput2 = SignalType::Constant;
				line.constantInput2 = std::stoi(s[2]);
			} else {
				line.signalTypeInput2 = SignalType::Wire;
				line.wireInput2 = s[2];
			}
		}
		else if (s[1] == "OR") {
			line.type = InstructionType::OR;
			line.wireOutput = s[4];
			if (isConstant(s[0])) {
				line.signalTypeInput1 = SignalType::Constant;
				line.constantInput1 = std::stoi(s[0]);
			} else {
				line.signalTypeInput1 = SignalType::Wire;
				line.wireInput1 = s[0];
			}
			if (isConstant(s[2])) {
				line.signalTypeInput2 = SignalType::Constant;
				line.constantInput2 = std::stoi(s[2]);
			} else {
				line.signalTypeInput2 = SignalType::Wire;
				line.wireInput2 = s[2];
			}
		}
		else if (s[1] == "LSHIFT") {
			line.type = InstructionType::LSHIFT;
			line.wireOutput = s[4];
			if (isConstant(s[0])) {
				line.signalTypeInput1 = SignalType::Constant;
				line.constantInput1 = std::stoi(s[0]);
			} else {
				line.signalTypeInput1 = SignalType::Wire;
				line.wireInput1 = s[0];
			}
			if (isConstant(s[2])) {
				line.signalTypeInput2 = SignalType::Constant;
				line.constantInput2 = std::stoi(s[2]);
			} else {
				line.signalTypeInput2 = SignalType::Wire;
				line.wireInput2 = s[2];
			}
		}
		else if (s[1] == "RSHIFT") {
			line.type = InstructionType::RSHIFT;
			line.wireOutput = s[4];
			if (isConstant(s[0])) {
				line.signalTypeInput1 = SignalType::Constant;
				line.constantInput1 = std::stoi(s[0]);
			} else {
				line.signalTypeInput1 = SignalType::Wire;
				line.wireInput1 = s[0];
			}
			if (isConstant(s[2])) {
				line.signalTypeInput2 = SignalType::Constant;
				line.constantInput2 = std::stoi(s[2]);
			} else {
				line.signalTypeInput2 = SignalType::Wire;
				line.wireInput2 = s[2];
			}
		}

		return line;
	}

	void Day07Puzzle::runLogic(const std::vector<std::string>& _input, ResolvedMap& _resolvedWires) {
		

		std::vector<std::pair<Day07ParsedLine, bool>> instructions;
		for (const auto& i : _input) {
			const auto& l = parseLine(i);
			instructions.emplace_back(l, _resolvedWires.count(l.wireOutput) > 0);
		}

		while (true) {
			bool allResolved = true;
			for (auto& [instr, resolved] : instructions) {
				if (resolved) {
					continue;
				}

				if (!isResolved(instr, _resolvedWires)) {
					allResolved = false;
					continue;
				}

				_resolvedWires[instr.wireOutput] = resolve(instr, _resolvedWires);
				resolved = true;
			}

			if (allResolved) { 
				break; 
			}
		}
	}
	bool Day07Puzzle::isResolved(const Day07ParsedLine& _line, const ResolvedMap& _resolvedWires) {
		if (_line.signalTypeInput1 == SignalType::Wire) {
			if (_resolvedWires.count(_line.wireInput1) == 0) {
				return false;
			}
		}

		if (_line.signalTypeInput2 == SignalType::Wire) {
			if (_resolvedWires.count(_line.wireInput2) == 0) {
				return false;
			}
		}

		return true;
	}
	SignalIntType Day07Puzzle::resolve(const Day07ParsedLine& _line, const ResolvedMap& _resolvedWires) {
		assert(isResolved(_line, _resolvedWires));

		switch (_line.type) {
		case InstructionType::INPUT:
			if (_line.signalTypeInput1 == SignalType::Constant) {
				return _line.constantInput1;
			}
			return _resolvedWires.at(_line.wireInput1);

		case InstructionType::AND:
		{
			const SignalIntType value1 = _line.signalTypeInput1 == SignalType::Constant
				? _line.constantInput1
				: _resolvedWires.at(_line.wireInput1);
			const SignalIntType value2 = _line.signalTypeInput2 == SignalType::Constant
				? _line.constantInput2
				: _resolvedWires.at(_line.wireInput2);

			return value1 & value2;
		}
		case InstructionType::OR:
		{
			const SignalIntType value1 = _line.signalTypeInput1 == SignalType::Constant
				? _line.constantInput1
				: _resolvedWires.at(_line.wireInput1);
			const SignalIntType value2 = _line.signalTypeInput2 == SignalType::Constant
				? _line.constantInput2
				: _resolvedWires.at(_line.wireInput2);

			return value1 | value2;
		}
		case InstructionType::LSHIFT:
		{
			const SignalIntType value1 = _line.signalTypeInput1 == SignalType::Constant
				? _line.constantInput1
				: _resolvedWires.at(_line.wireInput1);
			const SignalIntType value2 = _line.signalTypeInput2 == SignalType::Constant
				? _line.constantInput2
				: _resolvedWires.at(_line.wireInput2);

			return value1 << value2;
		}
		case InstructionType::RSHIFT:
		{
			const SignalIntType value1 = _line.signalTypeInput1 == SignalType::Constant
				? _line.constantInput1
				: _resolvedWires.at(_line.wireInput1);
			const SignalIntType value2 = _line.signalTypeInput2 == SignalType::Constant
				? _line.constantInput2
				: _resolvedWires.at(_line.wireInput2);

			return value1 >> value2;
		}
		case InstructionType::NOT:
		{
			const SignalIntType value1 = _line.signalTypeInput1 == SignalType::Constant
				? _line.constantInput1
				: _resolvedWires.at(_line.wireInput1);

			return (SignalIntType)~value1;
		}
		}

		return 0;
	}
}
