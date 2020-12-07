#include <2020/Day07Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>

#include <cassert>
#include <set>

namespace TwentyTwenty {

	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Handy Haversacks", 2020, 7) {
	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {

		const auto& parsed = Day07Puzzle::parseInput(m_InputLines);

		const auto& part1 = Day07Puzzle::doPart1(parsed);
		const auto& part2 = Day07Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	std::string Day07Puzzle::doPart1(const std::vector<Day7Struct>& _input) {

		const std::string start = "shiny gold";

		std::map<std::string, std::set<std::string>> info;

		for (const auto& s : _input) {
			for (const auto& [k, v] : s.contained) {
				info[k].insert(s.parent);
			}
		}

		std::set<std::string> uniqueHeldBy;

		std::function<void(const std::string&)> recurser =
			[&recurser, &info, &uniqueHeldBy](const std::string& _current) -> void {
			uniqueHeldBy.insert(_current);
			if (info.count(_current) != 0) {
				for (const auto& kv : info[_current]) {
					recurser(kv);
				}
			}
		};

		recurser(start);

		return std::to_string(uniqueHeldBy.size() - 1);
	}
	std::string Day07Puzzle::doPart2(const std::vector<Day7Struct>& _input) {

		const std::string start = "shiny gold";

		std::map<std::string, std::map<std::string, int>> info;
		for (const auto& s : _input) {
			for (const auto& [k, v] : s.contained) {
				info[s.parent][k] += v;
			}
		}

		std::function<int(const std::string&)> recurser = [&recurser , &info](const std::string& _current) -> int {
			int amount = 1;
			for (const auto& child : info[_current]) {
				amount += child.second * recurser(child.first);
			}

			return amount;
		};

		const int bags = recurser(start) - 1;

		return std::to_string(bags);
	}

	std::vector<Day7Struct> Day07Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		std::vector<Day7Struct> parsed;

		for (const auto& input : _inputLines) {

			const auto& parts = ze::StringExtensions::splitStringByDelimeter(input, " ");

			assert(parts[2] == "bags");
			assert(parts[3] == "contain");

			auto& next = parsed.emplace_back();
			next.parent = parts[0] + " " + parts[1];

			for (unsigned i = 4; i < parts.size(); i += 4) {
				const std::string child = parts[i+1] + " " + parts[i+2];
				const auto amountString = parts[i];
				if (amountString == "no") {
					break;
				}
				const int amount = std::stoi(amountString);

				next.contained[child] = amount;
			}
		}

		return parsed;
	}
}
