#include <2019/Day24Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <set>

#define SIZE 5

namespace TwentyNineteen {

	struct Day24Cell {
		bool bug{ false };
		unsigned adjacent{ 0 };
	};
	struct ErisGrid {
		std::vector<std::vector<Day24Cell>> grid;
		bool hasBugs{ false };
	};
	using Eris = std::unordered_map<int, ErisGrid>;

	
	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Planet of Discord", 2019, 24) {

	}
	Day24Puzzle::~Day24Puzzle() {

	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void dump(const ErisGrid& _eris) {
		for (const auto& _row : _eris.grid) {
			for (const auto cell : _row) {
				std::cout << (cell.bug == true ? '#' : '.');
			}
			std::cout << std::endl;
		}
	}

	std::string getStateString(const ErisGrid& _eris) {
		std::string s;

		for (const auto& _row : _eris.grid) {
			for (const auto cell : _row) {
				s += cell.bug ? '#' : '.';
			}
		}

		return s;
	}

	unsigned getAdjacentBugs(const ErisGrid& _eris, unsigned _x, unsigned _y) {
		unsigned adjacent = 0;

		const unsigned w = _eris.grid[0].size();
		const unsigned h = _eris.grid.size();

		// TM
		if (_y > 0) {
			if (_eris.grid[_y - 1][_x].bug) {
				adjacent++;
			}
		}
		// ML
		if (_x > 0) {
			if (_eris.grid[_y][_x - 1].bug) {
				adjacent++;
			}
		}
		// MR
		if (_x < w - 1) {
			if (_eris.grid[_y][_x + 1].bug) {
				adjacent++;
			}
		}
		// BM
		if (_y < h - 1) {
			if (_eris.grid[_y + 1][_x].bug) {
				adjacent++;
			}
		}

		return adjacent;
	}

	long long calculateBiodiversity(const ErisGrid& _eris) {
		long long bio = 0;
		long long power = 0;
		for (unsigned y = 0; y < _eris.grid.size(); ++y) {
			for (unsigned x = 0; x < _eris.grid[y].size(); ++x) {
				if (_eris.grid[y][x].bug) {
					auto cellBio = std::pow(2, power);
					bio += cellBio;
				}
				power++;
			}
		}
		return bio;
	}

	void updateBugs(ErisGrid& _eris) {
		for (unsigned y = 0; y < _eris.grid.size(); ++y) {
			for (unsigned x = 0; x < _eris.grid[y].size(); ++x) {
				auto& cell = _eris.grid[y][x];
				if (cell.bug) {
					if (cell.adjacent != 1) {
						cell.bug = false;
					} else {
						cell.bug = true;
					}
				} else {
					if (cell.adjacent == 1 || cell.adjacent == 2) {
						cell.bug = true;
					} else {
						cell.bug = false;
					}
				}
				cell.adjacent = 0;
			}
		}
	}

	void simulate(ErisGrid& _eris) {
		for (unsigned y = 0; y < _eris.grid.size(); ++y) {
			for (unsigned x = 0; x < _eris.grid[y].size(); ++x) {
				auto& cell = _eris.grid[y][x];
				cell.adjacent = getAdjacentBugs(_eris, x, y);
			}
		}

		updateBugs(_eris);
	}

	std::string Day24Puzzle::getPart1() {
		ErisGrid eris;
		std::set<std::string> duplicateSet;
		unsigned bufferIndex = 0;

		for (const auto& line : m_InputLines) {
			auto& row = eris.grid.emplace_back();
			for (const char c : line) {
				auto& cell = row.emplace_back();
				cell.bug = c == '#';
			}
		}
		long long bio1 = 0;
		dump(eris);
		duplicateSet.insert(getStateString(eris));
		unsigned i = 0;
		while (true) {
			simulate(eris);
			std::string state = getStateString(eris);
			if (duplicateSet.find(state) != duplicateSet.end()) {
				for (unsigned j = 0; j < 5; ++j) {
				}
				bio1 = calculateBiodiversity(eris);
				break;
			} else {
				duplicateSet.insert(state);
			}
			i++;
		}

		return std::to_string(bio1);
	}

	void ensureGridExistsAtLevel(Eris& _eris, int _level) {
		auto& grid = _eris[_level];
		if (grid.grid.empty()) {
			for (unsigned y = 0; y < SIZE; ++y) {
				auto& row = grid.grid.emplace_back();
				for (unsigned x = 0; x < SIZE; ++x) {
					auto& cell = row.emplace_back();
					cell.adjacent = 0;
					cell.bug = false;
				}
			}
		}
	}

	unsigned hasBug(Eris& _eris, int _level, unsigned _x, unsigned _y) {
		ensureGridExistsAtLevel(_eris, _level);
		auto& grid = _eris[_level];

		return grid.grid[_y][_x].bug ? 1 : 0;
	}

	unsigned getAdjacentRecursive(Eris& _eris, int _level, unsigned _x, unsigned _y) {

		ErisGrid& grid = _eris[_level];

		unsigned adj = 0;

		// TOP
		if (_y == 0) {
			// Get recursive at level - 1
			adj += hasBug(_eris, _level - 1 , 2, 1);
		}
		else if (_y == 3 && _x == 2)  {
			// Get recursive at level + 1
			adj += hasBug(_eris, _level + 1, 0, 4);
			adj += hasBug(_eris, _level + 1, 1, 4);
			adj += hasBug(_eris, _level + 1, 2, 4);
			adj += hasBug(_eris, _level + 1, 3, 4);
			adj += hasBug(_eris, _level + 1, 4, 4);
		}
		else {
			// No recursion needed
			adj += hasBug(_eris, _level + 0, _x, _y - 1);
		}

		// LEFT
		if (_x == 0) {
			// Get recursive at level - 1
			adj += hasBug(_eris, _level - 1, 1, 2);
		}
		else if (_x == 3 && _y == 2) {
			// Get recursive at level + 1
			adj += hasBug(_eris, _level + 1, 4, 0);
			adj += hasBug(_eris, _level + 1, 4, 1);
			adj += hasBug(_eris, _level + 1, 4, 2);
			adj += hasBug(_eris, _level + 1, 4, 3);
			adj += hasBug(_eris, _level + 1, 4, 4);
		}
		else {
			// No recursion needed
			adj += hasBug(_eris, _level + 0, _x - 1, _y);
		}

		// RIGHT
		if (_x == SIZE - 1) {
			// Get recursive at level - 1
			adj += hasBug(_eris, _level - 1, 3, 2);
		}
		else if (_x == 1 && _y == 2) {
			// Get recursive at level + 1
			adj += hasBug(_eris, _level + 1, 0, 0);
			adj += hasBug(_eris, _level + 1, 0, 1);
			adj += hasBug(_eris, _level + 1, 0, 2);
			adj += hasBug(_eris, _level + 1, 0, 3);
			adj += hasBug(_eris, _level + 1, 0, 4);
		} else {
			// No recursion needed
			adj += hasBug(_eris, _level + 0, _x + 1, _y);
		}

		// BOTTOM
		if (_y == SIZE - 1) {
			// Get recursive at level - 1
			adj += hasBug(_eris, _level - 1, 2, 3);
		} else if (_x == 2 && _y == 1) {
			// Get recursive at level + 1
			adj += hasBug(_eris, _level + 1, 0, 0);
			adj += hasBug(_eris, _level + 1, 1, 0);
			adj += hasBug(_eris, _level + 1, 2, 0);
			adj += hasBug(_eris, _level + 1, 3, 0);
			adj += hasBug(_eris, _level + 1, 4, 0);
		} else {
			// No recursion needed
			adj += hasBug(_eris, _level + 0, _x, _y + 1);
		}

		return adj;
	}

	void calculateAdjacentRecursive(Eris& _eris, int _level) {
		ensureGridExistsAtLevel(_eris, _level);
		auto& grid = _eris[_level];
		grid.hasBugs = false;
		for (unsigned y = 0; y < SIZE; ++y) {
			for (unsigned x = 0; x < SIZE; ++x) {
				if (x == 2 && y == 2) { continue; }
				auto& cell = grid.grid[y][x];
				cell.adjacent = getAdjacentRecursive(_eris, _level, x, y);
				if (cell.adjacent > 0) {
					grid.hasBugs = true;
				}
			}
		}
	}

	std::pair<int, int> getMinMaxLevels(Eris& _eris) {
		auto min = (*std::min_element(_eris.begin(), _eris.end(),
			[](const auto& _lhs, const auto& _rhs) -> int {
				return _lhs.first < _rhs.first;
			})).first;
		auto max = (*std::max_element(_eris.begin(), _eris.end(),
			[](const auto& _lhs, const auto& _rhs) -> int {
				return _lhs.first < _rhs.first;
			})).first;

		return { min, max };
	}

	void simulateRecursive(Eris& _eris) {
		auto levels = getMinMaxLevels(_eris);
		for (int l = levels.first - 1; l <= levels.second + 1; ++l) {
			calculateAdjacentRecursive(_eris, l);
		}
		for (int l = levels.first - 1; l <= levels.second + 1; ++l) {
			updateBugs(_eris[l]);
		}
	}

	unsigned getBugsOnLevel(Eris& _eris, int _level) {
		if (_eris.find(_level) == _eris.end() ){
			return 0;
		}
		unsigned b = 0;
		auto& grid = _eris[_level];
		for (unsigned y = 0; y < SIZE; ++y) {
			for (unsigned x = 0; x < SIZE; ++x) {
				if (x == 2 && y == 2) { continue; }
				auto& cell = grid.grid[y][x];
				if (cell.bug) {
					b++;
				}
			}
		}
		return b;
	}

	std::string Day24Puzzle::getPart2(unsigned _minutes) {
		Eris eris;

		auto& erisZero = eris[0];
		erisZero.hasBugs = true;
		for (const auto& line : m_InputLines) {
			auto& row = erisZero.grid.emplace_back();
			for (const char c : line) {
				auto& cell = row.emplace_back();
				cell.bug = c == '#';
			}
		}
		auto bvb = getBugsOnLevel(eris, 0);
		for (unsigned i = 0; i < _minutes; ++i) {
			simulateRecursive(eris);
		}


		auto levels = getMinMaxLevels(eris);
		unsigned bugs = 0;
		for (int l = levels.first - 1; l <= levels.second + 1; ++l) {
			bugs += getBugsOnLevel(eris, l);
		}

		return std::to_string(bugs);
	}
	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		return { getPart1() , getPart2(200) };
	}
}
