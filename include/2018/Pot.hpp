#ifndef INCLUDED_ADVENT_OF_CODE_2018_POT_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_POT_HPP_

#include <memory>

namespace TwentyEighteen {
	struct Pot {

		Pot(bool _plant) : plant(_plant) {}

		bool isRoot{ false };
		bool plant;
		bool hasPlantNext{ false };

		std::shared_ptr<Pot> prev;
		std::shared_ptr<Pot> next;
	};
}

#endif // INCLUDED_ADVENT_OF_CODE_2018_POT_HPP_