#include <2020/Day12Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <zeno/Core.hpp>
#include <algorithm>
#include <unordered_map>

namespace TwentyTwenty {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Rain Risk", 2020, 12) {
	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		const auto& parsed = Day12Puzzle::parse(m_InputLines);

		const auto part1 = Day12Puzzle::doPart1(parsed);
		const auto part2 = Day12Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	std::vector<Day12Struct> Day12Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<Day12Struct> parsed;
		std::transform(_inputLines.begin(), _inputLines.end(), std::back_inserter(parsed), translate);
		return parsed;
	}
	Day12Struct Day12Puzzle::translate(const std::string& _line) {
		Day12Struct current{};

		switch (_line[0]) {
		case 'N':
			current.direction = Day12Struct::Direction::NORTH;
			break;
		case 'S':
			current.direction = Day12Struct::Direction::SOUTH;
			break;
		case 'E':
			current.direction = Day12Struct::Direction::EAST;
			break;
		case 'W':
			current.direction = Day12Struct::Direction::WEST;
			break;
		case 'R':
			current.direction = Day12Struct::Direction::RIGHT;
			break;
		case 'L':
			current.direction = Day12Struct::Direction::LEFT;
			break;
		case 'F':
			current.direction = Day12Struct::Direction::FORWARD;
			break;
		}

		current.value = std::stol(_line.substr(1));

		return current;
	}
	std::string Day12Puzzle::doPart1(const std::vector<Day12Struct>& _parsed) {

		Day12Struct::Direction dir{ Day12Struct::Direction::EAST };

		std::unordered_map<Day12Struct::Direction, ze::Vector2<long>> directionsToVector;
		directionsToVector[Day12Struct::Direction::EAST] = { +1, 0 };
		directionsToVector[Day12Struct::Direction::WEST] = { -1, 0 };
		directionsToVector[Day12Struct::Direction::SOUTH] = {0, -1 };
		directionsToVector[Day12Struct::Direction::NORTH] = { 0,+1 };

		ze::Vector2<long> coords;

		for (const auto& s : _parsed) {
			switch (s.direction) {
			case Day12Struct::Direction::FORWARD:
				coords += directionsToVector[dir] * s.value;
				break;
			case Day12Struct::Direction::EAST:
			case Day12Struct::Direction::WEST:
			case Day12Struct::Direction::SOUTH:
			case Day12Struct::Direction::NORTH:
				coords += directionsToVector[s.direction] * s.value;
				break;
			case Day12Struct::Direction::LEFT:
			{
				for (unsigned i = 0; i < s.value / 90; ++i) {
					if (dir == Day12Struct::Direction::EAST) {
						dir = Day12Struct::Direction::NORTH;
					}
					else if (dir == Day12Struct::Direction::NORTH) {
						dir = Day12Struct::Direction::WEST;
					}
					else if (dir == Day12Struct::Direction::WEST) {
						dir = Day12Struct::Direction::SOUTH;
					}
					else if (dir == Day12Struct::Direction::SOUTH) {
						dir = Day12Struct::Direction::EAST;
					}
				}
			}
			break;
			case Day12Struct::Direction::RIGHT:
			{
				for (long i = 0; i < s.value / 90; ++i) {
					if (dir == Day12Struct::Direction::WEST) {
						dir = Day12Struct::Direction::NORTH;
					}
					else if (dir == Day12Struct::Direction::NORTH) {
						dir = Day12Struct::Direction::EAST;
					}
					else if (dir == Day12Struct::Direction::EAST) {
						dir = Day12Struct::Direction::SOUTH;
					}
					else if (dir == Day12Struct::Direction::SOUTH) {
						dir = Day12Struct::Direction::WEST;
					}
				}
			}
			break; 
			}
		}

		return std::to_string(std::abs(coords.x) + std::abs(coords.y));
	}
	std::string Day12Puzzle::doPart2(const std::vector<Day12Struct>& _parsed) {

		std::unordered_map<Day12Struct::Direction, ze::Vector2<long>> directionsToVector;
		directionsToVector[Day12Struct::Direction::EAST] = { +1, 0 };
		directionsToVector[Day12Struct::Direction::WEST] = { -1, 0 };
		directionsToVector[Day12Struct::Direction::SOUTH] = { 0, -1 };
		directionsToVector[Day12Struct::Direction::NORTH] = { 0,+1 };

		ze::Vector2<long> coords;
		ze::Vector2<long> waypoint{ 10,1 };

		for (const auto& s : _parsed) {
			switch (s.direction) {
			case Day12Struct::Direction::FORWARD:
				coords += waypoint * s.value;
				break;
			case Day12Struct::Direction::EAST:
			case Day12Struct::Direction::WEST:
			case Day12Struct::Direction::SOUTH:
			case Day12Struct::Direction::NORTH:
				waypoint += directionsToVector[s.direction] * s.value;
				break;
			case Day12Struct::Direction::LEFT:
			case Day12Struct::Direction::RIGHT:
			{
				auto angle = static_cast<float>(s.value) * 3.14159265f / 180.0f;
				if (s.direction == Day12Struct::Direction::LEFT) {
					angle *= -1.0f;
				}
				auto rotated = ze::Mat4x4::createRotationZ(
					angle
				) * ze::Vector2f(waypoint);
				waypoint = ze::Vector2<long>(std::round(rotated.x), std::round(rotated.y));

			}
			break;
			}
		}

		return std::to_string(std::abs(coords.x) + std::abs(coords.y));
	}
}
