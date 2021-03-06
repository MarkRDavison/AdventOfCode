#include <2018/Day09Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyEighteen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2018, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
