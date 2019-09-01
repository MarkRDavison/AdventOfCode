#include <catch/catch.hpp>
#include <2015/Day03Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 3 Part 1 Example work", "[2015][Day03]") {
	    const std::vector<std::pair<std::string, std::string>> input = {
			{ ">", "2" },
			{ "^>v<", "4" },
			{ "^v^v^v^v^v", "2" },
		};

		for (const auto& p : input) {

			Day03Puzzle puzzle{};
			puzzle.setVerbose(true);
			puzzle.setInputLines({ p.first });

			auto answers = puzzle.fastSolve();

			REQUIRE(p.second == answers.first);
		}
	}

	TEST_CASE("Day 3 Part 2 Example work", "[2015][Day03]") {
		const std::vector<std::pair<std::string, std::string>> input = {
			{ "^v", "3" },
			{ "^>v<", "3" },
			{ "^v^v^v^v^v", "11" },
		};

		for (const auto& p : input) {

			Day03Puzzle puzzle{};
			puzzle.setVerbose(true);
			puzzle.setInputLines({ p.first });

			auto answers = puzzle.fastSolve();

			REQUIRE(p.second == answers.second);
		}
	}

}
