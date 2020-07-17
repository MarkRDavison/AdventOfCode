#include <catch/catch.hpp>
#include <2015/Day10Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 10 Example works for 1 iteration", "[2015][Day10]") {
		REQUIRE(2 == Day10Puzzle::getResult("1", 1));
		REQUIRE(2 == Day10Puzzle::getResult("11", 1));
		REQUIRE(4 == Day10Puzzle::getResult("21", 1));
		REQUIRE(6 == Day10Puzzle::getResult("1211", 1));
		REQUIRE(6 == Day10Puzzle::getResult("111221", 1));
	}
	TEST_CASE("2015 Day 10 Example works for multiple iteration", "[2015][Day10]") {
		REQUIRE(6 == Day10Puzzle::getResult("1", 5));
	}

}
