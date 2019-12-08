#include <Core/Pathfinding.hpp>
#include <iostream>
#include <cmath>

namespace core {

	void EdgeNetwork::addEdge(const std::string& _a, const std::string& _b) {
		addEdge(_a, _b, 0.0f);
	}
	void EdgeNetwork::addEdge(const std::string& _a, const std::string& _b, float _weight) {
		sg.edges[_a].push_back(_b);
		sg.weights.emplace(_a + "_" + _b, _weight);
	}
	std::vector<std::string> EdgeNetwork::getShortestPath(const std::string& _start, const std::string& _end) {
		std::unordered_map<std::string, std::string> origins;
		std::unordered_map<std::string, float> costs;
		internal::dijkstraSearch(sg, _start, _end, origins, costs);
		return internal::reconstruct_path(_start, _end, origins);
	}
	std::vector<std::string> EdgeNetwork::getNodes() {
		std::vector<std::string>nodes;
		for (const auto& _n : sg.edges) {
			nodes.push_back(_n.first);
		}
		return nodes;
	}
	std::vector<std::pair<std::string, std::pair<unsigned, float>>> EdgeNetwork::performDepthFirstSearch(const std::string& _start, const std::string& _end) {
		return internal::depthFirstSearch(sg, _start, _end);
	}

	std::vector<std::pair<std::string, std::pair<unsigned, float>>> EdgeNetwork::performBreadthFirstSearch(const std::string& _start, const std::string& _end) {
		const auto result = internal::breadthFirstSearch(sg, _start, _end);
		return {};
	}
	unsigned EdgeNetwork::performDijkstraSearch(const std::string& _start, const std::string& _end) {
		std::unordered_map<std::string, std::string> origins;
		std::unordered_map<std::string, float> costs;
		internal::dijkstraSearch(sg, _start, _end, origins, costs);

		return costs.size();
	}
	unsigned EdgeNetwork::performAStarSearch(const std::string& _start, const std::string& _end) {
		std::unordered_map<std::string, std::string> origins;
		std::unordered_map<std::string, float> costs;
		internal::aStarSearch(sg, _start, _end, origins, costs);
		const auto& path = internal::reconstruct_path(_start, _end, origins);
		
		return 0;
	}

	std::vector<std::string> doDepthFirstMinCostHeuristicRecursive(internal::EdgeGraph& _graph, const std::string& _node, std::unordered_set<std::string> _visited, float _cost) {
		//std::cout << "Entered: " << _node << " at " << _cost << std::endl;
		_visited.insert(_node);
		bool leaf = true;
		for (const auto& n : _graph.neighbours(_node)) {
			if (_visited.find(n) != _visited.end()) { continue; }
			leaf = false;
			float newCost = _cost + _graph.weights[_node + "_" + n];
			//std::cout << "From " << _node << " can go to: " << n << " at a cost of " << newCost << std::endl;
			auto childRecommendation = doDepthFirstMinCostHeuristicRecursive(_graph, n, _visited, newCost);
		}
		if (leaf) {
			std::cout << "I (" << _node << ") am a leaf, cost " << _cost << std::endl;
		}
		
		//_visited.insert(_node);
		//bool wentToChild = false;
		//for (const auto& n : _graph.neighbours(_node)) {
		//	if (_visited.count(n) > 0) { continue; }
		//
		//	float newCost = _cost + _graph.weights[_node + "_" + n];
		//	if (newCost > _bestCost) {
		//		continue;
		//	}
		//
		//	wentToChild = true;
		//	float best = doDepthFirstMinCostHeuristicRecursive(_graph, n, _visited, _cost + _graph.weights[_node + "_" + n], _bestCost);
		//	if (best < _bestCost) {
		//		_bestCost = best;
		//	}
		//}
		//
		//if (!wentToChild) {
		//	return _cost;
		//}

		return {};
	}

	unsigned EdgeNetwork::depthFirstMinCostHeuristic(const std::string& _start) {
		std::unordered_set<std::string> visited;
		const auto& path = doDepthFirstMinCostHeuristicRecursive(sg, _start, visited, 0.0f);

		return 0;
	}
}