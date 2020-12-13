#include <2020/Day11Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>
#include <functional>

namespace TwentyTwenty {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Seating System", 2020, 11) {
	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::solve(const std::vector<std::string>& _input) {
		struct Cell {
			char c[2];
		};

		const int width = (int)_input[0].size();
		const int height = (int)_input.size();

		const auto& performIterationPart = [width, height](core::Region<Cell>& _region, unsigned _index, int _neighbourThreshold, int _searchDistance) -> bool {
			bool changes{ false };
			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width; ++x) {
					const char current = _region.getCell(x, y).c[_index];
					auto& next = _region.getCell(x, y).c[(_index + 1) % 2];

					int occupiedNeighbours = 0;
					for (int yOff = -1; yOff <= 1; ++yOff) {
						for (int xOff = -1; xOff <= 1; ++xOff) {
							if (yOff == 0 && xOff == 0) { continue; }
							for (int length = 1; length <= _searchDistance; ++length) {
								const int yNeighbour = y + yOff * length;
								const int xNeighbour = x + xOff * length;
								if (xNeighbour >= 0 && yNeighbour >= 0 &&
									xNeighbour < width && yNeighbour < height) {
									const char v = _region.getCell(xNeighbour, yNeighbour).c[_index];
									if (v == '#') {
										occupiedNeighbours++;
									}
									if (v != '.') {
										break;
									}
								}
							}
						}
					}

					next = current;
					if (current == 'L') {
						if (occupiedNeighbours == 0) {
							next = '#';
							changes = true;
						}

					}
					else if (current == '#') {
						if (occupiedNeighbours >= _neighbourThreshold) {
							next = 'L';
							changes = true;
						}
					}
				}
			}
			return changes;
		};

		const auto solveIterations = [&](std::function<bool(core::Region<Cell>&, unsigned, int, int)> _fxn, int _neighbourThreshold, int _searchDistance) -> std::string {
			core::Region<Cell> region;
			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width; ++x) {
					auto& cell = region.getCell(x, y);
					cell.c[0] = _input[y][x];
					cell.c[1] = _input[y][x];
				}
			}
			unsigned iter = 0;
			for (unsigned i = 0; ;) {
				if (!_fxn(region, i, _neighbourThreshold, _searchDistance)) {
					break;
				}
				i = (i + 1) % 2;
			}

			int count = 0;
			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width; ++x) {
					if (region.getCell(x, y).c[0] == '#') {
						count++;
					}
				}
			}
			
			return std::to_string(count);
		};



		return { 
			solveIterations(performIterationPart, 4, 1),
			solveIterations(performIterationPart, 5, std::max(width, height))
		};
	}
	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		return solve(m_InputLines);
	}

}
