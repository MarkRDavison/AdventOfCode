#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_15_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_15_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day15Puzzle : public core::PuzzleBase {
	public:
		Day15Puzzle();
		~Day15Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<std::pair<int, int>> getNumberAndStartingPositions(const std::vector<std::string>& _input);

		static bool isValidFromStartTime(const std::vector<std::pair<int, int>>& _positions, int _startTime);

		static int getFirstTime(const std::vector<std::pair<int, int>>& _positions);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_15_PUZZLE_HPP_