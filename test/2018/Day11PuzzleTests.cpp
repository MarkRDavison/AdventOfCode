#include <catch/catch.hpp>
#include <2018/Day11Puzzle.hpp>

namespace TwentyEighteen {
	
	TEST_CASE("Day 11 Part 1 & 2 Example works", "[2018][Day11]") {
		const std::vector<std::string> input = {
			"42"
		};

		Day11Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("21,61" == answers.first);
		REQUIRE("232,251,12" == answers.second);
	}

}