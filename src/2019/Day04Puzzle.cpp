#include <2019/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>

namespace TwentyNineteen {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Secure Container", 2019, 4) {

	}
	Day04Puzzle::~Day04Puzzle() {

	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	bool Day04Puzzle::isValid(int _number, bool _part1) {
		int digit_6 = _number % 10;
		int digit_5 = (_number / 10) % 10;
		int digit_4 = (_number / 100) % 10;
		int digit_3 = (_number / 1000) % 10;
		int digit_2 = (_number / 10000) % 10;
		int digit_1 = (_number / 100000) % 10;

		if (digit_6 < digit_5 ||
			digit_5 < digit_4 ||
			digit_4 < digit_3 ||
			digit_3 < digit_2 ||
			digit_2 < digit_1) {
			return false;
		}

		if (_part1) {
			if (digit_6 == digit_5 ||
				digit_5 == digit_4 ||
				digit_4 == digit_3 ||
				digit_3 == digit_2 ||
				digit_2 == digit_1) {
				return true;
			}
			return false;
		}

		// PART 2
		if (digit_6 == digit_5 ||
			digit_5 == digit_4 ||
			digit_4 == digit_3 ||
			digit_3 == digit_2 ||
			digit_2 == digit_1) {


			std::unordered_map<int, unsigned> counts;
			counts[digit_1]++;
			counts[digit_2]++;
			counts[digit_3]++;
			counts[digit_4]++;
			counts[digit_5]++;
			counts[digit_6]++;

			if (counts.size() != 6) {
				for (const auto& kvp : counts) {
					if (kvp.second == 2) {
						return true;
					}
				}
				return false;
			}
		}

		return false;
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {

		auto& p = core::StringExtensions::splitStringByDelimeter(m_InputLines[0], "-");
		const int minimum = std::atoi(p[0].c_str());
		const int maximum = std::atoi(p[1].c_str());

		int part1Count = 0;
		int part2Count = 0;

		for (int k = minimum; k <= maximum; ++k) {
			if (isValid(k, true)) {
				part1Count++;
			}
			if (isValid(k, false)) {
				part2Count++;
			}
		}

		return { std::to_string(part1Count), std::to_string(part2Count) };
	}
}
