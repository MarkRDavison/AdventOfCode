#include <catch/catch.hpp>
#include <2015/Day02Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 2 Part 1 Examples work", "[2015][Day02]") {
		REQUIRE(58 == Day02Puzzle::getPart1(Day02Puzzle::ParsedInput{ 2,3,4 }));
		REQUIRE(43 == Day02Puzzle::getPart1(Day02Puzzle::ParsedInput{ 1,1,10 }));
		REQUIRE(175 == Day02Puzzle::getPart1(Day02Puzzle::ParsedInput{ 5,5,5 }));
		REQUIRE(273 == Day02Puzzle::getPart1(Day02Puzzle::ParsedInput{ 7,5,7 }));
	}

	TEST_CASE("2015 Day 2 Part 2 Example work", "[2015][Day02]") {
		REQUIRE(34 == Day02Puzzle::getPart2(Day02Puzzle::ParsedInput{ 2,3,4 }));
		REQUIRE(14 == Day02Puzzle::getPart2(Day02Puzzle::ParsedInput{ 1,1,10 }));
	}

}
