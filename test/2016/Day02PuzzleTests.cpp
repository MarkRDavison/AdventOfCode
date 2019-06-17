#include <catch/catch.hpp>
#include <2016/Day02Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 2 Part 1 Example work", "[2016][Day02]") {
	    const std::vector<std::string> input = {
			"ULL",
			"RRDDD",
			"LURDL",
			"UUUUD"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1985" == answers.first);
	}

	TEST_CASE("Day 2 Part 2 Example work", "[2016][Day02]") {
	    const std::vector<std::string> input = { 
			"ULL",
			"RRDDD",
			"LURDL",
			"UUUUD" 
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("5DB3" == answers.second);
	}

}
