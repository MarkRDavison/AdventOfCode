#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_12_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_12_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	class Day12Puzzle : public core::PuzzleBase {
	public:
		Day12Puzzle();
		~Day12Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static long sumNumbersBasic(const std::string& _json);
		static long sumNumbersExcludingRed(const std::string& _json);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_12_PUZZLE_HPP_