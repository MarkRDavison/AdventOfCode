#include <2020/Day13Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>
#include <cassert>

namespace TwentyTwenty {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Shuttle Search", 2020, 13) {
	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		const auto& parsed = Day13Puzzle::parseInput(m_InputLines);

		const auto& part1 = Day13Puzzle::doPart1(parsed);
		const auto& part2 = Day13Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	Day13Struct Day13Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		Day13Struct parsed;
		parsed.earliest = std::stoll(_inputLines[0]);
		for (const auto& s : ze::StringExtensions::splitStringByDelimeter(_inputLines[1], ",")) {
			if (s != "x") {
				parsed.busIds.insert(std::stoll(s));
				parsed.busIdsWithSpacing.push_back(std::stoll(s));
			}
			else {
				parsed.busIdsWithSpacing.push_back(-1);
			}
		}
		return parsed;
	}

	std::string Day13Puzzle::doPart1(const Day13Struct& _parsed) {

		std::unordered_map<long long, long long> busIdsEarliest;

		for (const auto busId : _parsed.busIds) {
			const long long firstArival = ((_parsed.earliest / busId) + 1)* busId;
			busIdsEarliest[busId] = firstArival;
		}

		const auto& minElement = std::min_element(busIdsEarliest.begin(), busIdsEarliest.end(),
			[](const auto& _lhs, const auto& _rhs) -> int {
				return _lhs.second < _rhs.second;
			});

		const auto& [busId, arrivalTime] = *minElement;

		const long long waitTime = arrivalTime - _parsed.earliest;

		const long long answer = waitTime * busId;

		return std::to_string(answer);
	}

	// https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
	long long inv(long long a, long long m) {
		long long m0 = m, t, q;
		long long x0 = 0, x1 = 1;

		if (m == 1) {
			return 0;
		}

		while (a > 1) {
			q = a / m;
			t = m;
			m = a % m, a = t;
			t = x0;
			x0 = x1 - q * x0;
			x1 = t;
		}

		if (x1 < 0) {
			x1 += m0;
		}

		return x1;
	}

	// https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
	long long chineseRemainderTheorem(const std::vector<long long>& _modulos, const std::vector<long long>& _remainders)
	{
		assert(_modulos.size() == _remainders.size());
		long long prod = 1;
		for (unsigned i = 0; i < _modulos.size(); i++) {
			prod *= _modulos[i];
		}

		long long result = 0;

		for (unsigned i = 0; i < _modulos.size(); i++)
		{
			long long pp = prod / _modulos[i];
			result += _remainders[i] * inv(pp, _modulos[i]) * pp;
		}

		return result % prod;
	}

	std::string Day13Puzzle::doPart2(const Day13Struct& _parsed) {

		std::vector<long long> modulos;
		std::vector<long long> remainders;

		int delay = 0;
		for (const auto& id : _parsed.busIdsWithSpacing) {
			if (id > 0) {
				modulos.push_back(id);
				remainders.push_back(id - delay);
			}
			delay++;
		}

		return std::to_string(chineseRemainderTheorem(modulos, remainders));
	}
}
