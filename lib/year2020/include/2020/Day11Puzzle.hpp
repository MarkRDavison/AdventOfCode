#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_11_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_11_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>

namespace TwentyTwenty {

	
	class Day11Puzzle : public core::PuzzleBase {
	public:
		Day11Puzzle();
		~Day11Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<std::string, std::string> solve(const std::vector<std::string>& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_11_PUZZLE_HPP_