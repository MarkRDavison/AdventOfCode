#include <catch/catch.hpp>
#include <2016/Day19Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 19 solveElfPresents works", "[2016][Day19]") {
		REQUIRE(3 == Day19Puzzle::solveElfPresents(5));
	}
	TEST_CASE("2016 Day 19 solveElfPresentsAcross works", "[2016][Day19]") {
		REQUIRE(2 == Day19Puzzle::solveElfPresentsAcross(5));
		REQUIRE(3 == Day19Puzzle::solveElfPresentsAcross(6));
		REQUIRE(7 == Day19Puzzle::solveElfPresentsAcross(8));
	}

}
