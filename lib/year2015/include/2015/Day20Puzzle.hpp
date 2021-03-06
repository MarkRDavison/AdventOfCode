#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_20_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_20_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	using BigNumberThing = long;
	class Day20Puzzle : public core::PuzzleBase {
	public:
		Day20Puzzle();
		~Day20Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static BigNumberThing getNumberOfPresentsForHouseNumber(BigNumberThing _houseNumber);
		static BigNumberThing getNumberOfPresentsForHouseNumberPart2(BigNumberThing _houseNumber);
		static BigNumberThing getPart1(BigNumberThing _input);
		static BigNumberThing getPart2(BigNumberThing _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_20_PUZZLE_HPP_