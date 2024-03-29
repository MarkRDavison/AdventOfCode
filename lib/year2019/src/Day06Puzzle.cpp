#include <2019/Day06Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
