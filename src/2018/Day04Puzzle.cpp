#include <2018/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <regex>
#include <2018/Gaurd.hpp>
#include <map>

namespace TwentyEighteen {

	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Repose Record", 2018, 4) {

	}

	Day04Puzzle::~Day04Puzzle() {

	}

	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {

		std::vector<ParsedGaurdLine> guards;

		std::smatch m;
		const std::regex regex("\\[([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+)\\] (falls)?(wakes)?(Guard #([0-9]+))?");

		for (const std::string& _row : m_InputLines) {
			std::regex_search(_row, m, regex);

			const int year = std::atoi(m[1].str().c_str());
			const int month = std::atoi(m[2].str().c_str());
			const int day = std::atoi(m[3].str().c_str());

			const int hour = std::atoi(m[4].str().c_str());
			const int minute = std::atoi(m[5].str().c_str());

			const bool asleep = m[6].matched;

			const bool newGuardShift = m[8].matched;
			int guardId = -1;
			if (newGuardShift) {
				guardId = std::atoi(m[9].str().c_str());
			}

			guards.emplace_back(guardId, year, month, day, hour, minute, !asleep);
		}

		std::sort(guards.begin(), guards.end());


		std::map<GuardId, int> guardsAsleepMap;
		std::map<std::pair<GuardId, Minute>, int> guardMostAsleepMinuteMap;

		GuardId currentGuard = -1;
		std::size_t previousMinute = 0;
		for (const ParsedGaurdLine& _pgl : guards) {
			if (_pgl.id != -1) {
				currentGuard = _pgl.id;
				previousMinute = 0;
				continue;
			}

			if (_pgl.awake) {
				// Set the minutes we were awake for
				for (std::size_t min = previousMinute; min < static_cast<std::size_t>(_pgl.minute); min++) {
					guardsAsleepMap[currentGuard]++;
					guardMostAsleepMinuteMap[{currentGuard, min}]++;
				}
			} else {
				// Set that we woke up
				previousMinute = _pgl.minute;
			}
		}

		auto mostAlseepGuard = *std::max_element(guardsAsleepMap.begin(), guardsAsleepMap.end(), [](const std::pair<GuardId, int>& _lhs, const std::pair<GuardId, int>& _rhs) -> bool {
			return _lhs.second < _rhs.second;
		});


		GuardId mostConsistentAsleepMinuteGuard = 0;
		Minute mostConsistentAsleepMinute = 0;
		int mostConsistentAsleepCount = 0;

		Minute mostAsleepMinute = 0;
		int mostAsleepCount = 0;
		for (const auto& kvp : guardMostAsleepMinuteMap) {
			if (kvp.first.first == mostAlseepGuard.first) {
				if (kvp.second > mostAsleepCount) {
					mostAsleepCount = kvp.second;
					mostAsleepMinute = kvp.first.second;
				}
			}

			if (kvp.second > mostConsistentAsleepCount) {
				mostConsistentAsleepCount = kvp.second;
				mostConsistentAsleepMinuteGuard = kvp.first.first;
				mostConsistentAsleepMinute = kvp.first.second;
			}
		}

		return { std::to_string(mostAlseepGuard.first * mostAsleepMinute), std::to_string(mostConsistentAsleepMinuteGuard * mostConsistentAsleepMinute) };
	}

}
