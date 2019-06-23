#include <2016/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>

namespace TwentySixteen {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Internet Protocol Version 7", 2016, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}

	bool Day07Puzzle::containsAutonomousBridgeBypassAnnotation(const std::string& _string) {
		if (_string.size() < 4) {
			return false;
		}

		for (unsigned i = 0; i < _string.size() - 3; ++i) {
			const char a1 = _string[i + 0];
			const char b1 = _string[i + 1];
			const char b2 = _string[i + 2];
			const char a2 = _string[i + 3];

			if (a1 == a2 && 
				b1 == b2 && 
				a1 != b1 && 
				a2 != b2) {
				return true;
			}
		}

		return false;
	}

	std::vector<std::string> Day07Puzzle::getABAorBAB(const std::vector<std::string>& _outsideBracketParts) {
		std::vector<std::string> result;

		for (const std::string& _part : _outsideBracketParts) {
			for (unsigned i = 0; i < _part.size() - 2; ++i) {
				if (_part[i + 0] == _part[i + 2] &&
					_part[i + 0] != _part[i + 1]) {
					result.push_back(_part.substr(i, 3));
				}
			}
		}

		return result;
	}

	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		// Area-Broadcast Accessor outside square brackets
		// Byte Allocation Block within square brackets

		unsigned part1 = 0;
		unsigned part2 = 0;

		for (const auto& line : m_InputLines) {
			std::vector<std::string> outside{};
			std::vector<std::string> inside{};
			{	// Part 1
				bool withinBrackets = false;
				bool supportsTLS = false;
				bool hasTLSFailure = false;
				for (const auto& part : core::StringExtensions::splitStringByDelimeter(line, "[]")) {

					if (containsAutonomousBridgeBypassAnnotation(part)) {
						if (!withinBrackets) {
							supportsTLS = true;
						} else {
							hasTLSFailure = true;
						}
					}

					if (withinBrackets) {
						inside.push_back(part);
					} else {
						outside.push_back(part);
					}

					withinBrackets = !withinBrackets;
				}

				if (supportsTLS && !hasTLSFailure) {
					part1++;
				}
			}
			{	// Part 2
				const auto& abas = getABAorBAB(outside);
				const auto& babs = getABAorBAB(inside);
				for (const auto& aba : abas) {
					bool found = false;
					for (const auto& bab : babs) {
						if (aba[0] == aba[2] &&
							aba[0] == bab[1] &&
							bab[0] == bab[2] &&
							bab[0] == aba[1] &&
							aba[0] != aba[1] &&
							bab[0] != bab[1]) {
							part2++;

							if (getVerbose()) {
								std::cout << "Found " << aba << " & " << bab << " in " << line << std::endl;
							}
							found = true;
							break;
						}
					}
					if (found) {
						break;
					}
				}
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
