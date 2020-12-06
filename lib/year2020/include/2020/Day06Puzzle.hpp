#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_06_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_06_PUZZLE_HPP_

#include <set>
#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {
	
	class Day06Puzzle : public core::PuzzleBase {
	public:
		Day06Puzzle();
		~Day06Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		using Questions = std::vector<std::set<char>>;

		static std::vector<Questions> parseInput(const std::vector<std::string>& _input);
		static std::string doPart1(const std::vector<Questions>& _parsedInput);
		static std::string doPart2(const std::vector<Questions>& _parsedInput);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_06_PUZZLE_HPP_