#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_06_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_06_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>
#include <vector>

namespace TwentySixteen {
	
	class Day06Puzzle : public core::PuzzleBase {
	public:
		Day06Puzzle();
		~Day06Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void processSignal(const std::string& _signal, std::vector<std::unordered_map<char, int>>& _instances);

		static std::string doPart1(const std::vector<std::string>& _input);
		static std::string doPart2(const std::vector<std::string>& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_06_PUZZLE_HPP_