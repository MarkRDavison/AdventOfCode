#include <2020/Day08Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <2020/HandheldConsole.hpp>

#include <set>

namespace TwentyTwenty {

	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Handheld Halting", 2020, 8) {
	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		HandheldConsole console(m_InputLines);

		std::set<HandheldConsoleValue> visitedProgramCounters;

		while (visitedProgramCounters.find(console.programCounter) == visitedProgramCounters.end()) {
			visitedProgramCounters.insert(console.programCounter);
			console.runOperationAtProgramCounter();
		}

		const auto part1 = console.registers[HandheldConsole::AccumulatorName];

		for (unsigned i = 0; i < console.originalOperations.size(); ++i) {
			const auto currentOpCode = console.originalOperations[i].type;
			if (currentOpCode != ConsoleOperation::OpType::NOP &&
				currentOpCode != ConsoleOperation::OpType::JMP) {
				continue;
			}
			visitedProgramCounters = std::set<HandheldConsoleValue>();

			auto newOperations(console.originalOperations);
			newOperations[i].type = (currentOpCode == ConsoleOperation::OpType::NOP
				? ConsoleOperation::OpType::JMP
				: ConsoleOperation::OpType::NOP
			);
			HandheldConsole modifiedConsole(newOperations);

			while (visitedProgramCounters.find(modifiedConsole.programCounter) == visitedProgramCounters.end()) {
				visitedProgramCounters.insert(modifiedConsole.programCounter);
				modifiedConsole.runOperationAtProgramCounter();
				if (0 > modifiedConsole.programCounter || modifiedConsole.programCounter >= modifiedConsole.originalOperations.size()) {
					return { std::to_string(part1), std::to_string(modifiedConsole.registers[HandheldConsole::AccumulatorName]) };
				}
			}
		}

		return { std::to_string(part1), "Part 2 failed." };
	}
	/*
	std::vector<Day8Struct> Day08Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		std::vector<Day8Struct> parsed;

		for (const auto& i : _inputLines) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(i, " ");
			auto& operation = parsed.emplace_back();
			operation.op = parts[0];
			operation.value = (IntcodeValue)std::stoi(parts[1]);
		}

		return parsed;
	}
	std::string Day08Puzzle::doPart1(const std::vector<Day8Struct>& _input) {

		
		IntcodeValue pc = 0;
		IntcodeValue acc = 0;

		std::map<std::string, OperationFxn> operations;
		operations["acc"] = [&pc, &acc](IntcodeValue _value) -> void {
			acc += _value;
			pc++;
		};
		operations["jmp"] = [&pc, &acc](IntcodeValue _value) -> void {
			pc += _value;
		};
		operations["nop"] = [&pc, &acc](IntcodeValue _value) -> void {
			pc++;
		};


		std::set<IntcodeValue> visitedPcs;
		while (visitedPcs.find(pc) == visitedPcs.end()) {
			visitedPcs.insert(pc);
			const auto& operation = _input[pc];
			operations[operation.op](operation.value);
		}

		return std::to_string(acc);
	}
	std::string Day08Puzzle::doPart2(const std::vector<Day8Struct>& _input) {


		IntcodeValue acc = 0;
		for (unsigned i = 0; i < _input.size(); ++i) { 
			if (_input[i].op != "nop" &&
				_input[i].op != "jmp") {
				continue;
			}
			std::vector<Day8Struct> input(_input);
			input[i].op = (input[i].op == "nop" ? "jmp" : "nop");


			IntcodeValue pc = 0;
			acc = 0;

			std::map<std::string, OperationFxn> operations;
			operations["acc"] = [&pc, &acc](IntcodeValue _value) -> void {
				acc += _value;
				pc++;
			};
			operations["jmp"] = [&pc, &acc](IntcodeValue _value) -> void {
				pc += _value;
			};
			operations["nop"] = [&pc, &acc](IntcodeValue _value) -> void {
				pc++;
			};

			std::set<IntcodeValue> visitedPcs;
			bool repeat = false;
			while (0 <= pc && pc < input.size()) {
				if (visitedPcs.count(pc) > 0) {
					repeat = true;
					break;
				}
				visitedPcs.insert(pc);
				const auto& operation = input[pc];
				operations[operation.op](operation.value);
			}

			if (!repeat) {
				break;
			}
		}
		return std::to_string(acc);
	}
	*/
}
