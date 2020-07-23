#include <catch/catch.hpp>
#include <2015/Day11Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 11 passwords are incremented correctly", "[2015][Day11]") {
		REQUIRE("abcdefgj" == Day11Puzzle::increment("abcdefgh"));
		REQUIRE("abcdefha" == Day11Puzzle::increment("abcdefgz"));
		REQUIRE("ghjaaaaa" == Day11Puzzle::increment("ghijklmn"));
	}
	TEST_CASE("2015 Day 11 password requirements are validated correctly", "[2015][Day11]") {
		REQUIRE_FALSE(Day11Puzzle::validate("hijklmmn"));
		REQUIRE_FALSE(Day11Puzzle::validate("abbceffg"));
		REQUIRE_FALSE(Day11Puzzle::validate("abbcegjk"));
		REQUIRE_FALSE(Day11Puzzle::validate("abcdefhh"));
		REQUIRE(Day11Puzzle::validate("abbcdffg"));
	}

	TEST_CASE("2015 Day 11 Part 1 Example work", "[2015][Day11]") {
		REQUIRE("abcdffaa" == Day11Puzzle::getNextPassword("abcdefgh"));
		REQUIRE("ghjaabcc" == Day11Puzzle::getNextPassword("ghijklmn"));
	}

}
