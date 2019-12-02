#include <catch/catch.hpp>
#include <2019/Day01Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("Day 1 part 1 calculate fuel for module works", "[2019][Day01]") {
		REQUIRE(2 == Day01Puzzle::calculateFuelForModule(12));
		REQUIRE(2 == Day01Puzzle::calculateFuelForModule(14));
		REQUIRE(654 == Day01Puzzle::calculateFuelForModule(1969));
		REQUIRE(33583 == Day01Puzzle::calculateFuelForModule(100756));
	}
	TEST_CASE("Day 1 part 2 calculate fuel for module works", "[2019][Day01]") {
		REQUIRE(2 == Day01Puzzle::calculateFuelForModuleRecursive(14));
		REQUIRE(966 == Day01Puzzle::calculateFuelForModuleRecursive(1969));
		REQUIRE(50346 == Day01Puzzle::calculateFuelForModuleRecursive(100756));
	}

	TEST_CASE("Day 1 Part 1 Example work", "[2019][Day01]") {
	    const std::vector<std::string> input = {
			"100756"
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("33583" == answers.first);
	}

	TEST_CASE("Day 1 Part 2 Example work", "[2019][Day01]") {
	    const std::vector<std::string> input = {
			"100756"
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("50346" == answers.second);
	}

}
