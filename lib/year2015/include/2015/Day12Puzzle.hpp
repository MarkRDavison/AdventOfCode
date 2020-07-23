#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_12_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_12_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace ze {
	class JsonNode;
}

namespace TwentyFifteen {
	
	class Day12Puzzle : public core::PuzzleBase {
	public:
		Day12Puzzle();
		~Day12Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<int, int> solve(const std::string& _input);
		static int recurser(const ze::JsonNode& _node, bool _validate);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_12_PUZZLE_HPP_