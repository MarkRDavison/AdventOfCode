#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_01_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_01_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day01Puzzle : public core::PuzzleBase {
	public:
		Day01Puzzle();
		~Day01Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<int, int> getAnswers(const std::string& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_01_PUZZLE_HPP_