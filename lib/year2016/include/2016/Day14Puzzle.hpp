#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_14_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_14_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day14Puzzle : public core::PuzzleBase {
	public:
		Day14Puzzle();
		~Day14Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static bool isKey(const std::string& _salt, unsigned _index, bool _part2);

		static unsigned getNthKeyIndex(const std::string& _salt, unsigned _keyNumber, bool _part2);
		static unsigned getNthKeyIndexMultiThreaded(const std::string& _salt, unsigned _keyNumber, bool _part2);

		inline static bool hasTriple(const std::string& _input, char& _triple) {

			for (unsigned i = 0; i < _input.size() - 2; ++i) {
				if (_input[i + 0] == _input[i + 1] &&
					_input[i + 1] == _input[i + 2]) {
					_triple = _input[i];
					return true;
				}
			}

			return false;
		}
		inline static bool hasQuintuple (const std::string& _input, char _triple) {

			for (unsigned i = 0; i < _input.size() - 4; ++i) {
				if (_input[i+0] == _triple &&
					_input[i + 0] == _input[i + 1] &&
					_input[i + 1] == _input[i + 2] &&
					_input[i + 2] == _input[i + 3] &&
					_input[i + 3] == _input[i + 4]) {
					_triple = _input[i];
					return true;
				}
			}

			return false;
		}

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_14_PUZZLE_HPP_