#include <catch/catch.hpp>
#include <2015/Day15Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 15 parsing input works", "[2015][Day15]") {
	    const std::vector<std::string> input = {
"Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8",
"Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3"
		};

		const auto& result = Day15Puzzle::parseInput(input);

		REQUIRE("Butterscotch" == result[0].name);
		REQUIRE(-1 == result[0].capacity);
		REQUIRE(-2 == result[0].durability);
		REQUIRE(6 == result[0].flavour);
		REQUIRE(3 == result[0].texture);
		REQUIRE(8 == result[0].calories);

		REQUIRE("Cinnamon" == result[1].name);
		REQUIRE(2 == result[1].capacity);
		REQUIRE(3 == result[1].durability);
		REQUIRE(-2 == result[1].flavour);
		REQUIRE(-1 == result[1].texture);
		REQUIRE(3 == result[1].calories);
	}

	TEST_CASE("2015 Day 15 Examples work", "[2015][Day15]") {
		const std::vector<std::string> input = {
"Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8",
"Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3"
		};
	
	    Day15Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);
	
	    auto answers = puzzle.fastSolve();

		REQUIRE("62842880" == answers.first);
		REQUIRE("57600000" == answers.second);
	}

}
