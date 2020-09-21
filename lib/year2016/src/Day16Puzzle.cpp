#include <2016/Day16Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Dragon Checksum", 2016, 16) {

	}
	Day16Puzzle::~Day16Puzzle() {

	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		const auto part1 = calculateChecksumFromStateForSize(m_InputLines[0], 272);
		const auto part2 = calculateChecksumFromStateForSize(m_InputLines[0], 35651584);
		return { part1, part2 };
	}

	std::string Day16Puzzle::performDragonProcess(const std::string& _input) {
		std::string b(_input);
		std::reverse(b.begin(), b.end());

		for (auto& c : b) {
			if (c == '0') {
				c = '1';
			}
			else {
				c = '0';
			}
		}

		return _input + "0" + b;
	}

	std::string Day16Puzzle::performDragonProcessForDesiredSize(const std::string& _input, unsigned _size) {
		std::string data(_input);

		while (data.size() < _size) {
			data = performDragonProcess(data);
		}

		return data.substr(0, _size);
	}

	std::string Day16Puzzle::calculateChecksum(const std::string& _input) {

		std::string checksum(_input);

		do {
			std::string nextChecksum;

			for (unsigned i = 0; i < checksum.size(); i += 2) {
				nextChecksum += (checksum[i + 0] == checksum[i + 1]
					? '1'
					: '0');
			}

			checksum = nextChecksum;
		}
		while (checksum.size() % 2 != 1);

		return checksum;
	}

	std::string Day16Puzzle::calculateChecksumFromStateForSize(const std::string& _state, unsigned _length) {
		const std::string data = performDragonProcessForDesiredSize(_state, _length);
		return calculateChecksum(data);
	}

}
