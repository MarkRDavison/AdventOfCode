#include <catch/catch.hpp>
#include <2015/Day03Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 3 char to orientation works", "[2015][Day03]") {
		REQUIRE(core::Orientation::Up == Day03Puzzle::getOrientation('^'));
		REQUIRE(core::Orientation::Down == Day03Puzzle::getOrientation('v'));
		REQUIRE(core::Orientation::Left == Day03Puzzle::getOrientation('<'));
		REQUIRE(core::Orientation::Right == Day03Puzzle::getOrientation('>'));
		REQUIRE(core::Orientation::None == Day03Puzzle::getOrientation('1'));
	}

	TEST_CASE("2015 Day 3 Part 1 visiting locations works", "[2015][Day03]") {
		const std::vector<std::string>& directions = {
			">",
			"^>v<",
			"^v^v^v^v^v"
		};
		SECTION("Visiting " + directions.at(0) + " works") {
			const auto& map = Day03Puzzle::visitLocations(directions[0], 1);

			REQUIRE(2 == map.size());
			REQUIRE(1 == map.at(ze::Vector2i(0, 0)));
			REQUIRE(1 == map.at(ze::Vector2i(1, 0)));
		}

		SECTION("Visiting " + directions.at(1) + " works") {
			const auto& map = Day03Puzzle::visitLocations(directions[1], 1);

			REQUIRE(4 == map.size());
			REQUIRE(2 == map.at(ze::Vector2i(0, 0)));
			REQUIRE(1 == map.at(ze::Vector2i(0, 1)));
			REQUIRE(1 == map.at(ze::Vector2i(1, 1)));
			REQUIRE(1 == map.at(ze::Vector2i(1, 0)));
		}

		SECTION("Visiting " + directions.at(2) + " works") {
			const auto& map = Day03Puzzle::visitLocations(directions[2], 1);

			REQUIRE(2 == map.size());
			REQUIRE(6 == map.at(ze::Vector2i(0, 0)));
			REQUIRE(5 == map.at(ze::Vector2i(0, 1)));
		}
	}

	TEST_CASE("2015 Day 3 Part 1 Examples work", "[2015][Day03]") {
		REQUIRE(2 == Day03Puzzle::getResult(Day03Puzzle::visitLocations(">", 1)));
		REQUIRE(4 == Day03Puzzle::getResult(Day03Puzzle::visitLocations("^>v<", 1)));
		REQUIRE(2 == Day03Puzzle::getResult(Day03Puzzle::visitLocations("^v^v^v^v^v", 1)));
	}

	TEST_CASE("2015 Day 3 Part 2 Examples work", "[2015][Day03]") {
		REQUIRE(3 == Day03Puzzle::getResult(Day03Puzzle::visitLocations("^v", 2)));
		REQUIRE(3 == Day03Puzzle::getResult(Day03Puzzle::visitLocations("^>v<", 2)));
		REQUIRE(11 == Day03Puzzle::getResult(Day03Puzzle::visitLocations("^v^v^v^v^v", 2)));
	}

}
