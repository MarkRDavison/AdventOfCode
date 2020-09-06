#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_04_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_04_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day04Puzzle : public core::PuzzleBase {
	public:
		Day04Puzzle();
		~Day04Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static bool validateRoom(const std::string& _roomInfo, int& _sectorId);
		static bool isNorthPoleRoom(const std::string& _roomInfo, int& _sectorId, const std::string& _key);
		static int doPart1(const std::vector<std::string>& _input);
		static int doPart2(const std::vector<std::string>& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_04_PUZZLE_HPP_