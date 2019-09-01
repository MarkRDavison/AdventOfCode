#include <catch/catch.hpp>
#include <2015/Day02Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("parseLine works", "[2015][Day02]") {
		const std::vector<std::pair<std::string, Day02Puzzle::ParsedLine>> inputResults = {
			{ "2x3x4", Day02Puzzle::ParsedLine(2,3,4) },
			{ "2x2x4", Day02Puzzle::ParsedLine(2,2,4) },
			{ "1x2x4", Day02Puzzle::ParsedLine(1,2,4) },
			{ "10x2x40", Day02Puzzle::ParsedLine(10,2,40) },
		};

		for (const auto& p : inputResults) {
			const auto& parsed = Day02Puzzle::parseLine(p.first);

			REQUIRE(p.second == parsed);
		}
	}

	TEST_CASE("Getting the wrapping area works", "[2015][Day02]") {
		const std::vector<std::pair<Day02Puzzle::ParsedLine, int>> inputResults = {
			{ Day02Puzzle::ParsedLine(2,3,4), 2 * (2 * 3 + 3 * 4 + 4 * 2) + 2 * 3},
			{ Day02Puzzle::ParsedLine(10,2,40), 2 * (10 * 2 + 2 * 40 + 10 * 40) + 10 * 2 }
		};

		for (const auto& p : inputResults) {
			REQUIRE(p.second == Day02Puzzle::wrappingArea(p.first));
		}
	}

	TEST_CASE("Day 2 Part 1 Example work", "[2015][Day02]") {
	    const std::vector<std::string> input = {
			"2x3x4",
			"1x1x10"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("101" == answers.first);
	}

	TEST_CASE("ribbonLength works", "[2015][Day02]") {
		const std::vector<std::pair<Day02Puzzle::ParsedLine, int>> inputResults = {
			{ Day02Puzzle::ParsedLine(2,3,4), 2 * (2 + 3) + 2 * 3 * 4 },
			{ Day02Puzzle::ParsedLine(10,2,40), 2 * (10 + 2) + 10 * 2 * 40 }
		};

		for (const auto& p : inputResults) {
			REQUIRE(p.second == Day02Puzzle::ribbonLength(p.first));
		}
	}

	TEST_CASE("Day 2 Part 2 Example work", "[2015][Day02]") {
		const std::vector<std::string> input = {
			"2x3x4",
			"1x1x10"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("48" == answers.second);
	}

}
