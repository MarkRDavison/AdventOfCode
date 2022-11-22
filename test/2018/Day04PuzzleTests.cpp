#include <catch/catch.hpp>
#include <2018/Day04Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 4 Examples work", "[2018][Day04]") {
	    const std::vector<std::string> input = {
"[1518-11-01 00:00] Guard #10 begins shift",
"[1518-11-01 00:05] falls asleep",
"[1518-11-01 00:25] wakes up",
"[1518-11-01 00:30] falls asleep",
"[1518-11-01 00:55] wakes up",
"[1518-11-01 23:58] Guard #99 begins shift",
"[1518-11-02 00:40] falls asleep",
"[1518-11-02 00:50] wakes up",
"[1518-11-03 00:05] Guard #10 begins shift",
"[1518-11-03 00:24] falls asleep",
"[1518-11-03 00:29] wakes up",
"[1518-11-04 00:02] Guard #99 begins shift",
"[1518-11-04 00:36] falls asleep",
"[1518-11-04 00:46] wakes up",
"[1518-11-05 00:03] Guard #99 begins shift",
"[1518-11-05 00:45] falls asleep",
"[1518-11-05 00:55] wakes up"
		};

	    Day04Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("240" == answers.first);
		REQUIRE("4455" == answers.second);
	}

}
