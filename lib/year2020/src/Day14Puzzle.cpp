#include <2020/Day14Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyTwenty {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2020, 14) {
	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
