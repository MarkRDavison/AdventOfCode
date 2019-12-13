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
	
	TEST_CASE("Priority queue stuff") {


		internal::PriorityQueue<core::Vector2i, float> queue2;

		queue2.put(core::Vector2i{ 3,3 }, 3.0f);
		queue2.put(core::Vector2i{ 2,2 }, 2.0f);
		queue2.put(core::Vector2i{ 5,5 }, 5.0f);
		queue2.put(core::Vector2i{ 1,1 }, 1.0f);
		queue2.put(core::Vector2i{ 4,4 }, 4.0f);

		while (!queue2.empty()) {
			auto v = queue2.get();
			std::cout << "asdasd" << v.x << std::endl;
		}

	}

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

		std::cout << "========================================" << std::endl;
		for (unsigned y = 0; y < height; ++y) {
			auto& row = network.getCells()[y];
			for (unsigned x = 0; x < width; ++x) {
				const Cell& c = row[x];
				if (c.canPass) {
					std::cout << ".";
				} else {
					std::cout << "#";
				}
			}
			std::cout << std::endl;
		}
		std::cout << "========================================" << std::endl;

		const auto& path = network.performAStarSearch({ 1,1 }, { static_cast<int>(width) - 2, static_cast<int>(height) - 2 });
		for (unsigned y = 0; y < height; ++y) {
			auto& row = network.getCells()[y];
			for (unsigned x = 0; x < width; ++x) {
				const Cell& c = row[x];
				if (c.canPass) {
					if (std::find_if(path.begin(), path.end(), [x, y](const core::Vector2i& _pathCoord) -> bool { return _pathCoord.x == x && _pathCoord.y == y; }) != path.end()) {
						std::cout << "*";
					} else {
						std::cout << ".";
					}
				} else {
					std::cout << "#";
				}
			}
			std::cout << std::endl;
		}

		std::cout << "========================================" << std::endl;

	}
}