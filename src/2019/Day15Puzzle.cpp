#include <2019/Day15Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Orientation.hpp>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cassert>

#define NORTH 1
#define SOUTH 2
#define WEST 3
#define EAST 4

#define STATUS_HIT_WALL 0
#define STATUS_MOVE 1
#define STATUS_HIT_OXYGEN 2

#define DROID 'D'
#define WALL '#'
#define VACANT '.'
#define OXYGEN '@'
#define UNKNOWN '?'
#define START 'S'

namespace TwentyNineteen {

	enum class Type {
		Unkown = 0,
		Droid,
		Wall,
		Vacant,
		Oxygen,
		Start
	};

	struct Droid {

		Droid() {};
		Droid(const Droid& _droid) :
			m(_droid.m),
			position(_droid.position) {
		}

		IntcodeMachine m;
		core::Vector2i position;
	};

	struct Cell {

		Cell() :
			type(Type::Unkown),
			allNeighboursExplored(false),
			cost(0),
			cameFrom(0),
			oxyCost(999999)
		{

		}

		Type type;
		bool allNeighboursExplored;
		int cost;
		int cameFrom;
		int oxyCost;
	};

	class CustomMap {
	public:
		Cell& getCell(int _x, int _y) {
			minY = std::min(minY, _y);
			maxY = std::max(maxY, _y);
			minX = std::min(minX, _x);
			maxX = std::max(maxX, _x);
			const std::string key = std::to_string(_x) + "_" + std::to_string(_y);
			if (cells.find(key) == cells.end()) {
				cells[key] = Cell();
			}
			return cells[key];
		}

		int minY{ 0 };
		int maxY{ 0 };
		int minX{ 0 };
		int maxX{ 0 };
	private:
		std::unordered_map<std::string, Cell> cells;
	};

	using Map = core::Region<Cell>;
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Oxygen System", 2019, 15) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	core::Vector2i getOffsetFromInput(IntcodeValue _input) {
		switch (_input) {
		case NORTH:
			return core::Vector2i(+0, -1);
		case SOUTH:
			return core::Vector2i(+0, +1);
		case EAST:
			return core::Vector2i(+1, +0);
		case WEST:
			return core::Vector2i(-1, +0);
		default:
			throw std::runtime_error("Invalid input");
		}
	}

	IntcodeValue getOppositeInput(IntcodeValue _input) {
		switch (_input) {
		case NORTH:
			return SOUTH;
		case SOUTH:
			return NORTH;
		case EAST:
			return WEST;
		case WEST:
			return EAST;
		default:
			throw std::runtime_error("Invalid input");
		}
	}

	IntcodeValue getResponse(Droid *_droid, IntcodeValue _input) {
		_droid->m.setInput(_input);
		auto response = _droid->m.executeResult();
		assert(response == IntcodeMachine::ExecutionResult::Output);
		return _droid->m.getOutput();
	}

	bool exploreAndReturnSingleDirection(Map& _region, Droid *_droid, IntcodeValue _input) {
		IntcodeValue result = getResponse(_droid, _input);
		core::Vector2i location = _droid->position + getOffsetFromInput(_input);
		Cell& cell = _region.getCell(location.x, location.y);
		if (result == STATUS_HIT_WALL) {
			cell.type = Type::Wall;
		} else if (result == STATUS_MOVE) {
			cell.type = Type::Vacant;
			auto response = getResponse(_droid, getOppositeInput(_input));
			assert(STATUS_MOVE == response);
		} else {
			cell.type = Type::Oxygen;
			cell.cost = _region.getCell(_droid->position.x, _droid->position.y).cost + 1;
			cell.cameFrom = getOppositeInput(_input);
			return false;
		}
		return true;
	}

	std::vector<IntcodeValue> getDirectionsNotExplored(Map& _region, Droid *_droid) {
		std::vector<IntcodeValue> directions;

		Cell& north = _region.getCell(_droid->position.x + 0, _droid->position.y - 1);
		if (north.type == Type::Vacant && !north.allNeighboursExplored) {
			directions.push_back(NORTH);
		}

		Cell& east  = _region.getCell(_droid->position.x + 1, _droid->position.y + 0);
		if (east.type == Type::Vacant && !east.allNeighboursExplored) {
			directions.push_back(EAST);
		}

		Cell& south = _region.getCell(_droid->position.x + 0, _droid->position.y + 1);
		if (south.type == Type::Vacant && !south.allNeighboursExplored) {
			directions.push_back(SOUTH);
		}

		Cell& west  = _region.getCell(_droid->position.x - 1, _droid->position.y + 0);
		if (west.type == Type::Vacant && !west.allNeighboursExplored) {
			directions.push_back(WEST);
		}

		return directions;
	}

	void exploreAllAdjacentCellsAndReturnToStart(Map& _region, Droid *_droid) {
		Cell& current = _region.getCell(_droid->position.x, _droid->position.y);
		current.allNeighboursExplored = true;

		if (exploreAndReturnSingleDirection(_region, _droid, NORTH)) {
			Cell& north = _region.getCell(_droid->position.x + 0, _droid->position.y + 0);
			if (north.cost == -1 && north.cameFrom == -1) {
				north.cost = current.cost + 1;
				north.cameFrom = SOUTH;
			}
		} else {
			return;
		}

		if (exploreAndReturnSingleDirection(_region, _droid, EAST)) {
			Cell& east = _region.getCell(_droid->position.x + 1, _droid->position.y + 0);
			if (east.cost == -1 && east.cameFrom == -1) {
				east.cost = current.cost + 1;
				east.cameFrom = WEST;
			}
		} else {
			return;
		}
		if (exploreAndReturnSingleDirection(_region, _droid, SOUTH)) {
			Cell& south = _region.getCell(_droid->position.x + 0, _droid->position.y + 1);
			if (south.cost == -1 && south.cameFrom == -1) {
				south.cost = current.cost + 1;
				south.cameFrom = NORTH;
			}
		} else {
			return;
		}
		if (exploreAndReturnSingleDirection(_region, _droid, WEST)) {
			Cell& west = _region.getCell(_droid->position.x - 1, _droid->position.y + 0);
			if (west.cost == -1 && west.cameFrom == -1) {
				west.cost = current.cost + 1;
				west.cameFrom = EAST;
			}
		} else {
			return;
		}
	}

	void dumpRegion(Map& _region, const std::vector<Droid *>& _droids) {
		static int iter = 0;
		std::vector<std::string> regionTextVector;
		for (int y = _region.minY; y <= _region.maxY; ++y) {
			std::string regionText;
			for (int x = _region.minX; x <= _region.maxX; ++x) {
				bool found = false;
				for (const Droid*d : _droids) {
					if (d->position.x == x && d->position.y == y) {
						found = true;
						break;
					}
				}
				if (found) {
					regionText += DROID;
					continue;
				}
				if (x == 0 && y == 0) {
					regionText += START;
				} else {
					const auto& cell = _region.getCell(x, y);
					switch (cell.type) {
					case Type::Vacant:
						regionText += VACANT;
						break;
					case Type::Wall:
						regionText += WALL;
						break;
					case Type::Oxygen:
						regionText += OXYGEN;
						break;
					case Type::Unkown:
					default:
						regionText += ' ';
						break;
					}
				}

			}
			regionTextVector.push_back(regionText);
		}

		std::cout << "==================" << iter++ << "====================" << std::endl;
		for (const auto& _row : regionTextVector) {
			std::cout << _row << std::endl;
		}
	}

	void floodFill(Map& _region, core::Vector2i& _start, int _depth) {
		if (_start.y >= _region.minY &&
			_start.y <= _region.maxY &&
			_start.x >= _region.minX &&
			_start.x <= _region.maxX) {
			Cell& c = _region.getCell(_start.x, _start.y);
			if ((c.type == Type::Vacant ||
				c.type == Type::Oxygen ||
				c.type == Type::Start) &&
				c.oxyCost == 0) {

				c.oxyCost = _depth;

				floodFill(_region, _start + getOffsetFromInput(NORTH), _depth + 1);
				floodFill(_region, _start + getOffsetFromInput(SOUTH), _depth + 1);
				floodFill(_region, _start + getOffsetFromInput(EAST), _depth + 1);
				floodFill(_region, _start + getOffsetFromInput(WEST), _depth + 1);

			}
		}
	}

	int findMaxDistanceFromOxygen(Map& _region, core::Vector2i& _start) {
		floodFill(_region, _start, 0);

		int max = 0;

		for (int y = _region.minY; y < _region.maxY; ++y) {
			for (int x = _region.minX; x < _region.maxX; ++x) {
				Cell& c = _region.getCell(x, y);
				if (c.type != Type::Wall) {
					max = std::max(max, c.oxyCost);
				}
			}
		}
		return max;
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		Map region;
		Cell& start = region.getCell(0, 0);
		{
			start.type = Type::Vacant;
			start.cameFrom = 0;
			start.cost = 0;
		}
		Droid* droid = new Droid();
		droid->m.loadProgram(m_InputLines[0]);
		std::vector<Droid*> droids{ droid };

		while (!droids.empty()) {
			for (Droid *droid : std::vector<Droid*>(droids)) {
				exploreAllAdjacentCellsAndReturnToStart(region, droid);
				const auto& directionsToGo = getDirectionsNotExplored(region, droid);
				if (directionsToGo.empty()) {
					droids.erase(std::remove_if(droids.begin(), droids.end(), [droid](const Droid* _d) -> bool { return _d == droid; }), droids.end());
					continue;
				}

				for (unsigned i = 1; i < directionsToGo.size(); ++i) {
					Droid* newDroid = new Droid(*droid);
					newDroid->position += getOffsetFromInput(directionsToGo[i]);
					auto response = getResponse(newDroid, directionsToGo[i]);
					assert(STATUS_MOVE == response);
					droids.push_back(newDroid);
				}

				droid->position += getOffsetFromInput(directionsToGo[0]);
				auto response = getResponse(droid, directionsToGo[0]);
				assert(STATUS_MOVE == response);
			}
		}
		dumpRegion(region, droids);

		for (Droid* d : droids) {
			delete d;
		}

		core::Vector2i startLoc{ 0,0 };
		core::Vector2i oxyLoc;
		bool oxyFound = false;
		for (int y = region.minY; y < region.maxY; ++y) {
			for (int x = region.minX; x < region.maxX; ++x) {
				if (region.getCell(x, y).type == Type::Oxygen) {
					oxyFound = true;
					oxyLoc.x = x;
					oxyLoc.y = y;
					break;
				}
			}
			if (oxyFound) { break; }
		}

		core::Vector2i coord(oxyLoc);
		int part1 = 0;
		Cell current = region.getCell(coord.x, coord.y);
		while (current.cameFrom != 0) {
			auto offset = getOffsetFromInput(current.cameFrom);
			coord += offset;
			current = region.getCell(coord.x, coord.y);
			part1++;
		}

		int part2 = findMaxDistanceFromOxygen(region, oxyLoc);


		return { std::to_string(part1), std::to_string(part2) };
	}
}
