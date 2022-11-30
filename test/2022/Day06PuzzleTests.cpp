#include <catch/catch.hpp>
#include <2022/Day06Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 6 Examples work", "[2022][Day06]") {
	    const std::vector<std::string> input = {};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
