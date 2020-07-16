#include <2015/Day02Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>

namespace TwentyFifteen {
		
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("I Was Told There Would Be No Math", 2015, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	int Day02Puzzle::part1(const std::vector<ParsedInput>& _input) {
		int total = 0;
		for (const auto& _pi : _input) {
			total += getPart1(_pi);
		}
		return total;
	}
	int Day02Puzzle::getPart1(const ParsedInput& _input) {
		int total =
			2 * _input.h * _input.l +
			2 * _input.l * _input.w +
			2 * _input.w * _input.h;

		int extra = _input.h * _input.l * _input.w;
		extra /= std::max(_input.h, std::max(_input.l, _input.w));

		return total + extra;
	}
	int Day02Puzzle::part2(const std::vector<ParsedInput>& _input) {
		int total = 0;
		for (const auto& _pi : _input) {
			total += getPart2(_pi);
		}
		return total;
	}
	int Day02Puzzle::getPart2(const ParsedInput& _input) {
		int circ = _input.l + _input.w + _input.h;
		circ -= std::max(std::max(_input.l, _input.w), _input.h);
		circ *= 2;

		int ribbon = _input.l * _input.w * _input.h;

		return circ + ribbon;
	}

	std::vector<Day02Puzzle::ParsedInput> Day02Puzzle::parseInput(const std::vector<std::string>& _input) {
		std::vector<Day02Puzzle::ParsedInput> pi;

		for (const std::string& line : _input) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(line, "x");

			auto& parsed = pi.emplace_back();
			parsed.l = std::stoi(parts[0]);
			parsed.w = std::stoi(parts[1]);
			parsed.h = std::stoi(parts[2]);
		}

		return pi;
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		const auto& input = parseInput(m_InputLines);
		return { std::to_string(part1(input)), std::to_string(part2(input)) };
	}
}
