#ifndef INCLUDED_ADVENT_OF_CODE_CORE_STATES_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_STATES_HPP_

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <Core/Pathfinding.hpp>

namespace core {

	template <typename State, typename StateInfo>
	class StateTransitionManager {
	public:
		StateTransitionManager(const StateInfo& _info)
			: m_StateInfo(_info) {
		}

		template<typename SeenCostHash>
		unsigned getShortestSolutionForStateByPredicate(State _start, std::function<bool(const State& _state)> _pred) {
			State current = _start;

			internal::PriorityQueue< std::pair<State, unsigned>, unsigned> open;
			std::unordered_map<State, unsigned, SeenCostHash> seenCost;
			std::unordered_map<State, std::pair<State, unsigned>> cameFrom;
			seenCost[current] = 0;
			unsigned cost = 0;

			std::unordered_map<State, unsigned> predicateStates;

			open.put(std::make_pair(current, 0), 0);
			cameFrom[_start] = std::make_pair(_start, 0);
			long i = 0;
			unsigned minimumCurrentCost = std::numeric_limits<unsigned>::max();
			while (!open.empty()) {
				i++;
				auto next = open.get();
				cost = next.second;
				current = next.first;
				seenCost[current] = cost;
				if (_pred(current)) {
					if (minimumCurrentCost > cost) {
						minimumCurrentCost = cost;
					}
				}

				for (const auto& n : current.enumerate(m_StateInfo)) {
					if (n.valid(m_StateInfo)) {
						auto nextCost = cost + current.cost(n, m_StateInfo);
						if (nextCost > minimumCurrentCost) {
							continue;
						}
						if (seenCost.find(n) == seenCost.end()) {
							// We have not seen it before
							open.put(std::make_pair(n, nextCost), n.priority(m_StateInfo));
							cameFrom[n] = std::make_pair(current, nextCost);
						} else {
							// maybe its cheaper
							if (seenCost[n] > nextCost) {
								open.put(std::make_pair(n, nextCost), n.priority(m_StateInfo));
								cameFrom[n] = std::make_pair(current, nextCost);
							}
						}
					}
				}
			}

			State bestState = _start;
			unsigned minCost = std::numeric_limits<unsigned>::max();
			for (const auto& [state, cost] : predicateStates) {
				if (minCost > cost) {
					minCost = cost;
					bestState = state;
				}
			}

			return minCost;
		}

		std::unordered_map<State, std::pair<State, unsigned>> getBreadthFirstExploredStateSpace(State _start) {
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

				for (const auto& n : current.enumerate(m_StateInfo)) {
					if (n.valid(m_StateInfo)) {
						auto nextCost = cost + current.cost(n, m_StateInfo);
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

			return cameFrom;
		}

		std::vector<State> getShortestSolution(State _start, State _stop) {
			auto cameFrom = getBreadthFirstExploredStateSpace(_start);

			if (cameFrom.find(_stop) != cameFrom.end()) {
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
		unsigned getShortestSolutionLength(State _start, State _stop) {
			auto cameFrom = getBreadthFirstExploredStateSpace(_start);
			unsigned length = 0;
			State pathState = _stop;
			if (cameFrom.find(_stop) != cameFrom.end()) {
				while (pathState != _start) {
					length++;
					pathState = cameFrom[pathState].first;
				}
				length++;
			}
			return length;
		}

	private:
		const StateInfo& m_StateInfo;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_STATES_HPP_