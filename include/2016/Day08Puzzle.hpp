#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_08_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_08_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day08Puzzle : public core::PuzzleBase {
	public:
		Day08Puzzle();
		~Day08Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		void setCustomScreenSize(unsigned _width, unsigned _height) {
			m_Width = _width;
			m_Height = _height;
		}

	private:

	private:
		std::vector<std::string> m_InputLines;
		unsigned m_Width{ 50 };
		unsigned m_Height{ 6 };
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_08_PUZZLE_HPP_