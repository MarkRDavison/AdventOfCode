#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_11_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_11_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	class Day11Puzzle : public core::PuzzleBase {
	public:
		Day11Puzzle();
		~Day11Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::string increment(const std::string& _password);
		static bool validate(const std::string& _password);
		static std::string getNextPassword(const std::string& _password);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_11_PUZZLE_HPP_