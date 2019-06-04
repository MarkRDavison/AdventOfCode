#ifndef INCLUDED_ADVENT_OF_CODE_2018_REGISTER_MACHINE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_REGISTER_MACHINE_HPP_

#include <2018/RegisterInstruction.hpp>
#include <vector>

namespace TwentyEighteen {
	
	class RegisterMachine {
	public:
		RegisterMachine(std::size_t _registerBankLength, const std::vector<RegisterInstruction>& _program, RegisterValue& _programCounter);
		RegisterMachine(std::size_t _registerBankLength, const std::vector<RegisterInstruction>& _program, RegisterValue _programCounterIndex, bool _useCounter);
		~RegisterMachine();

		const std::size_t RegisterBankLength;

		std::vector<RegisterValue>& getRegisters() { return m_Registers; }
		const std::vector<RegisterValue>& getRegisters() const { return m_Registers; }

		static void applyInstruction(OpCode _opcode, std::vector<RegisterValue>& _registers, RegisterValue _a, RegisterValue _b, RegisterValue _c);
		static void applyInstruction(const RegisterInstruction& _registerInstruction, std::vector<RegisterValue>& _registers);

		void runProgramToCompletion();

		void runProgramForXIterations(std::size_t _iterations);

		RegisterValue& getProgramCounter();
		const RegisterValue& getProgramCounter() const;

	private:
		std::vector<RegisterValue> m_Registers;
		RegisterValue& m_ProgramCounter;
		const std::vector<RegisterInstruction>& m_Program;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_REGISTER_MACHINE_HPP_