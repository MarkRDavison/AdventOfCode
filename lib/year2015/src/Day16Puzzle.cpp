#include <2015/Day16Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Aunt Sue", 2015, 16) {

	}
	Day16Puzzle::~Day16Puzzle() {

	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		const auto& parsed = parseInput(m_InputLines);
		std::unordered_map<std::string, int> data;
		data["children"] = 3;
		data["cats"] = 7;
		data["samoyeds"] = 2;
		data["pomeranians"] = 3;
		data["akitas"] = 0;
		data["vizslas"] = 0;
		data["goldfish"] = 5;
		data["trees"] = 3;
		data["cars"] = 2;
		data["perfumes"] = 1;

		const auto& potentials1 = getPotentialIds(data, parsed, false);
		const auto& potentials2 = getPotentialIds(data, parsed, true);

		return { std::to_string(potentials1[0]), std::to_string(potentials2[0]) };
	}

	std::vector<SueInfo> Day16Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		std::vector<SueInfo> result;

		for (const auto& i : _inputLines) {
			SueInfo& info = result.emplace_back();
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, " :,");
			info.id = stoi(s[1]);

			for (unsigned i = 2; i < s.size() - 1; i += 2) {
				const auto& name = s[i];
				const auto amount = stoi(s[i + 1]);

				info.compounds[name] = amount;
			}
		}

		return result;
	}
	bool Day16Puzzle::isInvalid(const SueInfo& _sueInfo, const std::unordered_map<std::string, int>&_data, bool _part2) {

		for (const auto& [k, v] : _sueInfo.compounds) {
			if (_data.count(k) > 0) {
				if (_part2) {
					if (k == "cats" || k == "trees") {
						if (v <= _data.at(k)) {
							return true;
						}
					}
					else if (k == "pomeranians" || k == "goldfish") {
						if (v >= _data.at(k)) {
							return true;
						}
					}
					else {
						if (_data.at(k) != v) {
							return true;
						}
					}
				} else {
					if (_data.at(k) != v) {
						return true;
					}
				}
			}
		}

		return false;
	}
	std::vector<int> Day16Puzzle::getPotentialIds(const std::unordered_map<std::string, int>& _data, const std::vector<SueInfo>& _sueInfo, bool _part2) {
		std::vector<int> potentials;

		for (const auto& sue : _sueInfo) {
			if (isInvalid(sue, _data, _part2)) {
				continue;
			}
			potentials.push_back(sue.id);
		}

		return potentials;
	}
}
