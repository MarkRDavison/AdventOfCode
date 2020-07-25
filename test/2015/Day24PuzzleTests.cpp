#include <catch/catch.hpp>
#include <2015/Day24Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 24 Part 1 Example works", "[2015][Day24]") {
		const std::vector<int> input = {
			1,2,3,4,5,7,8,9,10,11
		};

		REQUIRE(99 == Day24Puzzle::findSmallestQuantumEntaglement(input, 3));
	}
	TEST_CASE("2015 Day 24 Part 2 Example works", "[2015][Day24]") {
		const std::vector<int> input = {
			1,2,3,4,5,7,8,9,10,11
		};

		REQUIRE(44 == Day24Puzzle::findSmallestQuantumEntaglement(input, 4));
	}

}
