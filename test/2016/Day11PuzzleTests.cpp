#include <catch/catch.hpp>
#include <2016/Day11Puzzle.hpp>

namespace TwentySixteen {


	TEST_CASE("2016 Day 11 valid works", "[2016][Day11]") {
		Day11Puzzle::FacilityStateInfo info;
		REQUIRE(Day11Puzzle::FacilityState(1, { 2,1,3,1 }).valid(info));
		REQUIRE(Day11Puzzle::FacilityState(1, { 1,1,1,1 }).valid(info));
		REQUIRE_FALSE(Day11Puzzle::FacilityState(1, { 2,1,1,1 }).valid(info));
		REQUIRE_FALSE(Day11Puzzle::FacilityState(1, { 1,1,2,1 }).valid(info));

	}

	TEST_CASE("2016 Day 11 Part 1 Example work", "[2016][Day11]") {
		const std::vector<std::string> input = {
"The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.",
"The second floor contains a hydrogen generator.",
"The third floor contains a lithium generator.",
"The fourth floor contains nothing relevant."
		};

		auto [start, end, info] = Day11Puzzle::parseInput(input, false);
		REQUIRE(11 == Day11Puzzle::lengthOfPath(start, end, info));
	}

}
