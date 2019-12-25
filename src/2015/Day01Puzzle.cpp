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

	unsigned Day01Puzzle::doPart1(const std::string& _input) {
		unsigned floor = 0;
		for (char c : _input) {
			if (c == '(') {
				floor++;
			} else {
				floor--;
			}
		}
		return floor;
	}
	unsigned Day01Puzzle::doPart2(const std::string& _input) {
		unsigned index = 0;
		unsigned floor = 0;
		for (char c : _input) {
			index++;
			if (c == '(') {
				floor++;
			} else {
				floor--;
			}
			if (floor == -1) {
				break;
			}
		}
		return index;
	}
	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		return { std::to_string(doPart1(m_InputLines[0])), std::to_string(doPart2(m_InputLines[0])) };
	}
}
