#include <2016/Day15Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2016, 15) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
