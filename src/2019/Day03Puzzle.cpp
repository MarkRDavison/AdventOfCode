#include <2019/Day03Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>

namespace TwentyNineteen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	static core::Vector2i charToDirection(char _c) {
		if (_c == 'R') {
			return { 1,0 };
		}if (_c == 'L') {
			return { -1,0 };
		}if (_c == 'U') {
			return { 0,1 };
		}if (_c == 'D') {
			return { 0,-1 };
		}
		return {};
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {

		core::Region<Day03Cell> region;

		core::Vector2i currentPosition = { 0,0 };

		int closestIntersection = std::numeric_limits<int>::max();
		int part2 = std::numeric_limits<int>::max();

		region.getCell(0, 0).first = true;
		region.getCell(0, 0).second = true;

		int count = 0;
		for (const auto& part : core::StringExtensions::splitStringByDelimeter(m_InputLines[0], ",")) {
			const auto& dir = charToDirection(part[0]);
			const int length = std::atoi(part.substr(1).c_str());

			for (int i = 0; i < length; ++i) {
				count++;
				const int x = currentPosition.x + dir.x;
				const int y = currentPosition.y + dir.y;
				auto& cell = region.getCell(x, y);
				cell.first = true;
				cell.firstCount = std::min(cell.firstCount, count);
				currentPosition = { x,y };
			}
		}
		currentPosition = { 0,0 };
		count = 0;
		for (const auto& part : core::StringExtensions::splitStringByDelimeter(m_InputLines[1], ",")) {
			const auto& dir = charToDirection(part[0]);
			const int length = std::atoi(part.substr(1).c_str());

			for (int i = 0; i < length; ++i) {
				count++;
				const int x = currentPosition.x + dir.x;\
				const int y = currentPosition.y + dir.y;
				auto& cell = region.getCell(x, y);
				cell.second = true;
				cell.secondCount = std::min(cell.secondCount, count);
				currentPosition = { x,y };
				if (x == 0 && y == 0) {
					continue;
				}
				if (cell.first) {
					int currentDistance = std::abs(x) + std::abs(y);
					closestIntersection = std::min(closestIntersection, currentDistance);
					
					int currentCount = cell.firstCount + cell.secondCount;
					part2 = std::min(part2, currentCount);
				}
			}
		}

		return { std::to_string(closestIntersection), std::to_string(part2) };
	}
}
