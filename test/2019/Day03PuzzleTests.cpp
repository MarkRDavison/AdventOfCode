#include <catch/catch.hpp>
#include <2019/Day03Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("Day 3 Part 1 Example work", "[2019][Day03]") {
	    const std::vector<std::string> input = {
"R8,U5,L5,D3",
"U7,R6,D4,L4"
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
		REQUIRE("6" == answers.first);
	}

	TEST_CASE("Day 3 Part 2 Example work", "[2019][Day03]") {
		const std::vector<std::string> input = {
"R75,D30,R83,U83,L12,D49,R71,U7,L72",
"U62,R66,U55,R34,D71,R55,D58,R83"
		};

		Day03Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("610" == answers.second);
	}

	TEST_CASE("Day 3 Part 2 Example 2 work", "[2019][Day03]") {
		const std::vector<std::string> input = {
"R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51",
"U98,R91,D20,R16,D67,R40,U7,R15,U6,R7"
		};

		Day03Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("410" == answers.second);
	}

}
