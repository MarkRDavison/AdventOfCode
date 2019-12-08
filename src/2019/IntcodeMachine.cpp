#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

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

	void IntcodeMachine::loadProgram(const std::string& _program) {
		m_Program.clear();
		for (const auto& strValue : core::StringExtensions::splitStringByDelimeter(_program, ",")) {
			m_Program.emplace_back(std::atoi(strValue.c_str()));
		}
		resetProgram();
	}
	void IntcodeMachine::resetProgram() {
		m_Memory = std::vector<long>(m_Program);
		m_ProgramCounter = 0;
	}

	void IntcodeMachine::execute() {		

		if (m_HasHaltedFromOpCode) { return; }
		while (true) {
			const int opCode = m_Memory[m_ProgramCounter];

			const int DE = opCode % 100;
			const int C = (opCode / 100) % 10;
			const int B = (opCode / 1000) % 10;
			const int A = (opCode / 10000) % 10;

			if (DE == OPCODE_MUL) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];

				auto& parameter_B = B == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 2]]
					: m_Memory[m_ProgramCounter + 2];

				auto& parameter_A = A == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 3]]
					: m_Memory[m_ProgramCounter + 3];

				parameter_A = parameter_B * parameter_C;
				m_ProgramCounter += 4;
			} else if (DE == OPCODE_ADD) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];

				auto& parameter_B = B == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 2]]
					: m_Memory[m_ProgramCounter + 2];

				auto& parameter_A = A == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 3]]
					: m_Memory[m_ProgramCounter + 3];

				parameter_A = parameter_B + parameter_C;
				m_ProgramCounter += 4;
			} else if (DE == OPCODE_3) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];

				if (m_Input.empty() && m_HaltWhenInputEmpty) {
					break;
				}
				parameter_C = m_Input.front();
				m_Input.pop();
				m_ProgramCounter += 2;

			} else if (DE == OPCODE_4) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];

				m_Output = parameter_C;
				m_ProgramCounter += 2;
				if (m_HaltWhenOutputSet) {
					m_OutputRetrieved = false;
					break;
				}
			} else if (DE == OPCODE_5) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];
				if (parameter_C == 0) {
					m_ProgramCounter += 3;
					continue;
				}

				auto& parameter_B = B == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 2]]
					: m_Memory[m_ProgramCounter + 2];
				m_ProgramCounter = parameter_B;
			} else if (DE == OPCODE_6) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];
				if (parameter_C != 0) {
					m_ProgramCounter += 3;
					continue;
				}

				auto& parameter_B = B == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 2]]
					: m_Memory[m_ProgramCounter + 2];
				m_ProgramCounter = parameter_B;
			} else if (DE == OPCODE_7) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];

				auto& parameter_B = B == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 2]]
					: m_Memory[m_ProgramCounter + 2];

				auto& parameter_A = A == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 3]]
					: m_Memory[m_ProgramCounter + 3];

				if (parameter_C < parameter_B) {
					parameter_A = 1;
				} else {
					parameter_A = 0;
				}
				m_ProgramCounter += 4;
			} else if (DE == OPCODE_8) {
				auto& parameter_C = C == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 1]]
					: m_Memory[m_ProgramCounter + 1];

				auto& parameter_B = B == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 2]]
					: m_Memory[m_ProgramCounter + 2];

				auto& parameter_A = A == POSITION_MODE
					? m_Memory[m_Memory[m_ProgramCounter + 3]]
					: m_Memory[m_ProgramCounter + 3];

				if (parameter_C == parameter_B) {
					parameter_A = 1;
				} else {
					parameter_A = 0;
				}
				m_ProgramCounter += 4;
			} else if (DE == OPCODE_STOP) {
				m_HasHaltedFromOpCode = true;
				break;
			}
		}
	}

	void IntcodeMachine::setValue(long _value, unsigned _memoryIndex) {
		assert(m_Memory.size() > _memoryIndex);
		m_Memory[_memoryIndex] = _value;
	}
	long IntcodeMachine::getValue(unsigned _memoryIndex) const {
		assert(m_Memory.size() > _memoryIndex);
		return m_Memory[_memoryIndex];
	}
}