#include <catch/catch.hpp>
#include <2016/Day16Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 16 performDragonProcess works", "[2016][Day16]") {
		REQUIRE("100" == Day16Puzzle::performDragonProcess("1"));
		REQUIRE("001" == Day16Puzzle::performDragonProcess("0"));
		REQUIRE("11111000000" == Day16Puzzle::performDragonProcess("11111"));
		REQUIRE("1111000010100101011110000" == Day16Puzzle::performDragonProcess("111100001010"));
	}

	TEST_CASE("2016 Day 16 performDragonProcessForDesiredSize works", "[2016][Day16]") {
		REQUIRE("10000011110010000111" == Day16Puzzle::performDragonProcessForDesiredSize("10000", 20));
	}

	TEST_CASE("2016 Day 16 calculateChecksum works", "[2016][Day16]") {
		REQUIRE("100" == Day16Puzzle::calculateChecksum("110010110100"));
		REQUIRE("01100" == Day16Puzzle::calculateChecksum("10000011110010000111"));
	}

	TEST_CASE("2016 Day 16 calculateChecksumFromStateForSize works", "[2016][Day16]") {
		REQUIRE("01100" == Day16Puzzle::calculateChecksumFromStateForSize("10000", 20));
	}

}
