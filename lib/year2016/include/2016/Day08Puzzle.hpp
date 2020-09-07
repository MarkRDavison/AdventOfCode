#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_08_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_08_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day08Puzzle : public core::PuzzleBase {
	public:
		Day08Puzzle();
		~Day08Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void applyInstruction(const std::string& _instruction, unsigned _width, unsigned _height, char* _screen);
		static void applyRectInstruction(unsigned _width, unsigned _height, char* _screen, unsigned _x, unsigned _y);
		static void applyRotateColumnInstruction(unsigned _width, unsigned _height, char* _screen, unsigned _column, unsigned _amount);
		static void applyRotateRowInstruction(unsigned _width, unsigned _height, char* _screen, unsigned _row, unsigned _amount);

		static int doPart1(const std::vector<std::string>& _input, unsigned _width, unsigned _height, std::string& _screen);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_08_PUZZLE_HPP_