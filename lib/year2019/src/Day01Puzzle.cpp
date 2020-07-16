#include <2019/Day01Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
