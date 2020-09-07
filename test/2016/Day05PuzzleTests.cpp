#include <catch/catch.hpp>
#include <2016/Day05Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 5 isValidIndex works", "[2016][Day05]") {
		char next;
		REQUIRE(Day05Puzzle::isValidIndex("abc", 3231929, next));
		REQUIRE('1' == next);
		REQUIRE(Day05Puzzle::isValidIndex("abc", 5017308, next));
		REQUIRE('8' == next);
		REQUIRE(Day05Puzzle::isValidIndex("abc", 5278568, next));
		REQUIRE('f' == next);
	}
	/*
	TEST_CASE("2016 Day 5 Part 2 Example work", "[2016][Day05]") {
	    const std::vector<std::string> input = {};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}
	*/
}
