#include <catch/catch.hpp>
#include <2015/Day04Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 4 Part 1 Example work", "[2015][Day04]") {
		const std::vector<std::string> input = { "abcdef" };

		Day04Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("609043" == answers.first);
	}

	TEST_CASE("Day 4 Part 1 Example 2 work", "[2015][Day04]") {
		const std::vector<std::string> input = { "pqrstuv" };

		Day04Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("1048970" == answers.first);
	}

}
