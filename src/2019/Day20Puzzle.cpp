#include <2019/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Pathfinding.hpp>
#include <Core/Vector2.hpp>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>



namespace TwentyNineteen {

	struct PositionWithDepth {
		core::Vector2i position;
		int depth;

		bool operator==(const PositionWithDepth& _other) const {
			return
				position == _other.position &&
				depth == _other.depth;
		}

		bool operator!=(const PositionWithDepth& _other) const {
			return !(*this == _other);
		}
	};

	struct PositionWithDepthHashStruct {
		std::size_t operator()(const PositionWithDepth& _obj) const {
			return std::hash<int>()(_obj.position.x) ^ std::hash<int>()(_obj.position.y) ^ std::hash<int>()(_obj.depth);
		}
	};

	struct DonutCell {
		char c;
		char portal{ 0 };
		std::pair<char, char> portalKey;
	};

	bool isOnOuterEdge(int width, int height, core::Vector2i _position) {
		if (_position.x == 0 ||
			_position.y == 0 ||
			_position.x == width - 1 ||
			_position.y == height - 1) {
			return true;
		}
		return false;
	}

	using PortalLocations = std::map<std::pair<char, char>, std::unordered_set<core::Vector2i, core::vector2_hash_fxn>>;
	using DonutMap = std::vector<std::vector<DonutCell>>;

	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Donut Maze", 2019, 20) {

	}
	Day20Puzzle::~Day20Puzzle() {

	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void dump(const std::vector<std::vector<DonutCell>>& _map, PortalLocations& _portals) {

		for (unsigned y = 0; y < _map.size(); ++y) {
			for (unsigned x = 0; x < _map[y].size(); ++x) {
				const DonutCell& cell = _map[y][x];
				if (cell.portal != 0) {
					std::cout << cell.portal;
				}
				else {
					assert(cell.c == '.' ||
						cell.c == '#' ||
						cell.c == ' ');
					std::cout << cell.c;
				}
			}
			std::cout << std::endl;
		}
	}

	std::pair<char, char> makePortalPair(char _1, char _2) {
		return std::make_pair(std::min(_1, _2), std::max(_1, _2));
	}

	std::vector<PositionWithDepth> enumerate(core::Vector2i _current, const std::vector<std::vector<DonutCell>>& _map, PortalLocations& _portals, int _depth, int _depthIncrement) {
		std::vector<PositionWithDepth> possible;

		const auto& currentCell = _map[_current.y][_current.x];

		if (_current.y != 0) {
			const auto& cell = _map[_current.y - 1][_current.x];
			if (cell.c == '.') {
				possible.push_back({ { _current.x, _current.y - 1 }, _depth });
			}
		}
		if (_current.y < _map.size() - 1) {
			const auto& cell = _map[_current.y + 1][_current.x];
			if (cell.c == '.') {
				possible.push_back({{ _current.x, _current.y + 1 }, _depth });
			}
		}
		if (_current.x != 0) {
			const auto& cell = _map[_current.y][_current.x - 1];
			if (cell.c == '.') {
				possible.push_back({{ _current.x - 1, _current.y }, _depth });
			}
		}
		if (_current.x  < _map[0].size() - 1) {
			const auto& cell = _map[_current.y][_current.x + 1];
			if (cell.c == '.') {
				possible.push_back({ { _current.x + 1, _current.y }, _depth });
			}
		}

		if (currentCell.portal != 0) {
			const auto& portalLocInfo = _portals[currentCell.portalKey];
			for (const auto& portalEndPoint : portalLocInfo) {
				if (portalEndPoint != _current) {
					int newDepth = _depth;
					if (_depth == 0) {
						if (currentCell.portalKey == std::make_pair('A', 'A') ||
							currentCell.portalKey == std::make_pair('Z', 'Z')) {
							// Entrance/Exit on recursive maps don't exist
							continue;
						}
						else if (isOnOuterEdge(_map[0].size(), _map.size(), _current)) {
							if (_depthIncrement != 0) {
								// We are at an outer portal, with part 2 mode, so they are walls, only A/Z allow exiting
								continue;
							}
						}
					}
					if (isOnOuterEdge(_map[0].size(), _map.size(), _current)) {
						newDepth -= _depthIncrement;
					} else {
						newDepth += _depthIncrement;
					}
					possible.push_back({ portalEndPoint, newDepth });
				}
			}			
		}

		return possible;
	}

	unsigned findExitPathLength(const DonutMap& _map, PortalLocations& _portals, bool _recursive) {
		int depthIncrement = _recursive ? 1 : 0;
		assert(_portals[makePortalPair('A', 'A')].size() == 1);
		PositionWithDepth start = { *_portals[makePortalPair('A', 'A')].begin(), 0 };
		assert(_portals[makePortalPair('Z', 'Z')].size() == 1);
		PositionWithDepth finish = { *_portals[makePortalPair('Z', 'Z')].begin(),0 };

		PositionWithDepth current = start;
		internal::PriorityQueue<std::pair<PositionWithDepth, int>, int> openPriority;

		std::unordered_map<PositionWithDepth, int, PositionWithDepthHashStruct> seenCost;
		std::unordered_map<PositionWithDepth, std::pair<PositionWithDepth, int>, PositionWithDepthHashStruct> cameFrom;
		seenCost[current] = 0;
		cameFrom[current] = std::make_pair(current, 0);
		openPriority.put(std::make_pair(current, 0), 0);

		int maxDepth = 0;
		int cost = 0;
		while (!openPriority.empty()) {

			auto next = openPriority.get();

			cost = next.second;
			current = next.first;
			seenCost[current] = cost;

			if (current == finish) {
				break;
			}

			for (const auto& n : enumerate(current.position, _map, _portals, current.depth, depthIncrement)) {
				auto nextCost = cost + 1;
				if (seenCost.find(n) == seenCost.end()) {
					// Brand new
					openPriority.put(std::make_pair(n, nextCost), n.depth);
					cameFrom[n] = std::make_pair(current, nextCost);
				} else {
					// Seen it before
					if (seenCost[n] > nextCost) {
						// Its better though
						openPriority.put(std::make_pair(n, nextCost), n.depth);
						cameFrom[n] = std::make_pair(current, nextCost);
					}
				}
			}
		}

		std::vector<PositionWithDepth> path;
		PositionWithDepth currentPathNode = finish;
		while (currentPathNode != start) {
			path.push_back(currentPathNode);
			currentPathNode = cameFrom[currentPathNode].first;
		}
		path.push_back(start);

		return path.size() - 1;
	}

	void parseInput(TwentyNineteen::DonutMap& map, TwentyNineteen::PortalLocations& portalLocations, const std::vector<std::string>& _input) {

		unsigned totalHeight = _input.size();
		unsigned totalWidth = _input[0].size();

		core::Vector2i topLeftInterna{ -1,-1 };
		core::Vector2i bottomRightInternal{ -1,-1 };

		for (unsigned y = 0; y < totalHeight; ++y) {
			bool yValid = false;
			if (y >= 2 && y < totalHeight - 2) {
				map.emplace_back();
				yValid = true;
			}
			for (unsigned x = 0; x < totalWidth; ++x) {
				bool xValid = x >= 2 && x < totalWidth - 2;
				char value = _input[y][x];
				int mapX = x - 2;
				int mapY = y - 2;
				if (value == ' ') {
					if (topLeftInterna == core::Vector2i{ -1, -1 }) {
						if (yValid && xValid) {
							topLeftInterna = { mapX , mapY };
						}
					}
					if (topLeftInterna != core::Vector2i{ -1, -1 }) {
						if (yValid && xValid) {
							bottomRightInternal = { mapX , mapY };
						}
					}
				}
				if (yValid && x >= 2 && x < totalWidth - 2) {
					DonutCell& cell = map.back().emplace_back();
					cell.c = value;
					if (cell.c != '#' && cell.c != '.') {
						cell.c = ' ';
					}
				}
				if (y == 2 && x >= 2 && x < totalWidth - 2) {
					char adj1 = _input[y - 1][x];
					char adj2 = _input[y - 2][x];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}
				}
				if (x == 2 && y >= 2 && y < totalHeight - 2) {
					char adj1 = _input[y][x - 1];
					char adj2 = _input[y][x - 2];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}
				}
				if (x == totalWidth - 3 && y >= 2 && y < totalHeight - 2) {
					char adj1 = _input[y][x + 1];
					char adj2 = _input[y][x + 2];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}

				}
				if (y == totalHeight - 3 && x >= 2 && x < totalWidth - 2) {
					char adj1 = _input[y + 1][x];
					char adj2 = _input[y + 2][x];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}

				}
				if (yValid && xValid &&
					topLeftInterna.x <= mapX &&
					topLeftInterna.y <= mapY) {

					if (mapY == topLeftInterna.y && _input[y - 1][x] != ' ') {
						char adj1 = _input[y + 0][x];
						char adj2 = _input[y + 1][x];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY - 1));
						}
					}
					if (mapY == bottomRightInternal.y && _input[y + 1][x] != ' ') {
						char adj1 = _input[y + 0][x];
						char adj2 = _input[y - 1][x];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY + 1));
						}
					}
					if (mapX == topLeftInterna.x && _input[y][x - 1] != ' ') {
						char adj1 = _input[y][x + 0];
						char adj2 = _input[y][x + 1];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX - 1, mapY));
						}
					}
					if (mapY == bottomRightInternal.y && _input[y][x + 1] != ' ') {
						char adj1 = _input[y][x + 0];
						char adj2 = _input[y][x - 1];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX + 1, mapY));
						}
					}
				}
			}
		}

		for (const auto& portal : portalLocations) {
			for (auto coord : portal.second) {
				map[coord.y][coord.x].portal = portal.first.first;
				map[coord.y][coord.x].portalKey = portal.first;
			}
		}
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {		
		DonutMap map;
		PortalLocations portalLocations;

		parseInput(map, portalLocations, m_InputLines);

		if (getVerbose()) {
			dump(map, portalLocations);
		}

		auto part1 = findExitPathLength(map, portalLocations, false);
		auto part2 = findExitPathLength(map, portalLocations, true);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
