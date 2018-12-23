#include <2018/Day17Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {

	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("???", 2018, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}

	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {

		return { "???", "???" };
	}

}
