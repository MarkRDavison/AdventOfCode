#include <2017/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2017, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
