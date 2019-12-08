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
		void setStartState(State _start) {
			start = _start;
		}
		void setStopState(State _stop) {
			stop = _stop;
		}

		void goToEnd() {
			State current;
			std::queue<std::pair<State, unsigned>> open;
			std::unordered_map<State, unsigned> seenCost;
			seenCost[current] = 0;
			unsigned cost = 0;

			open.push(std::make_pair(current, 0));

			while (!open.empty()) {
				auto next = open.front();
				open.pop();
				cost = next.second;
				current = next.first;
				seenCost[current] = cost;

				for (const auto& n : current.enumerate()) {
					if (n.valid()) {
						if (seenCost.find(n) == seenCost.end()) {
							// We have not seen it before
							open.push(std::make_pair(n, cost + current.cost(n)));
						} else {
							// maybe its cheaper
							if (seenCost[n] > cost + current.cost(n)) {
								open.push(std::make_pair(n, cost + current.cost(n)));
							}
						}
					}
				}
			}

			if (seenCost.find(stop) != seenCost.end()) {
				std::cout << "Found " << stop.str() << ", costs: " << seenCost[stop] << std::endl;
			} else {
				std::cout << "Never found the end" << std::endl;
			}
		}


	private:
		State start;
		State stop;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_STATES_HPP_