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

}
