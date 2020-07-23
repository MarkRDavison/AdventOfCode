#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_14_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_14_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	struct ReindeerInfo {
		std::string name;
		int speed;
		int duration;
		int restDuration;
	};

	class Day14Puzzle : public core::PuzzleBase {
	public:
		Day14Puzzle();
		~Day14Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<ReindeerInfo> parseInput(const std::vector<std::string>& _input);
		static int getDistanceFromTime(const ReindeerInfo& _info, int _time);

		static std::pair<int, std::string> getMaxDistanceAfterTime(const std::vector<ReindeerInfo>& _info, int _time);
		static std::pair<int, std::string> getMaxPointsAfterTime(const std::vector<ReindeerInfo>& _info, int _time);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_14_PUZZLE_HPP_