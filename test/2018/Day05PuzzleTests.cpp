#include <catch/catch.hpp>
#include <2018/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 5 Part 1 Example works", "[2018][Day5]") {
		const std::vector<std::string> input = {
			"dabAcCaCBAcCcaDA"
		};

		Day05Puzzle puzzle{};
		puzzle.setVerbose(true);

		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("10" == answers.first);
		REQUIRE("4" == answers.second);
	}

}
