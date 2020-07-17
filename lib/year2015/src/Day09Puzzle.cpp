#include <2015/Day09Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("All in a Single Night", 2015, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		core::EdgeNetwork network;
		Day09Puzzle::populateNetwork(network, m_InputLines);

		const auto& part1 = network.getShortestPathVisitingAll();
		const auto& part2 = network.getLongestPathVisitingAll();

		return { std::to_string(part1.second), std::to_string(part2.second) };
	}

	void Day09Puzzle::populateNetwork(core::EdgeNetwork& _network, const std::vector<std::string>& _input) {
		for (const auto& str : _input) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(str, " ");
			const auto& start = s[0];
			const auto& finish = s[2];
			const auto weight = std::stof(s[4]);

			_network.addEdge(finish, start, weight);
			_network.addEdge(start, finish, weight);
		}
	}
}
