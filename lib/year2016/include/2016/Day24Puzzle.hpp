#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_24_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_24_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	struct DuctCell {
		bool open{ false };

		bool valid() {
			return open;
		}
		float costTo(const DuctCell& _target) const {
			return 1.0f;
		}
	};

	class Day24Puzzle : public core::PuzzleBase {
	public:
		Day24Puzzle();
		~Day24Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_24_PUZZLE_HPP_