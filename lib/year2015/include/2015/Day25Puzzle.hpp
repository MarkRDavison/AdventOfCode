#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_25_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_25_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {

	using NumberType = long long;
	constexpr NumberType start = 20151125;
	constexpr NumberType MULTIPLIER = 252533;
	constexpr NumberType MODULATOR = 33554393;
	
	class Day25Puzzle : public core::PuzzleBase {
	public:
		Day25Puzzle();
		~Day25Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static NumberType getAnswer(int _column, int _row, NumberType _start);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_25_PUZZLE_HPP_