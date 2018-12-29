#include <2018/Day14Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {

	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Chocolate Charts", 2018, 14) {

	}
	Day14Puzzle::~Day14Puzzle() {

	}

	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(_initialisationInfo.parameters );
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {

		std::string input(m_InputLines[0]);
		std::string Part1Answer;
		std::string Part2Answer;

		unsigned elf1Index = 0;
		unsigned elf2Index = 1;

		std::vector<int> scores{ 3,7 };
		bool running = true;

		const int InputInt = std::atoi(input.c_str());
		std::vector<int> vectorisedScore;
		for (char _c : input) {
			vectorisedScore.emplace_back(std::atoi(&_c));
		}

		while (running) {
			bool twoAdded = false;
			const int ScoreSum = scores[elf1Index] + scores[elf2Index];

			const int Elf1NewScore = ScoreSum / 10 % 10;
			const int Elf2NewScore = ScoreSum % 10;
			if (ScoreSum >= 10) {
				scores.emplace_back(Elf1NewScore);
				twoAdded = true;
			}
			scores.emplace_back(Elf2NewScore);

			elf1Index += 1 + scores[elf1Index];
			elf1Index = elf1Index % scores.size();
			elf2Index += 1 + scores[elf2Index];
			elf2Index = elf2Index % scores.size();

			const bool part1StillRunning = scores.size() < static_cast<unsigned>(10 + InputInt);
			if (!part1StillRunning) {
				if (Part1Answer.empty()) {
					for (unsigned i = static_cast<unsigned>(InputInt); i < static_cast<unsigned>(InputInt) + 10; ++i) {
						Part1Answer += std::to_string(scores[i]);
					}
					if (!Part2Answer.empty()) {
						running = false;
					}
				}
			}

			for (unsigned addedOffset = 0; addedOffset < (twoAdded ? 2u : 1u); ++addedOffset) {
				if (scores.size() >= vectorisedScore.size() + addedOffset) {
					const unsigned startingScoreIndex = scores.size() - vectorisedScore.size() - addedOffset;

					bool found = true;
					for (unsigned i = 0; i < vectorisedScore.size(); ++i) {
						if (vectorisedScore[i] != scores[startingScoreIndex + i]) {
							found = false;
							break;
						}
					}

					if (found) {
						if (Part2Answer.empty()) {
							Part2Answer = std::to_string(scores.size() - vectorisedScore.size());
							if (!Part1Answer.empty()) {
								running = false;
							}
						}
					}
				}
			}
			

		}

		return { Part1Answer, Part2Answer };
	}

}
