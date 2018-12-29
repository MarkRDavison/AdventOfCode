#include <catch/catch.hpp>
#include <2018/Day13Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 13 Part 1 Example works", "[2018][Day13]") {
		const std::vector<std::string> input = {
"/->-\\        ",
"|   |  /----\\",
"| /-+--+-\\  |",
"| | |  | v  |",
"\\-+-/  \\-+--/",
"  \\------/   ",
		};

		Day13Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve();

		REQUIRE("7,3" == answer.first);
	}

	TEST_CASE("Day 13 Part 2 Example works", "[2018][Day13]") {
		const std::vector<std::string> input = {
"/>-<\\  ",
"|   |  ",
"| /<+-\\",
"| | | v",
"\\>+</ |",
"  |   ^",
"  \\<->/",
		};

		Day13Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve();

		REQUIRE("6,4" == answer.second);
	}

}