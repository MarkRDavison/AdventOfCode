#include <catch/catch.hpp>
#include <2015/Day05Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 5 Part 1 Example work", "[2015][Day05]") {
	    const std::vector<std::string> input = {
			"ugknbfddgicrmopn",
			"aaa",
			"jchzalrnumimnmhp",
			"haegwjzuvuyypxyu",
			"dvszwmarrgswjxmb"
		};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("2" == answers.first);
	}

	TEST_CASE("isNicePart2 works", "[2015][Day05]") {
		REQUIRE(Day05Puzzle::isNicePart2("xyxy"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart2("aaa"));
		REQUIRE(Day05Puzzle::isNicePart2("qjhvhtzxzqqjkmpb"));
		REQUIRE(Day05Puzzle::isNicePart2("xxyxx"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart2("uurcxstgmygtbstg"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart2("ieodomkazucvgmuy"));
	}

	TEST_CASE("Day 5 Part 2 Example work", "[2015][Day05]") {
	    const std::vector<std::string> input = { 
			"qjhvhtzxzqqjkmpb",
			"xxyxx",
			"uurcxstgmygtbstg",
			"ieodomkazucvgmuy"
		};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("2" == answers.second);
	}

}
