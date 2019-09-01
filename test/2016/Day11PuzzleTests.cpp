#include <catch/catch.hpp>
#include <2016/Day11Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 11 Part 1 Example work", "[2016][Day11]") {
	    const std::vector<std::string> input = {
"The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.",
"The second floor contains a hydrogen generator.",
"The third floor contains a lithium generator.",
"The fourth floor contains nothing relevant."
		};

	    Day11Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}
}
