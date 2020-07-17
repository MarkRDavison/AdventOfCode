#include <catch/catch.hpp>
#include <2015/Day08Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 8 Part 1 Examples work", "[2015][Day08]") {
		const std::string str = R"("aaa\"aaa")";

		REQUIRE(LengthData(2, 0) == Day08Puzzle::getLengthMemory(R"("")"));
		REQUIRE(LengthData(5, 3) == Day08Puzzle::getLengthMemory(R"("abc")"));
		REQUIRE(LengthData(10, 7) == Day08Puzzle::getLengthMemory(str));
		REQUIRE(LengthData(6, 1) == Day08Puzzle::getLengthMemory(R"("\x27")"));

		REQUIRE(12 == Day08Puzzle::getPart1({
			R"("")",
			R"("abc")",
			str,
			R"("\x27")"
		}));
	}

	TEST_CASE("2015 Day 8 Part 2 Examples work", "[2015][Day08]") {
		const std::string str = R"("aaa\"aaa")";

		REQUIRE(LengthData(2, 6) == Day08Puzzle::getLengthEncode(R"("")"));
		REQUIRE(LengthData(5, 9) == Day08Puzzle::getLengthEncode(R"("abc")"));
		REQUIRE(LengthData(10, 16) == Day08Puzzle::getLengthEncode(str));
		REQUIRE(LengthData(6, 11) == Day08Puzzle::getLengthEncode(R"("\x27")"));

		REQUIRE(19 == Day08Puzzle::getPart2({
			R"("")",
			R"("abc")",
			str,
			R"("\x27")"
		}));
	}

}
