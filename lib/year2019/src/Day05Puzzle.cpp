#include <2019/Day05Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
