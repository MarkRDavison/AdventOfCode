#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_02_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_02_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {	
	class Day02Puzzle : public core::PuzzleBase {
	public:
		struct ParsedLine {

			ParsedLine(int _l, int _w, int _h) :
				length(_l), width(_w), height(_h) { }

			int length;
			int width;
			int height;

			bool operator==(const ParsedLine& _other) const {
				return 
					this->length == _other.length &&
					this->width == _other.width &&
					this->height == _other.height;
			}
		};

		Day02Puzzle();
		~Day02Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static ParsedLine parseLine(const std::string& _inputLine);
		static int wrappingArea(const ParsedLine& _line);
		static int ribbonLength(const ParsedLine& _line);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_02_PUZZLE_HPP_