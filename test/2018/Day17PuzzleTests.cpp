#include <catch/catch.hpp>
#include <2018/Day17Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 17 Part 1 & 2 Example works", "[2018][Day17]") {
		const std::vector<std::string> input = {
			"x=495, y=2..7",
			"y=7, x=495..501",
			"x=501, y=3..7",
			"x=498, y=2..4",
			"x=506, y=1..2",
			"x=498, y=10..13",
			"x=504, y=10..13",
			"y=13, x=498..504",
		};

		Day17Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("57" == answers.first);
		REQUIRE("29" == answers.second);
	}

}