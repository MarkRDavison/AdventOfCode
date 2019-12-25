#include <2015/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2015, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
