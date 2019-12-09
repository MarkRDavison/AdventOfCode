#include <catch/catch.hpp>
#include <2015/Day11Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 11 password is valid works", "[2015][Day11]") {
		REQUIRE_FALSE(Day11Puzzle::isValid("hijklmmn"));
		REQUIRE_FALSE(Day11Puzzle::isValid("abbceffg"));
		REQUIRE_FALSE(Day11Puzzle::isValid("abbcegjk"));
		REQUIRE(Day11Puzzle::isValid("abcdffaa"));
		REQUIRE(Day11Puzzle::isValid("ghjaabcc"));
	}

	TEST_CASE("Day 11 increment password works", "[2015][Day11]") {
		REQUIRE("aaaaaaab" == Day11Puzzle::incrementPassword("aaaaaaaa"));
		REQUIRE("aaaaaaba" == Day11Puzzle::incrementPassword("aaaaaaaz"));
		REQUIRE("hijklmmo" == Day11Puzzle::incrementPassword("hijklmmn"));
	}
}
