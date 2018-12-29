#include <catch/catch.hpp>
#include <2018/Day07Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("Day 7 Part 1 Example works", "[2018][Day7]") {
		const std::vector<std::string> input = {
"Step C must be finished before step A can begin.",
"Step C must be finished before step F can begin.",
"Step A must be finished before step B can begin.",
"Step A must be finished before step D can begin.",
"Step B must be finished before step E can begin.",
"Step D must be finished before step E can begin.",
"Step F must be finished before step E can begin.",
		};

		Day07Puzzle puzzle(1, 0);
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("CABDFE" == answers.first);
	}

	TEST_CASE("Day 7 Part 2 Example works", "[2018][Day7]") {
		const std::vector<std::string> input = {
"Step C must be finished before step A can begin.",
"Step C must be finished before step F can begin.",
"Step A must be finished before step B can begin.",
"Step A must be finished before step D can begin.",
"Step B must be finished before step E can begin.",
"Step D must be finished before step E can begin.",
"Step F must be finished before step E can begin.",
		};

		Day07Puzzle puzzle(2, 0);
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();
		
		REQUIRE("15" == answers.second);
	}

}