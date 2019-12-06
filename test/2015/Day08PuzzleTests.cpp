#include <catch/catch.hpp>
#include <2015/Day08Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 8 get info works for different escape characters") {
		auto info = Day08Puzzle::getInfo("\"kexh\\\"pmi\"");
		REQUIRE(11 == info.characterSize);
		REQUIRE(8 == info.memorySize);
	}
	
	TEST_CASE("Day 8 encoding works", "[2015][Day08]") {
		REQUIRE(6 == Day08Puzzle::encodeSize("\"\""));
		REQUIRE(9 == Day08Puzzle::encodeSize("\"abc\""));
		REQUIRE(16 == Day08Puzzle::encodeSize("\"aaa\\\"aaa\""));
		REQUIRE(11 == Day08Puzzle::encodeSize("\"\\x27\""));
	}

}
