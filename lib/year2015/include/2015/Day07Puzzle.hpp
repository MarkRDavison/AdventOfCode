#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyFifteen {

	using SignalIntType = std::uint16_t;
	using ResolvedMap = std::unordered_map<std::string, SignalIntType>;

	enum class InstructionType {
		INPUT,
		AND,
		OR,
		LSHIFT,
		RSHIFT,
		NOT
	};

	enum class SignalType {
		NotRequired		= 0,
		Constant		= 1,
		Wire			= 2
	};

	struct Day07ParsedLine {
		InstructionType type;

		SignalType signalTypeInput1{ SignalType::NotRequired };
		SignalType signalTypeInput2{ SignalType::NotRequired };

		SignalIntType constantInput1;
		SignalIntType constantInput2;

		std::string wireInput1;
		std::string wireInput2;
		std::string wireOutput;
	};

	class Day07Puzzle : public core::PuzzleBase {
	public:
		Day07Puzzle();
		~Day07Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static Day07ParsedLine parseLine(const std::string& _input);

		static void runLogic(const std::vector<std::string>& _input, ResolvedMap& _resolvedWires);
		
		static bool isResolved(const Day07ParsedLine& _line, const ResolvedMap& _resolvedWires);
		static SignalIntType resolve(const Day07ParsedLine& _line, const ResolvedMap& _resolvedWires);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_07_PUZZLE_HPP_