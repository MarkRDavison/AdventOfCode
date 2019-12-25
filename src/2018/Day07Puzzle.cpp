#include <2018/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2018, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
