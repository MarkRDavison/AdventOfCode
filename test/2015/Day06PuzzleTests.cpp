#include <catch/catch.hpp>
#include <2015/Day06Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 6 Input parsing works", "[2015][Day06]") {
		const auto& parsed = Day06Puzzle::parseLines({
			"turn on 0,0 through 999,999",
			"toggle 0,0 through 999,0",
			"turn off 499,499 through 500,500"
		});

		SECTION("Parsing on instruction works") {
			const auto p = parsed[0];
			REQUIRE(Day06InputLine::Action::On == p.action);
			REQUIRE(ze::IntRect(0, 0, 1000, 1000) == p.bounds);
		}
		SECTION("Parsing toggle instruction works") {
			const auto p = parsed[1];
			REQUIRE(Day06InputLine::Action::Toggle == p.action);
			REQUIRE(ze::IntRect(0, 0, 1000, 1) == p.bounds);
		}
		SECTION("Parsing off instruction works") {
			const auto p = parsed[2];
			REQUIRE(Day06InputLine::Action::Off == p.action);
			REQUIRE(ze::IntRect(499, 499, 2, 2) == p.bounds);
		}
	}

	TEST_CASE("2015 Day 6 Part 1 Example work", "[2015][Day06]") {
		constexpr std::size_t size{ 10 };

		std::vector<int> grid(size * size, 0);

		Day06Puzzle::applyLinePart1<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 0, 10, 5), Day06InputLine::Action::On));
		Day06Puzzle::applyLinePart1<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 5, 10, 5), Day06InputLine::Action::Toggle));
		Day06Puzzle::applyLinePart1<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 5, 5, 5), Day06InputLine::Action::Off));

		int setLights = 0;
		for (auto y = 0; y < size; ++y) {
			for (auto x = 0; x < size; ++x) {
				setLights += grid[y * size + x];
			}
		}

		REQUIRE(75 == setLights);
	}

	TEST_CASE("2015 Day 6 Part 2 Example work", "[2015][Day06]") {
		constexpr std::size_t size{ 10 };

		std::vector<int> grid(size * size, 0);

		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 0, 10, 5), Day06InputLine::Action::On));
		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 5, 10, 5), Day06InputLine::Action::Toggle));
		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 5, 5, 5), Day06InputLine::Action::Off));
		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 0, 1, 1), Day06InputLine::Action::Off));
		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 0, 1, 1), Day06InputLine::Action::Off));
		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 0, 1, 1), Day06InputLine::Action::Off));
		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 0, 1, 1), Day06InputLine::Action::Off));
		Day06Puzzle::applyLinePart2<size>(
			grid,
			Day06InputLine(ze::IntRect(0, 0, 1, 1), Day06InputLine::Action::Off));

		int setLights = 0;
		for (auto y = 0; y < size; ++y) {
			for (auto x = 0; x < size; ++x) {
				setLights += grid[y * size + x];
			}
		}

		REQUIRE(124 == setLights);
	}

}
