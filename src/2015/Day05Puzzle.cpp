#include <2015/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Doesn't He Have Intern-Elves For This?", 2015, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	
	bool Day05Puzzle::isNicePart1(const std::string& _string) {
		// It contains at least three vowels(aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
		// It contains at least one letter that appears twice in a row, like xx, abcdde(dd), or aabbccdd(aa, bb, cc, or dd).
		// It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.

		unsigned vowelCount = 0;
		bool doubleCharacter = false;

		for (unsigned i = 0; i < _string.size(); ++i) {
			if (vowelCount < 3) {
				if (isVowel(_string[i])) {
					vowelCount++;
				}
			}
			if (i != _string.size() - 1) {
				if (!doubleCharacter) {
					doubleCharacter = _string[i] == _string[i + 1];
				}
				if (_string[i] == 'a' && _string[i + 1] == 'b' ||
					_string[i] == 'c' && _string[i + 1] == 'd' ||
					_string[i] == 'p' && _string[i + 1] == 'q' ||
					_string[i] == 'x' && _string[i + 1] == 'y') {
					return false;
				}
			}
		}


		return vowelCount >= 3 && doubleCharacter;
	}

	bool Day05Puzzle::isNicePart2(const std::string& _string) {
		// It contains a pair of any two letters that appears at least twice in the string without overlapping, like xyxy(xy) or aabcdefgaa(aa), but not like aaa(aa, but it overlaps).

		bool valid = false;
		for (unsigned i = 0; i < _string.size() - 2; ++i) {
			const char c1 = _string[i];
			const char c2 = _string[i+1];
			for (unsigned j = i + 2; j < _string.size(); ++j) {
				if (c1 == _string[j] &&
					c2 == _string[j + 1]) {
					valid = true;
					break;
				}
			}
			if (valid) {
				break;
			}
		}

		if (!valid) {
			return false;
		}

		// It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi(efe), or even aaa.
		for (unsigned i = 0; i <= _string.size() - 3; ++i) {
			if (_string[i] == _string[i + 2]) {
				return true;
			}
		}

		return false;
	}
	bool Day05Puzzle::isVowel(char _c) {
		return
			_c == 'a' ||
			_c == 'e' ||
			_c == 'i' ||
			_c == 'o' ||
			_c == 'u';
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {

		unsigned niceLines_1 = 0;
		unsigned niceLines_2 = 0;

		for (const std::string& _line : m_InputLines) {
			niceLines_1 += isNicePart1(_line) ? 1 : 0;
			niceLines_2 += isNicePart2(_line) ? 1 : 0;
		}
		
		return { std::to_string(niceLines_1), std::to_string(niceLines_2) };
	}
}
