#include <2019/Day21Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
