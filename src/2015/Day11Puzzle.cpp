#include <2015/Day11Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

namespace TwentyFifteen {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Corporate Policy", 2015, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		std::string password1 = m_InputLines[0];
		while (true) {
			if (isValid(password1)) {
				break;
			}
			password1 = incrementPassword(password1);
		}

		password1 = incrementPassword(password1);
		std::string password2 = password1;
		while (true) {
			if (isValid(password2)) {
				break;
			}
			password2 = incrementPassword(password2);
		}

		return { password1, password2 };
	}

	bool Day11Puzzle::isValid(const std::string& _password) {
		// Passwords must include one increasing straight of at least three letters, like abc, bcd, cde, and so on, up to xyz.They cannot skip letters; abd doesn't count.
		// Passwords may not contain the letters i, o, or l, as these letters can be mistaken for other charactersand are therefore confusing.
		// Passwords must contain at least two different, non - overlapping pairs of letters, like aa, bb, or zz.

		unsigned doublesFound = 0;
		unsigned minDoubleStartIndex = 0;
		bool tripleFound = false;
		for (unsigned i = 0; i < _password.size(); ++i) {
			char c = _password[i];
			if (c == 'i' || c == 'o' || c == 'l') {
				return false;
			}
			if (!tripleFound) {
				if (i + 2 < _password.size()) {
					// We can check the triple
					unsigned first = static_cast<unsigned>(_password[i + 0]);
					unsigned second = static_cast<unsigned>(_password[i + 1]);
					unsigned third = static_cast<unsigned>(_password[i + 2]);

					if (first + 2 == second + 1 &&
						second + 1 == third) {
						tripleFound = true;
					}
				}
			}
			if (doublesFound < 2 && minDoubleStartIndex <= i) {
				if (i + 1 < _password.size()) {
					if (_password[i + 0] == _password[i + 1]) {
						minDoubleStartIndex = i + 2;
						doublesFound++;
					}
				}
			}
		}


		return tripleFound && doublesFound == 2;
	}

	std::string Day11Puzzle::incrementPassword(const std::string& _password) {
		std::string password(_password);
		unsigned i = password.size();
		do {
			i--;


			if (password[i] == 'z') {
				assert(i != 0);
				password[i] = 'a';
				continue;
			}
			password[i]++;
			break;


		} while (i > 0);

		return password;
	}
}
