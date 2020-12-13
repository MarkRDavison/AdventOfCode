#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_10_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_10_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {

	using Day10NumberValue = long long;
	
	class Day10Puzzle : public core::PuzzleBase {
	public:
		Day10Puzzle();
		~Day10Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;


		static std::vector<Day10NumberValue> parse(const std::vector<std::string>& _inputLines);

		static std::string doPart1(const std::vector<Day10NumberValue>& _parsed);
		static std::string doPart2(const std::vector<Day10NumberValue>& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_10_PUZZLE_HPP_