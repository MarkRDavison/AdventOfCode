#include <2019/Day05Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Sunny with a Chance of Asteroids", 2019, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long getDiagnosticCode(const std::string& _program, long _input) {
		IntcodeMachine machine{};
		machine.loadProgram(_program);
		machine.setInput(_input);
		machine.execute();
		return machine.getOutput();
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		return { std::to_string(getDiagnosticCode(m_InputLines[0], 1)), std::to_string(getDiagnosticCode(m_InputLines[0], 5)) };
	}
}
