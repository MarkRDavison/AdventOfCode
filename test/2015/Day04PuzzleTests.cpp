#include <catch/catch.hpp>
#include <2015/Day04Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 4 Example 1 work", "[2015][Day04]") {
		std::mutex m;

		const std::vector<std::pair<std::string, int>>& data = {
			{"abcdef", 609043},
			{"pqrstuv", 1048970},
		};

		for (const auto& d : data) {
			SECTION("Finding 5 length zeroed MD5 for " + d.first + " works.") {

				std::vector<unsigned> part1;
				std::vector<unsigned> part2;
				Day04Puzzle::findZeroedMd5(d.first, d.second - 1, 2, m, part1, part2);

				REQUIRE(d.second == part1[0]);
			}
		}
	}

}
