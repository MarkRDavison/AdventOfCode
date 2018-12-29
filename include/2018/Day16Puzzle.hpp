#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_16_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_16_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <2018/RegisterInstruction.hpp>
#include <2018/TrainingRegisterInstruction.hpp>

namespace TwentyEighteen {

	class Day16Puzzle : public core::PuzzleBase {
	public:
		Day16Puzzle(bool _solvePart2 = true);
		~Day16Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		void runTrainingOnInstruction(RegisterTrainingInstruction& _trainingInstruction) const;

	private:
		bool m_SolvePart2;
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_16_PUZZLE_HPP_