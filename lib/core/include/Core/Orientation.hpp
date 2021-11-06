#ifndef INCLUDED_ADVENT_OF_CODE_CORE_ORIENATION_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_ORIENATION_HPP_

#include <zeno-engine/Core/Vector2.hpp>

namespace core {

	enum class Orientation {
		Up,
		Down,
		Left, 
		Right,
		None
	};

	class OrientationHelper {
	public:
		OrientationHelper() = delete;
		~OrientationHelper() = delete;

		static ze::Vector2i toDirection(Orientation _orientation) {
			switch (_orientation) {
			case Orientation::Up:
				return ze::Vector2i{ 0, +1 };
			case Orientation::Down:
				return ze::Vector2i{ 0, -1 };
			case Orientation::Right:
				return ze::Vector2i{ +1, 0 };
			case Orientation::Left:
				return ze::Vector2i{ -1, 0 };
			default:
				return ze::Vector2i{ 0, 0 };
			}
		}

		static Orientation turn(Orientation _direction, Orientation _turnDirection) {
			if (_turnDirection == Orientation::Up ||
				_turnDirection == Orientation::Down ||
				_turnDirection == Orientation::None ||
				_direction == Orientation::None) {
				return _direction;
			}

			if (_turnDirection == Orientation::Left) {
				switch (_direction) {
				case Orientation::Up:
					return Orientation::Left;
				case Orientation::Down:
					return Orientation::Right;
				case Orientation::Right:
					return Orientation::Up;
				case Orientation::Left:
					return Orientation::Down;
				}
			} else {
				switch (_direction) {
				case Orientation::Up:
					return Orientation::Right;
				case Orientation::Down:
					return Orientation::Left;
				case Orientation::Right:
					return Orientation::Down;
				case Orientation::Left:
					return Orientation::Up;
				}
			}

			return Orientation::None;
		}
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_ORIENATION_HPP_