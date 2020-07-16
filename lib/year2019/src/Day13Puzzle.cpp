#include <2019/Day13Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
