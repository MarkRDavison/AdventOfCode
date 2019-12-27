#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
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

	struct Cell {
		bool canPass{ true };
		bool valid() const { return canPass; }

		float costTo(const Cell& _target) const {
			return 1.0f;
		}
	};

	TEST_CASE("2D cartesian A* pathfinding works", "[Core][Pathfinding]") {

		CartesianNetwork<Cell> network{};

		std::vector<std::string> map = {
"####################",
"#..................#",
"#..................#",
"##############.....#",
"#..................#",
"#..................#",
"#...################",
"#.....##...........#",
"#.....##...........#",
"#.....##...........#",
"#.....##...######..#",
"#.....##.....#.....#",
"#.....##.....#.....#",
"#.....##.....#.....#",
"#.....##.....#.....#",
"#.....##.....#.....#",
"#.....##.....#.....#",
"#.....##.....#.....#",
"#.....##.....#.....#",
"#............#.....#",
"####################"
		};

		unsigned height = map.size();
		unsigned width = map[0].size();

		for (unsigned y = 0; y < height; ++y) {
			auto& row = network.getCells().emplace_back();
			for (unsigned x = 0; x < width; ++x) {
				Cell& cell = row.emplace_back();
				if (map[y][x] == '#') {
					cell.canPass = false;
				}
			}
		}
		const auto& path = network.performAStarSearch({ 1,1 }, { static_cast<int>(width) - 2, static_cast<int>(height) - 2 });
	}
}