#include <2018/Day17Puzzle.hpp>
#include <2018/ParsedClayVein.hpp>
#include <Core/StringExtensions.hpp>
#include <SFML/System/Vector2.hpp>
#include <regex>
#include <stack>

namespace TwentyEighteen {

	bool isCharEmpty(char _c) {
		return _c == '.';
	}
	bool isCharEmptyOrFlowing(char _c) {
		return _c == '.' || _c == '|';
	}

	bool isCharSolid(char _c) {
		return _c == '#' || _c == '~';
	}

	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Reservoir Research", 2018, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}

	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<unsigned, unsigned> Day17Puzzle::parseInputAndPrepareGround(std::vector<std::vector<char>>& _ground) {
		std::smatch m;
		const std::regex regex("([xy])=([0-9]+), ([xy])=([0-9]+)..([0-9]+)");

		int minX = std::numeric_limits<int>::max();
		int minY = std::numeric_limits<int>::max();
		int maxX = std::numeric_limits<int>::min();
		int maxY = std::numeric_limits<int>::min();

		std::vector<ParsedClayVein> veins;
		for (const std::string& _line : m_InputLines) {
			const bool result = std::regex_search(_line, m, regex);
			if (result) {

				const std::string firstChar = m[1].str();
				const int firstNumber = std::atoi(m[2].str().c_str());
				const std::string secondChar = m[3].str();
				const int secondNumber1 = std::atoi(m[4].str().c_str());
				const int secondNumber2 = std::atoi(m[5].str().c_str());

				if (firstChar == "x") {
					veins.emplace_back(firstNumber, firstNumber, secondNumber1, secondNumber2);
				}
				else {
					veins.emplace_back(secondNumber1, secondNumber2, firstNumber, firstNumber);
				}
				ParsedClayVein& pcv = veins.back();

				minX = std::min(minX, pcv.xMin - 2);
				maxX = std::max(maxX, pcv.xMax + 2);
				minY = std::min(minY, pcv.yMin);
				maxY = std::max(maxY, pcv.yMax);
			}
		}

		std::pair<unsigned, unsigned> result { minY, maxY};
		maxY += 2;

		for (int y = 0; y <= maxY; ++y) {
			_ground.emplace_back(maxX + 2, '.');
		}

		for (const ParsedClayVein& _pcv : veins) {
			for (int y = _pcv.yMin; y <= _pcv.yMax; ++y) {
				for (int x = _pcv.xMin; x <= _pcv.xMax; ++x) {
					_ground[y][x] = '#';
				}
			}
		}
		_ground[0][500] = '+';

		return result;
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		std::vector<std::vector<char>> ground;
		std::stack<sf::Vector2u> dropPoints;
		dropPoints.emplace(500, 0);

		const std::pair<unsigned, unsigned> minMaxY = parseInputAndPrepareGround(ground);
		std::size_t minDrawX = 500;

		if (getVerbose()) {
			printGround(ground, minDrawX, 0);
		}

		while (!dropPoints.empty()) {
			const sf::Vector2u p = dropPoints.top();
			dropPoints.pop();

			if (p.y + 1 >= ground.size()) {
				continue;
			}

			const char charP = getChar(ground, p.x, p.y + 1);

			if (isCharEmpty(charP)) {
				{
					ground[p.y + 1][p.x] = '|';
					dropPoints.emplace(p.x, p.y + 1);
				}
			} else if (isCharSolid(charP)) {
				{
					const unsigned row = p.y;
					const unsigned rowBelow = p.y + 1;
					bool containedRight;
					bool containedLeft;
					unsigned minX = p.x;
					unsigned maxX = p.x;

					{
						for (unsigned x = p.x + 1; ;++x) {
							const char cBelow = getChar(ground, x, rowBelow);
							const char c = getChar(ground, x, row);
							if (isCharEmptyOrFlowing(cBelow)) {
								containedRight = false;
								maxX = x;
								dropPoints.emplace(x, row);
								break;
							}
							if (isCharSolid(c)) {
								containedRight = true;
								break;
							}
							maxX = x;
						}
					}
					{
						for (unsigned x = p.x - 1; ;--x) {
							const char cBelow = getChar(ground, x, rowBelow);
							const char c = getChar(ground, x, row);
							if (isCharEmptyOrFlowing(cBelow)) {
								containedLeft = false;
								minX = x;
								dropPoints.emplace(x, row);
								break;
							}
							if (isCharSolid(c)) {
								containedLeft = true;
								break;
							}
							minX = x;
						}
					}

					if (containedLeft && containedRight) {
						dropPoints.emplace(p.x, p.y - 1);
					}
					const char c = (containedRight && containedLeft) ? '~' : '|';
					for (unsigned x = minX; x <= maxX; ++x) {
						ground[row][x] = c;
					}
					minDrawX = std::min(minDrawX, minX - 2);
				}
			}

			if (getVerbose()) {
				printGround(ground, minDrawX, 0);
			}
		}

		int flowing = 0;
		int settled = 0;
		for (std::size_t y = minMaxY.first; y <= minMaxY.second; ++y) {
			for (char c : ground[y]) {
				if (c == '~') {
					settled++;
				} else if (c == '|') {
					flowing++;
				}
			}
		}

		return { std::to_string(flowing + settled), std::to_string(settled) };
	}

	std::vector<std::string> Day17Puzzle::dumpGround(const std::vector<std::vector<char>>& _ground, std::size_t _minX, std::size_t _minY) {
		std::vector<std::string> dumped;
		for (const auto& _row : _ground) {
			std::string rowString;
			for (std::size_t x = _minX; x < _row.size(); ++x) {
				rowString += _row[x];
			}
			dumped.push_back(rowString);
		}

		return dumped;
	}

	void Day17Puzzle::printGround(const std::vector<std::vector<char>>& _ground, std::size_t _minX, std::size_t _minY) {
		std::cout << std::string(_ground.front().size() - _minX, '=') << std::endl;
		for (const std::string& _row : dumpGround(_ground, _minX, _minY)) {
			std::cout << _row << std::endl;
		}
	}

	char Day17Puzzle::getChar(const std::vector<std::vector<char>>& _ground, unsigned _x, unsigned _y) {
		return _ground[_y][_x];
	}

}
