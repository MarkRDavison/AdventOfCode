#include <2016/Day07Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_set>

namespace TwentySixteen {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Internet Protocol Version 7", 2016, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		const auto part1 = doPart1(m_InputLines);
		const auto part2 = doPart2(m_InputLines);
		return { std::to_string(part1), std::to_string(part2) };
	}

	bool Day07Puzzle::supportsSSL(const std::string& _ip) {
		std::unordered_set<std::string> abas;
		std::unordered_set<std::string> babs;
		bool withinHypernet = false;

		for (const auto& seq : ze::StringExtensions::splitStringByDelimeter(_ip, "[]")) {

			for (unsigned i = 0; i <= seq.size() - 3; ++i) {
				if (seq[i + 0] == seq[i + 1] ||
					seq[i + 0] != seq[i + 2]) {
					continue;
				}

				if (withinHypernet) {
					babs.insert(seq.substr(i, 3));
				}
				else {
					abas.insert(seq.substr(i, 3));
				}
			}

			withinHypernet = !withinHypernet;
		}

		for (const auto& aba : abas) {
			const std::string bab{ aba[1], aba[2], aba[1] };
			if (babs.count(bab) > 0) {
				return true;
			}
		}

		return false;
	}
	bool Day07Puzzle::supportsTLS(const std::string& _ip) {
		bool withinHypernet = false;
		bool abbaOutsideHypernet = false;
		for (const auto& seq : ze::StringExtensions::splitStringByDelimeter(_ip, "[]")) {
			const bool supportsABBA = hasABBA(seq);
			if (supportsABBA) {
				if (withinHypernet) {
					return false;
				}
				else {
					abbaOutsideHypernet = true;
				}
			}

			withinHypernet = !withinHypernet;
		}

		return abbaOutsideHypernet;
	}
	bool Day07Puzzle::hasABBA(const std::string& _sequence) {
		for (unsigned i = 0; i <= _sequence.size() - 4; ++i) {
			if (_sequence[i + 0] != _sequence[i + 1] &&
				_sequence[i + 1] == _sequence[i + 2] &&
				_sequence[i + 0] == _sequence[i + 3]) {
				return true;
			}
		}
		return false;
	}
	int Day07Puzzle::doPart1(const std::vector<std::string>& _input) {
		int count = 0;
		for (const auto& ip : _input) {
			if (supportsTLS(ip)) {
				count++;
			}
		}
		return count;
	}
	int Day07Puzzle::doPart2(const std::vector<std::string>& _input) {
		int count = 0;
		for (const auto& ip : _input) {
			if (supportsSSL(ip)) {
				count++;
			}
		}
		return count;
	}
}
