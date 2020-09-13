#include <2016/Day12Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <cassert>

namespace TwentySixteen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Leonardo's Monorail", 2016, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {

		AssembunnyInteger part1;
		AssembunnyInteger part2;

		{
			Registers registers = { 0 };
			AssembunnyInteger programCounter = 0;

			AssembunnyInteger prev = registers[3];
			while (programCounter >= 0 && programCounter < (AssembunnyInteger)m_InputLines.size()) {
				Day12Puzzle::applyInstruction(programCounter, registers, m_InputLines[programCounter]);

				if (prev != registers[3]) {
					prev = registers[3];
					std::cout << "PC: " << programCounter
						<< " - [" << registers[0]
						<< ", " << registers[1]
						<< ", " << registers[2]
						<< ", " << registers[3]
						<< "]" << std::endl;
				}
			}

			part1 = registers[0];
		}
		{
			Registers registers = { 0 };
			registers[2] = 1;
			AssembunnyInteger programCounter = 0;

			AssembunnyInteger prev = registers[3];

			while (programCounter >= 0 && programCounter < (AssembunnyInteger)m_InputLines.size()) {
				Day12Puzzle::applyInstruction(programCounter, registers, m_InputLines[programCounter]);

				if (prev != registers[3]) {
					prev = registers[3];
					std::cout << "PC: " << programCounter
						<< " - [" << registers[0]
						<< ", " << registers[1]
						<< ", " << registers[2]
						<< ", " << registers[3]
						<< "]" << std::endl;
				}
			}

			part2 = registers[0];
		}


		return { std::to_string(part1), std::to_string(part2) };
	}

	static bool isRegister(const std::string& _str) {
		return 'a' <= _str[0] && _str[0] <= 'd';
	}
	static AssembunnyInteger& getRegisterValue(Registers& _registers, const std::string& _register) {
		const auto reg = (unsigned)(_register[0] - 'a');
		return _registers[reg];
	}

	void Day12Puzzle::applyInstruction(AssembunnyInteger& _programCounter, Registers& _registers, const std::string& _instruction) {

		const auto& splits = ze::StringExtensions::splitStringByDelimeter(_instruction, " ");

		if (splits[0] == "cpy") {
			AssembunnyInteger value;
			if (isRegister(splits[1])) {
				value = getRegisterValue(_registers, splits[1]);
			}
			else {
				value = std::stoi(splits[1]);
			}
			auto& regValue = getRegisterValue(_registers, splits[2]);
			regValue = value;
		} else if (splits[0] == "inc") {
			auto& regValue = getRegisterValue(_registers, splits[1]);
			regValue++;
		} else if (splits[0] == "dec") {
			auto& regValue = getRegisterValue(_registers, splits[1]);
			regValue--;
		} else if (splits[0] == "jnz") {
			AssembunnyInteger value;
			if (isRegister(splits[1])) {
				value = getRegisterValue(_registers, splits[1]);
			} else {
				value = std::stoi(splits[1]);
			}
			if (value != 0) {
				_programCounter += std::stoi(splits[2]);
				return;
			}
		}

		_programCounter++;
	}
}
