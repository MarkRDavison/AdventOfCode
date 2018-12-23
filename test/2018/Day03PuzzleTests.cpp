#include <catch/catch.hpp>
#include <2018/Day03Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 3 Part 1 Example works", "[2018][Day3]") {
		const std::vector<std::string> input = {
			"#1 @ 1,3: 4x4",
			"#2 @ 3,1: 4x4",
			"#3 @ 5,5: 2x2",
		};

		Day03Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve();

		REQUIRE("4" == answer.first);
	}

	TEST_CASE("Day 3 Part 2 Example works", "[2018][Day3]") {
		const std::vector<std::string> input = {
			"#1 @ 1,3: 4x4",
			"#2 @ 3,1: 4x4",
			"#3 @ 5,5: 2x2",
		};

		Day03Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve();

		REQUIRE("3" == answer.second);
	}

}