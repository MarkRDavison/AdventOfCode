#include <catch/catch.hpp>
#include <2015/Day07Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 7 Parsing input works", "[2015][Day07]") {
		SECTION("Constant input to wire") {
			const auto& line = Day07Puzzle::parseLine("123 -> x");
			REQUIRE(InstructionType::INPUT == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(123 == line.constantInput1);
			REQUIRE("x" == line.wireOutput);
		}
		SECTION("Wire input to wire") {
			const auto& line = Day07Puzzle::parseLine("y -> x");
			REQUIRE(InstructionType::INPUT == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE("y" == line.wireInput1);
			REQUIRE("x" == line.wireOutput);
		}

		SECTION("NOT Constant") {
			const auto& line = Day07Puzzle::parseLine("NOT 1 -> x");
			REQUIRE(InstructionType::NOT == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(1 == line.constantInput1);
			REQUIRE("x" == line.wireOutput);
		}
		SECTION("NOT Wire") {
			const auto& line = Day07Puzzle::parseLine("NOT x -> y");
			REQUIRE(InstructionType::NOT == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE("x" == line.wireInput1);
			REQUIRE("y" == line.wireOutput);
		}

		SECTION("Wire AND Wire") {
			const auto& line = Day07Puzzle::parseLine("x AND y -> z");
			REQUIRE(InstructionType::AND == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE("y" == line.wireInput2);
			REQUIRE("z" == line.wireOutput);
		}
		SECTION("Constant AND Wire") {
			const auto& line = Day07Puzzle::parseLine("12 AND x -> y");
			REQUIRE(InstructionType::AND == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE(12 == line.constantInput1);
			REQUIRE("x" == line.wireInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Wire AND Constant") {
			const auto& line = Day07Puzzle::parseLine("x AND 12 -> y");
			REQUIRE(InstructionType::AND == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE(12 == line.constantInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Constant AND Constant") {
			const auto& line = Day07Puzzle::parseLine("10 AND 11 -> x");
			REQUIRE(InstructionType::AND == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE(10 == line.constantInput1);
			REQUIRE(11 == line.constantInput2);
			REQUIRE("x" == line.wireOutput);
		}

		SECTION("Wire OR Wire") {
			const auto& line = Day07Puzzle::parseLine("x OR y -> z");
			REQUIRE(InstructionType::OR == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE("y" == line.wireInput2);
			REQUIRE("z" == line.wireOutput);
		}
		SECTION("Constant OR Wire") {
			const auto& line = Day07Puzzle::parseLine("12 OR x -> y");
			REQUIRE(InstructionType::OR == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE(12 == line.constantInput1);
			REQUIRE("x" == line.wireInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Wire OR Constant") {
			const auto& line = Day07Puzzle::parseLine("x OR 12 -> y");
			REQUIRE(InstructionType::OR == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE(12 == line.constantInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Constant OR Constant") {
			const auto& line = Day07Puzzle::parseLine("10 OR 11 -> x");
			REQUIRE(InstructionType::OR == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE(10 == line.constantInput1);
			REQUIRE(11 == line.constantInput2);
			REQUIRE("x" == line.wireOutput);
		}

		SECTION("Wire LSHIFT Wire") {
			const auto& line = Day07Puzzle::parseLine("x LSHIFT y -> z");
			REQUIRE(InstructionType::LSHIFT == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE("y" == line.wireInput2);
			REQUIRE("z" == line.wireOutput);
		}
		SECTION("Wire LSHIFT Constant") {
			const auto& line = Day07Puzzle::parseLine("x LSHIFT 2 -> y");
			REQUIRE(InstructionType::LSHIFT == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE(2 == line.constantInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Constant LSHIFT Wire") {
			const auto& line = Day07Puzzle::parseLine("2 LSHIFT x -> y");
			REQUIRE(InstructionType::LSHIFT == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE(2 == line.constantInput1);
			REQUIRE("x" == line.wireInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Constant LSHIFT Constant") {
			const auto& line = Day07Puzzle::parseLine("12 LSHIFT 1 -> x");
			REQUIRE(InstructionType::LSHIFT == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE(12 == line.constantInput1);
			REQUIRE(1 == line.constantInput2);
			REQUIRE("x" == line.wireOutput);
		}

		SECTION("Wire RSHIFT Wire") {
			const auto& line = Day07Puzzle::parseLine("x RSHIFT y -> z");
			REQUIRE(InstructionType::RSHIFT == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE("y" == line.wireInput2);
			REQUIRE("z" == line.wireOutput);
		}
		SECTION("Wire RSHIFT Constant") {
			const auto& line = Day07Puzzle::parseLine("x RSHIFT 2 -> y");
			REQUIRE(InstructionType::RSHIFT == line.type);
			REQUIRE(SignalType::Wire == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE("x" == line.wireInput1);
			REQUIRE(2 == line.constantInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Constant RSHIFT Wire") {
			const auto& line = Day07Puzzle::parseLine("2 RSHIFT x -> y");
			REQUIRE(InstructionType::RSHIFT == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Wire == line.signalTypeInput2);
			REQUIRE(2 == line.constantInput1);
			REQUIRE("x" == line.wireInput2);
			REQUIRE("y" == line.wireOutput);
		}
		SECTION("Constant RSHIFT Constant") {
			const auto& line = Day07Puzzle::parseLine("12 RSHIFT 1 -> x");
			REQUIRE(InstructionType::RSHIFT == line.type);
			REQUIRE(SignalType::Constant == line.signalTypeInput1);
			REQUIRE(SignalType::Constant == line.signalTypeInput2);
			REQUIRE(12 == line.constantInput1);
			REQUIRE(1 == line.constantInput2);
			REQUIRE("x" == line.wireOutput);
		}
	}

	TEST_CASE("2015 Day 7 isResolved works", "[2015][Day07]") {
		REQUIRE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("123 -> x"), {}));
		REQUIRE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("456 -> y"), {}));
		REQUIRE_FALSE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("x AND y -> d"), {}));
		REQUIRE_FALSE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("x OR y -> e"), {}));
		REQUIRE_FALSE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("x LSHIFT 2 -> f"), {}));
		REQUIRE_FALSE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("x LSHIFT 2 -> f"), {}));
		REQUIRE_FALSE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("NOT x -> h"), {}));
		REQUIRE_FALSE(Day07Puzzle::isResolved(Day07Puzzle::parseLine("NOT y -> i"), {}));
	}

	TEST_CASE("2015 Day 7 Part 1 Example work", "[2015][Day07]") {
	    const std::vector<std::string> input = {
			"x LSHIFT 2 -> f",
			"y RSHIFT 2 -> g",
			"x AND y -> d",
			"x OR y -> e",
			"NOT x -> h",
			"123 -> x",
			"456 -> y",
			"NOT y -> i"
		};

		ResolvedMap resolved;
		Day07Puzzle::runLogic(input, resolved);

		REQUIRE(72 == resolved.at("d"));
		REQUIRE(507 == resolved.at("e"));
		REQUIRE(492 == resolved.at("f"));
		REQUIRE(114 == resolved.at("g"));
		REQUIRE(65412 == resolved.at("h"));
		REQUIRE(65079 == resolved.at("i"));
		REQUIRE(123 == resolved.at("x"));
		REQUIRE(456 == resolved.at("y"));
	}

	TEST_CASE("2015 Day 7 Part 2 Example work", "[2015][Day07]") {
		const std::vector<std::string> input = {
			"x LSHIFT 2 -> f",
			"y RSHIFT 2 -> g",
			"x AND y -> d",
			"x OR y -> e",
			"NOT x -> h",
			"123 -> x",
			"456 -> y",
			"NOT y -> i"
		};

		ResolvedMap resolved;
		resolved["x"] = 123;
		Day07Puzzle::runLogic(input, resolved);

		REQUIRE(72 == resolved.at("d"));
		REQUIRE(507 == resolved.at("e"));
		REQUIRE(492 == resolved.at("f"));
		REQUIRE(114 == resolved.at("g"));
		REQUIRE(65412 == resolved.at("h"));
		REQUIRE(65079 == resolved.at("i"));
		REQUIRE(123 == resolved.at("x"));
		REQUIRE(456 == resolved.at("y"));
	}

}
