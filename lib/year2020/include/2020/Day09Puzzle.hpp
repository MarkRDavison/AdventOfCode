#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_09_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_09_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {

	using NumberType = long long;

	class Day09Puzzle : public core::PuzzleBase {
	public:
		Day09Puzzle();
		~Day09Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<NumberType, NumberType> solve(const std::vector<std::string>& _inputLines, NumberType _preambleLength);
	
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_09_PUZZLE_HPP_