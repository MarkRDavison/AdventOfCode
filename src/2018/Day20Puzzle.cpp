#include <2018/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <stack>
#include <map>
#include <algorithm>

namespace TwentyEighteen {

	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("A Regular Map", 2018, 20) {

	}
	Day20Puzzle::~Day20Puzzle() {

	}

	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		std::stack<DistanceCoord> stack;
		std::map<std::pair<int, int>, int> distanceMap;

		int distance = 0;
		int x = 0;
		int y = 0;

		int Part1Answer = 0;
		int Part2Answer = 0;

		const std::string regex(m_InputLines[0].substr(1, m_InputLines[0].size() - 2));
		for (char c : regex) {

			if (c == '(') {
				stack.push(DistanceCoord{ distance, x, y });
			}
			else if (c == ')') {
				const DistanceCoord top = stack.top();
				distance = top.d;
				x = top.x;
				y = top.y;
				stack.pop();
			}
			else if (c == '|') {
				const DistanceCoord top = stack.top();
				distance = top.d;
				x = top.x;
				y = top.y;
			}
			else {
				x += (c == 'E' ? 1 : 0) - (c == 'W' ? 1 : 0);
				y += (c == 'S' ? 1 : 0) - (c == 'N' ? 1 : 0);
				distance++;
				if (distanceMap.count({ x, y }) == 0 || distance < distanceMap[{x, y}]) {
					distanceMap[{x, y}] = std::min(distanceMap[{x, y}], distance);
					Part1Answer = std::max(Part1Answer, distance);
					if (distance >= 1000) {
						Part2Answer++;
					}
				}
			}
		}

		return { std::to_string(Part1Answer), std::to_string(Part2Answer) };
	}

}
