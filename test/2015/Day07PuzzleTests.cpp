#include <catch/catch.hpp>
#include <2015/Day07Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 7 Part 1 Example work", "[2015][Day07]") {
	    const std::vector<std::string> input = {
			"123 -> x",
			"456 -> y",
			"x AND y -> d",
			"x OR y -> e",
			"x LSHIFT 2 -> f",
			"y RSHIFT 2 -> g",
			"NOT x -> h",
			"NOT y -> i"
		};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

	TEST_CASE("Day 7 Part 2 Example work", "[2015][Day07]") {
	    const std::vector<std::string> input = {};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
