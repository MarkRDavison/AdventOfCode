#include <2020/Day06Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

namespace TwentyTwenty {

	// TODO: Move this to utility framework
	std::vector<std::string> splitStringByLines2(const std::string& _parameter) {
		std::vector<std::string> result;
		std::stringstream stringStream(_parameter);
		std::string line;
		while (std::getline(stringStream, line)) {
			result.push_back(line);
		}

		return result;
	}
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Custom Customs", 2020, 6) {
	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(splitStringByLines2(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {

		const auto& parsed = parseInput(m_InputLines);

		auto part1 = doPart1(parsed);
		auto part2 = doPart2(parsed);


		return { part1, part2 };
	}

	std::vector<Day06Puzzle::Questions> Day06Puzzle::parseInput(const std::vector<std::string>& _input) {
		std::vector<Day06Puzzle::Questions> parsed;

		parsed.emplace_back();

		for (const auto& i : _input) {

			if (i.empty()) {
				parsed.emplace_back();
				continue;
			}

			auto& current = parsed.back();
			current.emplace_back();
			auto& qset = current.back();
			for (const char c : i) {
				qset.insert(c);
			}

		}

		return parsed;
	}

	std::string Day06Puzzle::doPart1(const std::vector<Questions>& _parsedInput) {

		int count = 0;

		for (const auto& input : _parsedInput) {
			std::set<char> uniqueAnswers;
			for (const auto& q : input) {
				for (const auto& answer : q) {
					uniqueAnswers.insert(answer);
				}
			}

			count += uniqueAnswers.size();
		}

		return std::to_string(count);;
	}
	std::string Day06Puzzle::doPart2(const std::vector<Questions>& _parsedInput) {
		int count = 0;

		for (const auto& t : _parsedInput) {
			for (const auto& c : t[0]) {
				bool valid = true;
				for (unsigned i = 1; i < t.size(); ++i) {
					if (t[i].count(c) <= 0) {
						valid = false;
						break;
					}
				}
				if (valid) {
					count++;
				}
			}

		}

		return std::to_string(count);;
	}
}
