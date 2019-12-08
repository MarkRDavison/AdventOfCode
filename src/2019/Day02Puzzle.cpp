#include <2019/Day02Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

#define OPCODE_ADD 1
#define OPCODE_MUL 2
#define OPCODE_STOP 99

namespace TwentyNineteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("1202 Program Alarm", 2019, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {

		IntcodeMachine machine{};

		machine.loadProgram(m_InputLines[0]);

		machine.setValue(12, 1);
		machine.setValue(2, 2);

		machine.execute();

		unsigned part1 = machine.getValue(0);

		const long target = 19690720;
		const long guessMax = 99;
		const long guessMin = 0;

		for (long noun = guessMin; noun < guessMax; ++noun) {
			for (long verb = guessMin; verb < guessMax; ++verb) {
				machine.resetProgram();

				machine.setValue(noun, 1);
				machine.setValue(verb, 2);

				machine.execute();

				if (machine.getValue(0) == target) {
					return { std::to_string(part1), std::to_string(noun * 100 + verb) };
				}
			}
		}
		return { std::to_string(part1), "Could not find solution" };
	}
}
