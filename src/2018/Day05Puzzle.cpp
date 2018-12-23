#include <2018/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {

	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("???", 2018, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}

	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {

		return { "???", "???" };
	}

}
