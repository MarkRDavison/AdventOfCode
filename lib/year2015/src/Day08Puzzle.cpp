#include <2015/Day08Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <numeric>

namespace TwentyFifteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Matchsticks", 2015, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		const auto p1 = getPart1(m_InputLines);
		const auto p2 = getPart2(m_InputLines);

		return { std::to_string(p1), std::to_string(p2) };
	}

	std::size_t Day08Puzzle::getPart1(const std::vector<std::string>& _input) {
		return std::accumulate(_input.begin(), _input.end(), 0u,
			[](std::size_t _a, const std::string& _line) -> std::size_t {
				const auto data = getLengthMemory(_line);

				_a += data.first;
				_a -= data.second;

				return _a;
			}
		);
	}
	std::size_t Day08Puzzle::getPart2(const std::vector<std::string>& _input) {
		return std::accumulate(_input.begin(), _input.end(), 0u,
			[](std::size_t _a, const std::string& _line) -> std::size_t {
				const auto data = getLengthEncode(_line);

				_a += data.second;
				_a -= data.first;

				return _a;
			}
		);
	}
	
	LengthData Day08Puzzle::getLengthMemory(const std::string& _string) {
		std::size_t s = 0;
		std::size_t i = 1;
		while (i < _string.size() - 1) {
			char c = _string[i];
			if (c == '\\') {
				if (_string[i + 1] == 'x') {
					// Hex
					s++;
					i += 4;
				} else {
					// escape
					s++;
					i += 2;
				}
			} else {
				s++;
				i++;
			}
		}

		return std::make_pair(_string.size(), s);
	}

	LengthData Day08Puzzle::getLengthEncode(const std::string& _string) {
		std::size_t s = 2;

		for (std::size_t i = 0; i < _string.size(); ++i) {
			char c = _string[i];

			if (c == '"' ||
				c == '\\') {
				s += 2;
			}
			else {
				s += 1;
			}
		}

		return std::make_pair(_string.size(), s);
	}
}
