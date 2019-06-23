#include <catch/catch.hpp>
#include <2016/Day08Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 8 Part 1 Example work", "[2016][Day08]") {
	    const std::vector<std::string> input = {
			"rect 3x2",
			"rotate column x=1 by 1",
			"rotate row y=0 by 4",
			"rotate column x=1 by 1"
		};

	    Day08Puzzle puzzle{};
		puzzle.setCustomScreenSize(7, 3);
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("6" == answers.first);
	}

}
