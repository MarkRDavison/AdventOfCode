#include <2020/Day22Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyTwenty {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2020, 22) {
	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
