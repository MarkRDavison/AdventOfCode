#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_05_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_05_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day05Puzzle : public core::PuzzleBase {
	public:
		Day05Puzzle();
		~Day05Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static bool isValidIndex(const std::string& _doorId, unsigned _index, char& _nextCharacter);
		static bool isValidIndex(const std::string& _doorId, unsigned _index, unsigned& _position, char& _nextCharacter);
		static std::string doPart1(const std::string& _doorId);
		static std::string doPart2(const std::string& _doorId);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_05_PUZZLE_HPP_