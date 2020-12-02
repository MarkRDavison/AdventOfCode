#include <2020/Day02Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyTwenty {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2020, 2) {
	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	bool isPasswordValid1(int _min, int _max, char _c, std::string _password) {

		int count = 0;
		for (const auto& c : _password) {
			if (c == _c) {
				count++;
			}
		}


		return _min <= count && count <= _max;
	}
	bool isPasswordValid2(int _first, int _second, char _c, std::string _password) {

		char first = _password[_first - 1];
		char second = _password[_second - 1];

		return 
			first == _c && second != _c ||
			first != _c && second == _c;
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {

		std::string part1;
		std::string part2;

		int part1count = 0;
		int part2count = 0;

		for (const auto& i : m_InputLines) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(i, "- :");
			const auto min = std::stoi(parts[0]);
			const auto max = std::stoi(parts[1]);
			const auto c = parts[2][0];
			const auto password = parts[3];

			if (isPasswordValid1(min, max, c, password)) {
				part1count++;
			}
			if (isPasswordValid2(min, max, c, password)) {
				part2count++;
			}
		}

		part1 = std::to_string(part1count);
		part2 = std::to_string(part2count);

		return { part1, part2 };
	}
}
