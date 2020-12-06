#include <catch/catch.hpp>
#include <2020/Day06Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 6 Part 1 Example work", "[2020][Day06]") {
	    const std::vector<std::string> input = {
"abc",
"",
"a",
"b",
"c",
"",
"ab",
"ac",
"",
"a",
"a",
"a",
"a",
"",
"b",	
		};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("11" == answers.first);
		REQUIRE("6" == answers.second);
	}


}
