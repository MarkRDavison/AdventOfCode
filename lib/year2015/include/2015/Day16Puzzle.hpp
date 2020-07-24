#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_16_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_16_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyFifteen {
	
	struct SueInfo {
		int id;
		std::unordered_map<std::string, int>compounds;
	};

	class Day16Puzzle : public core::PuzzleBase {
	public:
		Day16Puzzle();
		~Day16Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<SueInfo> parseInput(const std::vector<std::string>& _inputLines);
		static bool isInvalid(const SueInfo& _sueInfo, const std::unordered_map<std::string, int>& _data, bool _part2);

		static std::vector<int> getPotentialIds(const std::unordered_map<std::string, int>& _data, const std::vector<SueInfo>& _sueInfo, bool _part2);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_16_PUZZLE_HPP_