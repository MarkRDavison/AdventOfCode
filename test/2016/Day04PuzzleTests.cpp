#include <catch/catch.hpp>
#include <2016/Day04Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 4 Part 1 Example work", "[2016][Day04]") {
	    const std::vector<std::string> input = {
			"aaaaa-bbb-z-y-x-123[abxyz]",
			"a-b-c-d-e-f-g-h-987[abcde]",
			"not-a-real-room-404[oarel]",
			"totally-real-room-200[decoy]"
		};

	    Day04Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1514" == answers.first);
	}

}
