#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_17_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_17_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>

namespace TwentyEighteen {
	
	class Day17Puzzle : public core::PuzzleBase {
	public:
		struct ParsedClayVein {
			int minX{ 0 };
			int maxX{ 0 };
			int minY{ 0 };
			int maxY{ 0 };
		};

		Day17Puzzle();
		~Day17Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<ParsedClayVein> parseInput(const std::vector<std::string>& _input);
		static void populateMap(core::Region<char>& _map, const std::vector<ParsedClayVein>& _parsedInput);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_17_PUZZLE_HPP_