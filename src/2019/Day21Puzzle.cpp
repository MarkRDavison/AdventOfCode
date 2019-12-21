#include <2019/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Springdroid Adventure", 2019, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	
	std::vector<IntcodeValue> encode(const std::vector<std::string>& _springInstructions, const std::string& _mode) {
		std::vector<IntcodeValue> encoded;

		for (const auto& instr : _springInstructions) {
			for (char c : instr) {
				encoded.push_back((IntcodeValue)c);
			}
			encoded.push_back(10);
		}
		for (char c : _mode) {
			encoded.push_back((IntcodeValue)c);
		}
		encoded.push_back(10);

		return encoded;
	}

	IntcodeValue Day21Puzzle::getResultOrDumpError(const std::vector<std::string>& _springInstructions, const std::string& _mode) {
		IntcodeValue result = 0;
		IntcodeMachine m{};
		m.loadProgram(m_InputLines[0]);
		std::vector<IntcodeValue> output;
		for (auto ascii : encode(_springInstructions, _mode)) {
			m.setInput(ascii);
		}

		while (true) {
			auto status = m.executeResult();
			if (status == IntcodeMachine::ExecutionResult::Halt) {
				return output.back();
				break;
			} else if (status == IntcodeMachine::ExecutionResult::Output) {
				IntcodeValue out = m.getOutput();
				output.push_back(out);
			} else if (status == IntcodeMachine::ExecutionResult::Input) {
				break;
			}
		}

		std::string s;
		for (auto o : output) {
			if (o == 10) {
				s += '\n';
			} else {
				s += (char)o;
			}
		}
		std::cout << s << std::endl;
		return -1;
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		auto part1 = getResultOrDumpError({
			"NOT A T",
			"OR T J",
			"NOT B T",
			"OR T J",
			"NOT C T",
			"OR T J",
			"AND D J"
			}, "WALK");
		auto part2 = getResultOrDumpError({
			"NOT B J",
			"NOT C T",
			"OR T J",
			"NOT A T",
			"OR T J",
			"AND D J",
			"OR E T",
			"OR H T",
			"AND T J"
			}, "RUN");

		return { std::to_string(part1), std::to_string(part2) };
	}
}
