#ifndef INCLUDED_ADVENT_OF_CODE_2018_NANOBOT_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_NANOBOT_HPP_

namespace TwentyEighteen {
	
	using NanobotNumber = long long;
	struct Nanobot {

		Nanobot(NanobotNumber _x, NanobotNumber _y, NanobotNumber _z, NanobotNumber _r) :
			x(_x), y(_y), z(_z), r(_r) {}

		NanobotNumber x{ 0 };
		NanobotNumber y{ 0 };
		NanobotNumber z{ 0 };
		NanobotNumber r{ 0 };		
	};

	struct NanobotIntersectionRange {
		NanobotNumber minX{ 0 };
		NanobotNumber maxX{ 0 };
		NanobotNumber minY{ 0 };
		NanobotNumber maxY{ 0 };
		NanobotNumber minZ{ 0 };
		NanobotNumber maxZ{ 0 };
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_NANOBOT_HPP_