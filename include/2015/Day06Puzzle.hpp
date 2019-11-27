#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_06_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_06_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Vector2.hpp>

namespace TwentyFifteen {
	
	class Day06Puzzle : public core::PuzzleBase {
	public:
		Day06Puzzle();
		~Day06Puzzle() override;

		struct LightInstruction {
			enum class Type {
				TurnOn,
				TurnOff,
				Toggle
			} type;
			core::Vector2i start;
			core::Vector2i end;
		};

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static LightInstruction parseLine(const std::string& _line);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_06_PUZZLE_HPP_