#include <2016/Day01Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <zeno/Core/VectorMath.hpp>
#include <Core/Orientation.hpp>
#include <unordered_set>

namespace std {
	template<>
	struct hash<ze::Vector2i> {
		size_t operator()(const ze::Vector2i& obj) const {
			return std::hash<int>()(obj.x) ^ std::hash<int>()(obj.y);
		}
	};
}
namespace TwentySixteen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("No Time for a Taxicab", 2016, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		const auto& res = getAnswers(m_InputLines[0]);
		return { std::to_string(res.first), std::to_string(res.second) };
	}

	std::pair<int, int> Day01Puzzle::getAnswers(const std::string& _input) {
		int part2 = -1;
		std::unordered_set<ze::Vector2i> visited;
		core::Orientation orientation{ core::Orientation::Up };
		ze::Vector2i position;
		visited.insert(position);
		for (const auto& s : ze::StringExtensions::splitStringByDelimeter(_input, ", ")) {
			orientation = core::OrientationHelper::turn(orientation, s[0] == 'R'
				? core::Orientation::Right
				: core::Orientation::Left);

			const int distance = stoi(s.substr(1));
			for (int i = 1; i <= distance; ++i) {
				position += core::OrientationHelper::toDirection(orientation);

				if (part2 == -1) {
					if (visited.count(position) == 0) {
						visited.insert(position);
					} else {
						part2 = std::abs(position.x) + std::abs(position.y);
					}
				}
			}
		}

		return { std::abs(position.x) + std::abs(position.y), part2 };
	}
}
