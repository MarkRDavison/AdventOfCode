#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_08_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_08_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {
	
	class Day08Puzzle : public core::PuzzleBase {
	public:

		struct StringInfo {
			unsigned characterSize{ 0 };
			unsigned memorySize{ 0 };
			unsigned reincodeSize{ 0 };
		};

		Day08Puzzle();
		~Day08Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static StringInfo getInfo(const std::string& _line);
		static unsigned encodeSize(const std::string& _line);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_08_PUZZLE_HPP_