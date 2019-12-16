#include <2019/Day15Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Orientation.hpp>
#include <unordered_set>
#include <algorithm>
#include <cassert>

#define NORTH 1
#define SOUTH 2
#define WEST 3
#define EAST 4

#define STATUS_HIT_WALL 0
#define STATUS_MOVE 1
#define STATUS_MOVE_ARRIVE 2

#define DROID 'D'
#define WALL '#'
#define VACANT '.'
#define OXYGEN '*'
#define UNKNOWN '?'
#define START 'S'

namespace TwentyNineteen {

	core::Vector2i Day15Puzzle::oxyLocation{ 99999, -999999 };

	static bool found = false;

	struct Cell {

		Cell() :
		value(UNKNOWN),
		allNeighboursExplored(false),
		isDeadEnd(false),
		cost(0),
		cameFrom(0),
		oxyCost(999999) {

		}

		char value{ UNKNOWN };

		bool allNeighboursExplored{ false };

		bool isDeadEnd{ false };

		int cost{ 0};

		IntcodeValue cameFrom{ 0 };
		int oxyCost{ 999999 };

	};
	
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

	void dumpRegion(core::Region<Cell>& _region, core::Vector2i _droid) {
		std::cout << "=================" << std::endl;
		for (int y = _region.minY; y <= _region.maxY; ++y) {
			for (int x = _region.minX; x <= _region.maxX; ++x) {
				if (_droid.x == x && _droid.y == y) {
					std::cout << DROID;
				} else if (x == 0 && y == 0) {
					std::cout << START;
				} else  {
					std::cout << _region.getCell(x, y).value;
				}
			}
			std::cout << std::endl;
		}
	}

	void appendNonVisitedNeighbourToQueue(const core::Vector2i& _location, std::queue<core::Vector2i>& _queue, const std::unordered_set<core::Vector2i, core::vector2_hash_fxn>& _visited) {

		if (_visited.count(_location + core::Vector2i(+0, -1)) == 0) {
			// NORTH
			_queue.push(_location + core::Vector2i(+0, -1));
			return;
		}
		if (_visited.count(_location + core::Vector2i(+0, +1)) == 0) {
			// SOUTH
			_queue.push(_location + core::Vector2i(+0, +1));
			return;
		}
		if (_visited.count(_location + core::Vector2i(+1, +0)) == 0) {
			// EAST
			_queue.push(_location + core::Vector2i(+1, +0));
			return;
		}
		if (_visited.count(_location + core::Vector2i(-1, +0)) == 0) {
			// WEST
			_queue.push(_location + core::Vector2i(-1, +0));
			return;
		}

	}

	bool areAllNeighboursWallsOrOfLowerCost(const core::Vector2i& _location, core::Region<Cell>& _region) {
		Cell& current = _region.getCell(_location.x, _location.y);

		if (!current.allNeighboursExplored) {
			return false;
		}

		auto& north = _region.getCell(_location.x + 0, _location.y - 1);
		auto& south = _region.getCell(_location.x + 0, _location.y + 1);
		auto& east = _region.getCell(_location.x + 1, _location.y + 0);
		auto& west = _region.getCell(_location.x - 1, _location.y + 0);

		if ((north.value == WALL || north.cost < current.cost) &&
			(south.value == WALL || south.cost < current.cost) &&
			(east.value == WALL || east.cost < current.cost) &&
			(west.value == WALL || west.cost < current.cost)) {
			return true;
		}

		return false;
	}

	void appendNonVisitedNeighbourToQueue(const core::Vector2i& _location, std::queue<IntcodeValue>& _queue, const std::unordered_set<core::Vector2i, core::vector2_hash_fxn>& _visited, core::Region<Cell>& _region) {

		if (_visited.count(_location + core::Vector2i(+0, -1)) == 0) {
			// NORTH
			_queue.push(NORTH);
			return;
		}
		if (_visited.count(_location + core::Vector2i(+0, +1)) == 0) {
			// SOUTH
			_queue.push(SOUTH);
			return;
		}
		if (_visited.count(_location + core::Vector2i(+1, +0)) == 0) {
			// EAST
			_queue.push(EAST);
			return;
		}
		if (_visited.count(_location + core::Vector2i(-1, +0)) == 0) {
			// WEST
			_queue.push(WEST);
			return;
		}

		std::cout << "Failed to append a non visited neighbour, falling back to neighbour that is vacant" << std::endl;

		auto& north = _region.getCell(_location.x + 0, _location.y - 1);
		auto& south = _region.getCell(_location.x + 0, _location.y + 1);
		auto& east  = _region.getCell(_location.x + 1, _location.y + 0);
		auto& west  = _region.getCell(_location.x - 1, _location.y + 0);

		int valid = 0;
		if (north.value == VACANT && !north.isDeadEnd) {
			valid++;
		}
		if (south.value == VACANT && !south.isDeadEnd) {
			valid++;
		}
		if (east.value == VACANT && !east.isDeadEnd) {
			valid++;
		}
		if (west.value == VACANT && !west.isDeadEnd) {
			valid++;
		}
		if (valid == 1) {
			{
				if (north.value == VACANT) {
					// NORTH
					_queue.push(NORTH);
					return;
				}
			}
			{
				if (south.value == VACANT) {
					// SOUTH
					_queue.push(SOUTH);
					return;
				}
			}
			{
				if (east.value == VACANT) {
					// EAST
					_queue.push(EAST);
					return;
				}
			}
			{
				if (west.value == VACANT) {
					// WEST
					_queue.push(WEST);
					return;
				}
			}
		} else {
			// We have multiple open ones, choose by highest cost

			std::cout << "Choosing the best cost as all neighbours have been visited" << std::endl;

			auto cost = north.cost;
			IntcodeValue inputToReturn = NORTH;

			if (cost < south.cost) {
				cost = south.cost;
				inputToReturn = SOUTH;
			}
			if (cost < east.cost) {
				cost = east.cost;
				inputToReturn = EAST;
			}
			if (cost < west.cost) {
				cost = west.cost;
				inputToReturn = WEST;
			}
			_queue.push(inputToReturn);
			return;
		}

		std::cout << "Failed to append a visited vacant neighbour" << std::endl;
	}

	IntcodeValue getStatus(IntcodeValue _input, IntcodeMachine& _m) {
		_m.setInput(_input);
		
		auto res = _m.executeResult();

		assert(res == IntcodeMachine::ExecutionResult::Output);

		return _m.getOutput();
	}

	bool haveAllNeighboursBeenVisited(const core::Vector2i& _position, const std::unordered_set<core::Vector2i, core::vector2_hash_fxn>& _visited) {
		return
			_visited.count(_position + core::Vector2i(+1, +0)) > 0 &&
			_visited.count(_position + core::Vector2i(-1, +0)) > 0 &&
			_visited.count(_position + core::Vector2i(+0, +1)) > 0 &&
			_visited.count(_position + core::Vector2i(+0, -1)) > 0;
	}

	IntcodeValue getInputFromPositionAndTarget(const core::Vector2i& _position, const core::Vector2i& _target) {
		const auto offset = _target - _position;

		if (offset == core::Vector2i{ 0, -1 }) {
			// going up is north
			return NORTH;
		}
		if (offset == core::Vector2i{ 0, +1 }) {
			// going down is south
			return SOUTH;
		}
		if (offset == core::Vector2i{ -1, 0 }) {
			// going left is west
			return WEST;
		}
		if (offset == core::Vector2i{ +1, 0 }) {
			// going right is east
			return EAST;
		}

		throw std::runtime_error("Invalid target position");
	}

	IntcodeValue getReverseInput(IntcodeValue _input) {
		if (_input == NORTH) {
			return SOUTH;
		}
		if (_input == SOUTH) {
			return NORTH;
		}
		if (_input == EAST) {
			return WEST;
		}
		if (_input == WEST) {
			return EAST;
		}

		throw std::runtime_error("Invalid input");
	}

	std::string inputToFriendy(IntcodeValue _input) {
		if (_input == NORTH) {
			return "NORTH";
		}
		if (_input == SOUTH) {
			return "SOUTH";
		}
		if (_input == EAST) {
			return "EAST";
		}
		if (_input == WEST) {
			return "WEST";
		}

		throw std::runtime_error("Invalid input");
	}

	core::Vector2i getOffsetFromInput(IntcodeValue _input) {
		if (_input == NORTH) {
			return core::Vector2i{ 0,-1 };
		}
		if (_input == SOUTH) {
			return core::Vector2i{ 0,+1 };
		}
		if (_input == EAST) {
			return core::Vector2i{ +1,0 };
		}
		if (_input == WEST) {
			return core::Vector2i{ -1,0 };
		}

		throw std::runtime_error("Invalid input");
	}
	void clearInputBuffer() // works only if the input buffer is not empty
	{
		char c;
		do {
			c = getchar();
		} while (c != '\n' && c != EOF);
	}

	void moveDirectionReturnIfVacant(IntcodeMachine& _m, core::Region<Cell>& _region, std::unordered_set<core::Vector2i, core::vector2_hash_fxn>& _visited, IntcodeValue _direction, core::Vector2i _location) {

		auto status = getStatus(_direction, _m);
		auto newLoc = _location + getOffsetFromInput(_direction);

		if (newLoc == Day15Puzzle::oxyLocation) {
			return;
		}

		auto& cell = _region.getCell(newLoc.x, newLoc.y);
		auto& current = _region.getCell(_location.x, _location.y);
		_visited.insert(newLoc);

		if (status == STATUS_HIT_WALL) {
			cell.value = WALL;
		}
		else if (status == STATUS_MOVE) {
			cell.value = VACANT;
			auto status = getStatus(getReverseInput(_direction), _m);
			assert(status == STATUS_MOVE || status == STATUS_MOVE_ARRIVE);
		} else if (status == STATUS_MOVE_ARRIVE) {
			Day15Puzzle::oxyLocation = newLoc;
			_region.getCell(newLoc.x, newLoc.y).value = OXYGEN;
			found = true;
		}
	}

	void moveAllDirectionsReturnIfVacant(IntcodeMachine& _m, core::Region<Cell>& _region, std::unordered_set<core::Vector2i, core::vector2_hash_fxn>& _visited, core::Vector2i _location) {
		moveDirectionReturnIfVacant(_m, _region, _visited, NORTH, _location);
		moveDirectionReturnIfVacant(_m, _region, _visited, EAST, _location);
		moveDirectionReturnIfVacant(_m, _region, _visited, SOUTH, _location);
		moveDirectionReturnIfVacant(_m, _region, _visited, WEST, _location);

		auto& current = _region.getCell(_location.x, _location.y);

		auto& north = _region.getCell(_location.x + 0, _location.y - 1);
		if (north.cameFrom == -1) {
			north.cameFrom = SOUTH;
			north.cost = current.cost + 1;
		}
		auto& south = _region.getCell(_location.x + 0, _location.y + 1);
		if (south.cameFrom == -1) {
			south.cameFrom = NORTH;
			south.cost = current.cost + 1;
		}
		auto& east = _region.getCell(_location.x + 1, _location.y + 0);
		if (east.cameFrom == -1) {
			east.cameFrom = WEST;
			east.cost = current.cost + 1;
		}
		auto& west = _region.getCell(_location.x - 1, _location.y + 0);
		if (west.cameFrom == -1) {
			west.cameFrom = EAST;
			west.cost = current.cost + 1;
		}

		_region.getCell(_location.x, _location.y).allNeighboursExplored = true;
	}


	void appendVacantCellToQueue(const core::Vector2i& _location, std::queue<IntcodeValue>& _queue, const std::unordered_set<core::Vector2i, core::vector2_hash_fxn>& _visited, core::Region<Cell>& _region) {
		auto& current = _region.getCell(_location.x, _location.y);
		auto& north = _region.getCell(_location.x + 0, _location.y - 1);
		auto& south = _region.getCell(_location.x + 0, _location.y + 1);
		auto& east = _region.getCell(_location.x + 1, _location.y + 0);
		auto& west = _region.getCell(_location.x - 1, _location.y + 0);

		if (north.value == VACANT &&
			!north.allNeighboursExplored) {
			_queue.push(NORTH);
			return;
		}
		if (south.value == VACANT &&
			!south.allNeighboursExplored) {
			_queue.push(SOUTH);
			return;
		}
		if (east.value == VACANT &&
			!east.allNeighboursExplored) {
			_queue.push(EAST);
			return;
		}
		if (west.value == VACANT &&
			!west.allNeighboursExplored) {
			_queue.push(WEST);
			return;
		}

		current.isDeadEnd = true;
		_queue.push(current.cameFrom);
	}

	void floodFillOxygen(core::Region<Cell>& _region, core::Vector2i _loc, int _cost, int& _max) {
		auto& cell = _region.getCell(_loc.x, _loc.y);
		if (cell.value == WALL || 
			cell.value == 0 ||
			cell.oxyCost != 0) {
			return;
		}

		if (cell.oxyCost == 0) {
			cell.oxyCost = _cost;
			_max = std::max(_max, cell.oxyCost);
			floodFillOxygen(_region, _loc + getOffsetFromInput(NORTH), _cost + 1, _max);
			floodFillOxygen(_region, _loc + getOffsetFromInput(EAST), _cost + 1, _max);
			floodFillOxygen(_region, _loc + getOffsetFromInput(SOUTH), _cost + 1, _max);
			floodFillOxygen(_region, _loc + getOffsetFromInput(WEST), _cost + 1, _max);
		}
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {

		IntcodeMachine m{};
		m.loadProgram(m_InputLines[0]);

		int targetDirection = 1;

		std::unordered_set<core::Vector2i, core::vector2_hash_fxn> visited;
		core::Vector2i position{ 0,0 };
		core::Region<Cell> region;
		region.getCell(position.x, position.y).value = VACANT;
		region.getCell(position.x, position.y).cost = 0;
		visited.insert(position);

		dumpRegion(region, position);
		//getchar();

		bool userInput = false;
		bool wasJustSentBack = false;

		std::queue<IntcodeValue> inputs;

		auto exploreCurrentLocation = [&]() -> void {
			if (!region.getCell(position.x, position.y).allNeighboursExplored) {
				moveAllDirectionsReturnIfVacant(m, region, visited, position);
			}
			//dumpRegion(region, position); 
		};

		int iter = 0;

		while (!found){
			exploreCurrentLocation();
			appendVacantCellToQueue(position, inputs, visited, region);
			if (inputs.empty()) {
				break;
			}

			if (iter > 1300) {
				dumpRegion(region, position);
				std::cout << "iter: " << iter << ", input: " << inputToFriendy(inputs.front()) << std::endl;
				
				break;
			}

			auto input = inputs.front();
			inputs.pop();
			auto status = getStatus(input, m);
			assert(STATUS_MOVE == status || STATUS_MOVE_ARRIVE == status);
			position += getOffsetFromInput(input);
			iter++;
		};
		int max = 0;
		auto& oxyCell = region.getCell(Day15Puzzle::oxyLocation.x, Day15Puzzle::oxyLocation.y);
		oxyCell.value = OXYGEN;
		floodFillOxygen(region, { Day15Puzzle::oxyLocation }, 1, max);
		std::cout << "MAX: " << max << std::endl;

		dumpRegion(region, position);
		return { std::to_string(oxyCell.cost), std::to_string(max) };




		while (!inputs.empty() || userInput) {

			if (userInput) {
				system("cls");
				dumpRegion(region, position);
			} else {
				system("cls");
				dumpRegion(region, position);
				
				getchar();
			}



			if (userInput) {
				std::cout << "Enter Input: ";
				int input = getchar();
				clearInputBuffer();
				if (input == (int)'N') {
					targetDirection = NORTH;
				} else if (input == (int)'S') {
					targetDirection = SOUTH;
				} else if (input == (int)'E') {
					targetDirection = EAST;
				} else if (input == (int)'W') {
					targetDirection = WEST;
				}
			} else {
				targetDirection = inputs.front();
				inputs.pop();
			}

			auto loc = position + getOffsetFromInput(targetDirection);

			visited.insert(loc);

			auto status = getStatus(targetDirection, m);

			if (status == STATUS_HIT_WALL) {
				auto& cell = region.getCell(loc.x, loc.y);
				cell.value = WALL;
				if (!userInput) {
					if (inputs.empty()) {
						// Hit a wall, check if we are in a dead end.
						if (haveAllNeighboursBeenVisited(position, visited)) {
							// All have been visited
							auto& pastCell = region.getCell(position.x, position.y);
							pastCell.allNeighboursExplored = true;
							std::cout << "We have hit a wall, and we have explored everywhere around us" << std::endl;
						}

						// Hit Wall and nothing left to do.
						appendNonVisitedNeighbourToQueue(position, inputs, visited, region);


					}
				}
			} 
			else if (status == STATUS_MOVE) {
				auto& pastCell = region.getCell(position.x, position.y);
				auto& cell = region.getCell(loc.x, loc.y);
				cell.value = VACANT;


				pastCell.isDeadEnd = areAllNeighboursWallsOrOfLowerCost(loc, region);

				if (cell.cost == 0) {
					cell.cost = std::max(cell.cost, pastCell.cost + 1);
				}

				if (!userInput) {
					if (haveAllNeighboursBeenVisited(position, visited) || wasJustSentBack) {
						wasJustSentBack = false;
						// All good, carry on, put random direction in the queue
						appendNonVisitedNeighbourToQueue(loc, inputs, visited, region);
						auto& cell = region.getCell(position.x, position.y);
						cell.allNeighboursExplored = true;
					} else {
						// Go back
						auto reverse = getReverseInput(targetDirection);
						auto offset = getOffsetFromInput(reverse);

						auto nextLocation = loc + offset;
						auto& cell = region.getCell(nextLocation.x, nextLocation.y);
						if (cell.allNeighboursExplored) {
							// Dont go back...
							appendNonVisitedNeighbourToQueue(position, inputs, visited, region);
						} else {
							// Go back and explore everything
							inputs.push(reverse);
							wasJustSentBack = true;
						}
					}
				}
				position = loc;
			}
			else {
				assert(false);
			}
		}

		return { "Part 1", "Part 2" };
	}
}
