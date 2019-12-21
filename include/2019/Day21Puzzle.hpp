#ifndef INCLUDED_ADVENT_OF_CODE_2019_DAY_21_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2019_DAY_21_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <2019/IntcodeMachine.hpp>

namespace TwentyNineteen {
	
	class Day21Puzzle : public core::PuzzleBase {
	public:
		Day21Puzzle();
		~Day21Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		IntcodeValue getResultOrDumpError(const std::vector<std::string>& _springInstructions, const std::string& _mode);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2019_DAY_21_PUZZLE_HPP_