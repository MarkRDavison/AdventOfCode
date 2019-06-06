#include <2016/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Orientation.hpp>

#include <unordered_set>

namespace TwentySixteen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("No Time for a Taxicab", 2016, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		std::string data = (m_InputLines[0]);

		core::Orientation orientation{ core::Orientation::Up };
		core::Vector2i coordinates{};
		std::unordered_set<core::Vector2i, core::vector2_hash_fxn> visitedCoords;

		std::string part2;

		for (const auto& dir : core::StringExtensions::splitStringByDelimeter(data, ", ")) {
			auto offset = std::atoi(dir.substr(1).c_str());
			
			orientation = core::OrientationHelper::turn(orientation, dir[0] == Left ? core::Orientation::Left : core::Orientation::Right);

			auto direction = core::OrientationHelper::toDirection(orientation);

			for (int i = 0; i < offset; ++i) {
				coordinates.x += 1 * direction.x;
				coordinates.y += 1 * direction.y;

				if (part2.empty() && visitedCoords.count(coordinates) > 0) {
					part2 = std::to_string(std::abs(coordinates.x) + std::abs(coordinates.y));
				} else {
					visitedCoords.insert(coordinates);
				}
			}
		}

		auto part1 = std::abs(coordinates.x) + std::abs(coordinates.y);

		return { std::to_string(part1), part2 };
	}
}
