#include <catch/catch.hpp>
#include <2015/Day01Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 1 Part 1 Example work", "[2015][Day01]") {
		REQUIRE(+0 == Day01Puzzle::doPart1("(())"));
		REQUIRE(+0 == Day01Puzzle::doPart1("()()"));
		REQUIRE(+3 == Day01Puzzle::doPart1("((("));
		REQUIRE(+3 == Day01Puzzle::doPart1("(()(()("));
		REQUIRE(+3 == Day01Puzzle::doPart1("))((((("));
		REQUIRE(-1 == Day01Puzzle::doPart1("())"));
		REQUIRE(-1 == Day01Puzzle::doPart1("))("));
		REQUIRE(-3 == Day01Puzzle::doPart1(")))"));
		REQUIRE(-3 == Day01Puzzle::doPart1(")())())"));
	}

	TEST_CASE("2015 Day 1 Part 2 Example work", "[2015][Day01]") {
		REQUIRE(1 == Day01Puzzle::doPart2(")"));
		REQUIRE(5 == Day01Puzzle::doPart2("()())"));
	}

}
