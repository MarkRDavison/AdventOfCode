#include <catch/catch.hpp>
#include <2015/Day10Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("calculateLookAndSay works", "[2015][Day10]") {
		REQUIRE("11" == Day10Puzzle::calculateLookAndSay("1"));
		REQUIRE("21" == Day10Puzzle::calculateLookAndSay("11"));
		REQUIRE("1211" == Day10Puzzle::calculateLookAndSay("21"));
		REQUIRE("111221" == Day10Puzzle::calculateLookAndSay("1211"));
		REQUIRE("312211" == Day10Puzzle::calculateLookAndSay("111221"));
	}

}
