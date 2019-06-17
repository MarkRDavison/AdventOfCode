#include <2016/Day03Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Squares With Three Sides", 2016, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	bool isTriangleValid(int _1, int _2, int _3) {
		if (_1 < _2 + _3 &&
			_2 < _3 + _1 &&
			_3 < _1 + _2) {
			return true;
		}
		return false;
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		int part1Valid = 0;
		int part2Valid = 0;

		for (unsigned i = 0; i < m_InputLines.size(); i += 3) {
			auto parts = core::StringExtensions::splitStringByDelimeter(m_InputLines[i + 0], " ");
			int part0_0 = std::atoi(parts[0].c_str());
			int part0_1 = std::atoi(parts[1].c_str());
			int part0_2 = std::atoi(parts[2].c_str());

			parts = core::StringExtensions::splitStringByDelimeter(m_InputLines[i + 1], " ");
			int part1_0 = std::atoi(parts[0].c_str());
			int part1_1 = std::atoi(parts[1].c_str());
			int part1_2 = std::atoi(parts[2].c_str());

			parts = core::StringExtensions::splitStringByDelimeter(m_InputLines[i + 2], " ");
			int part2_0 = std::atoi(parts[0].c_str());
			int part2_1 = std::atoi(parts[1].c_str());
			int part2_2 = std::atoi(parts[2].c_str());

			if (isTriangleValid(part0_0, part0_1, part0_2)) {
				part1Valid++;
			}
			if (isTriangleValid(part1_0, part1_1, part1_2)) {
				part1Valid++;
			}
			if (isTriangleValid(part2_0, part2_1, part2_2)) {
				part1Valid++;
			}

			if (isTriangleValid(part0_0, part1_0, part2_0)) {
				part2Valid++;
			}
			if (isTriangleValid(part0_1, part1_1, part2_1)) {
				part2Valid++;
			}
			if (isTriangleValid(part0_2, part1_2, part2_2)) {
				part2Valid++;
			}
		}
		return { std::to_string(part1Valid), std::to_string(part2Valid) };
	}
}
