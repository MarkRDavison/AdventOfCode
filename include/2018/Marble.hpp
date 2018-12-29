#ifndef INCLUDED_ADVENT_OF_CODE_2018_MARBLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_MARBLE_HPP_

#include <memory>

namespace TwentyEighteen {
	struct Marble {

		Marble(int _value) : Value(_value) {

		}

		const int Value;

		std::shared_ptr<Marble> next{};
		std::shared_ptr<Marble> prev{};

	};
}

#endif // INCLUDED_ADVENT_OF_CODE_2018_MARBLE_HPP_