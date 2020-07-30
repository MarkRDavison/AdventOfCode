#include <catch/catch.hpp>
#include <2016/Day02Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 2 Part 1 Example work", "[2016][Day02]") {
		const std::vector<std::string> input = {
"ULL",
"RRDDD",
"LURDL",
"UUUUD"
		};

		REQUIRE("1985" == Day02Puzzle::doPart1(input));
	}

	TEST_CASE("2016 Day 2 Part 2 Example work", "[2016][Day02]") {
		const std::vector<std::string> input = {
"ULL",
"RRDDD",
"LURDL",
"UUUUD"
		};

		REQUIRE("5DB3" == Day02Puzzle::doPart2(input));
	}

}
