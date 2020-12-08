#ifndef ADVENT_OF_CODE_2020_HANDHELD_CONSOLE_HPP_
#define ADVENT_OF_CODE_2020_HANDHELD_CONSOLE_HPP_

#include <unordered_map>
#include <functional>
#include <vector>

namespace TwentyTwenty {

	using HandheldConsoleValue = long long;
	using RegisterKeyType = std::string;
	using RegisterValueType = HandheldConsoleValue;

	struct ConsoleOperation {


		enum class OpType {
			ACC,
			JMP,
			NOP
		};

		ConsoleOperation() : ConsoleOperation(OpType::NOP) {}
		ConsoleOperation(OpType _type) : type(_type) {}
		static OpType translate(const std::string& _opCode);
		OpType type;
		HandheldConsoleValue value{ 0 };
	};
	using HandheldConsoleRegisters = std::unordered_map<RegisterKeyType, RegisterValueType>;
	using HandheldConsoleFxn = std::function<void(const ConsoleOperation& _operation, HandheldConsoleValue& _programCounter, HandheldConsoleRegisters& _registers)>;
	using HandheldConsoleFxnMap = std::unordered_map<ConsoleOperation::OpType, HandheldConsoleFxn>;

	class HandheldConsole {
	public:
		static constexpr char AccumulatorName[] = "ACC";

		HandheldConsole(const std::vector<std::string>& _input);
		HandheldConsole(const std::vector<ConsoleOperation>& _operations);

		void runOperationAtProgramCounter();

	private:
		static std::vector<ConsoleOperation> parseInput(const std::vector<std::string>& _input);
		static ConsoleOperation parse(const std::string& _line);

	public:
		HandheldConsoleValue programCounter{ 0 };
		HandheldConsoleFxnMap functionMap;
		HandheldConsoleRegisters registers;
		const std::vector<ConsoleOperation> originalOperations;
	};
}

#endif // ADVENT_OF_CODE_2020_HANDHELD_CONSOLE_HPP_