#ifndef INCLUDED_ADVENT_OF_CODE_CORE_VECTOR_2_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_VECTOR_2_HPP_

namespace core {

	template <typename T>
	class Vector2 {
	public:

		Vector2() : Vector2(0, 0) {}
		Vector2(T _x, T _y) : x(_x), y(_y) {}

		T x;
		T y;

	};

	template <typename T>
	bool operator==(const Vector2<T>& _lhs, const Vector2<T>& _rhs) {
		return _lhs.x == _rhs.x && _lhs.y == _rhs.y;
	}

	struct vector2_hash_fxn {
		template<typename T>
		std::size_t operator()(const Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};

	using Vector2i = Vector2<int>;
	using Vector2f = Vector2<float>;

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_VECTOR_2_HPP_