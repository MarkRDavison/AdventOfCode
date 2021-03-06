#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_10_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_10_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	class Day10Puzzle : public core::PuzzleBase {
	public:
		Day10Puzzle();
		~Day10Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::size_t getResult(const std::string& _input, std::size_t _iterations);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_10_PUZZLE_HPP_