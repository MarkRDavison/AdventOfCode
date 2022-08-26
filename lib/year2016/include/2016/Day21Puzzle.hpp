#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_21_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_21_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {

	enum class InstructionType {
		SwapLetter,
		SwapPosition,
		MovePostion,
		Rotate,
		RotatePosition,
		ReversePositions
	};

	struct Instruction {
		Instruction(InstructionType _type) : type(_type) {}

		InstructionType type;

		int fromPosition{ 0u };
		int toPosition{ 0u };
		int steps{ 0u };

		char fromLetter{ '?' };
		char toLetter{ '?' };

	};
	
	class Day21Puzzle : public core::PuzzleBase {
	public:
		Day21Puzzle();
		~Day21Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		std::pair<std::string, std::string> fastSolve(const std::string& _startingPassword, const std::string& _endingPasword);

		static Instruction parse(const std::string& _input);
		static std::string apply(const Instruction& _instruction, const std::string& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_21_PUZZLE_HPP_