#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_12_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_12_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {

	struct Day12Struct {
		enum class Direction {
			NORTH,
			EAST,
			WEST,
			SOUTH,
			LEFT,
			RIGHT,
			FORWARD
		} direction;

		long value;
	};
	
	class Day12Puzzle : public core::PuzzleBase {
	public:
		Day12Puzzle();
		~Day12Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<Day12Struct> parse(const std::vector<std::string>& _inputLines);
		static Day12Struct translate(const std::string& _line);
		static std::string doPart1(const std::vector<Day12Struct>& _parsed);
		static std::string doPart2(const std::vector<Day12Struct>& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_12_PUZZLE_HPP_