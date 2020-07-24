#include <2015/Day17Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <functional>
#include <algorithm>
#include <numeric>
#include <Bits.h>

namespace TwentyFifteen {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("No Such Thing as Too Much", 2015, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	

	template<typename T>
	void iterateCombinations(const T& c, int k, std::function<void(const T&)> _callback) {
		int n = c.size();
		int combo = (1 << k) - 1;
		while (combo < 1 << n) {

			T temp;
			for (int i = 0; i < n; ++i) {
				if ((combo >> i) & 1) {
					temp.push_back(c[i]);
				}
			}
			_callback(temp);

			int x = combo & -combo;
			int y = combo + x;
			int z = (combo & ~y);
			combo = z / x;
			combo >>= 1;
			combo |= y;
		}
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		const auto result = getResult(m_InputLines, Volume);

		return { std::to_string(result.first), std::to_string(result.second) };
	}
	std::pair<int, int> Day17Puzzle::getResult(const std::vector<std::string>& _containers, int _volume) {
		std::vector<int> containers;
		for (const auto& s : _containers) {
			containers.push_back(stoi(s));
		}
		std::sort(containers.begin(), containers.end());
		int valid = 0;
		unsigned min = containers.size();
		std::unordered_map<unsigned, int> validPerSize;
		const std::function<void(const std::vector<int>&)> call = [&](const std::vector<int>& _vec) -> void {
			if (std::accumulate(_vec.begin(), _vec.end(), 0) == _volume) {
				valid++;
				validPerSize[_vec.size()]++;
				if (min > _vec.size()) {
					min = _vec.size();
				}
			}
		};

		for (unsigned i = 1; i <= containers.size(); ++i) {
			iterateCombinations(containers, i, call);
		}

		return { valid, validPerSize[min] };
	}
}
