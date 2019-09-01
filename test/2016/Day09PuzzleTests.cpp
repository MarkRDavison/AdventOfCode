#include <catch/catch.hpp>
#include <2016/Day09Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 9 with no decompressions works", "[2016][Day09]") {
		const std::vector<std::string> input = {
			"ADVENT"
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("6" == answers.first);
		REQUIRE("6" == answers.second);
	}

	TEST_CASE("Day 9 with single decompressions works", "[2016][Day09]") {
		const std::vector<std::string> input = {
			"A(1x5)BC"
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("7" == answers.first);
		REQUIRE("7" == answers.second);
	}

	TEST_CASE("Day 9 with single multi decompressions works", "[2016][Day09]") {
		const std::vector<std::string> input = {
			"(3x3)XYZ"
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("9" == answers.first);
		REQUIRE("9" == answers.second);
	}

	TEST_CASE("Day 9 with multi decompressions works", "[2016][Day09]") {
		const std::vector<std::string> input = {
			"A(2x2)BCD(2x2)EFG"
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("11" == answers.first);
		REQUIRE("11" == answers.second);
	}

	TEST_CASE("Day 9 with multi nested decompressions works", "[2016][Day09]") {
		const std::vector<std::string> input = {
			"X(8x2)(3x3)ABCY"
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("18" == answers.first);
		REQUIRE("20" == answers.second);
	}

	TEST_CASE("Day 9 with multi extra nested decompressions works", "[2016][Day09]") {
		const std::vector<std::string> input = {
			"(27x12)(20x12)(13x14)(7x10)(1x12)A"
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("241920" == answers.second);
	}

	TEST_CASE("Day 9 with multi extra extra nested decompressions works", "[2016][Day09]") {
		const std::vector<std::string> input = {
			"(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN"
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("445" == answers.second);
	}

}
