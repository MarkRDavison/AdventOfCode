#include <2016/Day18Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2016, 18) {

	}
	Day18Puzzle::~Day18Puzzle() {

	}


	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {
		const auto part1 = getSafeTilesCount(m_InputLines[0], 40);
		const auto part2 = getSafeTilesCount(m_InputLines[0], 400000);
		return { std::to_string(part1), std::to_string(part2) };
	}

	std::vector<std::string> Day18Puzzle::createMap(const std::string& _start, unsigned _rows) {
		std::vector<std::string> map;

		map.push_back(_start);

		for (unsigned i = 1; i < _rows; ++i) {
			const auto& previous = map.back();
			std::string next;

			for (unsigned x = 0; x < previous.size(); ++x) {
				char left = (x == 0) ? '.' : previous[x - 1];
				char center = previous[x];
				char right = (x == previous.size() -1) ? '.' : previous[x + 1];

				bool trap = false;
				if (left == '^' && center == '^' && right == '.') {
					trap = true;
				}
				else if (left == '.' && center == '^' && right == '^') {
					trap = true;
				}
				else if (left == '^' && center == '.' && right == '.') {
					trap = true;
				}
				else if (left == '.' && center == '.' && right == '^') {
					trap = true;
				}

				next += (trap ? '^' : '.');
			}


			map.push_back(next);
		}

		return map;
	}

	int Day18Puzzle::getSafeTilesCount(const std::string& _start, unsigned _rows) {
		

		const auto& safeCount = [](const std::string& _row) -> int {
			int cnt = 0;

			for (char c : _row) {
				if (c == '.') {
					cnt++;
				}
			}

			return cnt;
		};

		std::string previous = _start;
		int count = safeCount(previous);

		for (unsigned i = 1; i < _rows; ++i) {
			std::string next;

			for (unsigned x = 0; x < previous.size(); ++x) {
				char left = (x == 0) ? '.' : previous[x - 1];
				char center = previous[x];
				char right = (x == previous.size() - 1) ? '.' : previous[x + 1];

				bool trap = false;
				if (left == '^' && center == '^' && right == '.') {
					trap = true;
				} else if (left == '.' && center == '^' && right == '^') {
					trap = true;
				} else if (left == '^' && center == '.' && right == '.') {
					trap = true;
				} else if (left == '.' && center == '.' && right == '^') {
					trap = true;
				}

				next += (trap ? '^' : '.');
			}

			count += safeCount(next);

			previous = next;
		}

		return count;
	}
}
