#include <catch/CatchToString.hpp>
#include <2015/Day06Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 6 parseLine works", "[2015][Day06]") {
		const auto& p1 = Day06Puzzle::parseLine("turn on 0,0 through 999,999");
		const auto& p2 = Day06Puzzle::parseLine("turn off 499,499 through 500,500");
		const auto& p3 = Day06Puzzle::parseLine("toggle 0,0 through 999,0");

		REQUIRE(Day06Puzzle::LightInstruction::Type::TurnOn == p1.type);
		REQUIRE(core::Vector2i(0, 0) == p1.start);
		REQUIRE(core::Vector2i(999, 999) == p1.end);

		REQUIRE(Day06Puzzle::LightInstruction::Type::TurnOff == p2.type);
		REQUIRE(core::Vector2i(499, 499) == p2.start);
		REQUIRE(core::Vector2i(500, 500) == p2.end);

		REQUIRE(Day06Puzzle::LightInstruction::Type::Toggle == p3.type);
		REQUIRE(core::Vector2i(0, 0) == p3.start);
		REQUIRE(core::Vector2i(999, 0) == p3.end);
	}


	TEST_CASE("Day 6 Part 1 Example work", "[2015][Day06]") {
	    const std::vector<std::string> input = {
			"turn on 0,0 through 9,9",
			"turn off 2,2 through 3,3",
			"toggle 0,0 through 9,0"
		};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("86" == answers.first);
	}

	TEST_CASE("Day 6 Part 2 Example work", "[2015][Day06]") {
	    const std::vector<std::string> input = {
			"turn on 0,0 through 9,9",
			"toggle 0,0 through 9,9"
		};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("300" == answers.second);
	}

}
