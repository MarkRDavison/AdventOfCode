#include <catch/catch.hpp>
#include <2016/Day13Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 13 get traversable works", "[2016][Day13]") {
		REQUIRE(Day13Puzzle::getTraversable({ 0, 0 }, 10));
		REQUIRE_FALSE(Day13Puzzle::getTraversable({ 1, 0 }, 10));
		REQUIRE(Day13Puzzle::getTraversable({ 2, 0 }, 10));
		REQUIRE_FALSE(Day13Puzzle::getTraversable({ 3, 0 }, 10));
		REQUIRE_FALSE(Day13Puzzle::getTraversable({ 4, 0 }, 10));
		REQUIRE_FALSE(Day13Puzzle::getTraversable({ 5, 0 }, 10));
		REQUIRE_FALSE(Day13Puzzle::getTraversable({ 6, 0 }, 10));
		REQUIRE_FALSE(Day13Puzzle::getTraversable({ 2, 1 }, 10));
		REQUIRE(Day13Puzzle::getTraversable({ 1, 1 }, 10));
	}

	TEST_CASE("2016 Day 13 Part 1 Example work", "[2016][Day13]") {
		core::CartesianNetwork<OfficeCell> network;
		const OfficeInteger number = 10;
		const ze::Vector2<OfficeInteger> size = { 50, 50 };
		const ze::Vector2<OfficeInteger> start = { 1, 1 };
		const ze::Vector2<OfficeInteger> goal = { 7, 4 };

		Day13Puzzle::searchSpace(network, number, size);
		const auto& path = network.performAStarSearch(start, goal);

		REQUIRE(11 == Day13Puzzle::pathLength(network, start, goal));
	}

}
