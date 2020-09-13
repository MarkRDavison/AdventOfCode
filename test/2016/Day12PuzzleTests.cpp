#include <catch/catch.hpp>
#include <2016/Day12Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 12 Part 1 Example work", "[2016][Day12]") {
	    const std::vector<std::string> input = {
"cpy 41 a",
"inc a",
"inc a",
"dec a",
"jnz a 2",
"dec a"
		};

		Registers registers = { 0 };
		AssembunnyInteger programCounter = 0;

		while (programCounter >= 0 && programCounter  < input.size()) {
			Day12Puzzle::applyInstruction(programCounter, registers, input[programCounter]);
		}

		REQUIRE(42 == registers[0]);
	}

}
