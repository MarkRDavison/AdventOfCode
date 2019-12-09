#include <2015/Day10Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Elves Look, Elves Say", 2015, 10) {

	}
	Day10Puzzle::~Day10Puzzle() {

	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		const unsigned part1IterationCount = 40;
		const unsigned part2IterationCount = 50;

		std::string part1 = m_InputLines[0];
		for (unsigned i = 0; i < part1IterationCount; ++i) {
			part1 = calculateLookAndSay(part1);
			if (getVerbose()) {
				std::cout << "Part1 (" << i << "/" << part1IterationCount << ") - " << part1.size() << std::endl;
			}
		}

		std::string part2 = m_InputLines[0];
		for (unsigned i = 0; i < part2IterationCount; ++i) {
			part2 = calculateLookAndSay(part2);
			if (getVerbose()) {
				std::cout << "Part2 (" << i << "/" << part2IterationCount << ") - " << part2.size() << std::endl;
			}
		}

		return { std::to_string(part1.size()) , std::to_string(part2.size()) };
	}

	std::string Day10Puzzle::calculateLookAndSay(const std::string& _input) {
		std::string result;

		unsigned i = 0;
		while (i < _input.size()) {
			char c = _input[i];
			unsigned count = 1;

			while (i < _input.size() && _input[i + 1] == c) {
				i++;
				count++;
			}

			result += std::to_string(count) + c;
			i++;
		}


		return result;
	}
}
