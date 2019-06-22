#include <catch/catch.hpp>
#include <2016/Day06Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("Day 6 Part 1 Example work", "[2016][Day06]") {
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

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
		
		REQUIRE("easter" == answers.first);
	}

	TEST_CASE("Day 6 Part 2 Example work", "[2016][Day06]") {
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

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("advent" == answers.second);
	}

}
