#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_13_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_13_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Pathfinding.hpp>
#include <Core/Region.hpp>

namespace TwentySixteen {

	using OfficeInteger = long long;
	struct OfficeCell {
		bool open{ false };
		
		bool valid() {
			return open;
		}
		float costTo(const OfficeCell& _target) const {
			return 1.0f;
		}
	};
	
	class Day13Puzzle : public core::PuzzleBase {
	public:
		Day13Puzzle();
		~Day13Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		
		static bool getTraversable(const ze::Vector2<OfficeInteger>& _location, OfficeInteger _number);
		static void searchSpace(core::CartesianNetwork<OfficeCell>& _network, OfficeInteger _number, const ze::Vector2<OfficeInteger>& _maxSize);
		static int pathLength(core::CartesianNetwork<OfficeCell>& _network, const ze::Vector2<OfficeInteger>& _start, const ze::Vector2<OfficeInteger>& _end);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_13_PUZZLE_HPP_