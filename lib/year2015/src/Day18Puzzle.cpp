#include <2015/Day18Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Like a GIF For Your Yard", 2015, 18) {

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
		core::Region<LightCell> region;

		parseInput(region, m_InputLines);
		const int part1 = iterate(region, 100, false);

		parseInput(region, m_InputLines);
		const int part2 = iterate(region, 100, true);

		return { std::to_string(part1), std::to_string(part2) };
	}

	void Day18Puzzle::parseInput(core::Region<LightCell>& _region, const std::vector<std::string>& _inputLines) {
		for (unsigned y = 0; y < _inputLines.size(); ++y) {
			for (unsigned x = 0; x < _inputLines[y].size(); ++x) {
				auto& cell = _region.getCell((int)x, (int)y);
				cell.on = (_inputLines[y][x] == '#');
			}
		}
	}
	int Day18Puzzle::iterate(core::Region<LightCell>& _region, unsigned _iterations, bool _part2) {
		if (_part2) {
			_region.getCell(0, 0).on = true;
			_region.getCell(0, _region.maxY).on = true;
			_region.getCell(_region.maxX, _region.maxY).on = true;
			_region.getCell(_region.maxX, 0).on = true;
		}

		//std::cout << "0 iterations" << std::endl;
		//dumpRegion(_region);
		for (unsigned i = 0; i < _iterations; ++i) {
			for (int y = 0; y <= _region.maxY; ++y) {
				for (int x = 0; x <= _region.maxX; ++x) {
					auto& cell = _region.getCell(x, y);

					if (_part2 && (
						x == 0 && y == 0 ||
						x == 0 && y == _region.maxY ||
						x == _region.maxX && y == _region.maxY ||
						x == _region.maxX && y == 0)) {
						cell.on = true;
						cell.nextOn = true;
					}
					else {
						const auto numNeighboursOn = neighboursOn(_region, ze::Vector2i(x, y));
						if (cell.on) {
							cell.nextOn = numNeighboursOn == 2 || numNeighboursOn == 3;
						} else {
							cell.nextOn = numNeighboursOn == 3;
						}
					}
				}
			}

			for (int y = 0; y <= _region.maxY; ++y) {
				for (int x = 0; x <= _region.maxX; ++x) {
					auto& cell = _region.getCell(x, y);
					cell.on = cell.nextOn;
				}
			}
			//std::cout << i << " iterations" << std::endl;
			//dumpRegion(_region);
		}
		int lightsOn = 0;
		for (int y = 0; y <= _region.maxY; ++y) {
			for (int x = 0; x <= _region.maxX; ++x) {
				if (_region.getCell(x, y).on) {
					lightsOn++;
				}
			}
		}
		return lightsOn;
	}
	int Day18Puzzle::neighboursOn(const core::Region<LightCell>& _region, const ze::Vector2i& _coord) {
		int on = 0;
		for (int y = -1; y <= +1; ++y) {
			for (int x = -1; x <= +1; ++x) {
				if (x == 0 && y == 0) { continue; }
				const auto absoluteCoord = _coord + ze::Vector2i(x, y);
				if (absoluteCoord.x < _region.minX ||
					absoluteCoord.y < _region.minY ||
					absoluteCoord.x > _region.maxX ||
					absoluteCoord.y > _region.maxY) {
					continue;
				}
				on += (_region.getCell(absoluteCoord.x, absoluteCoord.y).on
					? 1
					: 0);
			}
		}

		return on;
	}
	
	void Day18Puzzle::dumpRegion(const core::Region<LightCell>& _region) {
		for (int y = 0; y <= _region.maxY; ++y) {
			for (int x = 0; x <= _region.maxX; ++x) {
				auto& cell = _region.getCell(x, y);
				std::cout << (cell.on ? '#' : '.');
			}
			std::cout << std::endl;
		}
	}
}
