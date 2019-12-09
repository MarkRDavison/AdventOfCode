#include <2019/Day09Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2019/IntcodeMachine.hpp>

namespace TwentyNineteen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Sensor Boost", 2019, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {

		IntcodeMachine machine1{};
		machine1.loadProgram(m_InputLines[0]);
		machine1.setInput(1);
		machine1.haltWhenOutputSet(true);
		machine1.execute();

		IntcodeMachine machine2{};
		machine2.loadProgram(m_InputLines[0]);
		machine2.setInput(2);
		machine2.haltWhenOutputSet(true);
		machine2.execute();

		return { std::to_string(machine1.getOutput()), std::to_string(machine2.getOutput()) };
	}
}
