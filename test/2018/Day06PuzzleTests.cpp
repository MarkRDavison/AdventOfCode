#include <catch/catch.hpp>
#include <2018/Day06Puzzle.hpp>

namespace TwentyEighteen {
	
	TEST_CASE("Day 6 Part 1 Example works", "[2018][Day6]") {
		const std::vector<std::string> input = {
			"1, 1",
			"1, 6",
			"8, 3",
			"3, 4",
			"5, 5",
			"8, 9",
		};

		Day06Puzzle puzzle(30);
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("17" == answers.first);
		REQUIRE("16" == answers.second);
	}

}