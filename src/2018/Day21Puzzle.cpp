#include <2018/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2018/RegisterInstruction.hpp>
#include <2018/RegisterMachine.hpp>
#include <unordered_set>

namespace TwentyEighteen {

	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Chronal Conversion", 2018, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}

	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		const RegisterValue instructionPointerRegister = std::atoi(core::StringExtensions::splitStringByDelimeter(m_InputLines[0], " ")[1].c_str());

		std::vector<RegisterInstruction> instructions;
		for (std::size_t i = 1; i < m_InputLines.size(); ++i) {
			const std::vector<std::string> instructionComponents = core::StringExtensions::splitStringByDelimeter(m_InputLines[i], " ");

			const OpCode code = StringToOpCode(instructionComponents[0]);
			const RegisterValue a = std::atoi(instructionComponents[1].c_str());
			const RegisterValue b = std::atoi(instructionComponents[2].c_str());
			const RegisterValue c = std::atoi(instructionComponents[3].c_str());

			instructions.emplace_back(code, a, b, c);
		}

		std::unordered_set<RegisterValue> numbers;
		RegisterValue part1Answer = 0;
		RegisterValue part2Answer = 0;
		{
			RegisterMachine machine(6, instructions, instructionPointerRegister, true);
			std::vector<RegisterValue>& registers = machine.getRegisters();

			RegisterValue& instructionCounter = machine.getProgramCounter();
			while (instructionCounter >= 0 && instructionCounter < instructions.size()) {
				RegisterMachine::applyInstruction(instructions[instructionCounter], registers);

				if (instructionCounter == 28) {
					if (numbers.empty()) {
						part1Answer = registers[2];
						std::cout << "Part 1: " << registers[2] << std::endl;
					}

					if (numbers.find(registers[2]) == numbers.end()) {
                        if (registers[2] == 14626276) {
                            std::cout << "ANSWER!" << std::endl;
                        }
                        std::cout << "Added number 2: " << registers[2] << std::endl;
						numbers.emplace(registers[2]);
					}
					else {
						part2Answer = registers[2];
                        std::cout << "Part 2: " << registers[2] << std::endl;
						break;
					}
				}
				instructionCounter++;
			}
		}

		return { std::to_string(part1Answer), std::to_string(part2Answer) };
	}

}
