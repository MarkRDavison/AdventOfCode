#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_18_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_18_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day18Puzzle : public core::PuzzleBase {
	public:
		Day18Puzzle();
		~Day18Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<std::string> createMap(const std::string& _start, unsigned _rows);
		static int getSafeTilesCount(const std::string& _start, unsigned _rows);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_18_PUZZLE_HPP_