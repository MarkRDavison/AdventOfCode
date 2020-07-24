#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_17_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_17_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	class Day17Puzzle : public core::PuzzleBase {
	public:
		static constexpr const int Volume{ 150 };

		Day17Puzzle();
		~Day17Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;


		static std::pair<int, int> getResult(const std::vector<std::string>& _containers, int _volume);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_17_PUZZLE_HPP_