#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_04_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_04_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <mutex>

namespace TwentyFifteen {
	
	class Day04Puzzle : public core::PuzzleBase {
	public:
		Day04Puzzle();
		~Day04Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void findZeroedMd5(const std::string& _input, unsigned _starting, unsigned _count, std::mutex& _mutex, std::vector<unsigned>& _output5, std::vector<unsigned>& _output6);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_04_PUZZLE_HPP_