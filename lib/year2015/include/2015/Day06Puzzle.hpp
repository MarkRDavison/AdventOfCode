#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_06_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_06_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <zeno/Core/Rect.hpp>

// TODO: This is very slow to compile

namespace TwentyFifteen {
	struct Day06InputLine {

		enum class Action {
			Off		= 0,
			On		= 1,
			Toggle	= 2
		};

		Day06InputLine(ze::IntRect _bounds, Action _action) :
			bounds(_bounds),
			action(_action) {

		}

		ze::IntRect bounds;
		Action action;
	};

	class Day06Puzzle : public core::PuzzleBase {
	public:
		Day06Puzzle();
		~Day06Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<Day06InputLine> parseLines(const std::vector<std::string>& _input);

		template<typename std::size_t TSize>
		static void applyLinePart1(std::vector<int>& _grid, const Day06InputLine& _line) {
			for (auto y = _line.bounds.left; y < _line.bounds.left + _line.bounds.width; ++y) {
				for (auto x = _line.bounds.bot; x < _line.bounds.bot + _line.bounds.height; ++x) {
					int& light = _grid[y * TSize + x];
					switch (_line.action) {
					case Day06InputLine::Action::On:
						light = 1;
						break;
					case Day06InputLine::Action::Off:
						light = 0;
						break;
					case Day06InputLine::Action::Toggle:
						if (light == 1) {
							light = 0;
						}
						else {
							light = 1;
						}
						break;
					}
				}
			}
		}

		template<typename std::size_t TSize>
		static void applyLinePart2(std::vector<int>& _grid, const Day06InputLine& _line) {
			for (auto y = _line.bounds.left; y < _line.bounds.left + _line.bounds.width; ++y) {
				for (auto x = _line.bounds.bot; x < _line.bounds.bot + _line.bounds.height; ++x) {
					int& light = _grid[y * TSize + x];
					switch (_line.action) {
					case Day06InputLine::Action::On:
						light += 1;
						break;
					case Day06InputLine::Action::Off:
						light -= 1;
						if (light < 0) {
							light = 0;
						}
						break;
					case Day06InputLine::Action::Toggle:
						light += 2;
						break;
					}
				}
			}
		}

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_06_PUZZLE_HPP_