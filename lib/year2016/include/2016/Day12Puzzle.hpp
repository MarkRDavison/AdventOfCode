#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_12_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_12_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	using AssembunnyInteger = long;
	using Registers = AssembunnyInteger[4];

	class Day12Puzzle : public core::PuzzleBase {
	public:
		Day12Puzzle();
		~Day12Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void applyInstruction(AssembunnyInteger& _programCounter, Registers& _registers, const std::string& _instruction);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_12_PUZZLE_HPP_