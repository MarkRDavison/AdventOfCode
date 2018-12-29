#include <2018/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <regex>
#include <SFML/System/Vector2.hpp>
#include <unordered_set>

namespace TwentyEighteen {

	Day06Puzzle::Day06Puzzle(int _threshold /*= 10000*/) :
		core::PuzzleBase("Chronal Coordinates", 2018, 6),
		m_Threshold(_threshold) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}

	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {

		std::smatch m;
		const std::regex regex("([0-9]+), ([0-9]+)");

		std::vector<std::pair<char, sf::Vector2i>> coordinates;

		int minX = std::numeric_limits<int>::max();
		int maxX = std::numeric_limits<int>::min();
		int minY = std::numeric_limits<int>::max();
		int maxY = std::numeric_limits<int>::min();

		char c = 'a';
		for (const std::string& _line : m_InputLines) {
			std::regex_match(_line, m, regex);

			const int x = std::atoi(m[1].str().c_str());
			const int y = std::atoi(m[2].str().c_str());

			minX = std::min(minX, x);
			maxX = std::max(maxX, x);
			minY = std::min(minY, y);
			maxY = std::max(maxY, y);

			coordinates.emplace_back(std::make_pair(c, sf::Vector2i(x, y)));
			c++;
		}

		std::cout << "min " << minX << "," << minY << " max " << maxX << "," << maxY << std::endl;

		std::unordered_set<char> infiniteCharacters;
		std::map<char, int> regionSize;

		int part2Answer = 0;

		for (int y = minY - 1; y < maxY + 1; ++y) {
			for (int x = minX - 1; x < maxX + 1; ++x) {
				char closest = '?';
				int closestDistance = std::numeric_limits<int>::max();
				int closestCount = 0;

				int totalDistance = 0;

				for (const auto& kvp : coordinates) {
					const int distance = std::abs(kvp.second.x - x) + std::abs(kvp.second.y - y);
					if (distance < closestDistance) {
						closestDistance = distance;
						closest = kvp.first;
						closestCount = 1;
					}
					else if (distance == closestDistance) {
						closestCount++;
					}
					totalDistance += distance;
				}

				if (totalDistance <= m_Threshold) {
					part2Answer++;
				}

				if (closest != '?' && closestCount == 1) {
					regionSize[closest]++;
					if (x == 0 || y == 0 || x == maxX || y == maxY) {
						infiniteCharacters.emplace(closest);
					}
				}
			}
		}

		int maxSize = 0;

		for (const auto& kvp : regionSize) {
			if (infiniteCharacters.count(kvp.first) > 0) {
				continue;
			}

			if (maxSize < kvp.second) {
				maxSize = kvp.second;
			}
		}

		return { std::to_string(maxSize), std::to_string(part2Answer) };
	}

}
