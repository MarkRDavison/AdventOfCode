#include <catch/catch.hpp>
#include <2015/Day19Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 19 capital split works", "[2015][Day19]") {
		const auto& res = Day19Puzzle::splitAtCapitalLetter("AaaaBbbCDEeeeFFFGhHj");
		REQUIRE(10 == res.size());
		REQUIRE("Aaaa" == res[0]);
		REQUIRE("Bbb" == res[1]);
		REQUIRE("C" == res[2]);
		REQUIRE("D" == res[3]);
		REQUIRE("Eeee" == res[4]);
		REQUIRE("F" == res[5]);
		REQUIRE("F" == res[6]);
		REQUIRE("F" == res[7]);
		REQUIRE("Gh" == res[8]);
		REQUIRE("Hj" == res[9]);
	}

	TEST_CASE("2015 Day 19 Parses input correctly", "[2015][Day19]") {
		const std::vector<std::string> input = {
"H => HO",
"H => OH",
"O => HH",
"",
"HOH"
		};

		const auto& parsed = Day19Puzzle::parseInput(input);

		REQUIRE("HOH" == parsed.second);
		REQUIRE(2 == parsed.first.size());
		REQUIRE(2 == parsed.first.at("H").size());
		REQUIRE("HO" == parsed.first.at("H")[0]);
		REQUIRE("OH" == parsed.first.at("H")[1]);
		REQUIRE(1 == parsed.first.at("O").size());
		REQUIRE("HH" == parsed.first.at("O")[0]);

		SECTION("Generating replacement instructions works correctly") {
			REQUIRE(4 == Day19Puzzle::getDistinctMolecues(parsed.first, parsed.second));
			REQUIRE(7 == Day19Puzzle::getDistinctMolecues(parsed.first, "HOHOHO"));
		}
	}

	TEST_CASE("2015 Day 19 getting steps to generate examples work", "[2015][Day19]") {
		const std::vector<std::string> input = {
"e => H",
"e => O",
"H => HO",
"H => OH",
"O => HH",
"",
"HOH"
		};

		const auto& parsed = Day19Puzzle::parseInput(input);

		REQUIRE(3 == Day19Puzzle::stepsToFabricate(parsed.first, "HOH"));
		REQUIRE(6 == Day19Puzzle::stepsToFabricate(parsed.first, "HOHOHO"));
	}

}
