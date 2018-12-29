#include <2018/Day16Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2018/RegisterMachine.hpp>
#include <map>

namespace TwentyEighteen {

	Day16Puzzle::Day16Puzzle(bool _solvePart2 /*= true*/) :
		core::PuzzleBase("Chronal Classification", 2018, 16),
		m_SolvePart2(_solvePart2) {

	}
	Day16Puzzle::~Day16Puzzle() {

	}

	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		std::vector<RegisterTrainingInstruction> trainingInstructions;

		std::size_t i = 0;
		for (i = 0; i < m_InputLines.size(); i += 3) {
			const std::string beforeLine = m_InputLines[i + 0];
			const std::string instructionLine = m_InputLines[i + 1];
			const std::string afterLine = m_InputLines[i + 2];

			if (beforeLine.find("Before") == std::string::npos) {
				break;
			}

			std::vector<std::string> befores = core::StringExtensions::splitStringByDelimeter(beforeLine, "[,]");
			std::vector<std::string> instruction = core::StringExtensions::splitStringByDelimeter(instructionLine, " ");
			std::vector<std::string> afters = core::StringExtensions::splitStringByDelimeter(afterLine, "[,]");

			const RegisterValue before0 = std::atoi(befores[1].c_str());
			const RegisterValue before1 = std::atoi(befores[2].c_str());
			const RegisterValue before2 = std::atoi(befores[3].c_str());
			const RegisterValue before3 = std::atoi(befores[4].c_str());

			const int mysteryCode = std::atoi(instruction[0].c_str());
			const RegisterValue mysteryA = std::atoi(instruction[1].c_str());
			const RegisterValue mysteryB = std::atoi(instruction[2].c_str());
			const RegisterValue mysteryC = std::atoi(instruction[3].c_str());

			const RegisterValue after0 = std::atoi(afters[1].c_str());
			const RegisterValue after1 = std::atoi(afters[2].c_str());
			const RegisterValue after2 = std::atoi(afters[3].c_str());
			const RegisterValue after3 = std::atoi(afters[4].c_str());

			trainingInstructions.emplace_back(MysteryRegisterInstruction{ mysteryCode, mysteryA, mysteryB, mysteryC }, before0, before1, before2, before3, after0, after1, after2, after3);
		}

		int threes = 0;
		for (RegisterTrainingInstruction& _trainingInstruction : trainingInstructions) {
			runTrainingOnInstruction(_trainingInstruction);
			if (_trainingInstruction.validOpCodes.size() >= 3) {
				threes++;
			}
		}
		if (!m_SolvePart2) {
			return { std::to_string(threes), "???" };
		}

		std::set<OpCode> verifiedOpCodes;
		std::map<int, OpCode> opCodeIdMap;

		bool opCodeFound = true;
		while (opCodeFound) {
			opCodeFound = false;
			for (RegisterTrainingInstruction& _trainingInstruction : trainingInstructions) {
				if (_trainingInstruction.validOpCodes.size() == 1) {
					// We know that this is valid.  So now update the rest
					const OpCode code = *_trainingInstruction.validOpCodes.begin();
					_trainingInstruction.opCode = code;
					verifiedOpCodes.emplace(code);
					opCodeFound = true;
					opCodeIdMap[_trainingInstruction.instruction.opCodeId] = code;

					if (getVerbose()) {
						std::cout << "OpCode " << OpCodeToString(code) << " is for id " << _trainingInstruction.instruction.opCodeId << std::endl;
					}

					for (RegisterTrainingInstruction& _removingVerifiedOpCodeTrainingInstruction : trainingInstructions) {
						_removingVerifiedOpCodeTrainingInstruction.validOpCodes.erase(code);
					}
					break;
				}
			}
		}

		std::vector<RegisterInstruction> instructions;

		for (;i < m_InputLines.size(); ++i) {
			const std::string inputLine = m_InputLines[i];
			if (inputLine.empty()) {
				continue;
			}

			std::vector<std::string> values = core::StringExtensions::splitStringByDelimeter(inputLine, " ");

			const int instructionId = std::atoi(values[0].c_str());
			const RegisterValue instructionA = std::atoi(values[1].c_str());
			const RegisterValue instructionB = std::atoi(values[2].c_str());
			const RegisterValue instructionC = std::atoi(values[3].c_str());

			instructions.emplace_back(opCodeIdMap[instructionId], instructionA, instructionB, instructionC);
		}

		RegisterValue programCounter = 0;
		RegisterMachine machine(4, instructions, programCounter);
		machine.runProgramToCompletion();

		return { std::to_string(threes), std::to_string(machine.getRegisters().at(0)) };
	}

	void Day16Puzzle::runTrainingOnInstruction(RegisterTrainingInstruction& _trainingInstruction) const {
		for (int i = 0; i < static_cast<int>(OpCode::NumberOfOpCodes); ++i) {
			const OpCode code = static_cast<OpCode>(i);

			std::vector<RegisterValue> registers(4, 0);
			for (std::size_t j = 0; j < 4; ++j) {
				registers[j] = _trainingInstruction.before[j];
			}

			RegisterMachine::applyInstruction(code, registers, _trainingInstruction.instruction.A, _trainingInstruction.instruction.B, _trainingInstruction.instruction.C);

			bool valid = true;
			for (std::size_t j = 0; j < 4; ++j) {
				if (registers[j] != _trainingInstruction.after[j]) {
					valid = false;
				}
			}

			if (valid) {
				_trainingInstruction.validOpCodes.emplace(code);
			}
		}
	}

}
