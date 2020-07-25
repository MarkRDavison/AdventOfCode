#include <2015/Day25Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <cmath>

namespace TwentyFifteen {
	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Let It Snow", 2015, 25) {

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
		const auto& s = ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " ,.");

		return { 
			std::to_string(getAnswer(stoi(s[s.size() - 1]), stoi(s[s.size() - 3]), start)), 
			"Free Star ***" 
		};
	}
	NumberType Day25Puzzle::getAnswer(int _column, int _row, NumberType _start) {
		const auto iterate = [](NumberType _value)->NumberType {
			return (_value * MULTIPLIER) % MODULATOR;
		};
		const auto getIndex = [](int _x, int _y) -> int {
			return  (_x + _y - 2) * (_x + _y - 1) / 2 + _x;
		};
		
		const int iterations = getIndex(_column, _row);
		NumberType answer = _start;
		for (int i = 1; i < iterations; ++i) {
			answer = iterate(answer);
		}
		return answer;
	}
}
