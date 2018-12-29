#include <2018/RegisterMachine.hpp>

namespace TwentyEighteen {
	   
	void applyADDR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] + _registers[_RegisterInstruction.B];
	}
	void applyADDI(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] + _RegisterInstruction.B;
	}
	void applyMULR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] * _registers[_RegisterInstruction.B];
	}
	void applyMULI(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] * _RegisterInstruction.B;
	}
	void applyBANR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] & _registers[_RegisterInstruction.B];
	}
	void applyBANI(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] & _RegisterInstruction.B;
	}
	void applyBORR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] | _registers[_RegisterInstruction.B];
	}
	void applyBORI(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] | _RegisterInstruction.B;
	}
	void applySETR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A];
	}
	void applySETI(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _RegisterInstruction.A;
	}
	void applyGTIR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _RegisterInstruction.A > _registers[_RegisterInstruction.B] ? 1 : 0;
	}
	void applyGTRI(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] > _RegisterInstruction.B ? 1 : 0;
	}
	void applyGTRR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] > _registers[_RegisterInstruction.B] ? 1 : 0;
	}
	void applyEQIR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _RegisterInstruction.A == _registers[_RegisterInstruction.B] ? 1 : 0;
	}
	void applyEQRI(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] == _RegisterInstruction.B ? 1 : 0;
	}
	void applyEQRR(const RegisterInstruction& _RegisterInstruction, std::vector<RegisterValue>& _registers) {
		_registers[_RegisterInstruction.C] = _registers[_RegisterInstruction.A] == _registers[_RegisterInstruction.B] ? 1 : 0;
	}

	void applyRegisterInstruction(const RegisterInstruction& _registerInstruction, std::vector<RegisterValue>& _registers) {
		switch (_registerInstruction.code) {
		case OpCode::addr: applyADDR(_registerInstruction, _registers); break;
		case OpCode::addi: applyADDI(_registerInstruction, _registers); break;
		case OpCode::mulr: applyMULR(_registerInstruction, _registers); break;
		case OpCode::muli: applyMULI(_registerInstruction, _registers); break;
		case OpCode::banr: applyBANR(_registerInstruction, _registers); break;
		case OpCode::bani: applyBANI(_registerInstruction, _registers); break;
		case OpCode::borr: applyBORR(_registerInstruction, _registers); break;
		case OpCode::bori: applyBORI(_registerInstruction, _registers); break;
		case OpCode::setr: applySETR(_registerInstruction, _registers); break;
		case OpCode::seti: applySETI(_registerInstruction, _registers); break;
		case OpCode::gtir: applyGTIR(_registerInstruction, _registers); break;
		case OpCode::gtri: applyGTRI(_registerInstruction, _registers); break;
		case OpCode::gtrr: applyGTRR(_registerInstruction, _registers); break;
		case OpCode::eqir: applyEQIR(_registerInstruction, _registers); break;
		case OpCode::eqri: applyEQRI(_registerInstruction, _registers); break;
		case OpCode::eqrr: applyEQRR(_registerInstruction, _registers); break;
		default: break;
		}
	}

	RegisterMachine::RegisterMachine(std::size_t _registerBankLength, const std::vector<RegisterInstruction>& _program, RegisterValue& _programCounter) :
		RegisterBankLength(_registerBankLength),
		m_Registers(_registerBankLength),
		m_ProgramCounter(_programCounter),
		m_Program(_program) {
		
	}
	RegisterMachine::RegisterMachine(std::size_t _registerBankLength, const std::vector<RegisterInstruction>& _program, RegisterValue _programCounterIndex, bool _useCounter) :
		RegisterBankLength(_registerBankLength),
		m_Registers(_registerBankLength),
		m_ProgramCounter(m_Registers[_programCounterIndex]),
		m_Program(_program) {
		
	}

	RegisterMachine::~RegisterMachine() {
		
	}

	void RegisterMachine::applyInstruction(OpCode _opcode, std::vector<RegisterValue>& _registers, RegisterValue _a, RegisterValue _b, RegisterValue _c) {
		applyInstruction(RegisterInstruction(_opcode, _a, _b, _c), _registers);
	}

	void RegisterMachine::applyInstruction(const RegisterInstruction& _registerInstruction, std::vector<RegisterValue>& _registers) {
		applyRegisterInstruction(_registerInstruction, _registers);
	}

	void RegisterMachine::runProgramToCompletion() {
		while (m_ProgramCounter < m_Program.size()) {
			const RegisterInstruction& _instruction = m_Program[m_ProgramCounter];

			applyRegisterInstruction(_instruction, m_Registers);
			m_ProgramCounter++;
		}
	}

	void RegisterMachine::runProgramForXIterations(std::size_t _iterations) {
		std::size_t iter = 0;
		while (m_ProgramCounter < m_Program.size() && iter < _iterations) {
			const RegisterInstruction& _instruction = m_Program[m_ProgramCounter];

			applyRegisterInstruction(_instruction, m_Registers);
			m_ProgramCounter++;
			iter++;
		}
	}

}
