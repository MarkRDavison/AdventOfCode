#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_09_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_09_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Pathfinding.hpp>

namespace TwentyFifteen {
	
	class Day09Puzzle : public core::PuzzleBase {
	public:
		Day09Puzzle();
		~Day09Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void populateNetwork(core::EdgeNetwork& _network, const std::vector<std::string>& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_09_PUZZLE_HPP_