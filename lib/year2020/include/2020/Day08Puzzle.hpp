#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_08_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_08_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <functional>
#include <map>

namespace TwentyTwenty {



	using IntcodeValue = long long;
	using OperationFxn = std::function<void(IntcodeValue)>;

	class HandlheldConsole {
		// TODO: Refactor this
	};

	struct Day8Struct {
		std::string op;
		IntcodeValue value;
	};
	
	class Day08Puzzle : public core::PuzzleBase {
	public:
		Day08Puzzle();
		~Day08Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<Day8Struct> parseInput(const std::vector<std::string>& _inputLines);
		static std::string doPart1(const std::vector<Day8Struct>& _input);
		static std::string doPart2(const std::vector<Day8Struct>& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_08_PUZZLE_HPP_