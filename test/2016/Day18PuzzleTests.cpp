#include <catch/catch.hpp>
#include <2016/Day18Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 18 createMap works", "[2016][Day18]") {
		auto map = Day18Puzzle::createMap("..^^.", 3);
		REQUIRE("..^^." == map[0]);
		REQUIRE(".^^^^" == map[1]);
		REQUIRE("^^..^" == map[2]);

		map = Day18Puzzle::createMap(".^^.^.^^^^", 10);
		REQUIRE(".^^.^.^^^^" == map[0]);
		REQUIRE("^^^...^..^" == map[1]);
		REQUIRE("^.^^.^.^^." == map[2]);
		REQUIRE("..^^...^^^" == map[3]);
		REQUIRE(".^^^^.^^.^" == map[4]);
		REQUIRE("^^..^.^^.." == map[5]);
		REQUIRE("^^^^..^^^." == map[6]);
		REQUIRE("^..^^^^.^^" == map[7]);
		REQUIRE(".^^^..^.^^" == map[8]);
		REQUIRE("^^.^^^..^^" == map[9]);
	}

	TEST_CASE("2016 Day 18 getSafeTilesCount works", "[2016][Day18]") {
		REQUIRE(38 == Day18Puzzle::getSafeTilesCount(".^^.^.^^^^", 10));
	}

}
