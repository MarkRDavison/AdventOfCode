#include <2020/Day05Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <bitset>
#include <set>

namespace TwentyTwenty {

	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Binary Boarding", 2020, 5) {
	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}


	Day05Puzzle::SeatInfo Day05Puzzle::getSeatInfo(const std::string& _input) {

		const auto rowInput = _input.substr(0, 7);
		const auto colInput = _input.substr(7, 3);

		const auto& getIndex = [](const std::string& _input) -> int {

			std::string val;

			for (const char c : _input) {
				if (c == 'R' || c == 'B') {
					val += '1';
				}
				else {
					val += '0';
				}
			}

			return std::bitset<10>(val).to_ulong();
		};

		SeatInfo info;
		info.row = getIndex(rowInput);
		info.column = getIndex(colInput);
		info.seatId = info.row * 8 + info.column;
		return info;
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		int part1 = 0;
		std::vector<SeatInfo> rowColumns;
		std::set<int> seatIds;
		for (const auto& str : m_InputLines) {
			const auto& info = getSeatInfo(str);
			rowColumns.push_back(info);
			seatIds.insert(info.seatId);
			if (info.seatId > part1) {
				part1 = info.seatId;
			}
		}
		std::vector<int> seats;
		std::copy(seatIds.begin(), seatIds.end(), std::back_inserter(seats));

		int part2 = 0;
		for (unsigned i = 1; i < seats.size(); ++i) {
			if (seats[i - 1] + 1 != seats[i] &&
				seats[i-1] + 2 == seats[i]) {
				part2 = seats[i] - 1;
				break;
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
