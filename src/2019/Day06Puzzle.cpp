#include <2019/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Pathfinding.hpp>
#include <Core/States.hpp>
#include <algorithm>
#include <numeric>
#include <set>

namespace TwentyNineteen {

	struct Day6StateInfo {
		std::unordered_map<std::string, std::set<std::string>> neighbourInfo;
	};
	struct Day6State {
		std::string id;

		std::vector<Day6State> enumerate(const Day6StateInfo& _stateInfo) {
			std::vector<Day6State> n;

			for (const auto& id : _stateInfo.neighbourInfo.at(id)) {
				n.push_back(Day6State{ id });
			}

			return n;
		}

		bool valid(const Day6StateInfo& _stateInfo) const { return true; }
		unsigned cost(const Day6State& _other, const Day6StateInfo& _stateInfo) { return 1; }
		bool operator==(const Day6State& _other) const { return id == _other.id; }
		bool operator!=(const Day6State& _other) const { return id != _other.id; }

	};
}

namespace std {
	template <>
	struct hash<TwentyNineteen::Day6State> {
		size_t operator()(const TwentyNineteen::Day6State& obj) const {
			auto hash = std::hash<std::string>()(obj.id);
			return hash;
		}
	};
}

namespace TwentyNineteen {
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Universal Orbit Map", 2019, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		Day6StateInfo info{};
		core::StateTransitionManager<Day6State, Day6StateInfo> stm(info);
		std::for_each(m_InputLines.begin(), m_InputLines.end(), [&info](const std::string& _str) -> void {
			const auto& pair = core::StringExtensions::splitStringByDelimeter(_str, ")");
			info.neighbourInfo[pair[0]].insert(pair[1]);
			info.neighbourInfo[pair[1]].insert(pair[0]);
		});

		Day6State com{ "COM" };
		Day6State you{ "YOU" };
		Day6State san{ "SAN" };

		const auto& part1Data = stm.getBreadthFirstExploredStateSpace(com);
		unsigned part1 = std::accumulate(part1Data.begin(), part1Data.end(), 0u, [](unsigned _a, const auto& _p) -> unsigned { return _a + _p.second.second; });		
		const auto& part2 = stm.getShortestSolution(you, san);

		return { std::to_string(part1), std::to_string(part2.size() - 3) };
	}
}
