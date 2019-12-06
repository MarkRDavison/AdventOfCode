#include <catch/catch.hpp>
#include <2019/Day06Puzzle.hpp>

namespace TwentyNineteen {
	
	TEST_CASE("Day 6 Example work", "[2019][Day06]") {
	    const std::vector<std::string> input = {
"COM)B",
"B)C",
"C)D",
"D)E",
"E)F",
"B)G",
"G)H",
"D)I",
"E)J",
"J)K",
"K)L",
"K)YOU",
"I)SAN" };

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("54" == answers.first);
		REQUIRE("4" == answers.second);
	}

}
