#ifndef INCLUDED_ADVENT_OF_CODE_CORE_VECTOR_2_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_VECTOR_2_HPP_

#include <cstdlib>
#include <cmath>

namespace core {

	template <typename T>
	class Vector2 {
	public:

		Vector2() : Vector2(0, 0) {}
		Vector2(T _x, T _y) : x(_x), y(_y) {}
		template <typename U>
		Vector2(const Vector2<U>& _other) :
			Vector2(static_cast<T>(_other.x), static_cast<T>(_other.y)) {
		}

		T x;
		T y;

	};

	template <typename T>
	bool operator==(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return _lhs.x == _rhs.x && _lhs.y == _rhs.y;
	}

	template <typename T>
	bool operator!=(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return !(_lhs == _rhs);
	}

	template <typename T>
	Vector2<T> operator+(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return { _lhs.x + _rhs.x, _lhs.y + _rhs.y };
	}

	template <typename T>
	Vector2<T> operator-(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return { _lhs.x - _rhs.x, _lhs.y - _rhs.y };
	}

	template <typename T>
	void operator+=(Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		_lhs.x += _rhs.x;
		_lhs.y += _rhs.y;
	}

	struct vector2_hash_fxn {
		template<typename T>
		std::size_t operator()(const Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};



	using Vector2i = Vector2<int>;
	using Vector2f = Vector2<float>;

	namespace VectorMath {

		static float toAngle(const core::Vector2<float>& _vec) {
			const float Radians = std::atan2(_vec.y, _vec.x);
			return Radians * 180.0f / static_cast<float>(3.14159265f);
		}

	}
}


#endif // INCLUDED_ADVENT_OF_CODE_CORE_VECTOR_2_HPP_