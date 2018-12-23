#include <catch/catch.hpp>
#include <Core/Region.hpp>

namespace core {
	struct RegionCell {
		int value{ 0 };
	};

	TEST_CASE("Updating region cell updates the item returned next time it is queried", "[Core][Region]") {
		Region<RegionCell> region{};

		const int cellValue = 12313;
		const std::pair<int, int> coord{ 0,655 };

		RegionCell& cell = region.getCell(coord.first, coord.second);

		cell.value = cellValue;

		REQUIRE(cellValue == region.getCell(coord.first, coord.second).value);
	}
}