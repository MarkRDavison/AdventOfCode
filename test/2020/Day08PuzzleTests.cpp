#include <catch/catch.hpp>
#include <2020/Day08Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 8 Examples work", "[2020][Day08]") {
	    const std::vector<std::string> input = {
"nop +0",
"acc +1",
"jmp +4",
"acc +3",
"jmp -3",
"acc -99",
"acc +1",
"jmp -4",
"acc +6"
		};

		const auto& parsed = Day08Puzzle::parseInput(input);

		const auto part1 = Day08Puzzle::doPart1(parsed);
		const auto part2 = Day08Puzzle::doPart2(parsed);

		REQUIRE("5" == part1);
		REQUIRE("8" == part2);
	}
}
