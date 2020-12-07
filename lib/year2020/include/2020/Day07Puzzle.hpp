#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <map>

namespace TwentyTwenty {

	struct Day7Struct {
		std::string parent;
		std::map<std::string, int> contained;
	};

	class Day07Puzzle : public core::PuzzleBase {
	public:
		Day07Puzzle();
		~Day07Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::string doPart1(const std::vector<Day7Struct>& _input);
		static std::string doPart2(const std::vector<Day7Struct>& _input);

		static std::vector<Day7Struct> parseInput(const std::vector<std::string>& _inputLines);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_07_PUZZLE_HPP_