#include <2016/Day15Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Timing is Everything", 2016, 15) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		auto positions = getNumberAndStartingPositions(m_InputLines);
		const auto part1 = getFirstTime(positions);
		positions.emplace_back(11, 0);
		const auto part2 = getFirstTime(positions);
		return { std::to_string(part1), std::to_string(part2) };
	}

	std::vector<std::pair<int, int>> Day15Puzzle::getNumberAndStartingPositions(const std::vector<std::string>& _input) {
		std::vector<std::pair<int, int>> positions;

		for (const auto& i : _input) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, " .");

			positions.emplace_back(std::stoi(s[3]), std::stoi(s.back()));
		}

		return positions;
	}

	bool Day15Puzzle::isValidFromStartTime(const std::vector<std::pair<int, int>>& _positions, int _startTime) {

		int time = _startTime;

		for (unsigned i = 0; i < _positions.size(); ++i) {
			const int numberPositions = _positions[i].first;
			const int startingPosition = _positions[i].second;

			time += 1;

			if ((startingPosition + time) % numberPositions != 0) {
				return false;
			}
		}


		return true;
	}

	int Day15Puzzle::getFirstTime(const std::vector<std::pair<int, int>>& _positions) {
		for (int i = 0;; ++i) {
			if (isValidFromStartTime(_positions, i)) {
				return i;
			}
		}

		return -1;
	}
}
