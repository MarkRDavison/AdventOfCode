#include <2018/Day08Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyEighteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2018, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
