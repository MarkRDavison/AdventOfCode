#include <catch/catch.hpp>
#include <2016/Day04Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 4 validating rooms works", "[2016][Day04]") {
		int sectorId = 0;
		REQUIRE(Day04Puzzle::validateRoom("aaaaa-bbb-z-y-x-123[abxyz]", sectorId));
		REQUIRE(123 == sectorId);
		REQUIRE(Day04Puzzle::validateRoom("a-b-c-d-e-f-g-h-987[abcde]", sectorId));
		REQUIRE(987 == sectorId);
		REQUIRE(Day04Puzzle::validateRoom("not-a-real-room-404[oarel]", sectorId));
		REQUIRE(404 == sectorId);
		REQUIRE_FALSE(Day04Puzzle::validateRoom("totally-real-room-200[decoy]", sectorId));
	}

	TEST_CASE("2016 Day 4 validating north pole room works", "[2016][Day04]") {
		int sectorId = 0;
		REQUIRE(Day04Puzzle::isNorthPoleRoom("qzmt-zixmtkozy-ivhz-343[abcde]", sectorId, "encrypted"));
		REQUIRE(343 == sectorId);
	}

}
