#include <2015/Day18Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2015, 18) {

	}
	Day18Puzzle::~Day18Puzzle() {

	}


	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
