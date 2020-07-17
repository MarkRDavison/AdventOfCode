#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_08_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_08_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	using LengthData = std::pair<std::size_t, std::size_t>;

	class Day08Puzzle : public core::PuzzleBase {
	public:
		Day08Puzzle();
		~Day08Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::size_t getPart1(const std::vector<std::string>& _input);
		static std::size_t getPart2(const std::vector<std::string>& _input);

		static LengthData getLengthMemory(const std::string& _string);
		static LengthData getLengthEncode(const std::string& _string);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_08_PUZZLE_HPP_