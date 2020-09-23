#include <catch/catch.hpp>
#include <2016/Day17Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 17 getRoomDoorState works", "[2016][Day17]") {
		auto state = Day17Puzzle::getRoomDoorState("hijkl", "");
		REQUIRE(state.U);
		REQUIRE(state.D);
		REQUIRE(state.L);
		REQUIRE_FALSE(state.R);

		state = Day17Puzzle::getRoomDoorState("hijkl", "D");
		REQUIRE(state.U);
		REQUIRE_FALSE(state.D);
		REQUIRE(state.L);
		REQUIRE(state.R);

		state = Day17Puzzle::getRoomDoorState("hijkl", "DR");
		REQUIRE_FALSE(state.U);
		REQUIRE_FALSE(state.D);
		REQUIRE_FALSE(state.L);
		REQUIRE_FALSE(state.R);
	}

	TEST_CASE("2016 Day 17 explore shortest works", "[2016][Day17]") {
		REQUIRE(Day17Puzzle::explore("hijkl", true).empty());
		REQUIRE("DDRRRD" == Day17Puzzle::explore("ihgpwlah", true));
		REQUIRE("DDUDRLRRUDRD" == Day17Puzzle::explore("kglvqrro", true));
		REQUIRE("DRURDRUDDLLDLUURRDULRLDUUDDDRR" == Day17Puzzle::explore("ulqzkmiv", true));
	}

	TEST_CASE("2016 Day 17 explore longest works", "[2016][Day17]") {
		REQUIRE(370 == Day17Puzzle::explore("ihgpwlah", false).size());
		REQUIRE(492 == Day17Puzzle::explore("kglvqrro", false).size());
		REQUIRE(830 == Day17Puzzle::explore("ulqzkmiv", false).size());
	}

}
