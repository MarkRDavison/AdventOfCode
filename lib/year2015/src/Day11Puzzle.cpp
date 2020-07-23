#include <2015/Day11Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Corporate Policy", 2015, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		const auto part1 = getNextPassword(m_InputLines[0]);
		return { part1, getNextPassword(part1) };
	}
	std::string Day11Puzzle::increment(const std::string& _password) {
		std::string p(_password);

		p.back()++;
		for (unsigned i = 0; i < _password.size(); ++i) {
			unsigned j = _password.size() - 1 - i;
			if (p[j] > 'z') {
				p[j] -= 26;
				if (j > 0) {
					p[j - 1]++;
				}
			}
		}
		
		for (unsigned i = 0; i < _password.size(); ++i) {
			char& c = p[i];
			while (c == 'i' || c == 'o' || c == 'l') {
				c++;
				for (unsigned j = i + 1; j < _password.size(); ++j) {
					p[j] = 'a';
				}
				break;
			}
		}

		return p;
	}
	bool Day11Puzzle::validate(const std::string& _password) {
		bool tripleIncreaseFound = false;
		bool doubleDoubleFound = false;
		char doubleFirstChar = '?';
		if (_password == "abcdffaa") {
			std::cout << "SHOULD WORK\n";
		}
		for (unsigned i = 0; i < _password.size(); ++i) {
			char c = _password[i];
			if (c == 'i' || c == 'o' || c == 'l') {
				return false;
			}
			if (!tripleIncreaseFound && i >= 2) {
				if (_password[i - 2] + 2 == _password[i - 1] + 1 &&
					_password[i - 1] + 1 == _password[i + 0]) {
					tripleIncreaseFound = true;
				}
			}

			if (!doubleDoubleFound && i >= 1) {
				if (_password[i - 1] == c) {
					if (doubleFirstChar == '?') {
						doubleFirstChar = c;
					}
					else if (c != doubleFirstChar) {
						doubleDoubleFound = true;
					}
				}
			}
		}
		return tripleIncreaseFound && doubleDoubleFound;
	}
	std::string Day11Puzzle::getNextPassword(const std::string& _password) {
		std::string p(_password);

		do {
			p = increment(p);
		} while (!validate(p));

		return p;
	}
}
