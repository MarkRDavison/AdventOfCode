#include <catch/catch.hpp>
#include <2018/Day14Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 14 Part 1 Example works", "[2018][Day14]") {
		const std::vector<std::string> input = {
			"9"
		};

		Day14Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve();

		REQUIRE("5158916779" == answer.first);
	}
	TEST_CASE("Day 14 Part 2 Example works", "[2018][Day14]") {
		const std::vector<std::string> input = {
			"59414"
		};

		Day14Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve();

		REQUIRE("2018" == answer.second);
	}

}