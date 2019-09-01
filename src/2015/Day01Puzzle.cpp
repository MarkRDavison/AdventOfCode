#include <2015/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Not Quite Lisp", 2015, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		int floor = 0;
		int basementPosition = 0;
		int index = 1;
		for (const char c : m_InputLines[0]) {
			if (c == Up) {
				floor++;
			} else {
				floor--;
			}
			if (floor < 0 && basementPosition == 0) {
				basementPosition = index;
			}

			index++;
		}


		return { std::to_string(floor), std::to_string(basementPosition) };
	}
}
