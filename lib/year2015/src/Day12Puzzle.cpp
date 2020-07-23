#include <2015/Day12Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <zeno/Utility/Json.hpp>
#include <unordered_set>
#include <unordered_map>
#include <stack>

typedef std::pair<unsigned, unsigned> containerDepth;

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

namespace TwentyFifteen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("JSAbacusFramework.io", 2015, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		const auto result = solve(m_InputLines[0]);
		return { std::to_string(result.first), std::to_string(result.second) };
	}
	std::pair<int, int> Day12Puzzle::solve(const std::string& _input) {
		ze::JsonDocument doc = ze::Json::parseFromText(_input);

		const int part1 = recurser(*doc.m_Root, false);
		const int part2 = recurser(*doc.m_Root, true);
		return std::make_pair(part1, part2);
	}
	int Day12Puzzle::recurser(const ze::JsonNode& _node, bool _validate) {
		int total = 0;

		bool valid = true;
		if (_validate) {
			if (_node.type == ze::JsonNode::Type::Object) {
				for (const auto& c : _node.children) {
					if (c->content == "red") {
						valid = false;
						break;
					}
				}
			}
		}

		if (valid) {
			for (const auto c : _node.children) {
				total += recurser(*c, _validate);
			}

			total += _node.integer;
		}
		return total;
	}
}
