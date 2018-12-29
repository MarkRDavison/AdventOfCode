#include <2018/Day15Puzzle.hpp>
#include <2018/Cave.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {

	Day15Puzzle::Day15Puzzle(bool _solvePart2 /*= true*/) :
		core::PuzzleBase("Beverage Bandits", 2018, 15),
		m_SolvePart2(_solvePart2) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}

	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {

		std::string Part1Answer;
		std::string Part2Answer;

		{
			const int ElfAttackPower = 3;
			Cave cave(m_InputLines, ElfAttackPower);
			if (getVerbose()) {
				std::cout << "Attempting to solve for elf power: " << ElfAttackPower << std::endl;
			}
			while (!cave.getComplete()) {
				cave.doTurn();
			}

			const int CompletedRounds = cave.getCompletedRound();
			const int RemainingHealth = cave.getTotalHealthRemaining();

			Part1Answer = std::to_string(CompletedRounds * RemainingHealth);
			if (!cave.getElfKilled()) {
				m_SolvePart2 = false;
				Part2Answer = Part1Answer;
			}
		}

		if (m_SolvePart2) {
			for (int _attackPower = 4; _attackPower <= 200; ++_attackPower) {
				Cave cave(m_InputLines, _attackPower);

				bool elfKilled = false;
				if (getVerbose()) {
					std::cout << "Attempting to solve for elf power: " << _attackPower << std::endl;
				}
				while (!cave.getComplete() && !elfKilled) {
					cave.doTurn();
					elfKilled = cave.getElfKilled();
				}

				if (!elfKilled) {
					const int CompletedRounds = cave.getCompletedRound();
					const int RemainingHealth = cave.getTotalHealthRemaining();

					Part2Answer = std::to_string(CompletedRounds * RemainingHealth);
					break;
				}
				else if (getVerbose()) {
					std::cout << "Elf attack power of " << _attackPower << " did not have clean sweep" << std::endl;
				}
			}
		}

		return { Part1Answer, Part2Answer };
	}

}
