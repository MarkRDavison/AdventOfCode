#include <2019/Day18Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/States.hpp>
#include <Core/Pathfinding.hpp>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <set>

struct KeyMapCell {
	core::Vector2i position;
	char c;
	char interest;
};

struct Day18State {

	char key;
	std::set<char> keys;

	bool operator==(const Day18State& _other) const {
		return
			key == _other.key &&
			keys == _other.keys;
	};

	std::size_t hash() const {
		std::stringstream ss;
		auto hasher = std::hash<char>();
		std::size_t h = hasher(key);

		for (const auto& c : keys) {
			h ^= hasher(c);
		}

		return h;
	}

	std::string str() const {
		std::stringstream ss;

		ss << key << "-";
		for (auto p : keys) {
			ss << "=" << p;
		}

		return ss.str();
	}

};

struct Day18StateHashFxn {
	std::size_t operator()(const Day18State& _obj) const {
		std::stringstream ss;

		ss << _obj.key << "-";
		for (auto p : _obj.keys) {
			ss << "=" << p;
		}

		return std::hash<std::string>()(ss.str());
	}
};

using Map = std::vector<std::vector<KeyMapCell>>;
using DestinationInfo = std::unordered_map<char, std::pair<int, std::string>>;
using AllDestinationInfo = std::unordered_map<char, DestinationInfo>;
struct StateInfo {
	Map map;
	std::set<char> keys{ 
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	};
};

namespace TwentyNineteen {

	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Many-Worlds Interpretation", 2019, 18) {

	}
	Day18Puzzle::~Day18Puzzle() {

	}
	
	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	
	std::vector<std::string> dumpMapToStringVector(const StateInfo& _info) {
		std::vector<std::string> strVec;

		for (unsigned y = 0; y < _info.map.size(); ++y) {
			auto& str = strVec.emplace_back();
			for (unsigned x = 0; x < _info.map[y].size(); ++x) {
				const auto& cell = _info.map[y][x];
				if (cell.interest != cell.c) {
					str += cell.interest;
				}
				else {
					str += cell.c;
				}
			}
		}

		return strVec;
	}

	DestinationInfo getDistanceInformationFrom(core::Vector2i& _source, const StateInfo& _stateInfo) {
		std::unordered_set<core::Vector2i, core::vector2_hash_fxn> visited;
		std::queue<std::pair<core::Vector2i, std::pair<int, std::string>>> queue;
		DestinationInfo destinationInfo;

		queue.push(std::make_pair(_source, std::make_pair(0, "")));

		while (!queue.empty()) {
			auto next = queue.front();
			queue.pop();

			const auto& cell = _stateInfo.map[next.first.y][next.first.x];


			if (next.second.first > 0 &&
				std::find(_stateInfo.keys.begin(), _stateInfo.keys.end(), std::tolower(cell.interest)) != _stateInfo.keys.end()) {
				destinationInfo[cell.interest] = next.second;
				next.second.second += cell.interest;
			}
			visited.insert(next.first);
			for (const auto& coord : { core::Vector2i(+0,-1), core::Vector2i(-1,+0), core::Vector2i(+1,+0), core::Vector2i(+0,+1) }) {
				auto newCoord = coord + next.first;
				if (newCoord.x > 0 &&
					newCoord.y > 0 &&
					newCoord.y < _stateInfo.map.size() - 1 &&
					newCoord.x < _stateInfo.map[0].size() - 1 &&
					'#' != _stateInfo.map[newCoord.y][newCoord.x].c &&
					visited.count(newCoord) == 0) {
					queue.push(std::make_pair(newCoord, std::make_pair(next.second.first + 1, next.second.second)));
				}
			}
		}

		return destinationInfo;
	}

	AllDestinationInfo findAllDestinationInfoForPointsOfInterest(const StateInfo& _info) {
		AllDestinationInfo allDestinationInfo;
		for (int y = 0; y < _info.map.size(); ++y) {
			for (int x = 0; x < _info.map[0].size(); ++x) {
				const auto& cell = _info.map[y][x];
				if ((cell.interest == '@' ||
					cell.interest == '1' ||
					cell.interest == '2' ||
					cell.interest == '3' ||
					cell.interest == '4') ||
					'a' <= cell.interest && cell.interest <= 'z') {
					allDestinationInfo[cell.interest] = getDistanceInformationFrom(core::Vector2i(x,y), _info);
				}
			}
		}

		return allDestinationInfo;
	}


	void dumpMapToConsole(const StateInfo& _info) {
		for (const auto& _str : dumpMapToStringVector(_info)) {
			std::cout << _str << std::endl;
		}
	}
	int Day18Puzzle::solve(const std::vector<std::string>& _inputLines, char _robot) {
		StateInfo info{};
		std::set<char> keys;

		std::set<char> starts;

		for (unsigned y = 0; y < _inputLines.size(); ++y) {
			auto& mapRow = info.map.emplace_back();
			for (unsigned x = 0; x < _inputLines[y].size(); ++x) {
				auto& cell = mapRow.emplace_back();
				cell.position = { (int)x, (int)y };
				cell.c = _inputLines[y][x];
				cell.interest = cell.c;
				if (cell.c != '#' && cell.c != '.') {
					if (cell.c == _robot) {
						starts.insert(cell.c);
					} else if ('a' <= cell.c && cell.c <= 'z') {
						keys.insert(cell.c);
					} else if ('A' <= cell.c && cell.c <= 'Z') {

					}
					cell.c = '.';
				}
			}
		}

		const auto& destInfo = findAllDestinationInfoForPointsOfInterest(info);

		std::unordered_map<Day18State, int, Day18StateHashFxn> seenCosts;
		std::unordered_map<Day18State, std::pair<Day18State, int>, Day18StateHashFxn> cameFrom;
		internal::PriorityQueue<std::pair<Day18State, int>, int> pQueue;
		Day18State start{ _robot, {} };
		pQueue.put({ start, 0 }, 0);

		std::set<char> reachableKeys;
		auto robotInfo = destInfo.at(_robot);
		for (const auto& _robotReach : robotInfo) {
			if ('a' <= _robotReach.first && _robotReach.first <= 'z') {
				reachableKeys.insert(_robotReach.first);
			}
		}

		int part1 = std::numeric_limits<int>::max();
		int numKeysInEndState = reachableKeys.size();
		while (!pQueue.empty()) {
			auto currentPair = pQueue.get();

			auto currentState = currentPair.first;
			auto currentCost = currentPair.second;

			if (part1 < currentCost) {
				// More expensive, no point continuing from here
				continue;
			}
			auto prevIter = seenCosts.find(currentState);
			if (prevIter != seenCosts.end() && (*prevIter).second < currentCost) {
				// Already been here and cheaper
				continue;
			} else {
				seenCosts[currentState] = currentCost;
			}

			if (currentState.keys.size() == numKeysInEndState) {
				if (part1 > currentCost) {
					part1 = currentCost;
				}
				continue;
			}

			// Enumerate next states
			for (char nextKey : keys) {
				if (nextKey == currentState.key) { continue; }
				if (currentState.keys.count(nextKey) == 0) {
					auto destInfoIter = destInfo.at(currentState.key).find(nextKey);
					if (destInfoIter == destInfo.at(currentState.key).end()) {
						continue;
					}
					auto destinationInfo = destInfo.at(currentState.key).at(nextKey);
					bool valid = true;
					for (char c : destinationInfo.second) {
						if (currentState.keys.count(std::tolower(c)) == 0) {
							if (reachableKeys.count(std::tolower(c)) != 0) {
								valid = false;
								break;
							}
						}
					}
					if (!valid) {
						continue;
					}
					// Dont have this key 
					Day18State nextState{};
					nextState.key = nextKey;
					nextState.keys = std::set<char>(currentState.keys);
					nextState.keys.insert(nextKey);
					auto nextCost = currentCost + destinationInfo.first;

					auto nextIter = seenCosts.find(nextState);
					if (nextIter == seenCosts.end() || (*nextIter).second > nextCost) {
						pQueue.put({ nextState, nextCost }, numKeysInEndState - nextState.keys.size() + part1 - nextCost);
					}
				}
			}
		}

		return part1;
	}
	int Day18Puzzle::solvePart2(const std::vector<std::string>& _inputLines) {
		core::Vector2<unsigned> start;
		for (unsigned y = 0; y < _inputLines.size(); ++y) {
			for (unsigned x = 0; x < _inputLines[y].size(); ++x) {
				if (_inputLines[y][x] == '@') {
					start = { x,y };
					break;
				}
			}
			if (start != core::Vector2<unsigned>{}) {
				break;
			}
		}

		unsigned totalWidth = _inputLines[0].size();
		unsigned totalHeight = _inputLines.size();

		unsigned subWidth = (totalWidth + 1) / 2;
		unsigned subHeight = (totalHeight + 1) / 2;

		std::vector<std::string> input(_inputLines);

		input[start.y - 1][start.x - 1] = '1';
		input[start.y - 1][start.x + 0] = '#';
		input[start.y - 1][start.x + 1] = '2';

		input[start.y + 0][start.x - 1] = '#';
		input[start.y + 0][start.x + 0] = '#';
		input[start.y + 0][start.x + 1] = '#';

		input[start.y + 1][start.x - 1] = '3';
		input[start.y + 1][start.x + 0] = '#';
		input[start.y + 1][start.x + 1] = '4';


		int part2_1 = solve(input, '1');
		int part2_2 = solve(input, '2');
		int part2_3 = solve(input, '3');
		int part2_4 = solve(input, '4');

		return part2_1 + part2_2 + part2_3 + part2_4;
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {
		
		int part1 = solve(m_InputLines, '@');

		int part2 = solvePart2(m_InputLines);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
