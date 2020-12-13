#include <catch/catch.hpp>
#include <2020/Day11Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 11 Examples work", "[2020][Day11]") {

		const std::vector<std::string> input = {
"L.LL.LL.LL",
"LLLLLLL.LL",
"L.L.L..L..",
"LLLL.LL.LL",
"L.LL.LL.LL",
"L.LLLLL.LL",
"..L.L.....",
"LLLLLLLLLL",
"L.LLLLLL.L",
"L.LLLLL.LL"
		};

		const auto answers = Day11Puzzle::solve(input);

		REQUIRE("37" == answers.first);
		REQUIRE("26" == answers.second);
	}

}
