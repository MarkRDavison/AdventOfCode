#include <2019/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

#define OPCODE_1 1
#define OPCODE_2 2
#define OPCODE_99 99

namespace TwentyNineteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("1202 Program Alarm", 2019, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {


		std::vector<long> valuesStart;
		for (const auto& strValue : core::StringExtensions::splitStringByDelimeter(m_InputLines[0], ",")) {
			valuesStart.emplace_back(std::atoi(strValue.c_str()));
			
		}

		const long target = 19690720;
		const long guessMax = 100;
		const long guessMin = 0;
		std::string part2;

		for (long n = guessMin; n < guessMax; ++n) {
			for (long v = guessMin; v < guessMax; ++v) {
				std::vector<long> values(valuesStart);

				const long noun = n;
				const long verb = v;

				values[1] = noun;
				values[2] = verb;
				unsigned int index = 0;
				unsigned counter = 0;
				while (true) {
					index++;
					const auto& opcode = values[counter];

					if (opcode == 99) {
						break;
					}

					const auto& val1 = values[values[counter + 1]];
					const auto& val2 = values[values[counter + 2]];
					auto& result = values[values[counter + 3]];

					if (opcode == OPCODE_1) {
						result = val1 + val2;
					} else if (opcode == OPCODE_2) {
						result = val1 * val2;
					}

					counter += 4;
				}

				if (values[0] == target) {
					part2 = std::to_string(n) + " x 100 + " + std::to_string(v) + " = " + std::to_string(n * 100 + v);
				}

			}
		}

		{
			std::vector<long> values(valuesStart);

			const long noun = 12;
			const long verb = 2;

			values[1] = noun;
			values[2] = verb;
			unsigned int index = 0;
			unsigned counter = 0;
			while (true) {
				index++;
				const auto& opcode = values[counter];

				if (opcode == 99) {
					return { std::to_string(values[0]), part2 };
				}

				const auto& val1 = values[values[counter + 1]];
				const auto& val2 = values[values[counter + 2]];
				auto& result = values[values[counter + 3]];

				if (opcode == OPCODE_1) {
					result = val1 + val2;
				} else if (opcode == OPCODE_2) {
					result = val1 * val2;
				}

				counter += 4;
			}
		}


	}
}
