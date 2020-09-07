#include <2016/Day06Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>

namespace TwentySixteen {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Signals and Noise", 2016, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		const auto part1 = doPart1(m_InputLines);
		const auto part2 = doPart2(m_InputLines);
		return { part1, part2 };
	}

	void Day06Puzzle::processSignal(const std::string& _signal, std::vector<std::unordered_map<char, int>>& _instances) {
		for (unsigned i = 0; i < _signal.size(); ++i) {
			_instances[i][_signal[i]]++;
		}
	}

	std::string Day06Puzzle::doPart1(const std::vector<std::string>& _input) {
		auto instances = std::vector<std::unordered_map<char, int>>(_input[0].size());
		for (const auto& i : _input) {
			processSignal(i, instances);
		}

		std::string message;
		for (const auto& info : instances) {
			const auto& max = std::max_element(info.begin(), info.end(), [](const auto& _lhs, const auto& _rhs) -> bool {
				return _lhs.second < _rhs.second;
				});

			message += (*max).first;
		}

		return message;
	}
	std::string Day06Puzzle::doPart2(const std::vector<std::string>& _input) {
		auto instances = std::vector<std::unordered_map<char, int>>(_input[0].size());
		for (const auto& i : _input) {
			processSignal(i, instances);
		}

		std::string message;
		for (const auto& info : instances) {
			const auto& max = std::min_element(info.begin(), info.end(), [](const auto& _lhs, const auto& _rhs) -> bool {
				return _lhs.second < _rhs.second;
				});

			message += (*max).first;
		}

		return message;
	}
}
