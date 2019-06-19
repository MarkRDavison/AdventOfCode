#include <2016/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/MD5.hpp>

namespace TwentySixteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("How About a Nice Game of Chess?", 2016, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		const std::string doorId = m_InputLines[0];

		std::string part1 = "________";
		std::string part2 = "________";

		int part1Count = 0;
		int part2Count = 0;

		bool part1Complete = false;
		bool part2Complete = false;

		unsigned i = 1500000;
		while (!part1Complete || !part2Complete) {
			const std::string input = doorId + std::to_string(i);
			const std::string& hash = core::md5(input);

			if (hash[0] == '0' &&
				hash[1] == '0' &&
				hash[2] == '0' &&
				hash[3] == '0' &&
				hash[4] == '0') {

				if (part1Count < 8) {
					part1[part1Count] = hash[5];
					part1Count++;
					if (part1Count == 8) {
						part1Complete = true;
					}
				}

				auto location = static_cast<int>(hash[5] - '0');
				if (location >= 0 && location < 8) {
					if (getVerbose()) {
						std::cout << "Interesting hash '" << hash << "' from input '" << input << " for location: " << location << ", value: " << hash[6] << std::endl;
					}
					if (part2[location] == '_') {
						part2Count++;
						part2[location] = hash[6];
						if (part2Count == 8) {
							part2Complete = true;
						}
					}
				}
			}

			if (getVerbose()) {
				if (i % 10000 == 0) {
					std::cout << "Part 1: " << part1 << ", Part 2: " << part2 << ", iterations: " << i << "\r";
				}
			}

			i++;
		}
		if (getVerbose()) {
			std::cout << std::endl;
		}

		return { part1, part2 };
	}
}
