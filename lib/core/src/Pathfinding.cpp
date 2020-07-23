#include <Core/Pathfinding.hpp>
#include <iostream>
#include <cmath>

namespace core {

	// TODO: Make these one method that you pass a comparator to
	std::pair<std::vector<std::string>, float> doDepthFirstMinCostRecursive(
		internal::EdgeGraph& _graph,
		std::vector<std::string> _path,
		float _cost,
		const std::string& _node,
		std::unordered_set<std::string> _visited,
		std::size_t _numToVisit,
		float _currentShortest) {

		if (_currentShortest < _cost) {
			return std::make_pair(_path, std::numeric_limits<float>::max());
		}

		_path.push_back(_node);
		_visited.insert(_node);

		if (_path.size() == _numToVisit) {
			return std::make_pair(_path, _cost);
		}

		std::vector<std::string> minPath;
		float minPathCost = std::numeric_limits<float>::max();

		for (const auto& n : _graph.neighbours(_node)) {
			if (_visited.count(n) != 0) {
				// Already been there on this path
				continue;
			}

			const auto& potential = doDepthFirstMinCostRecursive(
				_graph,
				_path,
				_cost + _graph.cost(_node, n),
				n,
				_visited,
				_numToVisit,
				_currentShortest
			);

			if (potential.second < minPathCost) {
				minPathCost = potential.second;
				minPath = potential.first;
			}
		}

		return std::make_pair(minPath, minPathCost);
	}
	std::pair<std::vector<std::string>, float> doDepthFirstMaxCostRecursive(
		internal::EdgeGraph& _graph,
		std::vector<std::string> _path,
		float _cost,
		const std::string& _node,
		std::unordered_set<std::string> _visited,
		std::size_t _numToVisit,
		float _currentLongest) {

		_path.push_back(_node);
		_visited.insert(_node);

		if (_path.size() == _numToVisit) {
			return std::make_pair(_path, _cost);
		}

		std::vector<std::string> minPath;
		float maxPathCost = std::numeric_limits<float>::min();

		for (const auto& n : _graph.neighbours(_node)) {
			if (_visited.count(n) != 0) {
				// Already been there on this path
				continue;
			}

			const auto& potential = doDepthFirstMaxCostRecursive(
				_graph,
				_path,
				_cost + _graph.cost(_node, n),
				n,
				_visited,
				_numToVisit,
				_currentLongest
			);

			if (potential.second > maxPathCost) {
				maxPathCost = potential.second;
				minPath = potential.first;
			}
		}

		return std::make_pair(minPath, maxPathCost);
	}

	void EdgeNetwork::addEdge(const std::string& _a, const std::string& _b) {
		addEdge(_a, _b, 0.0f);
	}
	void EdgeNetwork::addEdge(const std::string& _a, const std::string& _b, float _weight) {
		sg.edges[_a].insert(_b);
		sg.edges[_b].insert(_a);
		sg.weights.emplace(_a + "_" + _b, _weight);
		this->sg.nodes.insert(_a);
		this->sg.nodes.insert(_b);
	}
	std::vector<std::string> EdgeNetwork::getShortestPath(const std::string& _start, const std::string& _end) {
		std::unordered_map<std::string, std::string> origins;
		std::unordered_map<std::string, float> costs;
		internal::dijkstraSearch(sg, _start, _end, origins, costs);
		return internal::reconstruct_path(_start, _end, origins);
	}
	std::unordered_set<std::string> EdgeNetwork::getNodes() {
		return sg.nodes;
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
	std::pair<std::vector<std::string>, float> EdgeNetwork::getShortestPathVisitingAll(){
		std::pair<std::vector<std::string>, float> result;
		float shortest = std::numeric_limits<float>::max();
		for (const auto& n : getNodes()) {
			const auto& res = getShortestPathVisitingAll(n, shortest);
			if (shortest > res.second) {
				shortest = res.second;
				result = res;
			}
		}

		return result;
	}
	std::pair<std::vector<std::string>, float> EdgeNetwork::getShortestPathVisitingAll(const std::string& _start) {
		return getShortestPathVisitingAll(_start, std::numeric_limits<float>::max());
	}
	std::pair<std::vector<std::string>, float> EdgeNetwork::getShortestPathVisitingAll(const std::string& _start, float _currentShortest){
		return doDepthFirstMinCostRecursive(sg, {}, 0.0f, _start, {}, sg.nodes.size(), _currentShortest);
	}

	std::pair<std::vector<std::string>, float> EdgeNetwork::getLongestPathVisitingAll() {
		std::pair<std::vector<std::string>, float> result;
		float longest = std::numeric_limits<float>::min();
		for (const auto& n : getNodes()) {
			const auto& res = getLongestPathVisitingAll(n, longest);
			if (longest < res.second) {
				longest = res.second;
				result = res;
			}
		}

		return result;
	}
	std::pair<std::vector<std::string>, float> EdgeNetwork::getLongestPathVisitingAll(const std::string& _start) {
		return getLongestPathVisitingAll(_start, std::numeric_limits<float>::min());
	}
	std::pair<std::vector<std::string>, float> EdgeNetwork::getLongestPathVisitingAll(const std::string& _start, float _currentShortest) {
		return doDepthFirstMaxCostRecursive(sg, {}, 0.0f, _start, {}, sg.nodes.size(), _currentShortest);
	}

	std::pair<std::vector<std::string>, float> doDepthFirstMaxCostRecursiveReturningToStart(
		internal::EdgeGraph& _graph,
		std::vector<std::string> _path,
		float _cost,
		const std::string& _node,
		std::unordered_set<std::string> _visited,
		std::size_t _numToVisit,
		float _currentLongest) {

		_path.push_back(_node);
		_visited.insert(_node);

		if (_path.size() == _numToVisit) {
			_path.push_back(_path.front());
			_cost += _graph.cost(_node, _path.front());
			return std::make_pair(_path, _cost);
		}

		std::vector<std::string> minPath;
		float maxPathCost = std::numeric_limits<float>::min();

		for (const auto& n : _graph.neighbours(_node)) {
			if (_visited.count(n) != 0) {
				// Already been there on this path
				continue;
			}

			const auto& potential = doDepthFirstMaxCostRecursiveReturningToStart(
				_graph,
				_path,
				_cost + _graph.cost(_node, n),
				n,
				_visited,
				_numToVisit,
				_currentLongest
			);

			if (potential.second > maxPathCost) {
				maxPathCost = potential.second;
				minPath = potential.first;
			}
		}

		return std::make_pair(minPath, maxPathCost);
	}
	std::pair<std::vector<std::string>, float> EdgeNetwork::getLongestPathVisitingAllReturningToStart() {
		std::pair<std::vector<std::string>, float> result;
		float shortest = std::numeric_limits<float>::max();
		for (const auto& n : getNodes()) {
			const auto& res = getLongestPathVisitingAllReturningToStart(n, shortest);
			if (shortest > res.second) {
				shortest = res.second;
				result = res;
			}
		}

		return result;
	}
	std::pair<std::vector<std::string>, float> EdgeNetwork::getLongestPathVisitingAllReturningToStart(const std::string& _start) {
		return getLongestPathVisitingAllReturningToStart(_start, std::numeric_limits<float>::min());
	}
	std::pair<std::vector<std::string>, float> EdgeNetwork::getLongestPathVisitingAllReturningToStart(const std::string& _start, float _currentShortest) {
		return doDepthFirstMaxCostRecursiveReturningToStart(sg, {}, 0.0f, _start, {}, sg.nodes.size(), _currentShortest);
	}
}