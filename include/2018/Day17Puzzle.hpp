#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_17_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_17_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyEighteen {

	class Day17Puzzle : public core::PuzzleBase {
	public:
		Day17Puzzle();
		~Day17Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<unsigned, unsigned> parseInputAndPrepareGround(std::vector<std::vector<char>>& _ground);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<std::string> dumpGround(const std::vector<std::vector<char>>& _ground, std::size_t _minX, std::size_t _minY);
		static void printGround(const std::vector<std::vector<char>>& _ground, std::size_t _minX, std::size_t _minY);
		static char getChar(const std::vector<std::vector<char>>& _ground, unsigned _x, unsigned _y);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_17_PUZZLE_HPP_