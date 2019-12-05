#include <catch/catch.hpp>
#include <2019/Day04Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("Day 4 Example work", "[2019][Day04]") {
		REQUIRE(Day04Puzzle::isValid(111122, false));
		REQUIRE_FALSE(Day04Puzzle::isValid(555759, true));
		REQUIRE(Day04Puzzle::isValid(111111, true));
		REQUIRE_FALSE(Day04Puzzle::isValid(223450, true));
		REQUIRE_FALSE(Day04Puzzle::isValid(123789, true));

	    const std::vector<std::string> input = {
			"284639-748759"
		};

	    Day04Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("895" == answers.first);
		REQUIRE("591" == answers.second);
	}

}
