#include <catch/catch.hpp>
#include <2016/Day09Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 9 Part 1 Examples work", "[2016][Day09]") {
		REQUIRE( 6 == Day09Puzzle::doPart1("(6x1)(1x3)A"));
		REQUIRE( 6 == Day09Puzzle::doPart1("ADVENT"));
		REQUIRE( 7 == Day09Puzzle::doPart1("A(1x5)BC"));
		REQUIRE( 9 == Day09Puzzle::doPart1("(3x3)XYZ"));
		REQUIRE(11 == Day09Puzzle::doPart1("A(2x2)BCD(2x2)EFG"));
		REQUIRE(18 == Day09Puzzle::doPart1("X(8x2)(3x3)ABCY"));
	}

	TEST_CASE("2016 Day 9 Part 2 Examples work", "[2016][Day09]") {
		REQUIRE(9 == Day09Puzzle::doPart2("(3x3)XYZ"));
		REQUIRE(20 == Day09Puzzle::doPart2("X(8x2)(3x3)ABCY"));
		REQUIRE(241920 == Day09Puzzle::doPart2("(27x12)(20x12)(13x14)(7x10)(1x12)A"));
		REQUIRE(445 == Day09Puzzle::doPart2("(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN"));
	}

}
