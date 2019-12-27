#include <2015/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <numeric>

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

	int Day01Puzzle::doPart1(const std::string& _input) {
		return std::accumulate(_input.begin(), _input.end(), 0, [](int _accumulate, char _c) -> int {
			return _accumulate + (_c == '(' ? 1 : -1);
		});
	}
	int Day01Puzzle::doPart2(const std::string& _input) {
		int part2 = 0;
		int location = 0;
		auto discard = std::accumulate(_input.begin(), _input.end(), 0, [&part2, &location](int _accumulate, char _c) -> int {
			if (part2 != 0) {
				return 0;
			}
			_accumulate += _c == '(' ? 1 : -1;
			location++;
			if (_accumulate == -1) {
				part2 = location;
			}
			return _accumulate;
		});

		return part2;
	}
	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		return { std::to_string(doPart1(m_InputLines[0])), std::to_string(doPart2(m_InputLines[0])) };
	}
}
