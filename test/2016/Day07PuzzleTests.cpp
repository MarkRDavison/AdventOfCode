#include <catch/catch.hpp>
#include <2016/Day07Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("containsAutonomousBridgeBypassAnnotation method works", "[2016][Day07]") {
		REQUIRE(Day07Puzzle::containsAutonomousBridgeBypassAnnotation("abba"));
		REQUIRE(Day07Puzzle::containsAutonomousBridgeBypassAnnotation("abba"));
		REQUIRE_FALSE(Day07Puzzle::containsAutonomousBridgeBypassAnnotation("abab"));
		REQUIRE_FALSE(Day07Puzzle::containsAutonomousBridgeBypassAnnotation("aaaa"));
		REQUIRE_FALSE(Day07Puzzle::containsAutonomousBridgeBypassAnnotation("axya"));
		REQUIRE_FALSE(Day07Puzzle::containsAutonomousBridgeBypassAnnotation("xaay"));
		REQUIRE_FALSE(Day07Puzzle::containsAutonomousBridgeBypassAnnotation("abcd"));
	}

	TEST_CASE("Day 7 Part 1 Example work", "[2016][Day07]") {
	    const std::vector<std::string> input = {
			"abba[mnop]qrst",
			"abcd[bddb]xyyx",
			"aaaa[qwer]tyui",
			"ioxxoj[asdfgh]zxcvbn"
		};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("2" == answers.first);
	}

	TEST_CASE("Day 7 Part 2 Example work", "[2016][Day07]") {
	    const std::vector<std::string> input = {
			"aba[bab]xyz",
			"xyx[xyx]xyx",
			"aaa[kek]eke",
			"zazbz[bzb]cdb"
		};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("3" == answers.second);
	}

}
