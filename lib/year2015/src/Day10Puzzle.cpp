#include <2015/Day10Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Elves Look, Elves Say", 2015, 10) {

	}
	Day10Puzzle::~Day10Puzzle() {

	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		return { 
			std::to_string(getResult(m_InputLines[0], 40)),
			std::to_string(getResult(m_InputLines[0], 50))
		};
	}

	std::size_t Day10Puzzle::getResult(const std::string& _input, std::size_t _iterations) {
		std::size_t result = 0;

		using Info = std::pair<std::size_t, std::size_t>;
		std::vector<Info> info[2];
		std::size_t infoIndex = 0;

		std::size_t i = 0;
		while (i < _input.size()) {
			const char c = _input[i];
			std::size_t loc = i;
			while (loc < _input.size() - 1 && _input[loc+1] == c) {
				loc++;
			}

			info[0].emplace_back(loc - i + 1, c - '0');

			i = loc + 1;
		}

		for (unsigned iter = 1; iter < _iterations; iter++) {
			auto oldInfoIndex = infoIndex;
			auto newInfoIndex = (infoIndex + 1) % 2;

			infoIndex = (infoIndex + 1) % 2;
			info[infoIndex].clear();

			for (std::size_t pastInfoIter = 0; pastInfoIter < info[oldInfoIndex].size(); ++pastInfoIter) {
				const auto& pastInfo = info[oldInfoIndex][pastInfoIter];
				if (pastInfo.first == pastInfo.second) {
					if (pastInfoIter > 0) {
						auto& lastAddedInfo = info[newInfoIndex].back();

						if (lastAddedInfo.second == pastInfo.second) {
							lastAddedInfo.first += pastInfo.first;
						}
						else {
							info[newInfoIndex].emplace_back(2, pastInfo.second);
						}
					}
					else {
						info[newInfoIndex].emplace_back(2, pastInfo.second);
					}
				} else {
					if (pastInfoIter > 0) {
						auto& lastAddedInfo = info[newInfoIndex].back();
						if (lastAddedInfo.second == pastInfo.first) {
							lastAddedInfo.first += 1;
						}
						else {
							info[newInfoIndex].emplace_back(1, pastInfo.first);
						}
					} else {
						info[newInfoIndex].emplace_back(1, pastInfo.first);
					}
					info[newInfoIndex].emplace_back(1, pastInfo.second);
				}
			}

			infoIndex = newInfoIndex;
		}

		return info[infoIndex].size() * 2;
	}
}
