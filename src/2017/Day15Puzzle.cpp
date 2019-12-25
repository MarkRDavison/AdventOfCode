#include <2017/Day15Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2017, 15) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
