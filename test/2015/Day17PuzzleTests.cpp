#include <catch/catch.hpp>
#include <2015/Day17Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 17 Examples work", "[2015][Day17]") {
		const std::vector<std::string> input = { "20", "10", "15", "5", "5" };

		auto answer = Day17Puzzle::getResult(input, 25);

		REQUIRE(4 == answer.first);
		REQUIRE(3 == answer.second);
	}

}
