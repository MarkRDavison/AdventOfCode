#include <2016/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>

namespace TwentySixteen {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Signals and Noise", 2016, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {

		std::string part1;
		std::string part2;
		const unsigned size = m_InputLines[0].size();

		std::vector<std::unordered_map<char, int>> occurences(size);

		for (const std::string& _line : m_InputLines) {
			for (unsigned i = 0; i < size; ++i) {
				occurences[i][_line[i]] += 1;
			}
		}

		for (unsigned i = 0; i < size; ++i) {
			const auto& max = std::max_element(occurences[i].begin(), occurences[i].end(), 
				[&](const auto & _lhs, const auto & _rhs) -> int {
					return _lhs.second < _rhs.second;
				}
			);
			const auto& min = std::min_element(occurences[i].begin(), occurences[i].end(), 
				[&](const auto & _lhs, const auto & _rhs) -> int {
					return _lhs.second < _rhs.second;
				}
			);

			part1 += max->first;
			part2 += min->first;
		}		

		return { part1, part2 };
	}
}
