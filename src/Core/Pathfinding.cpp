#include <Core/Pathfinding.hpp>
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
	std::vector<std::pair<std::string, unsigned>> EdgeNetwork::performDepthFirstSearch(const std::string& _start, const std::string& _end) {
		return internal::depthFirstSearch(sg, _start, _end);
	}
}