#include <catch/catch.hpp>
#include <2016/Day01Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 1 Part 1 Example work", "[2016][Day01]") {
	    const std::vector<std::string> input = {
			"R5, L5, R5, R3"
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("12" == answers.first);
	}

	TEST_CASE("Day 1 Part 2 Example work", "[2016][Day01]") {
	    const std::vector<std::string> input = {
			"R8, R4, R4, R8"
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("4" == answers.second);
	}

}
