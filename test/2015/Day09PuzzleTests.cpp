#include <catch/catch.hpp>
#include <2015/Day09Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 9 Part 1 Example work", "[2015][Day09]") {
		const std::vector<std::string> input = {
"Dublin to London = 464",
"Belfast to London = 518",
"Dublin to Belfast = 141"
		};

		core::EdgeNetwork network;
		Day09Puzzle::populateNetwork(network, input);
		const auto& res = network.getShortestPathVisitingAll("London");

		REQUIRE(3 == res.first.size());
		REQUIRE("London" == res.first[0]);
		REQUIRE("Dublin" == res.first[1]);
		REQUIRE("Belfast" == res.first[2]);
		REQUIRE(605.0f == res.second);
	}

	TEST_CASE("2015 Day 9 Part 2 Example work", "[2015][Day09]") {
		const std::vector<std::string> input = {
"Dublin to London = 464",
"Belfast to London = 518",
"Dublin to Belfast = 141"
		};

		core::EdgeNetwork network;
		Day09Puzzle::populateNetwork(network, input);
		const auto& res = network.getLongestPathVisitingAll("Dublin");

		REQUIRE(3 == res.first.size());
		REQUIRE("Dublin" == res.first[0]);
		REQUIRE("London" == res.first[1]);
		REQUIRE("Belfast" == res.first[2]);
		REQUIRE(982.0f == res.second);
	}

}
