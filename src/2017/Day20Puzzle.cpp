#include <2017/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2017, 20) {

	}
	Day20Puzzle::~Day20Puzzle() {

	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
