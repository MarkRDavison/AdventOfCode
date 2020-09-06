#include <2016/Day04Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>
#include <map>

namespace TwentySixteen {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Security Through Obscurity", 2016, 4) {

	}
	Day04Puzzle::~Day04Puzzle() {

	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		const auto part1 = doPart1(m_InputLines);
		const auto part2 = doPart2(m_InputLines);
		return { std::to_string(part1), std::to_string(part2) };
	}

	bool Day04Puzzle::validateRoom(const std::string& _roomInfo, int& _sectorId) {
		std::map<char, int> charMap;

		const auto& split = ze::StringExtensions::splitStringByDelimeter(_roomInfo, "-[]");
		for (unsigned i = 0; i < split.size() - 2; ++i) {
			for (const auto c : split[i]) {
				charMap[c]++;
			}
		}

		std::vector<std::pair<char, int>> letterInfo;
		for (const auto& [k, v] : charMap) {
			letterInfo.emplace_back(k, v);
		}

		_sectorId = std::stoi(split[split.size() - 2]);
		const auto checksum = split.back();

		std::sort(letterInfo.begin(), letterInfo.end(), [](const auto& _lhs, const auto& _rhs) -> bool {
			if (_lhs.second != _rhs.second) {
				return _lhs.second >= _rhs.second;
			}
			return _lhs.first < _rhs.first;
		});

		for (unsigned i = 0; i < checksum.size(); ++i) {
			if (checksum[i] != letterInfo[i].first) {
				return false;
			}
		}

		return true;
	}
	bool Day04Puzzle::isNorthPoleRoom(const std::string& _roomInfo, int& _sectorId, const std::string& _key) {
		auto& split = ze::StringExtensions::splitStringByDelimeter(_roomInfo, "-[]");
		_sectorId = std::stoi(split[split.size() - 2]);

		for (unsigned i = 0; i < split.size() - 2; ++i) {
			for (auto& c : split[i]) {
				int value = (int)(c - 'a');
				value += _sectorId;
				value %= 26;
				c = (char)(value)+'a';
			}
			if (split[i] == _key) {
				return true;
			}
		}

		return false;
	}

	int Day04Puzzle::doPart1(const std::vector<std::string>& _input) {
		int sum = 0;
		int sectorId = 0;
		for (const auto& i : _input) {
			if (validateRoom(i, sectorId)) {
				sum += sectorId;
			}
		}

		return sum;
	}
	int Day04Puzzle::doPart2(const std::vector<std::string>& _input) {
		int sectorId = 0;
		for (const auto& i : _input) {
			if (isNorthPoleRoom(i, sectorId, "northpole")) {
				return sectorId;
			}
		}
		return 0;
	}
}
