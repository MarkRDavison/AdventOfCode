#include <2020/HandheldConsole.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <cassert>

namespace TwentyTwenty {


	constexpr const char HandheldConsole::AccumulatorName[];

	ConsoleOperation::OpType ConsoleOperation::translate(const std::string& _opCode) {
		if (_opCode == "nop") {
			return ConsoleOperation::OpType::NOP;
		}
		if (_opCode == "acc") {
			return ConsoleOperation::OpType::ACC;
		}
		if (_opCode == "jmp") {
			return ConsoleOperation::OpType::JMP;
		}
		throw std::exception("Invalid Operation");
	}

	HandheldConsole::HandheldConsole(const std::vector<std::string>& _input) :
		HandheldConsole(parseInput(_input)){

	}
	HandheldConsole::HandheldConsole(const std::vector<ConsoleOperation>& _operations) : 
		originalOperations(_operations) {

		functionMap[ConsoleOperation::OpType::NOP] =
			[](const ConsoleOperation& _operation, HandheldConsoleValue& _programCounter, HandheldConsoleRegisters& _registers) -> void {
			_programCounter++;
		};
		functionMap[ConsoleOperation::OpType::ACC] =
			[](const ConsoleOperation& _operation, HandheldConsoleValue& _programCounter, HandheldConsoleRegisters& _registers) -> void {
			_programCounter++;
			_registers[HandheldConsole::AccumulatorName] += _operation.value;
		};
		functionMap[ConsoleOperation::OpType::JMP] =
			[](const ConsoleOperation& _operation, HandheldConsoleValue& _programCounter, HandheldConsoleRegisters& _registers) -> void {
			_programCounter += _operation.value;
		};
	}

	void HandheldConsole::runOperationAtProgramCounter() {
		const auto& currentOperation = originalOperations[programCounter];

		auto& fxn = functionMap[currentOperation.type];

		fxn(currentOperation, programCounter, registers);
	}

	std::vector<ConsoleOperation> HandheldConsole::parseInput(const std::vector<std::string>& _input) {
		std::vector<ConsoleOperation> operations;

		for (const auto& i : _input) {
			operations.emplace_back(parse(i));
		}

		return operations;
	}
	ConsoleOperation HandheldConsole::parse(const std::string& _line) {
		const auto& parts = ze::StringExtensions::splitStringByDelimeter(_line, " ");
		ConsoleOperation operation(ConsoleOperation::translate(parts[0]));

		switch (operation.type) {
		case ConsoleOperation::OpType::NOP:
		case ConsoleOperation::OpType::ACC:
		case ConsoleOperation::OpType::JMP:
			operation.value = std::stoi(parts[1]);
			break;
		default:
			throw std::exception("Invalid Operation");
		}

		return operation;
	}
}