#include <catch/catch.hpp>
#include <2016/Day06Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 6 Part 1 Example work", "[2016][Day06]") {
	    const std::vector<std::string> input = {
"eedadn",
"drvtee",
"eandsr",
"raavrd",
"atevrs",
"tsrnev",
"sdttsa",
"rasrtv",
"nssdts",
"ntnada",
"svetve",
"tesnvt",
"vntsnd",
"vrdear",
"dvrsen",
"enarar"
		};

		REQUIRE("easter" == Day06Puzzle::doPart1(input));
	}

	TEST_CASE("2016 Day 6 Part 2 Example work", "[2016][Day06]") {
		const std::vector<std::string> input = {
"eedadn",
"drvtee",
"eandsr",
"raavrd",
"atevrs",
"tsrnev",
"sdttsa",
"rasrtv",
"nssdts",
"ntnada",
"svetve",
"tesnvt",
"vntsnd",
"vrdear",
"dvrsen",
"enarar"
		};

		REQUIRE("advent" == Day06Puzzle::doPart2(input));
	}
}
