#include <catch/catch.hpp>
#include <Core/Pathfinding.hpp>
#include <Core/StringExtensions.hpp>
#include <iostream>

namespace core {

	TEST_CASE("Test shortest path in edge graph", "[Core][Pathfinding]") {
		const std::vector<std::string> input = {
"COM)B",
"B)C",
"C)D",
"D)E",
"E)F",
"B)G",
"G)H",
"D)I",
"E)J",
"J)K",
"K)L",
"K)X",
"I)Y" };

		EdgeNetwork network{};

		const std::string start = "X";
		const std::string end = "Y";

		for (const auto& inp : input) {
			const auto& pair = core::StringExtensions::splitStringByDelimeter(inp, ")");
			network.addEdge(pair[0], pair[1]);
			network.addEdge(pair[1], pair[0]);
		}

		REQUIRE(7 == network.getShortestPath(start, end).size());

	}

}