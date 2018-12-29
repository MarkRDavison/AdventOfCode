#include <2018/Day18Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <set>
#include <map>

namespace TwentyEighteen {

	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Settlers of The North Pole", 2018, 18) {

	}
	Day18Puzzle::~Day18Puzzle() {

	}

	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {
		{
			for (std::size_t y = 0; y < m_InputLines.size(); ++y) {
				m_DoubleBufferedForest.emplace_back(m_InputLines[y].size());
				for (std::size_t x = 0; x < m_InputLines.front().size(); ++x) {
					m_DoubleBufferedForest[y][x] = { m_InputLines[y][x], m_InputLines[y][x] };
				}
			}

			if (getVerbose()) {
				printForest();
			}
		}

		const std::size_t targetPart2Minutes = 1000000000;

		std::set<NeighbourCount> seenCounts;
		std::vector<std::pair<NeighbourCount, int>> consecutiveCounts;

		NeighbourCount part1Count{};
		for (std::size_t i = 0; i < targetPart2Minutes; ++i) {
			performIteration();
			if (getVerbose()) {
				printForest();
			}

			if (m_Minutes == 10) {
				part1Count = calculateForestCount();
			}

			const NeighbourCount current = calculateForestCount();
			if (seenCounts.count(current) == 0) {
				seenCounts.emplace(current);
				if (!consecutiveCounts.empty()) {
					consecutiveCounts.clear();
				}
			} else {
				if (!consecutiveCounts.empty()) {
					const auto first = consecutiveCounts.front();
					if (first.first == current) {
						const auto offset = m_Minutes - first.second;

						const auto result = (targetPart2Minutes - first.second) % offset;

						const auto actualResult = consecutiveCounts[result];

						return { std::to_string(part1Count.Trees * part1Count.Lumberyards), std::to_string(actualResult.first.Trees * actualResult.first.Lumberyards)};
					}
				}
				consecutiveCounts.push_back(std::make_pair(current, m_Minutes));
			}
		}

		return { std::to_string(part1Count.Trees * part1Count.Lumberyards), "???" };
	}

	void Day18Puzzle::printForest() const {
		if (m_Minutes == 0) {
			std::cout << "Initially:" << std::endl;
		}
		else {
			std::cout << "After " << m_Minutes << " minutes:" << std::endl;
		}
		for (std::size_t y = 0; y < m_InputLines.size(); ++y) {
			for (std::size_t x = 0; x < m_InputLines.front().size(); ++x) {
				std::cout << (m_Type == BufferType::Front ? m_DoubleBufferedForest[y][x].first : m_DoubleBufferedForest[y][x].second);
			}
			std::cout << std::endl;
		}
	}

	void Day18Puzzle::performIteration() {
		m_CurrentCount = {};
		for (std::size_t y = 0; y < m_InputLines.size(); ++y) {
			for (std::size_t x = 0; x < m_InputLines.front().size(); ++x) {
				const NeighbourCount count = calculateNeighbourCount(x, y);
				auto& pair = m_DoubleBufferedForest[y][x];
				char& acre = m_Type == BufferType::Front ? pair.first : pair.second;
				if (acre == '.') {
					if (count.Trees >= 3) {
						acre = '|';
					}
				}
				else if (acre == '|') {
					if (count.Lumberyards >= 3) {
						acre = '#';
					}
				}
				else if (acre == '#') {
					if (count.Lumberyards == 0 || count.Trees == 0) {
						acre = '.';
					}
				}

				if (acre == '.') {
					m_CurrentCount.Open++;
				} else if (acre == '|') {
					m_CurrentCount.Trees++;
				} else if (acre == '#') {
					m_CurrentCount.Lumberyards++;
				}
			}
		}

		for (std::size_t y = 0; y < m_InputLines.size(); ++y) {
			for (std::size_t x = 0; x < m_InputLines.front().size(); ++x) {
				auto& pair = m_DoubleBufferedForest[y][x];
				if (m_Type == BufferType::Back) {
					pair.first = pair.second;
				} else {
					pair.second = pair.first;
				}
			}
		}

		m_Type = m_Type == BufferType::Back ? BufferType::Front : BufferType::Back;
		m_Minutes++;
	}

	inline
	NeighbourCount Day18Puzzle::calculateNeighbourCount(std::size_t _x, std::size_t _y) const {
		NeighbourCount count{};

		const BufferType compareType = m_Type == BufferType::Back 
			? BufferType::Front 
			: BufferType::Back;

		// Top Left
		if (_x > 0 && _y > 0) {
			const auto& pair = m_DoubleBufferedForest[_y - 1][_x - 1];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}

		// Top Middle
		if (_y > 0) {
			const auto& pair = m_DoubleBufferedForest[_y - 1][_x];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}
		// Top Right
		if (_y > 0 && _x < m_DoubleBufferedForest.front().size() - 1) {
			const auto& pair = m_DoubleBufferedForest[_y - 1][_x + 1];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}

		// Middle Left
		if (_x > 0) {
			const auto& pair = m_DoubleBufferedForest[_y][_x - 1];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}
		// Middle Right
		if (_x < m_DoubleBufferedForest.front().size() - 1) {
			const auto& pair = m_DoubleBufferedForest[_y][_x + 1];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}

		// Bottom Left
		if (_x > 0 && _y < m_DoubleBufferedForest.size() - 1) {
			const auto& pair = m_DoubleBufferedForest[_y + 1][_x - 1];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}
		// Bottom Middle
		if (_y < m_DoubleBufferedForest.size() - 1) {
			const auto& pair = m_DoubleBufferedForest[_y + 1][_x];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}
		// Bottom Right
		if (_x < m_DoubleBufferedForest.front().size() - 1 && _y < m_DoubleBufferedForest.size() - 1) {
			const auto& pair = m_DoubleBufferedForest[_y + 1][_x + 1];
			const char acre = compareType == BufferType::Front ? pair.first : pair.second;
			if (acre == '.') {
				count.Open++;
			}
			else if (acre == '#') {
				count.Lumberyards++;
			}
			else if (acre == '|') {
				count.Trees++;
			}
		}

		return count;
	}

	NeighbourCount Day18Puzzle::calculateForestCount() const {
		return m_CurrentCount;
	}

}
