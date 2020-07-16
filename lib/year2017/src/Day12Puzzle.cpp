#include <2017/Day12Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2017, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
