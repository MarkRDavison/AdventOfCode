#include <catch/catch.hpp>
#include <2018/Day09Puzzle.hpp>

namespace TwentyEighteen {
	
	TEST_CASE("Day 9 Part 1 Example works", "[2018][Day9]") {
		const std::string input = "10 players; last marble is worth 1618 points";

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines({ input });

		auto answers = puzzle.fastSolve();

		REQUIRE("8317" == answers.first);
	}

}