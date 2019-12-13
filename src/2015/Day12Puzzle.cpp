#include <2015/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <json/json.hpp>

using json = nlohmann::json;

namespace TwentyFifteen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("", 2015, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long sumRecurse(const json& _j, bool _excludeRed) {
		auto jstr = _j.dump();
		long total = 0;

		throw std::runtime_error("TODO");
		
		return total;
	}

	long Day12Puzzle::sumNumbersBasic(const std::string& _jsonInput) {
		json j =  json::parse(_jsonInput);
		
		return sumRecurse(j, false);
	}
	long Day12Puzzle::sumNumbersExcludingRed(const std::string& _jsonInput) {
		json j = json::parse(_jsonInput);

		return sumRecurse(j, true);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {

		long part1 = sumNumbersBasic(m_InputLines[0]);
		long part2 = sumNumbersExcludingRed(m_InputLines[0]);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
