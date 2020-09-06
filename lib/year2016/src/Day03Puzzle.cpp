#include <2016/Day03Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>

namespace TwentySixteen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Squares With Three Sides", 2016, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		const auto part1 = doPart1(m_InputLines);
		const auto part2 = doPart2(m_InputLines);
		return { std::to_string(part1), std::to_string(part2) };
	}

	bool Day03Puzzle::isValidTriangle(int _a, int _b, int _c) {
		const int max = std::max(_a, std::max(_b, _c));

		return (_a + _b + _c) - max > max;
	}
	int Day03Puzzle::doPart1(const std::vector<std::string>& _input) {
		int validTriangles = 0;

		for (const auto& i : _input) {
			const auto& sides = ze::StringExtensions::splitStringByDelimeter(i, " ");
			if (isValidTriangle(std::stoi(sides[0]), std::stoi(sides[1]), std::stoi(sides[2]))) {
				validTriangles++;
			}
		}

		return validTriangles;
	}
	int Day03Puzzle::doPart2(const std::vector<std::string>& _input) {
		int validTriangles = 0;

		for (unsigned i = 0; i < _input.size(); i += 3) {
			const auto& sides_0 = ze::StringExtensions::splitStringByDelimeter(_input[i + 0], " ");
			const auto& sides_1 = ze::StringExtensions::splitStringByDelimeter(_input[i + 1], " ");
			const auto& sides_2 = ze::StringExtensions::splitStringByDelimeter(_input[i + 2], " ");

			if (isValidTriangle(std::stoi(sides_0[0]), std::stoi(sides_1[0]), std::stoi(sides_2[0]))) {
				validTriangles++;
			}
			if (isValidTriangle(std::stoi(sides_0[1]), std::stoi(sides_1[1]), std::stoi(sides_2[1]))) {
				validTriangles++;
			}
			if (isValidTriangle(std::stoi(sides_0[2]), std::stoi(sides_1[2]), std::stoi(sides_2[2]))) {
				validTriangles++;
			}
		}

		return validTriangles;
	}
}
