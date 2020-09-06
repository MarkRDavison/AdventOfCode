#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_03_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_03_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day03Puzzle : public core::PuzzleBase {
	public:
		Day03Puzzle();
		~Day03Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static bool isValidTriangle(int _a, int _b, int _c);

		static int doPart1(const std::vector<std::string>& _input);
		static int doPart2(const std::vector<std::string>& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_03_PUZZLE_HPP_