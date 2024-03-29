#include <2022/Day19Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyTwo {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2022, 19) {
	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
