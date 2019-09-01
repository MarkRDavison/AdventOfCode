#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_03_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_03_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Vector2.hpp>

namespace TwentyFifteen {
	
	class Day03Puzzle : public core::PuzzleBase {
	public:

		static const constexpr char Up = '^';
		static const constexpr char Down = 'v';
		static const constexpr char Left = '<';
		static const constexpr char Right = '>';

		Day03Puzzle();
		~Day03Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static core::Vector2i charToDirection(char _c);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_03_PUZZLE_HPP_