#include <2020/Day04Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <set>

namespace TwentyTwenty {

	// TODO: Move this to utility framework
	std::vector<std::string> splitStringByLines(const std::string& _parameter) {
		std::vector<std::string> result;
		std::stringstream stringStream(_parameter);
		std::string line;
		while (std::getline(stringStream, line)) {
			result.push_back(line);
		}

		return result;
	}


	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Passport Processing", 2020, 4) {
	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}


	struct Passport {
		std::string byr;
		std::string iyr;
		std::string eyr;
		std::string hgt;
		std::string hcl;
		std::string ecl;
		std::string pid;
		std::string cid;
	};

	std::vector<Passport> loadPassports(const std::vector<std::string>& _inputLines) {
		std::vector<Passport> passports;
		passports.emplace_back();

		for (const auto& i : _inputLines) {
			if (i.empty()) {
				passports.emplace_back();
				continue;
			}

			Passport& current = passports.back();

			for (const auto& fields : ze::StringExtensions::splitStringByDelimeter(i, " ")) {
				const auto& parts = ze::StringExtensions::splitStringByDelimeter(fields, ":");

				const auto& fieldName = parts[0];
				const auto& fieldValue = parts[1];

				if (fieldName == "byr") {
					current.byr = fieldValue;
				}
				else if (fieldName == "iyr") {
					current.iyr = fieldValue;
				}
				else if (fieldName == "eyr") {
					current.eyr = fieldValue;
				}
				else if (fieldName == "hgt") {
					current.hgt = fieldValue;
				}
				else if (fieldName == "hcl") {
					current.hcl = fieldValue;
				}
				else if (fieldName == "ecl") {
					current.ecl = fieldValue;
				}
				else if (fieldName == "pid") {
					current.pid = fieldValue;
				}
				else if (fieldName == "cid") {
					current.cid = fieldValue;
				}
			}
		}

		return passports;
	}

	int getPart1(const std::vector<Passport>& _passports) {
		int valid = 0;

		for (const auto& p : _passports) {
			if (!p.byr.empty() &&
				!p.iyr.empty() &&
				!p.eyr.empty() &&
				!p.hgt.empty() &&
				!p.hcl.empty() &&
				!p.ecl.empty() &&
				!p.pid.empty()
				) {
				valid++;
			}
		}

		return valid;
	}
	int getPart2(const std::vector<Passport>& _passports) {
		int valid = 0;

		const std::set<char> digits{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		const std::set<char> hexDigits{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

		for (const auto& p : _passports) {

			if (!p.byr.empty()) {
				const int year = std::stoi(p.byr);
				if (1920 > year || year > 2002) {
					continue;
				}
			}
			else {
				continue;
			}

			if (!p.iyr.empty()) {
				const int year = std::stoi(p.iyr);
				if (2010 > year || year > 2020) {
					continue;
				}
			}
			else {
				continue;
			}

			if (!p.eyr.empty()) {
				const int year = std::stoi(p.eyr);
				if (2020 > year || year > 2030) {
					continue;
				}
			}
			else {
				continue;
			}

			if (!p.hgt.empty()) {
				bool cm = (
					'c' == p.hgt[p.hgt.size() - 2] &&
					'm' == p.hgt[p.hgt.size() - 1]
					);
				bool in = (
					'i' == p.hgt[p.hgt.size() - 2] &&
					'n' == p.hgt[p.hgt.size() - 1]
					);

				if (!cm && !in) {
					continue;
				}

				const int height = std::stoi(p.hgt.substr(0, p.hgt.size() - 2));

				if (cm && (150 > height || height > 193)) {
					continue;
				}
				else if (in && (59 > height || height > 76)) {
					continue;
				}
			}
			else {
				continue;
			}

			if (p.hcl.size() == 7) {
				if (p.hcl[0] != '#' ||
					hexDigits.count(p.hcl[1]) <= 0 ||
					hexDigits.count(p.hcl[2]) <= 0 ||
					hexDigits.count(p.hcl[3]) <= 0 ||
					hexDigits.count(p.hcl[4]) <= 0 ||
					hexDigits.count(p.hcl[5]) <= 0 ||
					hexDigits.count(p.hcl[6]) <= 0) {
					continue;
				}
			}
			else {
				continue;
			}

			if (!p.ecl.empty()) {
				if (p.ecl != "amb" &&
					p.ecl != "blu" &&
					p.ecl != "brn" &&
					p.ecl != "gry" &&
					p.ecl != "grn" &&
					p.ecl != "hzl" &&
					p.ecl != "oth") {
					continue;
				}
			}
			else {
				continue;
			}

			if (p.pid.size() == 9) {
				if (digits.count(p.pid[0]) <= 0 ||
					digits.count(p.pid[1]) <= 0 ||
					digits.count(p.pid[2]) <= 0 ||
					digits.count(p.pid[3]) <= 0 ||
					digits.count(p.pid[4]) <= 0 ||
					digits.count(p.pid[5]) <= 0 ||
					digits.count(p.pid[6]) <= 0 ||
					digits.count(p.pid[7]) <= 0 ||
					digits.count(p.pid[8]) <= 0) {
					continue;
				}
			}
			else {
				continue;
			}

			valid++;
		}

		return valid;
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		auto passports = loadPassports(m_InputLines);

		auto part1 = getPart1(passports);
		auto part2 = getPart2(passports);

		return { std::to_string(part1), std::to_string(part2) };
	}
	
}
