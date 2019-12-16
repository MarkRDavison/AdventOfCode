#ifndef INCLUDED_ADVENT_OF_CODE_2019_INTCODE_MACHINE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2019_INTCODE_MACHINE_HPP_

#include <vector>
#include <string>
#include <queue>

namespace TwentyNineteen {

	using IntcodeValue = long long;

	class IntcodeMachine {
	public:
		IntcodeMachine();
		//IntcodeMachine(const IntcodeMachine& _copy);

		void loadProgram(const std::string& _program);
		void resetProgram();
		void execute();
		enum class ExecutionResult {
			Input,
			Output,
			Halt
		};
		ExecutionResult executeResult();

		void setValue(IntcodeValue _value, unsigned _memoryIndex);
		IntcodeValue getValue(unsigned _memoryIndex) const;
		void setInput(IntcodeValue _value) { m_Input.push(_value); }
		IntcodeValue getOutput() {
			m_OutputRetrieved = true;
			return m_Output; 
		}
		IntcodeValue& getValue(IntcodeValue _mode, unsigned _pc);
		void haltWhenInputEmpty(bool _halt) { m_HaltWhenInputEmpty = _halt; }
		void haltWhenOutputSet(bool _halt) { m_HaltWhenOutputSet = _halt; }

		bool hasHaltedFromOpCode() const { return m_HasHaltedFromOpCode; }

		bool hasOutput() const {
			return m_OutputRetrieved;
		}

	private:
		unsigned m_ProgramCounter{ 0 };
		unsigned m_RelativeBase{ 0 };
		std::vector<IntcodeValue> m_Program;
		std::vector<IntcodeValue> m_Memory;

		std::queue<IntcodeValue> m_Input;

		IntcodeValue m_Output{ 0 };
		bool m_OutputRetrieved{ false };

		bool m_HaltWhenInputEmpty{ false };
		bool m_HaltWhenOutputSet{ false };
		bool m_HasHaltedFromOpCode{ false };
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2019_INTCODE_MACHINE_HPP_