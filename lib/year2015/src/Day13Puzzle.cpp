#include <2015/Day13Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <Core/Pathfinding.hpp>
#include <unordered_map>
#include <unordered_set>

namespace TwentyFifteen {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Knights of the Dinner Table", 2015, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		const auto result = solve(m_InputLines);
		return { std::to_string(result.first), std::to_string(result.second) };
	}

	std::pair<int, int> Day13Puzzle::solve(const std::vector<std::string>& _input) {
		core::EdgeNetwork network;

		std::unordered_map<std::string, std::unordered_map<std::string, int>> costs;
		std::unordered_set<std::string> people;


		for (const auto& i : _input) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, " .");
			const std::string n1 = s[0];
			const std::string n2 = s[10];
			const bool gain = s[2] == "gain";
			const int amount = std::stoi(s[3]) * (gain ? +1 : -1);

			costs[n1][n2] += amount;
			people.insert(n1);
		}

		for (auto p1 = people.begin(); p1 != people.end(); p1++) {
			for (auto p2 = people.begin(); p2 != people.end(); p2++) {
				if (p1 == p2) {
					continue;
				}

				const auto p1_p2 = costs[*p1][*p2];
				const auto p2_p1 = costs[*p2][*p1];

				network.addEdge(*p1, *p2, static_cast<float>(p1_p2 + p2_p1));
			}
		}

		const auto& part1 = network.getLongestPathVisitingAllReturningToStart();

		const std::string me = "me";
		for (auto p1 = people.begin(); p1 != people.end(); p1++) {

			network.addEdge(*p1, me, 0.0f);
			network.addEdge(me, *p1, 0.0f);
		}

		const auto& part2 = network.getLongestPathVisitingAllReturningToStart();

		return { static_cast<int>(part1.second), static_cast<int>(part2.second) };
	}
}
