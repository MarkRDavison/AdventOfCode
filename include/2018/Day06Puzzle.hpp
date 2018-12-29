#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_06_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_06_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyEighteen {

	struct Cell {
		char owningCell{'?'};
	};

	class Day06Puzzle : public core::PuzzleBase {
	public:
		Day06Puzzle(int _threshold = 10000);
		~Day06Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		int m_Threshold;
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_06_PUZZLE_HPP_