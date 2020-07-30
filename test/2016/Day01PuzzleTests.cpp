#include <catch/catch.hpp>
#include <2016/Day01Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 1 Part 1 Examples work", "[2016][Day01]") {
		REQUIRE(5 == Day01Puzzle::getAnswers("R2, L3").first);
		REQUIRE(2 == Day01Puzzle::getAnswers("R2, R2, R2").first);
		REQUIRE(12 == Day01Puzzle::getAnswers("R5, L5, R5, R3").first);
	}

	TEST_CASE("2016 Day 1 Part 2 Example works", "[2016][Day01]") {
		REQUIRE(4 == Day01Puzzle::getAnswers("R8, R4, R4, R8").second);
	}

}
