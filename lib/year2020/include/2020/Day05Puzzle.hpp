#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_05_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_05_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {
	
	class Day05Puzzle : public core::PuzzleBase {
	public:
		Day05Puzzle();
		~Day05Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		struct SeatInfo {
			int row;
			int column;
			int seatId;
		};

		static SeatInfo getSeatInfo(const std::string& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_05_PUZZLE_HPP_