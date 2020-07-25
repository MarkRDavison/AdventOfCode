#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_24_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_24_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	class Day24Puzzle : public core::PuzzleBase {
	public:
		Day24Puzzle();
		~Day24Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static long long findSmallestQuantumEntaglement(const std::vector<int>& _weights, int _sections);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_24_PUZZLE_HPP_