#ifndef INCLUDED_ADVENT_OF_CODE_2018_REGISTER_INSTRUCTION_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_REGISTER_INSTRUCTION_HPP_

#include <cstdlib>
#include <string>

namespace TwentyEighteen {

	using RegisterValue = std::size_t;
	
	enum class OpCode {
		addr = 0,
		addi = 1,
		mulr = 2,
		muli = 3,
		banr = 4,
		bani = 5,
		borr = 6,
		bori = 7,
		setr = 8,
		seti = 9,
		gtir = 10,
		gtri = 11,
		gtrr = 12,
		eqir = 13,
		eqri = 14,
		eqrr = 15,

		NumberOfOpCodes
	};

	static std::string OpCodeToString(OpCode _opCode) {
		switch (_opCode) {
			case OpCode::addr: return "addr";
			case OpCode::addi: return "addi";
			case OpCode::mulr: return "mulr";
			case OpCode::muli: return "muli";
			case OpCode::banr: return "banr";
			case OpCode::bani: return "bani";
			case OpCode::borr: return "borr";
			case OpCode::bori: return "bori";
			case OpCode::setr: return "setr";
			case OpCode::seti: return "seti";
			case OpCode::gtir: return "gtir";
			case OpCode::gtri: return "gtri";
			case OpCode::gtrr: return "gtrr";
			case OpCode::eqir: return "eqir";
			case OpCode::eqri: return "eqri";
			case OpCode::eqrr: return "eqrr";
			default: return "invalid";
		}
	}

	static OpCode StringToOpCode(const std::string _code) {
		if (_code == "addr") { return OpCode::addr;	}
		if (_code == "addi") { return OpCode::addi; }
		if (_code == "mulr") { return OpCode::mulr; }
		if (_code == "muli") { return OpCode::muli; }
		if (_code == "banr") { return OpCode::banr; }
		if (_code == "bani") { return OpCode::bani; }
		if (_code == "borr") { return OpCode::borr; }
		if (_code == "bori") { return OpCode::bori; }
		if (_code == "setr") { return OpCode::setr; }
		if (_code == "seti") { return OpCode::seti; }
		if (_code == "gtir") { return OpCode::gtir; }
		if (_code == "gtri") { return OpCode::gtri; }
		if (_code == "gtrr") { return OpCode::gtrr; }
		if (_code == "eqir") { return OpCode::eqir; }
		if (_code == "eqri") { return OpCode::eqri; }
		if (_code == "eqrr") { return OpCode::eqrr; }

		return OpCode::NumberOfOpCodes;
	}

	struct MysteryRegisterInstruction {

		MysteryRegisterInstruction(int _code, RegisterValue _a, RegisterValue _b, RegisterValue _c) : opCodeId(_code), A(_a), B(_b), C(_c) {}

		const int opCodeId;

		const RegisterValue A;
		const RegisterValue B;
		const RegisterValue C;

	};

	struct RegisterInstruction {
		
		RegisterInstruction(OpCode _code, RegisterValue _a, RegisterValue _b, RegisterValue _c) : code(_code), A(_a), B(_b), C(_c) {}

		const OpCode code;
		
		const RegisterValue A;
		const RegisterValue B;
		const RegisterValue C;

	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_REGISTER_INSTRUCTION_HPP_