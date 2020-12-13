#include <catch/catch.hpp>
#include <2020/Day13Puzzle.hpp>
#include <iostream>
#include <numeric>
#include <vector>
#include <execution>

namespace TwentyTwenty {

	TEST_CASE("Day 13 Examples work", "[2020][Day13]") {
	    const std::vector<std::string> input = {
			"939",
			"7,13,x,x,59,x,31,19"
		};

		const auto& parsed = Day13Puzzle::parseInput(input);

		REQUIRE(939 == parsed.earliest);
		REQUIRE(parsed.busIds.count(7) > 0);
		REQUIRE(parsed.busIds.count(13) > 0);
		REQUIRE(parsed.busIds.count(59) > 0);
		REQUIRE(parsed.busIds.count(31) > 0);
		REQUIRE(parsed.busIds.count(19) > 0);

		const auto& part1 = Day13Puzzle::doPart1(parsed);
		const auto& part2 = Day13Puzzle::doPart2(parsed);

		REQUIRE("295" == part1);
		REQUIRE("1068781" == part2);
	}
}
