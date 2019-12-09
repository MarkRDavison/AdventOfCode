#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <iostream>
#include <cassert>

#define OPCODE_ADD 1
#define OPCODE_MUL 2
#define OPCODE_3 3
#define OPCODE_4 4
#define OPCODE_5 5
#define OPCODE_6 6
#define OPCODE_7 7
#define OPCODE_8 8
#define OPCODE_9 9
#define OPCODE_STOP 99

#define POSITION_MODE 0
#define IMMEDIATE_MODE 1
#define RELATIVE_MODE 2

namespace TwentyNineteen {

	void IntcodeMachine::loadProgram(const std::string& _program) {
		m_Program.clear();
		for (const auto& strValue : core::StringExtensions::splitStringByDelimeter(_program, ",")) {
			m_Program.emplace_back(std::atoll(strValue.c_str()));
		}
		for (unsigned i = 0; i < 10000; ++i) {
			m_Program.emplace_back(0);
		}
		resetProgram();
	}
	void IntcodeMachine::resetProgram() {
		m_Memory = std::vector<IntcodeValue>(m_Program);
		m_ProgramCounter = 0;
	}


	IntcodeValue& IntcodeMachine::getValue(IntcodeValue _mode, unsigned _pc) {
		if (_mode == RELATIVE_MODE) {
			auto loc = m_Memory[_pc] + m_RelativeBase;
			assert(loc > 0);
			return m_Memory[static_cast<unsigned>(loc)];
		}
		else if (_mode == POSITION_MODE) {
			auto loc = m_Memory[_pc];
			assert(loc > 0);
			return m_Memory[static_cast<unsigned>(loc)];
		}
		else {
			return m_Memory[_pc];
		}
	}

	void IntcodeMachine::execute() {
		if (m_HasHaltedFromOpCode) { return; }
		while (true) {
			const IntcodeValue opCode = m_Memory[m_ProgramCounter];

			const int DE = opCode % 100;
			const int C = (opCode / 100) % 10;
			const int B = (opCode / 1000) % 10;
			const int A = (opCode / 10000) % 10;

			if (DE == OPCODE_MUL) {

				auto& parameter_C = getValue(C, m_ProgramCounter + 1);
				auto& parameter_B = getValue(B, m_ProgramCounter + 2);
				auto& parameter_A = getValue(A, m_ProgramCounter + 3);

				parameter_A = parameter_B * parameter_C;
				m_ProgramCounter += 4;
			} 
			else if (DE == OPCODE_ADD) {

				auto& parameter_C = getValue(C, m_ProgramCounter + 1);
				auto& parameter_B = getValue(B, m_ProgramCounter + 2);
				auto& parameter_A = getValue(A, m_ProgramCounter + 3);

				parameter_A = parameter_B + parameter_C;
				m_ProgramCounter += 4;
			} 
			else if (DE == OPCODE_3) {
				auto& parameter_C = getValue(C, m_ProgramCounter + 1);

				if (m_Input.empty() && m_HaltWhenInputEmpty) {
					break;
				}
				parameter_C = m_Input.front();
				m_Input.pop();
				m_ProgramCounter += 2;

			} 
			else if (DE == OPCODE_4) {
				auto& parameter_C = getValue(C, m_ProgramCounter + 1);

				m_Output = parameter_C;
				m_ProgramCounter += 2;
				if (m_HaltWhenOutputSet) {
					m_OutputRetrieved = false;
					break;
				}
			} else if (DE == OPCODE_5) {
				auto& parameter_C = getValue(C, m_ProgramCounter + 1);
				if (parameter_C == 0) {
					m_ProgramCounter += 3;
					continue;
				}

				auto& parameter_B = getValue(B, m_ProgramCounter + 2);
				assert(parameter_B > 0);
				m_ProgramCounter = static_cast<unsigned>(parameter_B);
			} else if (DE == OPCODE_6) {

				auto& parameter_C = getValue(C, m_ProgramCounter + 1);
				if (parameter_C != 0) {
					m_ProgramCounter += 3;
					continue;
				}

				auto& parameter_B = getValue(B, m_ProgramCounter + 2);
				assert(parameter_B > 0);
				m_ProgramCounter = static_cast<unsigned>(parameter_B);
			} else if (DE == OPCODE_7) {
				auto& parameter_C = getValue(C, m_ProgramCounter + 1);

				auto& parameter_B = getValue(B, m_ProgramCounter + 2);

				auto& parameter_A = getValue(A, m_ProgramCounter + 3);

				if (parameter_C < parameter_B) {
					parameter_A = 1;
				} else {
					parameter_A = 0;
				}
				m_ProgramCounter += 4;
			} else if (DE == OPCODE_8) {
				auto& parameter_C = getValue(C, m_ProgramCounter + 1);

				auto& parameter_B = getValue(B, m_ProgramCounter + 2);

				auto& parameter_A = getValue(A, m_ProgramCounter + 3);

				if (parameter_C == parameter_B) {
					parameter_A = 1;
				} else {
					parameter_A = 0;
				}
				m_ProgramCounter += 4;
			} else if (DE == OPCODE_9) {
				auto& parameter_C = getValue(C, m_ProgramCounter + 1);
				
				IntcodeValue newRelativeBase = static_cast<IntcodeValue>(m_RelativeBase) + parameter_C;
				assert(newRelativeBase > 0);
				m_RelativeBase = static_cast<unsigned>(newRelativeBase);
				m_ProgramCounter += 2;
			} else if (DE == OPCODE_STOP) {
				m_HasHaltedFromOpCode = true;
				break;
			}
		}
	}

	void IntcodeMachine::setValue(IntcodeValue _value, unsigned _memoryIndex) {
		assert(m_Memory.size() > _memoryIndex);
		m_Memory[_memoryIndex] = _value;
	}
	IntcodeValue IntcodeMachine::getValue(unsigned _memoryIndex) const {
		assert(m_Memory.size() > _memoryIndex);
		return m_Memory[_memoryIndex];
	}
}