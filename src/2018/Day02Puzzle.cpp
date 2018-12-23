#include <2018/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <unordered_map>

namespace TwentyEighteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Inventory Management System", 2018, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}

	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		std::size_t twos = 0;
		std::size_t threes = 0;

		std::string part2Result;

		for (std::size_t i = 0; i < m_InputLines.size(); ++i) {
			const std::string& _str1 = m_InputLines[i];
			for (std::size_t j = i + 1; j < m_InputLines.size(); ++j) {
				const std::string& _str2 = m_InputLines[j];

				std::size_t difference = 0;
				for (std::size_t k = 0; k < _str1.size(); ++k) {
					if (_str1[k] != _str2[k]) {
						difference++;
						if (difference > 1) {
							break;
						}
					}
				}

				if (difference == 1) {
					for (std::size_t k = 0; k < _str1.size(); ++k) {
						if (_str1[k] == _str2[k]) {
							part2Result += _str1[k];
						}
					}
				}
			}
			std::unordered_map<char, int> charMap;
			for (char c : _str1) {
				charMap[c] += 1;
			}
			std::size_t two = 0;
			std::size_t three = 0;
			for (const auto& kvp : charMap) {
				if (kvp.second == 2) {
					two = 1;
				} else if (kvp.second == 3) {
					three = 1;
				}
			}

			twos += two;
			threes += three;
		}

		return { std::to_string(twos * threes), part2Result };
	}

}
