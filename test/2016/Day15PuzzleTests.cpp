#include <catch/catch.hpp>
#include <2016/Day15Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 15 getNumberAndStartingPositions works", "[2016][Day15]") {
	    const std::vector<std::string> input = {
"Disc #1 has 5 positions; at time = 0, it is at position 4.",
"Disc #2 has 2 positions; at time = 0, it is at position 1."
		};

		const auto& p = Day15Puzzle::getNumberAndStartingPositions(input);

		REQUIRE(2 == p.size());

		REQUIRE(5 == p[0].first);
		REQUIRE(4 == p[0].second);

		REQUIRE(2 == p[1].first);
		REQUIRE(1 == p[1].second);
	}

	TEST_CASE("2016 Day 15 isValidFromStartTime works", "[2016][Day15]") {
		const std::vector<std::pair<int, int>> positions = {
			{5,4},
			{2,1}
		};

		REQUIRE_FALSE(Day15Puzzle::isValidFromStartTime(positions, 0));
		REQUIRE_FALSE(Day15Puzzle::isValidFromStartTime(positions, 1));
		REQUIRE_FALSE(Day15Puzzle::isValidFromStartTime(positions, 2));
		REQUIRE_FALSE(Day15Puzzle::isValidFromStartTime(positions, 3));
		REQUIRE_FALSE(Day15Puzzle::isValidFromStartTime(positions, 4));
		REQUIRE(Day15Puzzle::isValidFromStartTime(positions, 5));
	}

	TEST_CASE("2016 Day 15 getFirstTime works", "[2016][Day15]") {
		const std::vector<std::pair<int, int>> positions = {
			{5,4},
			{2,1}
		};

		REQUIRE(5 == Day15Puzzle::getFirstTime(positions));
	}
}
