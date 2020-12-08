#include <catch/catch.hpp>
#include <2020/Day08Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 8 Examples work", "[2020][Day08]") {
	    const std::vector<std::string> input = {
			"nop +0",
			"acc +1",
			"jmp +4",
			"acc +3",
			"jmp -3",
			"acc -99",
			"acc +1",
			"jmp -4",
			"acc +6"	
		};

	    Day08Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("5" == answers.first);
		REQUIRE("8" == answers.second);
	}
}
