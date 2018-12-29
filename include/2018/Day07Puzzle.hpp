#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyEighteen {

	class Day07Puzzle : public core::PuzzleBase {
	public:
		Day07Puzzle(int _numWorkers = 5, int _timeBase = 60);
		~Day07Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		static std::pair<std::string, int> solveForWorkers(int _workers, int _timeBase, const std::vector<std::pair<char, char>>& _inputPairs, bool _singleStepSteps);

	private:
		int m_Workers;
		int m_TimeBase;
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_07_PUZZLE_HPP_