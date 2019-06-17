#include <catch/catch.hpp>
#include <2016/Day03Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 3 Part 1 Example work", "[2016][Day03]") {
	    const std::vector<std::string> input = {
			"5 10 25",
			"5 10 25",
			"5 10 25"
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("0" == answers.first);
	}

	TEST_CASE("Day 3 Part 2 Example work", "[2016][Day03]") {
	    const std::vector<std::string> input = {
"101 301 501",
"102 302 502",
"103 303 503",
"201 401 601",
"202 402 602",
"203 403 603",
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("6" == answers.second);
	}

}
