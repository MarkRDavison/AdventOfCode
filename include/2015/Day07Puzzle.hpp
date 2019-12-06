#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <functional>

namespace TwentyFifteen {

	
	
	class Day07Puzzle : public core::PuzzleBase {
	public:

		using InstructionDataType = long;
		using CompiledInstruction = std::function<InstructionDataType(void)>;
		using Program = std::unordered_map<std::string, CompiledInstruction>;

		struct Computer {
			Program p;
			std::unordered_map<std::string, InstructionDataType> memoizedValues;
		};

		struct ParsedInstruction {

			enum class OperatorType {
				ASSIGN,
				AND,
				OR,
				LSHIFT,
				RSHIFT,
				NOT,
				NOOP,
				INVALID
			} type;

			std::string input1;
			std::string input2;
			InstructionDataType input1Int;
			InstructionDataType input2Int;
			std::string output;
		};

		Day07Puzzle();
		~Day07Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static ParsedInstruction parseInstruction(const std::string& _line);
		static void compileAssignInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr);
		static void compileAndInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr);
		static void compileOrInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr);
		static void compileLeftShiftInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr);
		static void compileRightShiftInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr);
		static void compileNotInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr);
		static void compileNoOpInstruction(Computer& _computer, const Day07Puzzle::ParsedInstruction& _instr);

		std::string desiredoutput{ "a" };

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_07_PUZZLE_HPP_