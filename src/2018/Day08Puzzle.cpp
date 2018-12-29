#include <2018/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <stack>
#include <numeric>

namespace TwentyEighteen {

	inline int topAndPop(std::stack<int>& _stack) {
		const int top = _stack.top();
		_stack.pop();
		return top;
	}

	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Memory Maneuver", 2018, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}

	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), " "));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		std::stack<int> values;
		for (auto it = m_InputLines.rbegin(); it != m_InputLines.rend(); ++it) {
			const std::string value = *it;
			values.emplace(std::atoi(value.c_str()));
		}

		const int numChildren = topAndPop(values);
		const int numMetadata = topAndPop(values);

		MetadataNode root(numChildren, numMetadata);

		addChildrenRecursively(root, values);

		const int summedMetadata = sumMetadata(root);
		const int calculatedMetadata = calculateMetadataSum(root);

		return { std::to_string(summedMetadata), std::to_string(calculatedMetadata) };
	}

	void Day08Puzzle::addChildrenRecursively(MetadataNode& _node, std::stack<int>& _values) {
		while (static_cast<std::size_t>(_node.NumberChildren) > _node.children.size()) {
			const int numChildren = topAndPop(_values);
			const int numMetadata = topAndPop(_values);

			_node.children.emplace_back(numChildren, numMetadata);

			MetadataNode& newChild = _node.children.back();
			addChildrenRecursively(newChild, _values);
		}

		while (static_cast<std::size_t>(_node.NumberMetadata) > _node.metadata.size()) {
			_node.metadata.emplace_back(topAndPop(_values));
		}
	}

	int Day08Puzzle::sumMetadata(const MetadataNode& _node) {
		int metadataSum = std::accumulate(_node.metadata.begin(), _node.metadata.end(), 0, [](int _sum, int _metadata) -> int {
			return _sum + _metadata;
		});

		for (const MetadataNode& _child : _node.children) {
			metadataSum += sumMetadata(_child);
		}

		return metadataSum;
	}

	int Day08Puzzle::calculateMetadataSum(const MetadataNode& _node) {
		if (_node.NumberChildren == 0) {
			int currentLevelMetadata = 0;
			for (int _metadata : _node.metadata) {
				currentLevelMetadata += _metadata;
			}
			return currentLevelMetadata;
		}
		int childMetaValue = 0;
		for (int metadata : _node.metadata) {
			const unsigned index = static_cast<unsigned>(metadata - 1);
			if (index >= _node.children.size()) {
				continue;
			}

			const MetadataNode& child = _node.children[index];
			childMetaValue += calculateMetadataSum(child);
		}

		return childMetaValue;
	}
}
