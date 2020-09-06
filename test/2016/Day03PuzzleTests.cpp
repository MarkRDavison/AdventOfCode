#include <catch/catch.hpp>
#include <2016/Day03Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 3 isValidTriangleWorks", "[2016][Day03]") {
		REQUIRE_FALSE(Day03Puzzle::isValidTriangle(5, 10, 25));
		REQUIRE(Day03Puzzle::isValidTriangle(10, 10, 10));
		REQUIRE(Day03Puzzle::isValidTriangle(10, 11, 12));
	}

}
