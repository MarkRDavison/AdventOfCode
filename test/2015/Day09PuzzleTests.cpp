#include <catch/catch.hpp>
#include <2015/Day09Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 9 Part 1 Example work", "[2015][Day09]") {
	    const std::vector<std::string> input = {
			"London to Dublin = 464",
			"London to Belfast = 518",
			"Dublin to Belfast = 141",
		};

	    Day09Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("605" == answers.first);
	}

	TEST_CASE("Day 9 Part 2 Example work", "[2015][Day09]") {
		const std::vector<std::string> input = {
			"London to Dublin = 464",
			"London to Belfast = 518",
			"Dublin to Belfast = 141",
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("982" == answers.second);
	}

}
