#include <catch/catch.hpp>
#include <2016/Day05Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 5 isValidIndex works", "[2016][Day05]") {
		char next;
		REQUIRE(Day05Puzzle::isValidIndex("abc", 3231929, next));
		REQUIRE('1' == next);
		REQUIRE(Day05Puzzle::isValidIndex("abc", 5017308, next));
		REQUIRE('8' == next);
		REQUIRE(Day05Puzzle::isValidIndex("abc", 5278568, next));
		REQUIRE('f' == next);
	}

}
