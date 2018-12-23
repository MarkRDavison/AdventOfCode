#include <catch/catch.hpp>
#include <2018/Day02Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 2 Part 1 Example works", "[Day2][2018]") {
		const std::vector<std::string> input = {
			"abcdef",
			"bababc",
			"abbcde",
			"abcccd",
			"aabcdd",
			"abcdee",
			"ababab",
		};

		Day02Puzzle puzzle{};
		puzzle.setVerbose(true);

		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("12" == answers.first);
	}

	TEST_CASE("Day 2 Part 2 Example works", "[Day2][2018]") {
		const std::vector<std::string> input = {
			"abcde",
			"fghij",
			"klmno",
			"pqrst",
			"fguij",
			"axcye",
			"wvxyz",
		};

		Day02Puzzle puzzle{};
		puzzle.setVerbose(true);

		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("fgij" == answers.second);
	}

}
