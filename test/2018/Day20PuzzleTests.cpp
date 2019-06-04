#include <catch/catch.hpp>
#include <2018/Day20Puzzle.hpp>

namespace TwentyEighteen {
	
	TEST_CASE("Day 20 Part 1 works", "[2018][Day20]") {
		const std::vector<std::string> input = {
			"^ESSWWN(E|NNENN(EESS(WNSE|)SSS|WWWSSSSE(SW|NNNE)))$"
		};

		Day20Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve();

		REQUIRE("23" == answer.first);
	}

}