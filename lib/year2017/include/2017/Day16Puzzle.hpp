#ifndef INCLUDED_ADVENT_OF_CODE_2017_DAY_16_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2017_DAY_16_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySeventeen {
	
	class Day16Puzzle : public core::PuzzleBase {
	public:
		Day16Puzzle();
		~Day16Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		std::pair<std::string, std::string> fastSolve(std::size_t _size);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2017_DAY_16_PUZZLE_HPP_