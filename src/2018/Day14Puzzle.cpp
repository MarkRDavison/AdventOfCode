#include <2018/Day14Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {

	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("???", 2018, 14) {

	}
	Day14Puzzle::~Day14Puzzle() {

	}

	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {

		return { "???", "???" };
	}

}
