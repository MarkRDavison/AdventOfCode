#include <catch/catch.hpp>
#include <2018/Day23Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 23 Part 1 Example works", "[2018][Day23]") {
		const std::vector<std::string> input = {
"pos=<0,0,0>, r=4",
"pos=<1,0,0>, r=1",
"pos=<4,0,0>, r=3",
"pos=<0,2,0>, r=1",
"pos=<0,5,0>, r=3",
"pos=<0,0,3>, r=1",
"pos=<1,1,1>, r=1",
"pos=<1,1,2>, r=1",
"pos=<1,3,1>, r=1",
		};

		Day23Puzzle puzzle{};
		puzzle.setVerbose(true);

		puzzle.setInputLines(input);

		const auto& answers = puzzle.fastSolve();

		REQUIRE("7" == answers.first);
	}

	TEST_CASE("Day 23 Part 2 Example works", "[2018][Day23]") {
		const std::vector<std::string> input = {
"pos=<10,12,12>, r=2",
"pos=<12,14,12>, r=2",
"pos=<16,12,12>, r=4",
"pos=<14,14,14>, r=6",
"pos=<50,50,50>, r=200",
"pos=<10,10,10>, r=5",
		};

		Day23Puzzle puzzle{};
		puzzle.setVerbose(true);

		puzzle.setInputLines(input);

		const auto& answers = puzzle.fastSolve();

		REQUIRE("36" == answers.second);
	}

}
