#include <catch/catch.hpp>
#include <2018/Day17Puzzle.hpp>

namespace TwentyEighteen {

	void validate(int _minX, int _maxX, int _minY, int _maxY, Day17Puzzle::ParsedClayVein _actual) {
		REQUIRE(_minX == _actual.minX);
		REQUIRE(_maxX == _actual.maxX);
		REQUIRE(_minY == _actual.minY);
		REQUIRE(_maxY == _actual.maxY);
	}

	TEST_CASE("2018 Day 17 parsing input works", "[2018][Day17]") {

	    const std::vector<std::string> input = {
			"x=495, y=2..7",
			"y=7, x=495..501",
			"x=501, y=3..7",
			"x=498, y=2..4",
			"x=506, y=1..2",
			"x=498, y=10..13",
			"x=504, y=10..13",
			"y=13, x=498..504",
		};

		const auto& parsedInput = Day17Puzzle::parseInput(input);
		validate(495, 495, 2, 7, parsedInput[0]);
		validate(495, 501, 7, 7, parsedInput[1]);
		validate(501, 501, 3, 7, parsedInput[2]);
		validate(498, 498, 2, 4, parsedInput[3]);
		validate(506, 506, 1, 2, parsedInput[4]);
		validate(498, 498, 10, 13, parsedInput[5]);
		validate(504, 504, 10, 13, parsedInput[6]);
		validate(498, 504, 13, 13, parsedInput[7]);
	}

	TEST_CASE("2018 Day 17 example 1 works", "[2018][Day17]") {
		const std::vector<std::string> input = {
			"x=495, y=2..7",
			"y=7, x=495..501",
			"x=501, y=3..7",
			"x=498, y=2..4",
			"x=506, y=1..2",
			"x=498, y=10..13",
			"x=504, y=10..13",
			"y=13, x=498..504",
		};

		Day17Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();
	}
}
