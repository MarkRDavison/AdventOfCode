#include <catch/catch.hpp>
#include <2019/Day02Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("Day 2 Part 1 Example work", "[2019][Day02]") {
	    const std::vector<std::string> input = {"1,9,10,3,2,3,11,0,99,30,40,50"};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

	}

	TEST_CASE("Day 2 Part 2 Example work", "[2019][Day02]") {
	    const std::vector<std::string> input = {};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
