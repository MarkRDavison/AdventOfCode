#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_02_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_02_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day02Puzzle : public core::PuzzleBase {
	public:
		Day02Puzzle();
		~Day02Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::string doPart1(const std::vector<std::string>& _inputLines);
		static std::string doPart2(const std::vector<std::string>& _inputLines);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_02_PUZZLE_HPP_