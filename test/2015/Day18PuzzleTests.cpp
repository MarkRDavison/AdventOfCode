#include <catch/catch.hpp>
#include <2015/Day18Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 18 region is constructed correctly", "[2015][Day18]") {
	    const std::vector<std::string> input = {
".#.#.#",
"...##.",
"#....#",
"..#...",
"#.#..#",
"####.."
		};

		core::Region<LightCell> region;
		Day18Puzzle::parseInput(region, input);

		for (unsigned y = 0; y < input.size(); ++y) {
			for (unsigned x = 0; x < input[y].size(); ++x) {
				bool on = input[y][x] == '#';
				const auto& cell = region.getCell((int)x, (int)y);
				REQUIRE(on == cell.on);
			}
		}
	}

	TEST_CASE("2015 Day 18 iterating works as expected for part 1", "[2015][Day18]") {

		const std::vector<std::string> input = {
".#.#.#",
"...##.",
"#....#",
"..#...",
"#.#..#",
"####.."
		};

		core::Region<LightCell> region;
		Day18Puzzle::parseInput(region, input);

		SECTION("Iterating 1 time works") {
			const std::vector<std::string> answer = {
"..##..",
"..##.#",
"...##.",
"......",
"#.....",
"#.##.."
			};
			Day18Puzzle::iterate(region, 1, false);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}

		SECTION("Iterating 2 times works") {
			const std::vector<std::string> answer = {
"..###.",
"......",
"..###.",
"......",
".#....",
".#...."
			};
			Day18Puzzle::iterate(region, 2, false);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}

		SECTION("Iterating 3 times works") {
			const std::vector<std::string> answer = {
"...#..",
"......",
"...#..",
"..##..",
"......",
"......"

			};
			Day18Puzzle::iterate(region, 3, false);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}

		SECTION("Iterating 4 times works") {
			const std::vector<std::string> answer = {
"......",
"......",
"..##..",
"..##..",
"......",
"......"

			};
			Day18Puzzle::iterate(region, 4, false);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}
	}

	TEST_CASE("2015 Day 18 iterating works as expected for part 2", "[2015][Day18]") {

		const std::vector<std::string> input = {
"##.#.#",
"...##.",
"#....#",
"..#...",
"#.#..#",
"####.#"
		};

		core::Region<LightCell> region;
		Day18Puzzle::parseInput(region, input);

		SECTION("Iterating 1 time works") {
			const std::vector<std::string> answer = {
"#.##.#",
"####.#",
"...##.",
"......",
"#...#.",
"#.####"
			};
			Day18Puzzle::iterate(region, 1, true);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}

		SECTION("Iterating 2 times works") {
			const std::vector<std::string> answer = {
"#..#.#",
"#....#",
".#.##.",
"...##.",
".#..##",
"##.###"
			};
			Day18Puzzle::iterate(region, 2, true);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}

		SECTION("Iterating 3 times works") {
			const std::vector<std::string> answer = {
"#...##",
"####.#",
"..##.#",
"......",
"##....",
"####.#"

			};
			Day18Puzzle::iterate(region, 3, true);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}

		SECTION("Iterating 4 times works") {
			const std::vector<std::string> answer = {
"#.####",
"#....#",
"...#..",
".##...",
"#.....",
"#.#..#"

			};
			Day18Puzzle::iterate(region, 4, true);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}

		SECTION("Iterating 5 times works") {
			const std::vector<std::string> answer = {
"##.###",
".##..#",
".##...",
".##...",
"#.#...",
"##...#"

			};
			Day18Puzzle::iterate(region, 5, true);

			for (unsigned y = 0; y < answer.size(); ++y) {
				for (unsigned x = 0; x < answer[y].size(); ++x) {
					const bool answerOn = answer[y][x] == '#';
					const bool cellOn = region.getCell((int)x, (int)y).on;

					REQUIRE(answerOn == cellOn);
				}
			}

		}
	}

	TEST_CASE("2015 Day 18 examples work correctly", "[2015][Day18]") {
		const std::vector<std::string> input = {
".#.#.#",
"...##.",
"#....#",
"..#...",
"#.#..#",
"####.."
		};

		core::Region<LightCell> region;
		Day18Puzzle::parseInput(region, input);
		REQUIRE(4 == Day18Puzzle::iterate(region, 4, false));

		Day18Puzzle::parseInput(region, input);
		REQUIRE(17 == Day18Puzzle::iterate(region, 5, true));
	}
}
