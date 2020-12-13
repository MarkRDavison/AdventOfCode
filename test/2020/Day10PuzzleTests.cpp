#include <catch/catch.hpp>
#include <2020/Day10Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 10 Examples work", "[2020][Day10]") {
	    const std::vector<std::string> input = {
"16",
"10",
"15",
"5",
"1",
"11",
"7",
"19",
"6",
"12",
"4"
		};

		const auto& parsed = Day10Puzzle::parse(input);

		const auto& part1 = Day10Puzzle::doPart1(parsed);
		const auto& part2 = Day10Puzzle::doPart2(parsed);

		REQUIRE("35" == part1);
		REQUIRE("8" == part2);
	}

}
