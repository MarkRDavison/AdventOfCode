#include <catch/catch.hpp>
#include <2020/Day07Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 7 Examples work", "[2020][Day07]") {
	    const std::vector<std::string> input = {
"light red bags contain 1 bright white bag, 2 muted yellow bags.",
"dark orange bags contain 3 bright white bags, 4 muted yellow bags.",
"bright white bags contain 1 shiny gold bag.",
"muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.",
"shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.",
"dark olive bags contain 3 faded blue bags, 4 dotted black bags.",
"vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.",
"faded blue bags contain no other bags.",
"dotted black bags contain no other bags."
		};

		const auto& parsed = Day07Puzzle::parseInput(input);

		const auto& part1 = Day07Puzzle::doPart1(parsed);
		const auto& part2 = Day07Puzzle::doPart2(parsed);

		REQUIRE("4" == part1);
		REQUIRE("32" == part2);
	}

}
