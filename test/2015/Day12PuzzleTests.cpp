#include <catch/catch.hpp>
#include <2015/Day12Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 12 summing from JSON basic works", "[2015][Day12]") {
		REQUIRE(6 == Day12Puzzle::sumNumbersBasic("[1,2,3]"));
		REQUIRE(6 == Day12Puzzle::sumNumbersBasic("{\"a\":2,\"b\":4}"));
		REQUIRE(3 == Day12Puzzle::sumNumbersBasic("[[[3]]]"));
		REQUIRE(3 == Day12Puzzle::sumNumbersBasic("{\"a\":{\"b\":4},\"c\":-1}"));
		REQUIRE(0 == Day12Puzzle::sumNumbersBasic("{\"a\":[-1,1]}"));
		REQUIRE(0 == Day12Puzzle::sumNumbersBasic("[-1,{\"a\":1}]"));
		REQUIRE(0 == Day12Puzzle::sumNumbersBasic("[]"));
		REQUIRE(0 == Day12Puzzle::sumNumbersBasic("{}"));
	}

	TEST_CASE("Day 12 summing from JSON excluding red works", "[2015][Day12]") {
		REQUIRE(6 == Day12Puzzle::sumNumbersExcludingRed("[1,2,3]"));
		REQUIRE(4 == Day12Puzzle::sumNumbersExcludingRed("[1,{\"c\":\"red\",\"b\":2},3]"));
		REQUIRE(0 == Day12Puzzle::sumNumbersExcludingRed("{\"d\":\"red\",\"e\":[1,2,3,4],\"f\":5}"));
		REQUIRE(6 == Day12Puzzle::sumNumbersExcludingRed("[1,\"red\",5]"));
	}

	TEST_CASE("Day 12 Part 1 Example work", "[2015][Day13]") {
		
		Day12Puzzle puzzle{};
		puzzle.setVerbose(true);
		core::InitialisationInfo info{};
		info.parameters.push_back("./Data/2015/Day12.txt");
		puzzle.initialise(info);
	
		auto answers = puzzle.fastSolve();
	}
}
