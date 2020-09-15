#include <catch/catch.hpp>
#include <2016/Day14Puzzle.hpp>
#include <Core/MD5.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 14 hasTriple works", "[2016][Day14]") {
		char triple;
		REQUIRE(Day14Puzzle::hasTriple("cc38887a5", triple));
		REQUIRE('8' == triple);
		REQUIRE(Day14Puzzle::hasTriple("111cc38887a5", triple));
		REQUIRE('1' == triple);
		REQUIRE(Day14Puzzle::hasTriple("11cc3887a555", triple));
		REQUIRE('5' == triple);
		REQUIRE_FALSE(Day14Puzzle::hasTriple("11cc3887a55", triple));
	}

	TEST_CASE("2016 Day 14 hasQuintuple works", "[2016][Day14]") {
		REQUIRE(Day14Puzzle::hasQuintuple("1cc3288888587a5", '8'));
		REQUIRE(Day14Puzzle::hasQuintuple("11111cc3222587a5", '1'));
		REQUIRE(Day14Puzzle::hasQuintuple("11xcf111cc3222587a55555", '5'));
		REQUIRE_FALSE(Day14Puzzle::hasQuintuple("111111cc3222587a55", '5'));
		REQUIRE_FALSE(Day14Puzzle::hasQuintuple("111c3222587a55", '5'));
	}

	TEST_CASE("2016 Day 14 isKey works", "[2016][Day14]") {
		REQUIRE_FALSE(Day14Puzzle::isKey("abc", 17, false));
		REQUIRE_FALSE(Day14Puzzle::isKey("abc", 18, false));
		REQUIRE(Day14Puzzle::isKey("abc", 39, false));
		REQUIRE(Day14Puzzle::isKey("abc", 92, false));
		REQUIRE(Day14Puzzle::isKey("abc", 22728, false));
	}

	TEST_CASE("2016 Day 14 isKey works for key stretching", "[2016][Day14][slow]") {
		REQUIRE(Day14Puzzle::isKey("abc", 10, true));
	}

	TEST_CASE("2016 Day 14 getNthKeyIndex works", "[2016][Day14]") {
		REQUIRE(39 == Day14Puzzle::getNthKeyIndex("abc", 1, false));
	}

	TEST_CASE("2016 Day 14 getNthKeyIndex works for key stretching", "[2016][Day14][slow]") {
		REQUIRE(10 == Day14Puzzle::getNthKeyIndex("abc", 1, true));
	}

}
