#include <2019/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>

namespace TwentyNineteen {

	struct DonutCell {
		char c;
		std::vector<core::Vector2i> adjacentLocations;
		char portal{ 0 };
		std::pair<char, char> portalKey;
	};

	using PortalLocations = std::map<std::pair<char, char>, std::unordered_set<core::Vector2i, core::vector2_hash_fxn>>;

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

	void dump(const std::vector<std::vector<DonutCell>>& _map, PortalLocations& _portals, std::unordered_set<core::Vector2i, core::vector2_hash_fxn>& _path) {

		for (unsigned y = 0; y < _map.size(); ++y) {
			for (unsigned x = 0; x < _map[y].size(); ++x) {
				const DonutCell& cell = _map[y][x];
				if (_path.count(core::Vector2i((int)x, (int)y)) > 0) {
					std::cout << '*';
				}
				else if (cell.portal != 0) {
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

	std::vector<core::Vector2i> enumerate(core::Vector2i _current, const std::vector<std::vector<DonutCell>>& _map, PortalLocations& _portals) {
		std::vector<core::Vector2i> possible;

		const auto& currentCell = _map[_current.y][_current.x];

		if (_current.y != 0) {
			const auto& cell = _map[_current.y - 1][_current.x];
			if (cell.c == '.') {
				possible.push_back({ _current.x, _current.y - 1 });
			}
		}
		if (_current.y < _map.size() - 1) {
			const auto& cell = _map[_current.y + 1][_current.x];
			if (cell.c == '.') {
				possible.push_back({ _current.x, _current.y + 1 });
			}
		}
		if (_current.x != 0) {
			const auto& cell = _map[_current.y][_current.x - 1];
			if (cell.c == '.') {
				possible.push_back({ _current.x - 1, _current.y });
			}
		}
		if (_current.x  < _map[0].size() - 1) {
			const auto& cell = _map[_current.y][_current.x + 1];
			if (cell.c == '.') {
				possible.push_back({ _current.x + 1, _current.y });
			}
		}

		if (currentCell.portal != 0) {
			const auto& portalLocInfo = _portals[currentCell.portalKey];
			for (const auto& portalEndPoint : portalLocInfo) {
				if (portalEndPoint != _current) {
					possible.push_back(portalEndPoint);
				}
			}			
		}

		return possible;
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {

		std::vector<std::vector<DonutCell>> map;
		std::map<char, std::vector<char>> availablePortals;
		PortalLocations portalLocations;

		unsigned totalHeight = m_InputLines.size();
		unsigned totalWidth = m_InputLines[0].size();

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
				char value = m_InputLines[y][x];
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
					char adj1 = m_InputLines[y - 1][x];
					char adj2 = m_InputLines[y - 2][x];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}
				} 
				if (x == 2 && y >= 2 && y < totalHeight - 2) {
					char adj1 = m_InputLines[y][x - 1];
					char adj2 = m_InputLines[y][x - 2];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}
				}
				if (x == totalWidth - 3 && y >= 2 && y < totalHeight - 2) {
					char adj1 = m_InputLines[y][x + 1];
					char adj2 = m_InputLines[y][x + 2];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}

				}
				if (y == totalHeight - 3 && x >= 2 && x < totalWidth - 2) {
					char adj1 = m_InputLines[y + 1][x];
					char adj2 = m_InputLines[y + 2][x];
					if ('A' <= adj1 && adj1 <= 'Z' &&
						'A' <= adj2 && adj2 <= 'Z') {
						portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY));
					}

				}
				if (yValid && xValid &&
					topLeftInterna.x <= mapX &&
					topLeftInterna.y <= mapY) {
					
					if (mapY == topLeftInterna.y && m_InputLines[y-1][x] != ' ') {
						char adj1 = m_InputLines[y + 0][x];
						char adj2 = m_InputLines[y + 1][x];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY - 1));
							std::cout << "Internal portal = North Internal: " << adj1 << " - " << adj2 << " at " << mapX << "," << mapY - 1 << std::endl;
						}
					}
					if (mapY == bottomRightInternal.y && m_InputLines[y + 1][x] != ' ') {
						char adj1 = m_InputLines[y + 0][x];
						char adj2 = m_InputLines[y - 1][x];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX, mapY + 1));
							std::cout << "Internal portal = South Internal: " << adj1 << " - " << adj2 << " at " << mapX << "," << mapY + 1 << std::endl;
						}
					}
					if (mapX == topLeftInterna.x && m_InputLines[y][x - 1] != ' ') {
						char adj1 = m_InputLines[y][x + 0];
						char adj2 = m_InputLines[y][x + 1];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX - 1, mapY));
							std::cout << "Internal portal = West Internal: " << adj1 << " - " << adj2 << " at " << mapX - 1 << "," << mapY << std::endl;
						}
					}
					if (mapY == bottomRightInternal.y && m_InputLines[y][x + 1] != ' ') {
						char adj1 = m_InputLines[y][x + 0];
						char adj2 = m_InputLines[y][x - 1];
						if ('A' <= adj1 && adj1 <= 'Z' &&
							'A' <= adj2 && adj2 <= 'Z') {
							portalLocations[makePortalPair(adj1, adj2)].insert(core::Vector2i(mapX + 1, mapY));
							std::cout << "Internal portal = East Internal: " << adj1 << " - " << adj2 << " at " << mapX + 1 << "," << mapY<< std::endl;
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

		std::unordered_set<core::Vector2i, core::vector2_hash_fxn> pathSet;
		dump(map, portalLocations, pathSet);

		assert(portalLocations[makePortalPair('A', 'A')].size() == 1);
		core::Vector2i start = *portalLocations[makePortalPair('A', 'A')].begin();
		assert(portalLocations[makePortalPair('Z', 'Z')].size() == 1);
		core::Vector2i finish = *portalLocations[makePortalPair('Z', 'Z')].begin();
		
		core::Vector2i current = start;
		std::queue<std::pair<core::Vector2i, int>> open;
		std::unordered_map<core::Vector2i, int, core::vector2_hash_fxn> seenCost;
		std::unordered_map<core::Vector2i, std::pair<core::Vector2i, int>, core::vector2_hash_fxn> cameFrom;
		seenCost[start] = 0;
		cameFrom[start] = std::make_pair(start, 0);
		open.push(std::make_pair(start, 0));
		int cost = 0;
		while (!open.empty()) {
			auto next = open.front();
			open.pop();

			cost = next.second;
			current = next.first;
			seenCost[current] = cost;

			for (const auto& n : enumerate(current, map, portalLocations)) {
				auto nextCost = cost + 1;
				if (seenCost.find(n) == seenCost.end()) {
					// Brand new
					open.push(std::make_pair(n, nextCost));
					cameFrom[n] = std::make_pair(current, nextCost);
				} else {
					// Seen it before
					if (seenCost[n] > nextCost) {
						// Its better though
						open.push(std::make_pair(n, nextCost));
						cameFrom[n] = std::make_pair(current, nextCost);
					}
				}
			}
		}

		std::vector<core::Vector2i> path;
		core::Vector2i currentPathNode = finish;
		while (currentPathNode != start) {
			path.push_back(currentPathNode);
			pathSet.insert(currentPathNode);
			currentPathNode = cameFrom[currentPathNode].first;
		}
		pathSet.insert(start);
		path.push_back(start);
		std::reverse(path.begin(), path.end());
		dump(map, portalLocations, pathSet);

		std::cout << "PART 1: " << path.size() - 1 << std::endl;
		return { std::to_string(path.size() - 1), "Part 2" };
	}
}
