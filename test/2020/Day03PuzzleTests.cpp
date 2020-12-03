#include <catch/catch.hpp>
#include <2020/Day03Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 3 Examples work", "[2020][Day03]") {
	    const std::vector<std::string> input = {
"..##.......",
"#...#...#..",
".#....#..#.",
"..#.#...#.#",
".#...##..#.",
"..#.##.....",
".#.#.#....#",
".#........#",
"#.##...#...",
"#...##....#",
".#..#...#.#"
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("7" == answers.first);
		REQUIRE("336" == answers.second);
	}
}
