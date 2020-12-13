#include <2020/Day10Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>
#include <unordered_map>

namespace TwentyTwenty {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2020, 10) {
	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		const auto& parsed = Day10Puzzle::parse(m_InputLines);

		const auto& part1 = Day10Puzzle::doPart1(parsed);
		const auto& part2 = Day10Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	std::vector<Day10NumberValue> Day10Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<Day10NumberValue> parsed;

		std::transform(_inputLines.begin(), _inputLines.end(), std::back_inserter(parsed),
			[](const std::string& _str) -> Day10NumberValue {
				return std::stoll(_str);
			});

		return parsed;
	}

	std::string Day10Puzzle::doPart1(const std::vector<Day10NumberValue>& _parsed) {
		const auto max = *std::max_element(_parsed.begin(), _parsed.end());

		const auto rating = max + 3;

		auto copy(_parsed);
		copy.push_back(0);
		copy.push_back(rating);
		std::sort(copy.begin(), copy.end());

		int count1Diff = 0;
		int count3Diff = 0;

		for (unsigned i = 1; i < copy.size(); ++i) {
			if (copy[i] - copy[i - 1] == 1) {
				count1Diff++;
			}
			else if (copy[i] - copy[i - 1] == 3) {
				count3Diff++;
			}
		}

		return std::to_string(count1Diff * count3Diff);
	}
	
	struct pair_hash {
		std::size_t operator () (const std::pair<Day10NumberValue, Day10NumberValue>& p) const {
			auto h1 = std::hash<Day10NumberValue>{}(p.first);
			auto h2 = std::hash<Day10NumberValue>{}(p.second);
			return h1 ^ h2;
		}
	};

	static Day10NumberValue Recurser(const Day10NumberValue*_values, unsigned _length, Day10NumberValue _start, Day10NumberValue _end, std::unordered_map<std::pair<Day10NumberValue, Day10NumberValue>, Day10NumberValue, pair_hash>& _memoized) {
		auto key = std::make_pair((Day10NumberValue)_length, _start);

		if (_memoized.find(key) != _memoized.end()) {
			return _memoized.at(key);
		}

		Day10NumberValue number = 0;

		if (_end - _start <= 3) {
			number += 1;
		}
		if (_length == 0) {
			return number;
		}
		if (_values[0] - _start <= 3) {
			number += Recurser(_values + 1, _length - 1, _values[0], _end, _memoized);
		}

		number += Recurser(_values + 1, _length - 1, _start, _end, _memoized);
		_memoized[key] = number;

		return number;
	}
	std::string Day10Puzzle::doPart2(const std::vector<Day10NumberValue>& _parsed) {
		const auto max = *std::max_element(_parsed.begin(), _parsed.end());

		const auto rating = max + 3;

		auto copy(_parsed);
		std::sort(copy.begin(), copy.end());

		std::unordered_map<std::pair<Day10NumberValue, Day10NumberValue>, Day10NumberValue, pair_hash> memoized;

		const auto part2 = Recurser(copy.data(), copy.size(), 0, rating, memoized);

		return std::to_string(part2);
	}
}
