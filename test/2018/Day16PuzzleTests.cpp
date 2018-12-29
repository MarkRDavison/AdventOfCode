#include <catch/catch.hpp>
#include <2018/Day16Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 16 Part 1 Example works", "[2018][Day16]") {
		const std::vector<std::string> input = {
"Before: [3, 2, 1, 1]",
"9 2 1 2",
"After:  [3, 2, 2, 1]",
		};

		Day16Puzzle puzzle(false);
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("1" == answers.first);
	}

}