#include <catch/catch.hpp>
#include <2015/Day12Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 12 Part 1 Examples work", "[2015][Day12]") {
		REQUIRE(6 == Day12Puzzle::solve("[1,2,3]").first);
		REQUIRE(6 == Day12Puzzle::solve("{\"a\":2,\"b\":4}").first);
		REQUIRE(3 == Day12Puzzle::solve("[[[3]]]").first);
		REQUIRE(3 == Day12Puzzle::solve("{\"a\":{\"b\":4},\"c\":-1}").first);
		REQUIRE(0 == Day12Puzzle::solve("{\"a\":[-1,1]}").first);
		REQUIRE(0 == Day12Puzzle::solve("[-1,{\"a\":1}]").first);
		REQUIRE(0 == Day12Puzzle::solve("[]").first);
		REQUIRE(0 == Day12Puzzle::solve("{}").first);
	}

	TEST_CASE("2015 Day 12 Part 2 Examples work", "[2015][Day12]") {
		REQUIRE(0 == Day12Puzzle::solve("{\"d\":\"red\",\"e\":[1,2,3,4],\"f\":5}").second);
		REQUIRE(4 == Day12Puzzle::solve("[1,{\"c\":\"red\",\"b\":2},3]").second);
		REQUIRE(6 == Day12Puzzle::solve("[1,\"red\",5]").second);
		REQUIRE(6 == Day12Puzzle::solve("[1,2,3]").second);		
	}

}
