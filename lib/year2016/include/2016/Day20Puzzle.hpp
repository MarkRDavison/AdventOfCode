#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_20_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_20_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {

	using IpValue = unsigned int;

	class Day20Puzzle : public core::PuzzleBase {
	public:
		Day20Puzzle();
		~Day20Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve(IpValue _max);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_20_PUZZLE_HPP_