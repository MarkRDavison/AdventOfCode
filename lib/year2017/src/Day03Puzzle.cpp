#include <2017/Day03Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2017, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
