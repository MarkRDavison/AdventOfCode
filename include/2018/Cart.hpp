#ifndef INCLUDED_ADVENT_OF_CODE_2018_CART_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_CART_HPP_

#include <string>

namespace TwentyEighteen {

	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { 1, 0, -1, 0 };

	const std::string cart = "v>^<";

	enum TurnDirection {
		Left,
		Straight,
		Right
	};

	struct Cart {

		Cart(int _x, int _y, std::size_t _cartChar) : x(_x), y(_y), directionX(dx[_cartChar]), directionY(dy[_cartChar]), charIndex(_cartChar) {
			static int id = 0;
			this->id = id++;
		}

		bool dead{ false };
		TurnDirection direction{ Left };
		int x;
		int y;
		int id;
		int directionX;
		int directionY;
		std::size_t charIndex;

		bool operator<(const Cart& other) {
			return std::make_pair(y, x) < std::make_pair(other.y, other.x);
		}

	};
}

#endif // INCLUDED_ADVENT_OF_CODE_2018_CART_HPP_