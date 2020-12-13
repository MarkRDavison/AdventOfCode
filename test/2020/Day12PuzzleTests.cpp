#include <catch/catch.hpp>
#include <2020/Day12Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 12 Examples work", "[2020][Day12]") {
	    const std::vector<std::string> input = {
"F10",
"N3",
"F7",
"R90",
"F11",
		};

		const auto& parsed = Day12Puzzle::parse(input);

		const auto part1 = Day12Puzzle::doPart1(parsed);
		const auto part2 = Day12Puzzle::doPart2(parsed);

		REQUIRE("25" == part1);
		REQUIRE("286" == part2);
	}

}
