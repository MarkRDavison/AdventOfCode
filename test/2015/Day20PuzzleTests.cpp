#include <catch/catch.hpp>
#include <2015/Day20Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 20 Part 1 Example works", "[2015][Day20]") {
		REQUIRE(10 == Day20Puzzle::getNumberOfPresentsForHouseNumber(1));
		REQUIRE(30 == Day20Puzzle::getNumberOfPresentsForHouseNumber(2));
		REQUIRE(40 == Day20Puzzle::getNumberOfPresentsForHouseNumber(3));
		REQUIRE(70 == Day20Puzzle::getNumberOfPresentsForHouseNumber(4));
		REQUIRE(60 == Day20Puzzle::getNumberOfPresentsForHouseNumber(5));
		REQUIRE(120 == Day20Puzzle::getNumberOfPresentsForHouseNumber(6));
		REQUIRE(80 == Day20Puzzle::getNumberOfPresentsForHouseNumber(7));
		REQUIRE(150 == Day20Puzzle::getNumberOfPresentsForHouseNumber(8));
		REQUIRE(130 == Day20Puzzle::getNumberOfPresentsForHouseNumber(9));
	}
	
	//TEST_CASE("2015 Day 20 Part 2 Example work", "[2015][Day20]") {
	//    const std::vector<std::string> input = {};
	//
	//    Day20Puzzle puzzle{};
	//    puzzle.setVerbose(true);
	//    puzzle.setInputLines(input);
	//
	//    auto answers = puzzle.fastSolve();
	//}

}
