#include <catch/catch.hpp>
#include <2015/Day05Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 5 Part 1 is string nice works", "[2015][Day05]") {
		REQUIRE(Day05Puzzle::isNicePart1("ugknbfddgicrmopn"));
		REQUIRE(Day05Puzzle::isNicePart1("aaa"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart1("jchzalrnumimnmhp"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart1("haegwjzuvuyypxyu"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart1("dvszwmarrgswjxmb"));
	}

	TEST_CASE("2015 Day 5 Part 1 Example work", "[2015][Day05]") {
	    const std::vector<std::string> input = {
			"ugknbfddgicrmopn",
			"aaa",
			"jchzalrnumimnmhp",
			"haegwjzuvuyypxyu",
			"dvszwmarrgswjxmb"
		};

		REQUIRE(2 == Day05Puzzle::getPart1(input));
	}

	TEST_CASE("2015 Day 5 Part 2 is string nice works", "[2015][Day05]") {
		REQUIRE(Day05Puzzle::isNicePart2("qjhvhtzxzqqjkmpb"));
		REQUIRE(Day05Puzzle::isNicePart2("xxyxx"));
		REQUIRE(Day05Puzzle::isNicePart2("xyxy"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart2("uurcxstgmygtbstg"));
		REQUIRE_FALSE(Day05Puzzle::isNicePart2("ieodomkazucvgmuy"));
	}

	TEST_CASE("2015 Day 5 Part 2 Example work", "[2015][Day05]") {
		const std::vector<std::string> input = {
			"qjhvhtzxzqqjkmpb",
			"xxyxx",
			"uurcxstgmygtbstg",
			"ieodomkazucvgmuy",
		};

		REQUIRE(2 == Day05Puzzle::getPart2(input));
	}

}
