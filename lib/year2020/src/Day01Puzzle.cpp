#include <2020/Day01Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <algorithm>

namespace TwentyTwenty {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Report Repair", 2020, 1) {
	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {

		const int target = 2020;

		std::string part1;
		std::string part2;

		std::vector<int> nums;

		for (const auto& i : m_InputLines) {
			nums.push_back(std::stoi(i));
		}

		for (unsigned i = 0; i < nums.size(); ++i) {
			const int iNum = nums[i];
			for (unsigned j = i + 1; j < nums.size(); ++j) {
				const int jNum = nums[j];

				const int ijSum = iNum + jNum;

				if (ijSum == target && part1.empty()) {
					part1 = std::to_string(iNum * jNum);
				}

				for (unsigned k = j + 1; k < nums.size(); ++k) {
					const int kNum = nums[k];

					const int ijkSum = ijSum + kNum;

					if (ijkSum == target && part2.empty()) {
						part2 = std::to_string(iNum * jNum * kNum);
					}
				}
			}
		}

		return { part1, part2 };
	}
}
