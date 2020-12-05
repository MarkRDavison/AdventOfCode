#include <catch/catch.hpp>
#include <2020/Day05Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 5 getSeatInfo works", "[2020][Day05]") {
	    
		const auto indexes = Day05Puzzle::getSeatInfo("FBFBBFFRLR");

		REQUIRE(44 == indexes.row);
		REQUIRE(5 == indexes.column);
		REQUIRE(357 == indexes.seatId);
	}

	TEST_CASE("Day 5 Part 1 Example work", "[2020][Day05]") {
	    const std::vector<std::string> input = {
			"BFFFBBFRRR",
			"FFFBBBFRRR",
			"BBFFBBFRLL"
		};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("820" == answers.first);
	}

}
