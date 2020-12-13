#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_13_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_13_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <set>

namespace TwentyTwenty {

	struct Day13Struct {
		long long earliest;
		std::set<long long> busIds;
		std::vector<long long> busIdsWithSpacing;
	};
	
	class Day13Puzzle : public core::PuzzleBase {
	public:
		Day13Puzzle();
		~Day13Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static Day13Struct parseInput(const std::vector<std::string>& _inputLines);

		static std::string doPart1(const Day13Struct& _parsed);
		static std::string doPart2(const Day13Struct& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_13_PUZZLE_HPP_