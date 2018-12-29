#include <catch/catch.hpp>
#include <2018/Day12Puzzle.hpp>

namespace TwentyEighteen {
	
	TEST_CASE("Day 12 Part 1 Example works", "[2018][Day12]") {
		const std::vector<std::string> input = {
			"initial state: #..#.#..##......###...###",
			"",
			"...## => #",
			"..#.. => #",
			".#... => #",
			".#.#. => #",
			".#.## => #",
			".##.. => #",
			".#### => #",
			"#.#.# => #",
			"#.### => #",
			"##.#. => #",
			"##.## => #",
			"###.. => #",
			"###.# => #",
			"####. => #",
		};

		Day12Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("325" == answers.first);
	}

}