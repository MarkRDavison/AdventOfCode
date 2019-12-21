#ifndef INCLUDED_ADVENT_OF_CODE_2019_DAY_18_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2019_DAY_18_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyNineteen {
	
	class Day18Puzzle : public core::PuzzleBase {
	public:
		Day18Puzzle();
		~Day18Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		int solve(const std::vector<std::string>& _inputLines, char _robot);
		int solvePart2(const std::vector<std::string>& _inputLines);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2019_DAY_18_PUZZLE_HPP_