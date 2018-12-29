#include <catch/catch.hpp>
#include <2018/Day15Puzzle.hpp>
#include <2018/Cave.hpp>

namespace TwentyEighteen {
	
	TEST_CASE("Day 15 Part 1 Example 1 works", "[2018][Day15]") {
		const std::vector<std::string> input = {
			"#########",
			"#G..G..G#",
			"#.......#",
			"#.......#",
			"#G..E..G#",
			"#.......#",
			"#.......#",
			"#G..G..G#",
			"#########",
		};

		Cave cave(input, 3);

		REQUIRE(cave.doesCurrentStateMatch(input));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#########",
			"#.G...G.#",
			"#...G...#",
			"#...E..G#",
			"#.G.....#",
			"#.......#",
			"#G..G..G#",
			"#.......#",
			"#########",
		}));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#########",
			"#..G.G..#",
			"#...G...#",
			"#.G.E.G.#",
			"#.......#",
			"#G..G..G#",
			"#.......#",
			"#.......#",
			"#########",
		}));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#########",
			"#.......#",
			"#..GGG..#",
			"#..GEG..#",
			"#G..G...#",
			"#......G#",
			"#.......#",
			"#.......#",
			"#########",
		}));
	}

	TEST_CASE("Day 15 Combat example 1 works", "[2018][Day15]") {
		const std::vector<std::string> input = {
			"#######",
			"#.G...#",
			"#...EG#",
			"#.#.#G#",
			"#..G#E#",
			"#.....#",
			"#######",
		};

		Cave cave(input, 3);

		REQUIRE(cave.doesCurrentStateMatch(input));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#..G..#",
			"#...EG#",
			"#.#G#G#",
			"#...#E#",
			"#.....#",
			"#######",
		}));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#...G.#",
			"#..GEG#",
			"#.#.#G#",
			"#...#E#",
			"#.....#",
			"#######",
		}));

		while (cave.getCompletedRound() < 23 - 1) {
			cave.doTurn();

			REQUIRE(cave.doesCurrentStateMatch({
				"#######",
				"#...G.#",
				"#..GEG#",
				"#.#.#G#",
				"#...#E#",
				"#.....#",
				"#######",
			}));
		}

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#...G.#",
			"#..G.G#",
			"#.#.#G#",
			"#...#E#",
			"#.....#",
			"#######",
		}));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#..G..#",
			"#...G.#",
			"#.#G#G#",
			"#...#E#",
			"#.....#",
			"#######",
		}));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#.G...#",
			"#..G..#",
			"#.#.#G#",
			"#..G#E#",
			"#.....#",
			"#######",
		}));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#G....#",
			"#.G...#",
			"#.#.#G#",
			"#...#E#",
			"#..G..#",
			"#######",
		}));

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#G....#",
			"#.G...#",
			"#.#.#G#",
			"#...#E#",
			"#...G.#",
			"#######",
		}));

		while (cave.getCompletedRound() < 47 - 1) {
			cave.doTurn();

			REQUIRE(cave.doesCurrentStateMatch({
				"#######",
				"#G....#",
				"#.G...#",
				"#.#.#G#",
				"#...#E#",
				"#....G#",
				"#######",
			}));
		}

		cave.doTurn();

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#G....#",
			"#.G...#",
			"#.#.#G#",
			"#...#.#",
			"#....G#",
			"#######",
		}));

		REQUIRE(47 == cave.getCompletedRound());
		REQUIRE(590 == cave.getTotalHealthRemaining());
	}

	TEST_CASE("Day 15 Combat example 2 works", "[2018][Day15]") {
		const std::vector<std::string> input = {
			"#######",
			"#G..#E#",
			"#E#E.E#",
			"#G.##.#",
			"#...#E#",
			"#...E.#",
			"#######",
		};

		Cave cave(input, 3);

		while (!cave.getComplete()) {
			cave.doTurn();
		}

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#...#E#",
			"#E#...#",
			"#.E##.#",
			"#E..#E#",
			"#.....#",
			"#######",
			}));

		REQUIRE(37 == cave.getCompletedRound());
		REQUIRE(982 == cave.getTotalHealthRemaining());

		Day15Puzzle puzzle(false);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE(std::to_string(37 * 982) == answers.first);
	}

	TEST_CASE("Day 15 Combat example 3 works", "[2018][Day15]") {
		const std::vector<std::string> input = {
			"#######",
			"#E.G#.#",
			"#.#G..#",
			"#G.#.G#",
			"#G..#.#",
			"#...E.#",
			"#######",
		};

		Cave cave(input, 3);

		while (!cave.getComplete()) {
			cave.doTurn();
		}

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#G.G#.#",
			"#.#G..#",
			"#..#..#",
			"#...#G#",
			"#...G.#",
			"#######",
		}));

		REQUIRE(35 == cave.getCompletedRound());
		REQUIRE(793 == cave.getTotalHealthRemaining());

		Day15Puzzle puzzle(false);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE(std::to_string(35 * 793) == answers.first);
	}

	TEST_CASE("Day 15 Combat example 4 works", "[2018][Day15]") {
		const std::vector<std::string> input = {
			"#######",
			"#.E...#",
			"#.#..G#",
			"#.###.#",
			"#E#G#G#",
			"#...#G#",
			"#######",
		};

		Cave cave(input, 3);

		while (!cave.getComplete()) {
			cave.doTurn();
		}

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#.....#",
			"#.#G..#",
			"#.###.#",
			"#.#.#.#",
			"#G.G#G#",
			"#######",
		}));

		REQUIRE(54 == cave.getCompletedRound());
		REQUIRE(536 == cave.getTotalHealthRemaining());

		Day15Puzzle puzzle(false);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE(std::to_string(54 * 536) == answers.first);
	}

	TEST_CASE("Day 15 Combat example 5 works", "[2018][Day15]") {
		const std::vector<std::string> input = {
			"#########",
			"#G......#",
			"#.E.#...#",
			"#..##..G#",
			"#...##..#",
			"#...#...#",
			"#.G...G.#",
			"#.....G.#",
			"#########",
		};

		Cave cave(input, 3);

		while (!cave.getComplete()) {
			cave.doTurn();
		}

		REQUIRE(cave.doesCurrentStateMatch({
			"#########",
			"#.G.....#",
			"#G.G#...#",
			"#.G##...#",
			"#...##..#",
			"#.G.#...#",
			"#.......#",
			"#.......#",
			"#########",
		}));

		REQUIRE(20 == cave.getCompletedRound());
		REQUIRE(937 == cave.getTotalHealthRemaining());

		Day15Puzzle puzzle(false);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE(std::to_string(20 * 937) == answers.first);
	}

	TEST_CASE("Day 15 Part 2 Example 1 Works", "[2018][Day15]") {
		const std::vector<std::string> input = {
			"#######",
			"#.G...#",
			"#...EG#",
			"#.#.#G#",
			"#..G#E#",
			"#.....#",
			"#######",
		};

		Cave cave(input, 15);

		while (!cave.getComplete()) {
			cave.doTurn();
		}

		REQUIRE(cave.doesCurrentStateMatch({
			"#######",
			"#..E..#",
			"#...E.#",
			"#.#.#.#",
			"#...#.#",
			"#.....#",
			"#######",
		}));

		REQUIRE(29 == cave.getCompletedRound());
		REQUIRE(172 == cave.getTotalHealthRemaining());

		Day15Puzzle puzzle(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE(std::to_string(29 * 172) == answers.second);
	}
}
