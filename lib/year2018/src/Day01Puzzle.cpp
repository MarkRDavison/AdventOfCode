#include <2018/Day01Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_set>

namespace TwentyEighteen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Chronal Calibration", 2018, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {

		using NumberValue = long;

		NumberValue part1 = 0;
		NumberValue part2 = std::numeric_limits<NumberValue>::min();
		std::unordered_set<NumberValue> seen;
		seen.insert(part1);

		NumberValue current = 0;
		while (part2 == std::numeric_limits<NumberValue>::min())
		{
			for (const auto& l : m_InputLines)
			{
				const auto num = std::stol(l);
				current += num;
				if (part2 == std::numeric_limits<NumberValue>::min() &&
					seen.find(current) != seen.end())
				{
					part2 = current;
				}
				seen.insert(current);
			}

			if (part1 == 0)
			{
				part1 = current;
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
