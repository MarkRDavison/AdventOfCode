#include <catch/catch.hpp>
#include <2018/Day01Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 1 Part 1 Example work", "[2018][Day1]") {
		const std::vector<std::string> input = {
"+3",
"+3",
"+4",
"-2",
"-4"
		};

		Day01Puzzle puzzle{};
		puzzle.setVerbose(true);

		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("4" == answers.first);
	}

	TEST_CASE("Day 1 Part 2 Example work", "[2018][Day1]") {
		const std::vector<std::string> input = {
"+3",
"+3",
"+4",
"-2",
"-4"
		};

		Day01Puzzle puzzle{};
		puzzle.setVerbose(true);

		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("10" == answers.second);
	}
	
}
