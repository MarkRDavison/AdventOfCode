#include <2015/Day03Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {

	constexpr const char U = '^';
	constexpr const char D = 'v';
	constexpr const char L = '<';
	constexpr const char R = '>';

	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Perfectly Spherical Houses in a Vacuum", 2015, 3) {

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
		return { 
			std::to_string(getResult(visitLocations(m_InputLines[0], 1))),
			std::to_string(getResult(visitLocations(m_InputLines[0], 2)))
		};
	}

	core::Orientation Day03Puzzle::getOrientation(char _c) {
		switch (_c) {
		case U:
			return core::Orientation::Up;
		case D:
			return core::Orientation::Down;
		case L:
			return core::Orientation::Left;
		case R:
			return core::Orientation::Right;
		default:
			return core::Orientation::None;
		}
	}
	Day03Puzzle::VisitMap Day03Puzzle::visitLocations(const std::string& _directions, unsigned _santas) {
		VisitMap visitMap;
		std::vector<ze::Vector2i> locs(_santas, ze::Vector2i());
		unsigned santaIndex = 0;
		visitMap[ze::Vector2i()]++;

		for (char c : _directions) {
			core::Orientation o = getOrientation(c);
			auto& loc = locs[santaIndex];

			loc += core::OrientationHelper::toDirection(o);
			visitMap[loc]++;

			santaIndex = (santaIndex + 1) % _santas;
		}

		return visitMap;
	}

	int Day03Puzzle::getResult(const VisitMap& _map) {
		return static_cast<int>(_map.size());
	}
}
