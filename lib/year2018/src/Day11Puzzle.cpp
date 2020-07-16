#include <2018/Day11Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyEighteen {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2018, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
