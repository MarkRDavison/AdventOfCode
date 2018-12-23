#include <2018/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <regex>
#include <2018/Gaurd.hpp>

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

		std::vector<ParsedGaurdLine> gaurds;

		std::smatch m;
		const std::regex regex("\\[([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+)\\] (falls)?(wakes)?(Guard #([0-9]+))?");

		for (const std::string& _row : m_InputLines) {
			std::regex_match(_row, m, regex);

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

			gaurds.emplace_back(guardId, year, month, day, hour, minute, !asleep);
		}

		std::sort(gaurds.begin(), gaurds.end());

		for (const ParsedGaurdLine& _guard : gaurds) {
			
		}

		return { "???", "???" };
	}

}
