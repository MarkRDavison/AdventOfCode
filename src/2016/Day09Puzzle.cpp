#include <2016/Day09Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cctype>
#include <regex>

namespace TwentySixteen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Explosives in Cyberspace", 2016, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	bool ischar(char _c) {
		return 'A' <= _c && _c <= 'Z';
	}
	std::pair<int, int> extractExpansionInfo2(const std::string& _string) {
		const auto& parts = core::StringExtensions::splitStringByDelimeter(_string, "(x)");

		if (parts.empty()) {
			return {};
		}

		return { std::atoi(parts[0].c_str()), std::atoi(parts[1].c_str()) };
	}

	unsigned part2Special(const std::string& _str) {
		std::vector<unsigned> weights(_str.size(), 1);
		unsigned length = 0;

		for (unsigned i = 0; i < _str.size(); ++i) {
			unsigned kk = i;
			const char c = _str[i];
			if (ischar(c)) {
				length += weights[i];
			} else if (c == '(') {
				for (unsigned j = i; j < _str.size(); ++j) {
					if (_str[j] == ')') {
						const std::string expansion = _str.substr(i, j - i + 1);
						i = j;
						auto info = extractExpansionInfo2(expansion);
						for (unsigned k = i; k < i + info.first; ++k) {
							weights[k + 1] *= info.second;
						}
						break;
					}
				}
			}
		}

		return length;
	}

	uint64_t decompressLength(const std::string& _input) {
		uint64_t result = 0;

		std::smatch m;
		const std::regex regex(R"(^\((\d+)x(\d+)\).*)");
		std::string::const_iterator it, startIt = _input.begin();

		while ((it = std::find(startIt, _input.end(), '(')) != _input.end()) {

			if (std::regex_match(it, _input.end(), m, regex)) {
				result += std::distance(startIt, it);
				it = std::find(it, _input.end(), ')') + 1;
				auto newIt = it + std::stoi(m[1].str().c_str());
				result += std::atoi(m[2].str().c_str()) * decompressLength(std::string(it, newIt));
				startIt = it = newIt;
			}
		}

		result += std::distance(startIt, _input.end());
		return result;
	}
	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	std::pair<int, int> extractExpansionInfo(const std::string& _string) {
		const auto& parts = core::StringExtensions::splitStringByDelimeter(_string, "(x)");

		if (parts.empty()) {
			return {};
		}

		return { std::atoi(parts[0].c_str()), std::atoi(parts[1].c_str()) };
	}
	unsigned getLength(const std::string& _string, bool _part1) {
		unsigned s = 0;

		std::string str(_string);
		while (!str.empty()) {
			auto expansionStartLocation = str.find("(");
			if (expansionStartLocation == std::string::npos) {
				s += str.size();
				str.clear();
				continue;
			}
			s += expansionStartLocation;
			str = str.substr(expansionStartLocation);

			const auto expansionEndLocation = str.find(")");

			auto expansion = str.substr(0, expansionEndLocation + 1);

			auto info = extractExpansionInfo(expansion);

			str = str.substr(expansionEndLocation + 1);

			std::string local;
			for (int i = 0; i < info.second; ++i) {
				local += str.substr(0, info.first);
			}

			str = str.substr(info.first);

			if (_part1) {
				s += local.size();
			}
			else {
				//str = local + str;
				s += getLength(local, _part1);
			}
		}
		return s;
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		const std::string& input = m_InputLines[0];

		unsigned part1 = getLength(input, true);
		unsigned part2 = getLength(input, false); //decompressLength(input);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
