#include <2020/Day09Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>

namespace TwentyTwenty {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Encoding Error", 2020, 9) {
	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		const auto& [part1, part2] = Day09Puzzle::solve(m_InputLines, 25);

		return { std::to_string(part1), std::to_string(part2) };
	}

	static bool isValid(NumberType _current, const NumberType* _prevStart, NumberType _preamble) {

		std::vector<NumberType> previous(_prevStart, _prevStart + _preamble);

		for (unsigned i = 0; i < previous.size(); ++i) {
			for (unsigned j = i + 1; j < previous.size(); ++j) {
				if (previous[i] + previous[j] == _current) {
					return true;
				}
			}
		}

		return false;
	}

	static std::pair<NumberType, NumberType> getContiguousRange(NumberType _invalid, const std::vector<NumberType>& _numbers) {
		for (unsigned i = 0; i < _numbers.size(); ++i) {
			NumberType currentSum = _numbers[i];

			for (unsigned j = i + 1; j < _numbers.size(); ++j) {
				if (currentSum == _invalid) {
					NumberType min = std::numeric_limits<NumberType>::max();
					NumberType max = std::numeric_limits<NumberType>::min();

					for (unsigned k = i; k <= j - 1; ++k) {
						min = std::min(min, _numbers[k]);
						max = std::max(max, _numbers[k]);
					}

					return { min, max };
				}
				if (currentSum > _invalid || j == _numbers.size()) {
					break;
				}
				currentSum = currentSum + _numbers[j];
			}
		}

		return { 0, 0 };
	}
	std::pair<NumberType, NumberType> Day09Puzzle::solve(const std::vector<std::string>& _inputLines, NumberType _preambleLength) {
		std::vector<NumberType> parsed;
		std::transform(_inputLines.begin(), _inputLines.end(), std::back_inserter(parsed),
			[](const std::string& _str) -> NumberType {
				return std::stoll(_str);
			});

		NumberType part1 = 0;

		for (unsigned i = (unsigned)_preambleLength; i < parsed.size(); ++i) {
			if (!isValid(parsed[i], &parsed[i - (unsigned)_preambleLength], _preambleLength)) {
				part1 = parsed[i];
				break;
			}
		}

		const auto& [min, max] = getContiguousRange(part1, parsed);

		NumberType part2 = min + max;

		return { part1, part2 };
	}
}
