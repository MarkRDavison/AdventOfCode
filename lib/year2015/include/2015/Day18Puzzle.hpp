#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_18_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_18_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>
#include <zeno/Core/Vector2.hpp>

namespace TwentyFifteen {

	struct LightCell {
		bool on{ false };
		bool nextOn{ false };
	};
	
	class Day18Puzzle : public core::PuzzleBase {
	public:
		Day18Puzzle();
		~Day18Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void parseInput(core::Region<LightCell>& _region, const std::vector<std::string>& _inputLines);
		static int iterate(core::Region<LightCell>& _region, unsigned _iterations, bool _part2);
		static int neighboursOn(const core::Region<LightCell>& _region, const ze::Vector2i& _coord);

		static void dumpRegion(const core::Region<LightCell>& _region);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_18_PUZZLE_HPP_