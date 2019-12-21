#include <catch/catch.hpp>
#include <2019/Day18Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("Day 18 Part 1 Example 1 work", "[2019][Day18]") {
		const std::vector<std::string> input = {
			"#########",
			"#b.A.@.a#",
			"#########"
		};
	
		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);
	
		REQUIRE(8 == puzzle.solve(input, '@'));
	}

	TEST_CASE("Day 18 Part 1 Example 2 work", "[2019][Day18]") {
		const std::vector<std::string> input = {
		"########################",
		"#f.D.E.e.C.b.A.@.a.B.c.#",
		"######################.#",
		"#d.....................#",
		"########################",
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		REQUIRE(86 == puzzle.solve(input, '@'));
	}

	TEST_CASE("Day 18 Part 1 Example 3 work", "[2019][Day18]") {
		const std::vector<std::string> input = {
"########################",
"#...............b.C.D.f#",
"#.######################",
"#.....@.a.B.c.d.A.e.F.g#",
"########################",
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		REQUIRE(132 == puzzle.solve(input, '@'));
	}
	TEST_CASE("Day 18 Part 1 Example 4 work", "[2019][Day18][Slow]") {
		const std::vector<std::string> input = {
"#################",
"#i.G..c...e..H.p#",
"########.########",
"#j.A..b...f..D.o#",
"########@########",
"#k.E..a...g..B.n#",
"########.########",
"#l.F..d...h..C.m#",
"#################",
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		REQUIRE(136 == puzzle.solve(input, '@'));
	}
	TEST_CASE("Day 18 Part 1 Example 5 work", "[2019][Day18]") {
		const std::vector<std::string> input = {
"########################",
"#@..............ac.GI.b#",
"###d#e#f################",
"###A#B#C################",
"###g#h#i################",
"########################",
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		REQUIRE(81 == puzzle.solve(input, '@'));
	}

	TEST_CASE("Day 18 Part 2 Example 1 work", "[2019][Day18]") {
		const std::vector<std::string> input = {
"#######",
"#a.#Cd#",
"##...##",
"##.@.##",
"##...##",
"#cB#Ab#",
"#######",
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);
		REQUIRE(8 == puzzle.solvePart2(input));
	}

	TEST_CASE("Day 18 Part 2 Example 2 work", "[2019][Day18]") {
		const std::vector<std::string> input = {
"###############",
"#d.ABC.#.....a#",
"######...######",
"######.@.######",
"######...######",
"#b.....#.....c#",
"###############",
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);
		REQUIRE(24 == puzzle.solvePart2(input));
	}

	TEST_CASE("Day 18 Part 2 Example 3 work", "[2019][Day18]") {
		const std::vector<std::string> input = {
"#############",
"#DcBa.#.GhKl#",
"#.###...#I###",
"#e#d#.@.#j#k#",
"###C#...###J#",
"#fEbA.#.FgHi#",
"#############",
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);
		REQUIRE(32 == puzzle.solvePart2(input));
	}
}
