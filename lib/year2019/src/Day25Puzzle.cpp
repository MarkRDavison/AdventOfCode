#include <2019/Day25Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 25) {

	}
	Day25Puzzle::~Day25Puzzle() {

	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {
		return { "Part 1", "*** Free ***" };
	}
}
