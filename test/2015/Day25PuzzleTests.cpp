#include <catch/catch.hpp>
#include <2015/Day25Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 25 Part 1 Example work", "[2015][Day25]") {

		REQUIRE(16080970 == Day25Puzzle::getAnswer(1, 3, start));
		REQUIRE(21629792 == Day25Puzzle::getAnswer(2, 2, start));
		REQUIRE(17289845 == Day25Puzzle::getAnswer(3, 1, start));
		REQUIRE(27995004 == Day25Puzzle::getAnswer(6, 6, start));

	}

}
