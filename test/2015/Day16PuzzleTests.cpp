#include <catch/catch.hpp>
#include <2015/Day16Puzzle.hpp>

namespace TwentyFifteen {

	TEST_CASE("2015 Day 16 parsing input works", "[2015][Day16]") {
		const std::vector<std::string> input = {
"Sue 1: children: 1, cars: 8, vizslas: 7",
"Sue 2: akitas: 10, perfumes: 10, children: 5",
		};

		const auto& parsed = Day16Puzzle::parseInput(input);

		REQUIRE(1 == parsed[0].id);
		REQUIRE(1 == parsed[0].compounds.at("children"));
		REQUIRE_FALSE(parsed[0].compounds.count("cats"));
		REQUIRE_FALSE(parsed[0].compounds.count("samoyeds"));
		REQUIRE_FALSE(parsed[0].compounds.count("pomeranians"));
		REQUIRE_FALSE(parsed[0].compounds.count("akitas"));
		REQUIRE(7 == parsed[0].compounds.at("vizslas"));
		REQUIRE_FALSE(parsed[0].compounds.count("goldfish"));
		REQUIRE_FALSE(parsed[0].compounds.count("trees"));
		REQUIRE(8 == parsed[0].compounds.at("cars"));
		REQUIRE_FALSE(parsed[0].compounds.count("perfumes"));

		REQUIRE(2 == parsed[1].id);
		REQUIRE(5 == parsed[1].compounds.at("children"));
		REQUIRE_FALSE(parsed[1].compounds.count("cats"));
		REQUIRE_FALSE(parsed[1].compounds.count("samoyeds"));
		REQUIRE_FALSE(parsed[1].compounds.count("pomeranians"));
		REQUIRE(10 == parsed[1].compounds.at("akitas"));
		REQUIRE_FALSE(parsed[1].compounds.count("vizslas"));
		REQUIRE_FALSE(parsed[1].compounds.count("goldfish"));
		REQUIRE_FALSE(parsed[1].compounds.count("trees"));
		REQUIRE_FALSE(parsed[1].compounds.count("cars"));
		REQUIRE(10 == parsed[1].compounds.at("perfumes"));
	}

	TEST_CASE("2015 Day 16 isInvalid for part1 works", "[2015][Day16]") {
		const std::vector<std::string> input = {
"Sue 1: children: 1, cars: 8, vizslas: 7",
"Sue 2: akitas: 0, perfumes: 1, children: 3",
		};

		const auto& parsed = Day16Puzzle::parseInput(input);
		std::unordered_map<std::string, int> data;
		data["children"] = 3;
		data["cats"] = 7;
		data["samoyeds"] = 2;
		data["pomeranians"] = 3;
		data["akitas"] = 0;
		data["vizslas"] = 0;
		data["goldfish"] = 5;
		data["trees"] = 3;
		data["cars"] = 2;
		data["perfumes"] = 1;

		REQUIRE(Day16Puzzle::isInvalid(parsed[0], data, false));
		REQUIRE_FALSE(Day16Puzzle::isInvalid(parsed[1], data, false));
	}

	TEST_CASE("2015 Day 16 isInvalid for part 2works", "[2015][Day16]") {
		const std::vector<std::string> input = {
"Sue 1: cats: 9, pomeranians: 1, children: 3",
"Sue 2: cats: 7, pomeranians: 3, children: 3",
		};

		const auto& parsed = Day16Puzzle::parseInput(input);
		std::unordered_map<std::string, int> data;
		data["children"] = 3;
		data["cats"] = 7;
		data["samoyeds"] = 2;
		data["pomeranians"] = 3;
		data["akitas"] = 0;
		data["vizslas"] = 0;
		data["goldfish"] = 5;
		data["trees"] = 3;
		data["cars"] = 2;
		data["perfumes"] = 1;

		REQUIRE_FALSE(Day16Puzzle::isInvalid(parsed[0], data, true));
		REQUIRE(Day16Puzzle::isInvalid(parsed[1], data, true));
	}

	TEST_CASE("2015 Day 16 getPotentialsIds for part 1 works", "[2015][Day16]") {
		const std::vector<std::string> input = {
"Sue 1: children: 1, cars: 8, vizslas: 7",
"Sue 2: akitas: 0, perfumes: 1, children: 3",
		};

		const auto& parsed = Day16Puzzle::parseInput(input);
		std::unordered_map<std::string, int> data;
		data["children"] = 3;
		data["cats"] = 7;
		data["samoyeds"] = 2;
		data["pomeranians"] = 3;
		data["akitas"] = 0;
		data["vizslas"] = 0;
		data["goldfish"] = 5;
		data["trees"] = 3;
		data["cars"] = 2;
		data["perfumes"] = 1;

		const auto& potentials = Day16Puzzle::getPotentialIds(data, parsed, true);

		REQUIRE(potentials.size() == 1);
		REQUIRE(2 == potentials[0]);
	}
}
