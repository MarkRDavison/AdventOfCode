#include <catch/catch.hpp>
#include <2020/Day01Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 1 Part 1 and 2 Examples work", "[2020][Day01]") {
	    const std::vector<std::string> input = {
			"1721",
			"979",
			"366",
			"299",
			"675",
			"1456"
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);
	    auto answers = puzzle.fastSolve();

		REQUIRE("514579" == answers.first);
		REQUIRE("241861950" == answers.second);
	}

}
