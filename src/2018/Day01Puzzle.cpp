#include <2018/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <set>

namespace TwentyEighteen {

	using Frequency = int;
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Chronal Calibration", 2018, 1) {

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
		Frequency freq{};
		Frequency firstDuplicateFrequency{ std::numeric_limits<Frequency>::max() };
		std::set<Frequency> seenFrequencies;

		Frequency part1Freq{ std::numeric_limits<Frequency>::max() };

		bool complete{ false };

		for (std::size_t i = 0; ; ++i) {
			for (const std::string& _inputRow : m_InputLines) {
				const char op = _inputRow[0];
				const Frequency value = std::atoi(_inputRow.substr(1).c_str());

				if (op == '+') {
					freq += value;
				}
				else {
					freq -= value;
				}

				if (seenFrequencies.count(freq) == 0) {
					seenFrequencies.emplace(freq);
				}
				else {
					firstDuplicateFrequency = freq;
					if (part1Freq != std::numeric_limits<Frequency>::max()) {
						complete = true;
						break;
					}

				}
			}

			if (i == 0) {
				part1Freq = freq;
				if (firstDuplicateFrequency != std::numeric_limits<Frequency>::max()) {
					complete = true;
					break;
				}
			}

			if (complete) {
				break;
			}
		}

		return { std::to_string(part1Freq), std::to_string(firstDuplicateFrequency) };
	}
}
