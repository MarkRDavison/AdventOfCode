#include <2018/Day19Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2018/RegisterMachine.hpp>
#include <algorithm>
#include <numeric>

namespace TwentyEighteen {

	std::vector<RegisterValue> primeFactors(RegisterValue n) {
		std::vector<RegisterValue> results;

		RegisterValue original(n);

		results.emplace_back(1);

		// Print the number of 2s that divide n 
		while (n % 2 == 0) {
			results.emplace_back(2);
			n = n / 2;
		}

		// n must be odd at this point.  So we can skip  
		// one element (Note i = i +2) 
		for (int i = 3; i <= sqrt(n); i = i + 2) {
			// While i divides n, print i and divide n 
			while (n%i == 0) {
				results.emplace_back(i);
				n = n / i;
			}
		}

		// This condition is to handle the case when n  
		// is a prime number greater than 2 
		if (n > 2) {
			results.emplace_back(n);
		}

		results.emplace_back(original);

		return results;
	}

	Day19Puzzle::Day19Puzzle(bool _solvePart2 /*= true*/) :
		core::PuzzleBase("Go With The Flow", 2018, 19),
		m_SolvePart2(_solvePart2) {

	}
	Day19Puzzle::~Day19Puzzle() {

	}

	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		const RegisterValue instructionPointerRegister = std::atoi(core::StringExtensions::splitStringByDelimeter(m_InputLines[0], " ")[1].c_str());

		std::vector<RegisterInstruction> instructions;
		for (std::size_t i = 1; i < m_InputLines.size(); ++i) {
			const std::vector<std::string> instructionComponents = core::StringExtensions::splitStringByDelimeter(m_InputLines[i], " ");

			const OpCode code = StringToOpCode(instructionComponents[0]);
			const RegisterValue a = std::atoi(instructionComponents[1].c_str());
			const RegisterValue b = std::atoi(instructionComponents[2].c_str());
			const RegisterValue c = std::atoi(instructionComponents[3].c_str());

			instructions.emplace_back(code, a, b, c);
		}

		RegisterValue part1Answer;
		{
			RegisterMachine machine(6, instructions, instructionPointerRegister, true);
			machine.runProgramToCompletion();
			part1Answer = machine.getRegisters()[0];
		}

		if (m_SolvePart2) {
			RegisterMachine machine(6, instructions, instructionPointerRegister, true);
			machine.getRegisters().front() = 1;

			machine.runProgramForXIterations(50);

			const auto registers = machine.getRegisters();

			const RegisterValue number = *std::max_element(registers.begin(), registers.end());

			const auto primeFactorsOfNumber = primeFactors(number);

			const RegisterValue part2Answer = std::accumulate(primeFactorsOfNumber.begin(), primeFactorsOfNumber.end(), 0, [](RegisterValue _sum, RegisterValue _factor) -> RegisterValue { return _sum + _factor; });

			return { std::to_string(part1Answer), std::to_string(part2Answer) };
		}

		return { std::to_string(part1Answer), "???" };
	}

}
