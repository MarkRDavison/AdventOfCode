#include <catch/catch.hpp>
#include <2016/Day08Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 8 applying instructions works", "[2016][Day08]") {
		char screen[7 * 3 + 1] = ".....................";

		REQUIRE(0 == strcmp(screen,
			"......."
			"......."
			"......."));
		Day08Puzzle::applyInstruction("rect 3x2", 7, 3, screen);
		REQUIRE(0 == strcmp(screen,
			"###...."
			"###...."
			"......."));
		Day08Puzzle::applyInstruction("rotate column x=1 by 1", 7, 3, screen);
		REQUIRE(0 == strcmp(screen,
			"#.#...."
			"###...."
			".#....."));
		Day08Puzzle::applyInstruction("rotate row y=0 by 4", 7, 3, screen);
		REQUIRE(0 == strcmp(screen,
			"....#.#"
			"###...."
			".#....."));
		Day08Puzzle::applyInstruction("rotate column x=1 by 1", 7, 3, screen);
		REQUIRE(0 == strcmp(screen,
			".#..#.#"
			"#.#...."
			".#....."));
	}

	TEST_CASE("2016 Day 8 part 1 works", "[2016][Day08]") {
		const std::vector<std::string> input = {
			"rect 3x2",
			"rotate column x=1 by 1",
			"rotate row y=0 by 4",
			"rotate column x=1 by 1"
		};
		std::string screen;
		REQUIRE(6 == Day08Puzzle::doPart1(input, 7, 3, screen));
	}
}
