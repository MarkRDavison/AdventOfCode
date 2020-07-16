#include <2016/Day23Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2016, 23) {

	}
	Day23Puzzle::~Day23Puzzle() {

	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
