#include <catch/catch.hpp>
#include <2015/Day14Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 14 parsing input works", "[2015][Day14]") {
		const std::vector<std::string> input = {
			"Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.",
			"Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds."
		};

		const auto& parsed = Day14Puzzle::parseInput(input);

		REQUIRE("Comet" == parsed[0].name);
		REQUIRE(14 == parsed[0].speed);
		REQUIRE(10 == parsed[0].duration);
		REQUIRE(127 == parsed[0].restDuration);

		REQUIRE("Dancer" == parsed[1].name);
		REQUIRE(16 == parsed[1].speed);
		REQUIRE(11 == parsed[1].duration);
		REQUIRE(162 == parsed[1].restDuration);

	}

	TEST_CASE("2015 Day 14 can calculate distance from time and info", "[2015][Day14]") {
		ReindeerInfo comet = { "Comet", 14, 10, 127 };
		ReindeerInfo dancer = { "Dancer", 16, 11, 162 };

		REQUIRE(14 == Day14Puzzle::getDistanceFromTime(comet, 1));
		REQUIRE(16 == Day14Puzzle::getDistanceFromTime(dancer, 1));

		REQUIRE(140 == Day14Puzzle::getDistanceFromTime(comet, 10));
		REQUIRE(160 == Day14Puzzle::getDistanceFromTime(dancer, 10));

		REQUIRE(140 == Day14Puzzle::getDistanceFromTime(comet, 11));
		REQUIRE(176 == Day14Puzzle::getDistanceFromTime(dancer, 11));

		REQUIRE(1120 == Day14Puzzle::getDistanceFromTime(comet, 1000));
		REQUIRE(1056 == Day14Puzzle::getDistanceFromTime(dancer, 1000));
	}

	TEST_CASE("2015 Day 14 Part 1 Example work", "[2015][Day14]") {
		ReindeerInfo comet = { "Comet", 14, 10, 127 };
		ReindeerInfo dancer = { "Dancer", 16, 11, 162 };

		const auto& result = Day14Puzzle::getMaxDistanceAfterTime({ comet, dancer }, 1000);

		REQUIRE(1120 == result.first);
		REQUIRE("Comet" == result.second);
	}

	TEST_CASE("2015 Day 14 Part 2 Example work", "[2015][Day14]") {
		ReindeerInfo comet = { "Comet", 14, 10, 127 };
		ReindeerInfo dancer = { "Dancer", 16, 11, 162 };

		const auto& result = Day14Puzzle::getMaxPointsAfterTime({ comet, dancer }, 1000);

		REQUIRE(689 == result.first);
		REQUIRE("Dancer" == result.second);
	}
	


}
