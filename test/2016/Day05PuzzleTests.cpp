#include <catch/catch.hpp>
#include <2016/Day05Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 5 Part 1 Example work", "[2016][Day05]") {
	    const std::vector<std::string> input = { "abc" };

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("18f47a30" == answers.first);
	}

	TEST_CASE("Day 5 Part 2 Example work", "[2016][Day05]") {
	    const std::vector<std::string> input = { "abc" };

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("05ace8e3" == answers.second);
	}

}
