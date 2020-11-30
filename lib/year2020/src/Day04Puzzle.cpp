#include <2020/Day04Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyTwenty {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2020, 4) {
	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
