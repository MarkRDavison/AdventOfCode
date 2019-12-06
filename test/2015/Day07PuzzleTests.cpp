#include <catch/catch.hpp>
#include <2015/Day07Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("Day 7 parse instructions works", "[2015][Day07]") {
		auto instr = Day07Puzzle::parseInstruction("123 -> x");
		REQUIRE(Day07Puzzle::ParsedInstruction::OperatorType::ASSIGN == instr.type);
		REQUIRE(123 == instr.input1Int);
		REQUIRE("x" == instr.output);
		instr = Day07Puzzle::parseInstruction("x AND y -> d");
		REQUIRE(Day07Puzzle::ParsedInstruction::OperatorType::AND == instr.type);
		REQUIRE("x" == instr.input1);
		REQUIRE("y" == instr.input2);
		REQUIRE("d" == instr.output);
		instr = Day07Puzzle::parseInstruction("x OR y -> e");
		REQUIRE(Day07Puzzle::ParsedInstruction::OperatorType::OR == instr.type);
		REQUIRE("x" == instr.input1);
		REQUIRE("y" == instr.input2);
		REQUIRE("e" == instr.output);
		instr = Day07Puzzle::parseInstruction("x LSHIFT 2 -> f");
		REQUIRE(Day07Puzzle::ParsedInstruction::OperatorType::LSHIFT == instr.type);
		REQUIRE("x" == instr.input1);
		REQUIRE(2 == instr.input2Int);
		REQUIRE("f" == instr.output);
		instr = Day07Puzzle::parseInstruction("y RSHIFT 2 -> g");
		REQUIRE(Day07Puzzle::ParsedInstruction::OperatorType::RSHIFT == instr.type);
		REQUIRE("y" == instr.input1);
		REQUIRE(2 == instr.input2Int);
		REQUIRE("g" == instr.output);
		instr = Day07Puzzle::parseInstruction("NOT x -> h");
		REQUIRE(Day07Puzzle::ParsedInstruction::OperatorType::NOT == instr.type);
		REQUIRE("x" == instr.input1);
		REQUIRE("h" == instr.output);
	}

	TEST_CASE("Day 7 Part 1 Example work", "[2015][Day07]") {
	    const std::vector<std::string> input = {
			"123 -> x",
			"456 -> y",
			"x AND y -> d",
			"x OR y -> e",
			"x -> j",
			"x LSHIFT 2 -> f",
			"y RSHIFT 2 -> g",
			"NOT x -> h",
			"NOT y -> i"
		};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);
		
		puzzle.desiredoutput = "d";
		REQUIRE("72" == puzzle.fastSolve().first);
		puzzle.desiredoutput = "e";
		REQUIRE("507" == puzzle.fastSolve().first);
		puzzle.desiredoutput = "f";
		REQUIRE("492" == puzzle.fastSolve().first);
		puzzle.desiredoutput = "h";
		REQUIRE("65412" == puzzle.fastSolve().first);
		puzzle.desiredoutput = "j";
		REQUIRE("123" == puzzle.fastSolve().first);
	}

}
