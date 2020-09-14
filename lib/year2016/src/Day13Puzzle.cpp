#include <2016/Day13Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("A Maze of Twisty Little Cubicles", 2016, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		core::CartesianNetwork<OfficeCell> network;
		const OfficeInteger number = std::stoi(m_InputLines[0]);
		const ze::Vector2<OfficeInteger> size = { 1000, 1000 };
		const ze::Vector2<OfficeInteger> start = { 1, 1 };
		const ze::Vector2<OfficeInteger> goal = { 31, 39 };

		Day13Puzzle::searchSpace(network, number, size);
		const auto& path = network.performAStarSearch(start, goal);

		const auto part1 = Day13Puzzle::pathLength(network, start, goal);

		const auto& searched = internal::breadthFirstSearchWithMaxSteps(network.cg, start, 50);

		return { std::to_string(part1), std::to_string(searched.size()) };
	}

	bool Day13Puzzle::getTraversable(const ze::Vector2<OfficeInteger>& _location, OfficeInteger _number) {
		OfficeInteger v = _location.x * _location.x + 3 * _location.x + 2 * _location.x * _location.y + _location.y + _location.y * _location.y + _number;

		bool space = true;

		while (v) {
			space = !space;
			v = v & (v - 1);
		}

		return space;
	}
	void Day13Puzzle::searchSpace(core::CartesianNetwork<OfficeCell>& _network, OfficeInteger _number, const ze::Vector2<OfficeInteger>& _maxSize) {
		for (OfficeInteger y = 0; y < _maxSize.y; ++y) {
			auto& row = _network.getCells().emplace_back();
			for (OfficeInteger x = 0; x < _maxSize.x; ++x) {
				auto& cell = row.emplace_back();
				cell.open = getTraversable({ x, y }, _number);
			}
		}
	}
	int Day13Puzzle::pathLength(core::CartesianNetwork<OfficeCell>& _network, const ze::Vector2<OfficeInteger>& _start, const ze::Vector2<OfficeInteger>& _end) {
		return _network.performAStarSearch(_start, _end).size() - 1;
	}
}
