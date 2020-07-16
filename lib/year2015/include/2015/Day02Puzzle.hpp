#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_02_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_02_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	class Day02Puzzle : public core::PuzzleBase {
	public:
		struct ParsedInput {
			int w;
			int h;
			int l;
		};

		Day02Puzzle();
		~Day02Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<ParsedInput> parseInput(const std::vector<std::string>& _input);
		static int part1(const std::vector<ParsedInput>& _input);
		static int getPart1(const ParsedInput& _input);
		static int part2(const std::vector<ParsedInput>& _input);
		static int getPart2(const ParsedInput& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_02_PUZZLE_HPP_