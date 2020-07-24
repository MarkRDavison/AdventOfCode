#include <2015/Day19Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

namespace TwentyFifteen {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Medicine for Rudolph", 2015, 19) {

	}
	Day19Puzzle::~Day19Puzzle() {

	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		const auto& parsed = Day19Puzzle::parseInput(m_InputLines);
		const auto part1 = Day19Puzzle::getDistinctMolecues(parsed.first, parsed.second);
		const auto part2 = Day19Puzzle::stepsToFabricate(parsed.first, parsed.second);
		return { std::to_string(part1), std::to_string(part2) };
	}

	std::pair<Replacements, std::string> Day19Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		Replacements replacements;
		for (const auto& i : _inputLines) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, "=> ");
			if (s.size() == 1) {
				// molecule
				return { replacements, s[0] };
			}
			else if (s.size() == 2) {
				// recipe
				if (s[1].size() % s[0].size() == 0) {
					// Might be a duplicate
					bool duplicate = true;
					for (unsigned i = 0; i < s[1].size(); i += s[0].size()) {
						if (s[0][i % s[0].size()] != s[1][i]) {
							duplicate = false;
							break;
						}
					}
					if (duplicate) {
						continue;
					}
				}

				replacements[s[0]].push_back(s[1]);
			}
		}

		return { replacements, _inputLines.back() };
	}
	int Day19Puzzle::getDistinctMolecues(const Replacements& _replacements, const std::string& _startingMolecule) {
		std::unordered_set<std::size_t> hashedMolecules;

		for (const auto& replacement : _replacements) {
			const auto size = (int)replacement.second.size();

			int occurrences = 0;
			unsigned start = 0;
			while ((start = _startingMolecule.find(replacement.first, start)) != std::string::npos) {
				++occurrences;

				for (const auto& possible : replacement.second) {
					hashedMolecules.insert(std::hash<std::string>()(

						_startingMolecule.substr(0, start) +
						possible +
						_startingMolecule.substr(start + replacement.first.length())

						));
				}
				

				start += replacement.first.length();
			}
		}

		return hashedMolecules.size();
	}

	std::vector<std::string> Day19Puzzle::splitAtCapitalLetter(const std::string& _string) {
		std::vector<std::string>result;

		constexpr char Capitals[]={ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

		std::size_t index = 0;
		while (true) {
			const auto loc = _string.find_first_of(Capitals, index);
			const auto locNext = _string.find_first_of(Capitals, loc+1);

			if (loc == std::string::npos) {
				break;
			}

			if (locNext == std::string::npos) {
				result.push_back(_string.substr(loc));
				break;
			}
			result.push_back(_string.substr(loc, locNext - loc));
			index = locNext;
		}

		return result;
	}
	
	int Day19Puzzle::stepsToFabricate(const Replacements& _replacements, const std::string& _target) {
		// 509 too high
		std::unordered_map<std::string, std::string> reverse;
		std::vector<std::string> reverseKeys;

		std::unordered_map<std::string, int> distanceFromElectron;
		distanceFromElectron["e"] = 0;


		for (const auto& replacement : _replacements) {
			for (const auto& rep : replacement.second) {
				reverse[rep] = replacement.first;
				reverseKeys.push_back(rep);
			}
		}

		bool changeMade = true;
		while (changeMade) {
			changeMade = false;
			for (const auto& [k, v] : _replacements) {
				if (distanceFromElectron.count(k) > 0) {
					for (const auto& replace : v) {
						if (distanceFromElectron.count(replace) == 0) {
							distanceFromElectron[replace] = distanceFromElectron.at(k) + 1;
							changeMade = true;
						}
					}
				}
			}

			for (const auto& [k, v] : _replacements) {
				for (const auto& [dek, dev] : distanceFromElectron) {
					for (const auto& ck : splitAtCapitalLetter(dek)) {
						if (distanceFromElectron.count(ck) == 0) {
							distanceFromElectron[ck] = dev + 1;
							changeMade = true;
						}
					}
				}
			}
		}

		std::sort(reverseKeys.begin(), reverseKeys.end(), 
			[&distanceFromElectron](const std::string& _lhs, const std::string& _rhs) -> bool {
				return distanceFromElectron.at(_lhs) < distanceFromElectron.at(_rhs);
			});

		int count = 0;
		std::string molecule(_target);
		while (true) {
			for (const auto& replacement : reverseKeys) {
				if (std::size_t loc = molecule.find(replacement); loc != std::string::npos) {
					molecule =
						molecule.substr(0, loc) +
						reverse[replacement] +
						molecule.substr(loc + replacement.size());
					count++;
				}
			}
			bool invalid = false;
			for (const char c : molecule) {
				if (c != 'e') {
					invalid = true;
					break;
				}
			}
			if (!invalid) {
				break;
			}
		}

		return count;
	}
}
