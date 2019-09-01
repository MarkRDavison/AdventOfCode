#include <2015/Day03Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>

namespace TwentyFifteen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Perfectly Spherical Houses in a Vacuum", 2015, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {

		core::Vector2i loc = { 0,0 };

		std::unordered_map<core::Vector2i, int, core::vector2_hash_fxn> visitedLocations;
		visitedLocations[loc]++;
		std::unordered_map<core::Vector2i, int, core::vector2_hash_fxn> visitedLocations2;
		visitedLocations2[loc]++;

		core::Vector2i locPart2[2];
		unsigned index = 0;

		for (auto& c : m_InputLines[0]) {
			auto direction = charToDirection(c);

			// Part 1
			loc += direction;
			visitedLocations[loc]++;

			// Part 2
			locPart2[index] += direction;
			visitedLocations2[locPart2[index]]++;

			index++;
			index = index % 2;
		}

		return {
			std::to_string(visitedLocations.size()),
			std::to_string(visitedLocations2.size())
		};
	}
	core::Vector2i Day03Puzzle::charToDirection(char _c) {
		switch (_c) {
		case Up:
			return { 0, +1 };
		case Down:
			return { 0, -1 };
		case Right:
			return { +1, 0 };
		case Left:
			return { -1, 0 };
		default:
			return { 0, 0 };
		}
	}
}
