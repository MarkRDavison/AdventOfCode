#include <2019/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>

#define OPCODE_ADD 1
#define OPCODE_MUL 2
#define OPCODE_3 3
#define OPCODE_4 4
#define OPCODE_5 5
#define OPCODE_6 6
#define OPCODE_7 7
#define OPCODE_8 8
#define OPCODE_STOP 99

#define POSITION_MODE 0
#define IMMEDIATE_MODE 1

namespace TwentyNineteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Sunny with a Chance of Asteroids", 2019, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long getDiagnosticCode(const std::string& _program, long _input) {
		std::vector<long> valuesStart;
		for (const auto& strValue : core::StringExtensions::splitStringByDelimeter(_program, ",")) {
			valuesStart.emplace_back(std::atoi(strValue.c_str()));
		}

		long output = -1;

		unsigned counter = 0;
		while (true) {
			const int opCode = valuesStart[counter];

			int digit_6 = opCode % 100;
			int digit_4 = (opCode / 100) % 10;
			int digit_3 = (opCode / 1000) % 10;
			int digit_2 = (opCode / 10000) % 10;

			const int DE = digit_6;
			const int C = digit_4;
			const int B = digit_3;
			const int A = digit_2;


			if (DE == OPCODE_MUL) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];

				auto& parameter_B = B == POSITION_MODE
					? valuesStart[valuesStart[counter + 2]]
					: valuesStart[counter + 2];

				auto& parameter_A = A == POSITION_MODE
					? valuesStart[valuesStart[counter + 3]]
					: valuesStart[counter + 3];

				parameter_A = parameter_B * parameter_C;
				counter += 4;
			} else if (DE == OPCODE_ADD) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];

				auto& parameter_B = B == POSITION_MODE
					? valuesStart[valuesStart[counter + 2]]
					: valuesStart[counter + 2];

				auto& parameter_A = A == POSITION_MODE
					? valuesStart[valuesStart[counter + 3]]
					: valuesStart[counter + 3];

				parameter_A = parameter_B + parameter_C;
				counter += 4;
			} else if (DE == OPCODE_3) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];

				parameter_C = _input;
				counter += 2;

			} else if (DE == OPCODE_4) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];

				output = parameter_C;
				counter += 2;
			} else if (DE == OPCODE_5) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];
				if (parameter_C == 0) {
					counter += 3;
					continue;
				}

				auto& parameter_B = B == POSITION_MODE
					? valuesStart[valuesStart[counter + 2]]
					: valuesStart[counter + 2];
				counter = parameter_B;
			} else if (DE == OPCODE_6) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];
				if (parameter_C != 0) {
					counter += 3;
					continue;
				}

				auto& parameter_B = B == POSITION_MODE
					? valuesStart[valuesStart[counter + 2]]
					: valuesStart[counter + 2];
				counter = parameter_B;
			} else if (DE == OPCODE_7) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];

				auto& parameter_B = B == POSITION_MODE
					? valuesStart[valuesStart[counter + 2]]
					: valuesStart[counter + 2];

				auto& parameter_A = A == POSITION_MODE
					? valuesStart[valuesStart[counter + 3]]
					: valuesStart[counter + 3];

				if (parameter_C < parameter_B) {
					parameter_A = 1;
				} else {
					parameter_A = 0;
				}
				counter += 4;
			} else if (DE == OPCODE_8) {
				auto& parameter_C = C == POSITION_MODE
					? valuesStart[valuesStart[counter + 1]]
					: valuesStart[counter + 1];

				auto& parameter_B = B == POSITION_MODE
					? valuesStart[valuesStart[counter + 2]]
					: valuesStart[counter + 2];

				auto& parameter_A = A == POSITION_MODE
					? valuesStart[valuesStart[counter + 3]]
					: valuesStart[counter + 3];

				if (parameter_C == parameter_B) {
					parameter_A = 1;
				} else {
					parameter_A = 0;
				}
				counter += 4;
			} else if (DE == OPCODE_STOP) {
				break;
			}
		}

		return output;
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		return { std::to_string(getDiagnosticCode(m_InputLines[0], 1)), std::to_string(getDiagnosticCode(m_InputLines[0], 5)) };
	}
}
