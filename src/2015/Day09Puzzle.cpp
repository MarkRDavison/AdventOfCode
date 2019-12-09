#include <2015/Day09Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>
#include <algorithm>
#include <map>

namespace TwentyFifteen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("All in a Single Night", 2015, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {

		std::unordered_set<std::string> cities;
		std::map<std::string, std::map<std::string, unsigned>> distances;

		for (const auto& path : m_InputLines) {
			const auto& parts = core::StringExtensions::splitStringByDelimeter(path, " ");
			const std::string from = parts[0];
			const std::string to = parts[2];
			const float weight = std::stof(parts[4]);

			cities.insert(to);
			cities.insert(from);
			distances[from][to] = distances[to][from] = (unsigned)weight;
		}
		std::vector<std::string> citiesVec;
		for (const auto & c : cities) {
			citiesVec.push_back(c);

		}
		unsigned bestCost = std::numeric_limits<unsigned>::max();
		unsigned worstCost = 0;
		std::sort(citiesVec.begin(), citiesVec.end());
		do {
			unsigned cost = 0;
			for (unsigned i = 1; i < citiesVec.size(); ++i) {
				cost += distances[citiesVec[i - 1]][citiesVec[i]];
			}

			if (cost < bestCost) {
				bestCost = cost;
			}
			if (cost > worstCost) {
				worstCost = cost;
			}
		} while (std::next_permutation(citiesVec.data(), citiesVec.data() + citiesVec.size()));

		return { std::to_string(bestCost), std::to_string(worstCost) };
	}
}
