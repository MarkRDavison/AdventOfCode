#include <2019/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("The Tyranny of the Rocket Equation", 2019, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {

		long part1Sum = 0;
		long part2Sum = 0;

		for (const auto& line : m_InputLines) {
			const long moduleValue = std::atoi(line.c_str());
			part1Sum += calculateFuelForModule(moduleValue);
			part2Sum += calculateFuelForModuleRecursive(moduleValue);
		}

		return { std::to_string(part1Sum), std::to_string(part2Sum) };
	}

	long Day01Puzzle::calculateFuelForModule(long _amount) {
		long result = (_amount / 3) - 2;
		return result < 0 ? 0 : result;
	}
	long Day01Puzzle::calculateFuelForModuleRecursive(long _amount) {
		long sum = 0;
		while (_amount > 0) {
			long current = calculateFuelForModule(_amount);
			_amount = current;
			sum += current;
		}
		return sum;
	}
}
