#ifndef INCLUDED_TEST_CATCH_TO_STRING_HPP_
#define INCLUDED_TEST_CATCH_TO_STRING_HPP_

#include <string>
#include <catch/catch.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace Catch {
	template<>
	struct StringMaker<sf::Vector2f> {
		static std::string convert(sf::Vector2f const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};

	template<>
	struct StringMaker<sf::Vector2i> {
		static std::string convert(sf::Vector2i const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};

	template<>
	struct StringMaker<sf::Vector2u> {
		static std::string convert(sf::Vector2u const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};

	template<>
	struct StringMaker<sf::FloatRect> {
		static std::string convert(sf::FloatRect const& _value) {
			return "left: " + std::to_string(_value.left) + ", top: " + std::to_string(_value.top) + ", width: " + std::to_string(_value.width) + ", height: " + std::to_string(_value.height);
		}
	};
}

#endif // INCLUDED_TEST_CATCH_TO_STRING_HPP_