#ifndef INCLUDED_ADVENT_OF_CODE_2018_TRAINING_REGISTER_INSTRUCTION_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_TRAINING_REGISTER_INSTRUCTION_HPP_

#include <2018/RegisterInstruction.hpp>
#include <set>

namespace TwentyEighteen {

	struct RegisterTrainingInstruction {

		RegisterTrainingInstruction(MysteryRegisterInstruction _instruction, 
			RegisterValue _b0, RegisterValue _b1, RegisterValue _b2, RegisterValue _b3, 
			RegisterValue _a0, RegisterValue _a1, RegisterValue _a2, RegisterValue _a3) :
			instruction(_instruction) {

			before[0] = _b0;
			before[1] = _b1;
			before[2] = _b2;
			before[3] = _b3;

			after[0] = _a0;
			after[1] = _a1;
			after[2] = _a2;
			after[3] = _a3;
		}

		MysteryRegisterInstruction instruction;

		RegisterValue before[4];
		RegisterValue after[4];

		std::set<OpCode> validOpCodes;

		OpCode opCode{ OpCode::NumberOfOpCodes };
	};
	
}

#endif // INCLUDED_ADVENT_OF_CODE_2018_TRAINING_REGISTER_INSTRUCTION_HPP_