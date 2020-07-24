#include <catch/catch.hpp>
#include <2015/Day21Puzzle.hpp>
#include <unordered_map>
#include <algorithm>
#include <numeric>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 21 Part 1 Example work", "[2015][Day21]") {
		CharacterStats player{ 8,5,5 };
		CharacterStats boss{ 12,7,2 };

		REQUIRE(Day21Puzzle::doesPlayerWin(player, boss));
	}

}
