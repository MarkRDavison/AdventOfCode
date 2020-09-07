#include <2016/Day05Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <zeno/Core/Clock.hpp>
#include <Core/MD5.hpp>
#include <algorithm>

namespace TwentySixteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("How About a Nice Game of Chess?", 2016, 5) {

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
		const auto part1 = doPart1(m_InputLines[0]);
		const auto part2 = doPart2(m_InputLines[0]);
		std::cout << std::endl;
		std::cout << std::endl;
		return { part1, part2 };
	}

	bool Day05Puzzle::isValidIndex(const std::string& _doorId, unsigned _index, char& _nextCharacter) {
		const auto& hash = core::md5(_doorId + std::to_string(_index));

		if (hash[0] == '0' &&
			hash[1] == '0' &&
			hash[2] == '0' &&
			hash[3] == '0' &&
			hash[4] == '0') {

			_nextCharacter = hash[5];
			return true;
		}

		return false;
	}
	bool Day05Puzzle::isValidIndex(const std::string& _doorId, unsigned _index, unsigned& _position, char& _nextCharacter) {
		const auto& hash = core::md5(_doorId + std::to_string(_index));

		if (hash[0] == '0' &&
			hash[1] == '0' &&
			hash[2] == '0' &&
			hash[3] == '0' &&
			hash[4] == '0') {

			_position = hash[5] - '0';
			if (0 <= _position && _position <= 7) {
				_nextCharacter = hash[6];
				return true;
			}
		}

		return false;
	}
	
	std::string Day05Puzzle::doPart1(const std::string& _doorId) {
		std::string password;
		char next;
		for (unsigned i = 0; password.size() < 8; ++i) {
			if (isValidIndex(_doorId, i, next)) {
				password += next;
				std::cout << "Password: " << password << std::string(8 - password.size(), '?') << std::endl;
			}
		}
		std::cout << "Part 1 complete: " << password << std::endl;
		return password;
	}
	std::string Day05Puzzle::doPart2(const std::string& _doorId) {
		std::string password = "????????";
		int valid = 0;
		char next;
		unsigned loc;
		for (unsigned i = 0; valid < 8; ++i) {
			if (isValidIndex(_doorId, i, loc, next)) {
				if (password[loc] == '?') {
					std::cout << "Password: " << password << std::endl;
					valid++;
					password[loc] = next;
				}
			}
		}
		std::cout << "Part 2 complete: " << password << std::endl;
		return password;
	}
}
