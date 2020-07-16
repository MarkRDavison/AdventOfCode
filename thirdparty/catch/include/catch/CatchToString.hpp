#ifndef INCLUDED_TEST_CATCH_TO_STRING_HPP_
#define INCLUDED_TEST_CATCH_TO_STRING_HPP_

#include <string>
#include <catch/catch.hpp>
#include <zeno/Core/Vector2.hpp>


namespace Catch {

	template<>
	struct StringMaker<ze::Vector2f> {
		static std::string convert(ze::Vector2f const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};

	template<>
	struct StringMaker<ze::Vector2i> {
		static std::string convert(ze::Vector2i const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};

}

#endif // INCLUDED_TEST_CATCH_TO_STRING_HPP_