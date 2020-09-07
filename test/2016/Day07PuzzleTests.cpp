#include <catch/catch.hpp>
#include <2016/Day07Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 7 supportsTLS works", "[2016][Day07]") {
		REQUIRE(Day07Puzzle::supportsTLS("abba[mnop]qrst"));
		REQUIRE_FALSE(Day07Puzzle::supportsTLS("abcd[bddb]xyyx"));
		REQUIRE_FALSE(Day07Puzzle::supportsTLS("aaaa[qwer]tyui"));
		REQUIRE(Day07Puzzle::supportsTLS("ioxxoj[asdfgh]zxcvbn"));
	}

	TEST_CASE("2016 Day 7 hasABBA works", "[2016][Day07]") {
		REQUIRE(Day07Puzzle::hasABBA("abba"));
		REQUIRE(Day07Puzzle::hasABBA("xyyx"));
		REQUIRE(Day07Puzzle::hasABBA("oxxo"));
		REQUIRE(Day07Puzzle::hasABBA("aoxxoc"));
		REQUIRE_FALSE(Day07Puzzle::hasABBA("mnop"));
		REQUIRE_FALSE(Day07Puzzle::hasABBA("aaaa"));
		REQUIRE_FALSE(Day07Puzzle::hasABBA("asdfgh"));
		REQUIRE_FALSE(Day07Puzzle::hasABBA("absaba"));
	}

	TEST_CASE("2016 Day 7 supportsSSL works", "[2016][Day07]") {
		REQUIRE(Day07Puzzle::supportsSSL("aba[bab]xyz"));
		REQUIRE_FALSE(Day07Puzzle::supportsSSL("xyx[xyx]xyx"));
		REQUIRE(Day07Puzzle::supportsSSL("aaa[kek]eke"));
		REQUIRE(Day07Puzzle::supportsSSL("zazbz[bzb]cdb"));
	}

}
