#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_17_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_17_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {

	struct RoomDoorState {
		bool U{ false };
		bool D{ false };
		bool L{ false };
		bool R{ false };
	};
	
	class Day17Puzzle : public core::PuzzleBase {
	public:
		Day17Puzzle();
		~Day17Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static RoomDoorState getRoomDoorState(const std::string& _passcode, const std::string& _path);
		static std::string explore(const std::string& _passcode, bool _shortest);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_17_PUZZLE_HPP_