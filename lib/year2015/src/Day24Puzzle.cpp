#include <2015/Day24Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cassert>

namespace TwentyFifteen {

	static long long minQe = std::numeric_limits<long long>::max();

	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("It Hangs in the Balance", 2015, 24) {

	}
	Day24Puzzle::~Day24Puzzle() {

	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		std::vector<int> weights;
		for (const auto& i : m_InputLines) {
			weights.push_back(stoi(i));
		}

		return { 
			std::to_string(findSmallestQuantumEntaglement(weights, 3)), 
			std::to_string(findSmallestQuantumEntaglement(weights, 4)) 
		};
	}
	long long Day24Puzzle::findSmallestQuantumEntaglement(const std::vector<int>& _weights, int _sections) {
		std::vector<int> weights(_weights);
		std::sort(weights.begin(), weights.end());

		using RecurseResult = std::pair<long long, unsigned>;
		const std::function<RecurseResult(const std::vector<int>&, unsigned, int, long long, int)> Recurser = [&Recurser](
			const std::vector<int>& _weights, unsigned _pos, int _remaining, long long _currentQE, int _numberPackages) -> RecurseResult {

				if (_remaining == 0) {
					return { _currentQE, _numberPackages };
				}

				if (_remaining < 0 || _pos == _weights.size()) {
					return { std::numeric_limits<long long>::max(),std::numeric_limits<int>::max() };
				}


				const auto bestIncluding = Recurser(_weights, _pos + 1, _remaining - _weights[_pos], _currentQE * (long long)_weights[_pos], _numberPackages + 1);
				const auto bestExcluding = Recurser(_weights, _pos + 1, _remaining, _currentQE, _numberPackages);

				if (bestIncluding.second < bestExcluding.second) {
					return bestIncluding;
				}
				else if (bestExcluding.second < bestIncluding.second) {
					return bestExcluding;
				}
				else {
					return bestIncluding.first < bestExcluding.first ? bestIncluding : bestExcluding;
				}
		};

		const auto part = Recurser(weights, 0, std::accumulate(_weights.begin(), _weights.end(), 0) / _sections, 1, 0);

		return part.first;
	}
}
