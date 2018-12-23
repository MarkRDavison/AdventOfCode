#ifndef INCLUDED_ADVENT_OF_CODE_CORE_REGION_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_REGION_HPP_

#include <array>
#include <map>

namespace core {
	
	template<typename T>
	class Region {
	public:
		static constexpr const int region_size = 16; //powers of two only!  4, 8, 16, 32, 64, etc
		static constexpr const int region_minor = region_size - 1;
		static constexpr const int region_major = ~region_minor;
		
		typedef std::array<std::array<T, region_size>, region_size> SubRegion; //a 16 by 16 region

		std::map<std::pair<int, int>, SubRegion> world;

		T& Region::getCell(int x, int y) {
			const std::pair<int, int> major_coords(x&region_major, y&region_major);
			SubRegion &r = world[major_coords];
			return r[x&region_minor][y&region_minor];
		}

	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_REGION_HPP_