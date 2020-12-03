#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_03_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_03_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {
	
	class Day03Puzzle : public core::PuzzleBase {
	public:
		Day03Puzzle();
		~Day03Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		long long getTreesForSlope(unsigned _x, unsigned _y) const;
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_03_PUZZLE_HPP_