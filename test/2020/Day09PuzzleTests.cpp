#include <catch/catch.hpp>
#include <2020/Day09Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 9 Examples work", "[2020][Day09]") {
	    const std::vector<std::string> input = {
"35",
"20",
"15",
"25",
"47",
"40",
"62",
"55",
"65",
"95",
"102",
"117",
"150",
"182",
"127",
"219",
"299",
"277",
"309",
"576",
		};

		const auto& [part1, part2] = Day09Puzzle::solve(input, 5);
		REQUIRE(127 == part1);
		REQUIRE(62 == part2);
	}

}
