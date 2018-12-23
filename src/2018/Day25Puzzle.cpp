#include <2018/Day25Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {

	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("???", 2018, 25) {

	}
	Day25Puzzle::~Day25Puzzle() {

	}

	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}
	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {
		return { "???", "???" };
	}
}