#include <2018/Day11Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <map>

namespace TwentyEighteen {

	int calculatePowerLevel(int _serialNumber, int _x, int _y) {
		const int rackId = _x + 10;
		int power = rackId * _y;
		power += _serialNumber;
		power *= rackId;

		const int hundreds = power / 100 % 10;
		return hundreds - 5;
	}

	int calculatePowerForRegion(core::Region<int>& _calculatedPowerLevels, int _x, int _y, int _size) {
		int sum = 0;

		for (int y = _y; y < _y + _size; ++y) {
			for (int x = _x; x < _x + _size; ++x) {
				sum += _calculatedPowerLevels.getCell(x, y);
			}
		}

		return sum;
	}

	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Chronal Charge", 2018, 11) {

	}

	Day11Puzzle::~Day11Puzzle() {

	}

	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(_initialisationInfo.parameters);
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		constexpr const int Width = 301;
		constexpr const int Height = 301;
		const int PowerLevel = std::atoi(m_InputLines[0].c_str());

		core::Region<int> powerLevels;

		std::array<std::array<int, Height>, Width> sum{ 0 };

		int bx1 = std::numeric_limits<int>::min();
		int by1 = std::numeric_limits<int>::min();
		int bx2 = std::numeric_limits<int>::min();
		int by2 = std::numeric_limits<int>::min();
		int bs2 = std::numeric_limits<int>::min();
		{
			int best1 = std::numeric_limits<int>::min();
			int best2 = std::numeric_limits<int>::min();
			for (int y = 1; y <= 300; y++) {
				for (int x = 1; x <= 300; x++) {
					const int id = x + 10;
					int p = id * y + PowerLevel;
					p = (p * id) / 100 % 10 - 5;
					sum[y][x] = p + sum[y - 1][x] + sum[y][x - 1] - sum[y - 1][x - 1];
				}
			}
			for (int s = 1; s <= 300; s++) {
				for (int y = s; y <= 300; y++) {
					for (int x = s; x <= 300; x++) {
						const int total = sum[y][x] - sum[y - s][x] - sum[y][x - s] + sum[y - s][x - s];
						if (total > best2) {
							best2 = total, bx2 = x, by2 = y, bs2 = s;
						}
						if (s == 3) {
							if (total > best1) {
								best1 = total, bx1 = x - 2, by1 = y - 2;
							}
						}
					}
				}
			}

			std::string Part1Answer = std::to_string(bx1) + "," + std::to_string(by1);

			std::string Part2Answer = std::to_string(bx2 - bs2 + 1) + "," + std::to_string(by2 - bs2 + 1) + "," + std::to_string(bs2);

			return { Part1Answer, Part2Answer };
		}
	}
}
