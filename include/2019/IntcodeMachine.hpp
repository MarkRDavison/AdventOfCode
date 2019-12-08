#ifndef INCLUDED_ADVENT_OF_CODE_2019_INTCODE_MACHINE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2019_INTCODE_MACHINE_HPP_

#include <vector>
#include <string>
#include <queue>

namespace TwentyNineteen {

	class IntcodeMachine {
	public:
		void loadProgram(const std::string& _program);
		void resetProgram();
		void execute();

		void setValue(long _value, unsigned _memoryIndex);
		long getValue(unsigned _memoryIndex) const;
		void setInput(long _value) { m_Input.push(_value); }
		long getOutput() { 
			m_OutputRetrieved = true;
			return m_Output; 
		}

		void haltWhenInputEmpty(bool _halt) { m_HaltWhenInputEmpty = _halt; }
		void haltWhenOutputSet(bool _halt) { m_HaltWhenOutputSet = _halt; }

		bool hasHaltedFromOpCode() const { return m_HasHaltedFromOpCode; }

	private:
		unsigned m_ProgramCounter{ 0 };
		std::vector<long> m_Program;
		std::vector<long> m_Memory;

		std::queue<long> m_Input;

		long m_Output{ 0 };
		bool m_OutputRetrieved{ false };

		bool m_HaltWhenInputEmpty{ false };
		bool m_HaltWhenOutputSet{ false };
		bool m_HasHaltedFromOpCode{ false };
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2019_INTCODE_MACHINE_HPP_