#include <2016/Day02Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <zeno/Core/Vector2.hpp>
#include <unordered_map>
#include <algorithm>

namespace std {
	template<>
	struct hash<ze::Vector2i> {
		size_t operator()(const ze::Vector2i& obj) const {
			return std::hash<int>()(obj.x) ^ std::hash<int>()(obj.y);
		}
	};
}

namespace TwentySixteen {

	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Bathroom Security", 2016, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		return { doPart1(m_InputLines), doPart2(m_InputLines) };
	}

	std::string Day02Puzzle::doPart1(const std::vector<std::string>& _inputLines) {
		std::string result;
		ze::Vector2i location{ 1,1 };
		for (const auto& row : _inputLines) {
			for (char c : row) {
				switch (c) {
				case 'U':
					location.y -= 1;
					break;
				case 'D':
					location.y += 1;
					break;
				case 'L':
					location.x -= 1;
					break;
				case 'R':
					location.x += 1;
					break;
				}

				location.x = std::min(2, std::max(0, location.x));
				location.y = std::min(2, std::max(0, location.y));
			}

			const int value = (location.y) * 3 + (location.x) + 1;
			result += std::to_string(value);
		}

		return result;
	}
	std::string Day02Puzzle::doPart2(const std::vector<std::string>& _inputLines) {
		std::unordered_map<ze::Vector2i, char> values;
		values[{+0, -2}] = '1';

		values[{-1, -1}] = '2';
		values[{+0, -1}] = '3';
		values[{+1, -1}] = '4';

		values[{-2, +0}] = '5';
		values[{-1, +0}] = '6';
		values[{+0, +0}] = '7';
		values[{+1, +0}] = '8';
		values[{+2, +0}] = '9';

		values[{-1, +1}] = 'A';
		values[{+0, +1}] = 'B';
		values[{+1, +1}] = 'C';

		values[{+0, +2}] = 'D';
		std::string result;
		ze::Vector2i location{ -2,0 };
		for (const auto& row : _inputLines) {
			for (char c : row) {
				switch (c) {
				case 'U':
					if (abs(location.x) + abs(location.y-1) <= 2) {
						location.y -= 1;
					}
					break;
				case 'D':
					if (abs(location.x) + abs(location.y+1) <= 2) {
						location.y += 1;
					}
					break;
				case 'L':
					if (abs(location.x-1) + abs(location.y) <= 2) {
						location.x -= 1;
					}
					break;
				case 'R':
					if (abs(location.x+1) + abs(location.y) <= 2) {
						location.x += 1;
					}
					break;
				}
			}

			result += values[location];
		}

		return result;
	}
}
