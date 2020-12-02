#include <catch/catch.hpp>
#include <2020/Day02Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 2 Examples work", "[2020][Day02]") {
	    const std::vector<std::string> input = {
"1-3 a: abcde",
"1-3 b: cdefg",
"2-9 c: ccccccccc"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("2" == answers.first);
		REQUIRE("1" == answers.second);
	}

}
