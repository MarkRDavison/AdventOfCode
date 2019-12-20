#ifndef INCLUDED_ADVENT_OF_CODE_CORE_STATES_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_STATES_HPP_

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <queue>

namespace core {

	template <typename State>
	class StateTransitionManager {
	public:
		std::vector<State> getShortestSolution(State _start, State _stop) {
			State current = _start;
			std::queue<std::pair<State, unsigned>> open;
			std::unordered_map<State, unsigned> seenCost;
			std::unordered_map<State, std::pair<State, unsigned>> cameFrom;
			seenCost[current] = 0;
			unsigned cost = 0;

			open.push(std::make_pair(current, 0));
			cameFrom[_start] = std::make_pair(_start, 0);

			while (!open.empty()) {
				auto next = open.front();
				open.pop();
				cost = next.second;
				current = next.first;
				seenCost[current] = cost;

				for (const auto& n : current.enumerate()) {
					if (n.valid()) {
						auto nextCost = cost + current.cost(n);
						if (seenCost.find(n) == seenCost.end()) {
							// We have not seen it before
							open.push(std::make_pair(n, nextCost));
							cameFrom[n] = std::make_pair(current, nextCost);
						} else {
							// maybe its cheaper
							if (seenCost[n] > nextCost) {
								open.push(std::make_pair(n, nextCost));
								cameFrom[n] = std::make_pair(current, nextCost);
							}
						}
					}
				}
			}

			if (seenCost.find(_stop) != seenCost.end()) {
				std::vector<State> path;
				State pathState = _stop;
				while (pathState != _start) {
					path.push_back(pathState);
					pathState = cameFrom[pathState].first;
				}
				path.push_back(pathState);
				std::reverse(path.begin(), path.end());
				return path;
			} 
			return {};
		}
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_STATES_HPP_