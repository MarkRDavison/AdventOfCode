#include <2019/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Pathfinding.hpp>
#include <algorithm>
#include <numeric>

namespace TwentyNineteen {

	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Universal Orbit Map", 2019, 6) {

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
		core::EdgeNetwork network{};

		const std::string centerOfMass = "COM";
		const std::string you = "YOU";
		const std::string santa = "SAN";

		std::for_each(m_InputLines.begin(), m_InputLines.end(), [&network](const std::string& _str) -> void {
			const auto& pair = core::StringExtensions::splitStringByDelimeter(_str, ")");
			network.addEdge(pair[0], pair[1]);
			network.addEdge(pair[1], pair[0]);
		});

		auto tc = network.performDepthFirstSearch(centerOfMass, "");
		auto part1Network = std::accumulate(tc.begin(), tc.end(), 0u, [](unsigned _a, const auto& _p) -> unsigned { return _a + _p.second.second; });			   
		auto part2Network = network.getShortestPath(you, santa).size() - 3; // Subtract 3, 1 for santa/you node, and another because this counts nodes not edges

		return { std::to_string(part1Network), std::to_string(part2Network) };
	}
}
