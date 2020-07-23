#include <2015/Day14Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>

namespace TwentyFifteen {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Reindeer Olympics", 2015, 14) {

	}
	Day14Puzzle::~Day14Puzzle() {

	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		const auto& info = parseInput(m_InputLines);

		const auto& part1 = getMaxDistanceAfterTime(info, 2503);
		const auto& part2 = getMaxPointsAfterTime(info, 2503);

		return { std::to_string(part1.first), std::to_string(part2.first) };
	}
	std::vector<ReindeerInfo> Day14Puzzle::parseInput(const std::vector<std::string>& _input) {
		std::vector<ReindeerInfo> parsed;

		for (const auto& i : _input) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, " ");
			ReindeerInfo& info = parsed.emplace_back();

			info.name = s[0];
			info.speed = stoi(s[3]);
			info.duration = stoi(s[6]);
			info.restDuration = stoi(s[13]);
		}

		return parsed;
	}
	int Day14Puzzle::getDistanceFromTime(const ReindeerInfo& _info, int _time) {
		const int completeCyles = _time / (_info.duration + _info.restDuration);
		const int incomplete = _time % (_info.duration + _info.restDuration);

		const int durationCompleted = std::min(incomplete, _info.duration);

		const int distance = (completeCyles * _info.duration + durationCompleted) * _info.speed;

		return distance;
	}

	std::pair<int, std::string> Day14Puzzle::getMaxDistanceAfterTime(const std::vector<ReindeerInfo>& _info, int _time) {
		std::string maxReindeer;
		int maxDistance = 0;
		for (const auto& info : _info) {
			int distance = getDistanceFromTime(info, _time);
			if (distance > maxDistance) {
				maxDistance = distance;
				maxReindeer = info.name;
			}
		}

		return std::make_pair(maxDistance, maxReindeer);
	}
	std::pair<int, std::string> Day14Puzzle::getMaxPointsAfterTime(const std::vector<ReindeerInfo>& _info, int _time) {
		std::unordered_map<std::string, int> points;

		for (int i = 1; i <= _time; ++i) {
			std::unordered_map<std::string, int> distance;
			for (const auto& info : _info) {
				distance[info.name] = getDistanceFromTime(info, i);
			}

			const auto maxDistance = std::max_element(distance.begin(), distance.end(), [](const auto& _lhs, const auto& _rhs) -> bool {return _lhs.second < _rhs.second;});

			for (const auto& [k, v] : distance) {
				if (maxDistance->second == v) {
					points[k]++;
				}
			}

		}

		auto winner = std::max_element(points.begin(), points.end(), [](const auto& _lhs, const auto& _rhs) -> bool {
			return _lhs.second < _rhs.second;
		});

		return std::make_pair((*winner).second, (*winner).first);
	}
}
