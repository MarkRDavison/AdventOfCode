#include <catch/catch.hpp>
#include <2019/Day10Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("Day 10 Part 1 Example 1 work", "[2019][Day10]") {
		const std::vector<std::string> input = {
			".#..#",
			".....",
			"#####",
			"....#",
			"...##"
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("8" == answers.first);
	}

	TEST_CASE("Day 10 Part 1 Example 2 work", "[2019][Day10]") {
		const std::vector<std::string> input = {
			"......#.#.",
			"#..#.#....",
			"..#######.",
			".#.#.###..",
			".#..#.....",
			"..#....#.#",
			"#..#....#.",
			".##.#..###",
			"##...#..#.",
			".#....####"
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("33" == answers.first);
	}

	TEST_CASE("Day 10 Part 1 Example 3 work", "[2019][Day10]") {
		const std::vector<std::string> input = {
			"#.#...#.#.",
			".###....#.",
			".#....#...",
			"##.#.#.#.#",
			"....#.#.#.",
			".##..###.#",
			"..#...##..",
			"..##....##",
			"......#...",
			".####.###."
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("35" == answers.first);
	}

	TEST_CASE("Day 10 Part 1 Example 4 work", "[2019][Day10]") {
		const std::vector<std::string> input = {
			".#..#..###",
			"####.###.#",
			"....###.#.",
			"..###.##.#",
			"##.##.#.#.",
			"....###..#",
			"..#.#..#.#",
			"#..#.#.###",
			".##...##.#",
			".....#.#.."
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("41" == answers.first);
	}

	TEST_CASE("Day 10 Part 1 Example 5 work", "[2019][Day10]") {
		const std::vector<std::string> input = {
			".#..##.###...#######",
			"##.############..##.",
			".#.######.########.#",
			".###.#######.####.#.",
			"#####.##.#.##.###.##",
			"..#####..#.#########",
			"####################",
			"#.####....###.#.#.##",
			"##.#################",
			"#####.##.###..####..",
			"..######..##.#######",
			"####.##.####...##..#",
			".#####..#.######.###",
			"##...#.##########...",
			"#.##########.#######",
			".####.#.###.###.#.##",
			"....##.##.###..#####",
			".#.#.###########.###",
			"#.#.#.#####.####.###",
			"###.##.####.##.#..##",
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("210" == answers.first);
	}

	TEST_CASE("Day 10 Part 1 Example work", "[2019][Day10]") {
		const std::vector<std::string> input = {
			".#..##.###...#######",
			"##.############..##.",
			".#.######.########.#",
			".###.#######.####.#.",
			"#####.##.#.##.###.##",
			"..#####..#.#########",
			"####################",
			"#.####....###.#.#.##",
			"##.#################",
			"#####.##.###..####..",
			"..######..##.#######",
			"####.##.####...##..#",
			".#####..#.######.###",
			"##...#.##########...",
			"#.##########.#######",
			".####.#.###.###.#.##",
			"....##.##.###..#####",
			".#.#.###########.###",
			"#.#.#.#####.####.###",
			"###.##.####.##.#..##",
		};

	    Day10Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("802" == answers.second);
	}
	TEST_CASE("Day 10 Part 2 Example 2 work", "[2019][Day10]") {
		const std::vector<std::string> input = {
			".#....#####...#..",
			"##...##.#####..##",
			"##...#...#.#####.",
			"..#.....#...###..",
			"..#.#.....#....##"
		};
		
		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);
		
		auto answers = puzzle.fastSolve();
	}
}
