#include <catch/catch.hpp>
#include <2015/Day01Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 1 Part 1 Example work", "[2015][Day01]") {

		const std::vector<std::pair<std::string, std::string>> inputResults = {
			{ "(())", "0" },
			{ "()()", "0" },
			{ "(((", "3" },
			{ "(()(()(", "3" },
			{ "))(((((", "3" },
			{ "())", "-1" },
			{ "))(", "-1" },
			{ ")))", "-3" },
			{ ")())())", "-3" },
		};

		for (const auto& p : inputResults) {
			Day01Puzzle puzzle{};
			puzzle.setVerbose(true);
			puzzle.setInputLines({p.first});

			auto answers = puzzle.fastSolve();

			REQUIRE(p.second == answers.first);
		}
	}

	TEST_CASE("Day 1 Part 2 Example work", "[2015][Day01]") {
		const std::vector<std::pair<std::string, std::string>> inputResults = {
			{ ")", "1" },
			{ "()())", "5" },
		};

		for (const auto& p : inputResults) {
			Day01Puzzle puzzle{};
			puzzle.setVerbose(true);
			puzzle.setInputLines({ p.first });

			auto answers = puzzle.fastSolve();

			REQUIRE(p.second == answers.second);
		}
	}

}
