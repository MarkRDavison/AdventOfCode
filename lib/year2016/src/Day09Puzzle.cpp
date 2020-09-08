#include <2016/Day09Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <functional>

namespace TwentySixteen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Explosives in Cyberspace", 2016, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		const auto part1 = doPart1(m_InputLines[0]);
		const auto part2 = doPart2(m_InputLines[0]);

		return { std::to_string(part1), std::to_string(part2) };
	}

	unsigned Day09Puzzle::doPart1(const std::string& _input) {
		unsigned count = 0; 

		std::size_t loc = 0;

		while (loc <= _input.size()) {
			const auto startLoc = _input.find('(', loc);
			if (startLoc == std::string::npos) {
				count += _input.size() - loc;
				break;
			}
			count += startLoc - loc;
			const auto endLoc = _input.find(')', startLoc);

			const auto& split = ze::StringExtensions::splitStringByDelimeter(_input.substr(startLoc + 1, endLoc - startLoc - 1), "x");

			const int a = std::stoi(split[0]);
			const int b = std::stoi(split[1]);

			count += (unsigned)(a * b);

			loc = endLoc + a + 1;
		}

		return count;
	}

	long long Day09Puzzle::doPart2(const std::string& _input) {
		const std::function<long long(const std::string&, unsigned, unsigned)> recurser = [&recurser](const std::string& _input, unsigned _startIndex, unsigned _endIndex) -> long long {
			long long count = 0;

			std::size_t loc = _startIndex;

			while (loc <= _endIndex) {
				if (_input[loc] != '(') {
					count++;
					loc++;
					continue;
				}
				const auto endLoc = _input.find(')', loc);

				const auto& split = ze::StringExtensions::splitStringByDelimeter(_input.substr(loc + 1, endLoc - loc - 1), "x");

				const unsigned a = (unsigned)std::stoi(split[0]);
				const unsigned b = (unsigned)std::stoi(split[1]);

				const long long recursed = recurser(_input, endLoc + 1, endLoc + a);

				count += (long long)b * recursed;
				loc = endLoc + a + 1;
			}
			return count;
		};

		return recurser(_input, 0, _input.size() - 1);
	}
}
