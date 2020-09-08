#include <catch/catch.hpp>
#include <2016/Day10Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 10 Examples work", "[2016][Day10]") {
	    const std::vector<std::string> input = {
"value 5 goes to bot 2",
"bot 2 gives low to bot 1 and high to bot 0",
"value 3 goes to bot 1",
"bot 1 gives low to output 1 and high to bot 0",
"bot 0 gives low to output 2 and high to output 0",
"value 2 goes to bot 2"
		};

		auto info = Day10Puzzle::initialiseRobotInfo(input);
		Day10Puzzle::iterateProcess(info);
		REQUIRE(2 == Day10Puzzle::getRobotNumberProcessingMicrochips(info, 5, 2));
		REQUIRE(2 == Day10Puzzle::getRobotNumberProcessingMicrochips(info, 2, 5));
		REQUIRE(5 == info.output[0]);
		REQUIRE(2 == info.output[1]);
		REQUIRE(3 == info.output[2]);
	}

}
