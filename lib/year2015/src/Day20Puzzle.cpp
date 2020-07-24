#include <2015/Day20Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

constexpr TwentyFifteen::BigNumberThing THRESHOLD = 100;

namespace TwentyFifteen {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Infinite Elves and Infinite Houses", 2015, 20) {

	}
	Day20Puzzle::~Day20Puzzle() {

	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		const auto part1 = getPart1((BigNumberThing)std::stol(m_InputLines[0]));
		const auto part2 = getPart2((BigNumberThing)std::stol(m_InputLines[0]));
		return { std::to_string(part1), std::to_string(part2) };
	}
	
	BigNumberThing Day20Puzzle::getNumberOfPresentsForHouseNumber(BigNumberThing _houseNumber) {
		BigNumberThing sum = 0;
		for (BigNumberThing i = 1; i <= (BigNumberThing)std::sqrt((double)_houseNumber); ++i) {
			if (_houseNumber % i == 0) {
				sum += i;
				if (_houseNumber / i != i) {
					sum += _houseNumber / i;
				}
			}
		}
		return sum * 10;
	}
	BigNumberThing Day20Puzzle::getNumberOfPresentsForHouseNumberPart2(BigNumberThing _houseNumber) {
		
		const auto hasElfDeliveredTooMany = [](BigNumberThing _elf, BigNumberThing _house) ->bool {
			const auto roughNumberDelivered = 11 * (_house / _elf);
			return roughNumberDelivered > 50;
		};
		
		
		BigNumberThing sum = 0;
		for (BigNumberThing i = 1; i <= (BigNumberThing)std::sqrt((double)_houseNumber); ++i) {
			if (_houseNumber % i == 0) {
				if (!hasElfDeliveredTooMany(i * 11, _houseNumber)) {
					sum += i * 11;
				}
				if (_houseNumber / i != i) {
					if (!hasElfDeliveredTooMany((_houseNumber / i) * 11, _houseNumber)) {
						sum += (_houseNumber / i) * 11;
					}
				}
			}
		}
		return sum;
	}
	BigNumberThing Day20Puzzle::getPart1(BigNumberThing _input) {
		BigNumberThing firstGuessOverr = 0;
		for (auto guess = 0; guess < _input; guess += 1000) {
			const BigNumberThing g = getNumberOfPresentsForHouseNumber(guess);
			if (g >= _input) {
				firstGuessOverr = guess;
				break;
			}
		}

		for (auto g = firstGuessOverr; g > 0; --g) {
			const BigNumberThing guess = getNumberOfPresentsForHouseNumber(g);
			if (guess >= _input) {
				firstGuessOverr = g;
			}
		}

		return firstGuessOverr;
	}
	BigNumberThing Day20Puzzle::getPart2(BigNumberThing _input) {
		BigNumberThing firstGuessOverr = 0;
		for (auto guess = 0; guess < _input; guess += 1000) {
			const BigNumberThing g = getNumberOfPresentsForHouseNumberPart2(guess);
			if (g >= _input) {
				firstGuessOverr = guess;
				break;
			}
		}

		unsigned iterWithoutSuccess = 0;
		for (auto g = firstGuessOverr; g > 0; --g) {
			const BigNumberThing guess = getNumberOfPresentsForHouseNumberPart2(g);
			iterWithoutSuccess++;
			if (guess >= _input) {
				firstGuessOverr = g;
				iterWithoutSuccess = 0;
			}
			if (iterWithoutSuccess >= 100000) {
				break;
			}
		}

		return firstGuessOverr;
	}
}
