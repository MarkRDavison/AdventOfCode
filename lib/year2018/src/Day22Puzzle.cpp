#include <2018/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2018, 22) {

	}
	Day22Puzzle::~Day22Puzzle() {

	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
