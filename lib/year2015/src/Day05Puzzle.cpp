#include <2015/Day05Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_set>
#include <algorithm>
#include <numeric>

namespace TwentyFifteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Doesn't He Have Intern-Elves For This?", 2015, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		return { 
			std::to_string(getPart1(m_InputLines)),
			std::to_string(getPart2(m_InputLines))
		};
	}

	int Day05Puzzle::getPart1(const std::vector<std::string>& _strings) {
		return std::accumulate(_strings.begin(), _strings.end(), 0, [](int _accumulate, const std::string& _string) -> int {
			int is_nice = isNicePart1(_string) ? 1 : 0;
			return _accumulate + is_nice;
		});
	}
	int Day05Puzzle::getPart2(const std::vector<std::string>& _strings) {
		return std::accumulate(_strings.begin(), _strings.end(), 0, [](int _accumulate, const std::string& _string) -> int {
			int is_nice = isNicePart2(_string) ? 1 : 0;
			return _accumulate + is_nice;
			});
	}
	bool Day05Puzzle::isNicePart1(const std::string& _string) {

		int vowelsFound = 0;
		bool duplicateFound{ false };

		for (unsigned i = 0; i < _string.size(); ++i) {
			const char cCurr = _string[i];
			
			if (i > 0) {
				const char cPrev = _string[i-1];
				if (cCurr == cPrev) {
					duplicateFound = true;
				}
				if (cPrev == 'a' && cCurr == 'b' ||
					cPrev == 'c' && cCurr == 'd' ||
					cPrev == 'p' && cCurr == 'q' ||
					cPrev == 'x' && cCurr == 'y') {
					return false;
				}
			}

			if (cCurr == 'a' || 
				cCurr == 'e' || 
				cCurr == 'i' || 
				cCurr == 'o' || 
				cCurr == 'u') {
				vowelsFound++;
			}
		}		

		return vowelsFound >= 3 && duplicateFound;
	}
	bool Day05Puzzle::isNicePart2(const std::string& _string) {

		bool mirrored = false;
		bool duplicated = false;

		for (unsigned i = 0; i < _string.size(); ++i) {
			const char cCurr = _string[i];
			if (!duplicated && i > 0) {
				const char cBack = _string[i - 1];

				for (unsigned j = i + 1; j < _string.size(); ++j) {
					if (cBack == _string[j] &&
						cCurr == _string[j + 1]) {
						duplicated = true;
						break;
					}
				}
			}

			if (!mirrored && i > 1) {
				if (cCurr == _string[i - 2]) {
					mirrored = true;
				}
			}

			if (mirrored && duplicated) {
				return true;
			}
		}


		return false;
	}
}
