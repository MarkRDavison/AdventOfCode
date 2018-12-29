#include <catch/catch.hpp>
#include <2018/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {
	
	TEST_CASE("Day 8 Part 1 Example works", "[2018][Day8]") {
		const std::string input = "2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2";

		Day08Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(core::StringExtensions::splitStringByDelimeter(input, " "));

		auto answers = puzzle.fastSolve();

		REQUIRE("138" == answers.first);
		REQUIRE("66" == answers.second);
	}

}
