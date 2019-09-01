#include <2015/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <regex>

namespace TwentyFifteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("I Was Told There Would Be No Math", 2015, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		int area = 0;
		int length = 0;
		for (const auto& i : m_InputLines) {
			const auto& parsed = parseLine(i);
			area += wrappingArea(parsed);
			length += ribbonLength(parsed);
		}


		return { std::to_string(area), std::to_string(length) };
	}
	Day02Puzzle::ParsedLine Day02Puzzle::parseLine(const std::string& _inputLine) {
		std::smatch m;
		const std::regex regex(R"(([0-9]+)x([0-9]+)x([0-9]+))");

		std::regex_match(_inputLine, m, regex);
		
		return { std::atoi(m[1].str().c_str()), std::atoi(m[2].str().c_str()), std::atoi(m[3].str().c_str())};
	}
	int Day02Puzzle::wrappingArea(const ParsedLine& _line) {
		const int max = std::max(_line.width, std::max(_line.height, _line.length));

		const int area = 2 * (_line.width * _line.height + _line.width * _line.length + _line.height * _line.length);

		const int extra = _line.width * _line.height * _line.length / max;

		return area + extra;
	}
	int Day02Puzzle::ribbonLength(const ParsedLine& _line) {
		const int max = std::max(_line.width, std::max(_line.height, _line.length));

		const int length = _line.width + _line.height + _line.length - max;

		return length * 2 + _line.width * _line.height * _line.length;
	}
}
