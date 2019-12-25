#include <2015/Day16Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2015, 16) {

	}
	Day16Puzzle::~Day16Puzzle() {

	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
