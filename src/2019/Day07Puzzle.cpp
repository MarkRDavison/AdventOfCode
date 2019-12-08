#include <2019/Day07Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>

namespace TwentyNineteen {

	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Amplification Circuit", 2019, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	unsigned doPart1(const std::string& _input) {
		std::vector<IntcodeMachine> amplifiers;
		for (unsigned i = 0; i < 5; ++i) {
			IntcodeMachine& m = amplifiers.emplace_back();
			m.loadProgram(_input);
			m.haltWhenInputEmpty(true);
			m.haltWhenOutputSet(true);
		}

		std::vector<long> phase = { 0,1,2,3,4 };
		std::vector<long> bestPhase = { 0,1,2,3,4 };
		long max = 0;
		do {
			long out = 0;
			for (unsigned i = 0; i < 5; ++i) {
				auto& a = amplifiers[i];
				a.resetProgram();
				a.setInput(phase[i]);
				a.setInput(out);
				a.execute();
				out = a.getOutput();
			}

			if (out > max) {
				max = out;
				bestPhase = std::vector<long>(phase);
			}

		} while (std::next_permutation(phase.begin(), phase.end()));

		return max;
	}
	
	unsigned Day07Puzzle::doPart2(const std::string& _input) {
		std::vector<IntcodeMachine> amplifiers;

		std::vector<long> phase = { 5,6,7,8,9 };
		std::vector<long> bestPhase = { 5,6,7,8,9 };
		long max = 0;
		do {
			amplifiers.clear();
			for (unsigned i = 0; i < 5; ++i) {
				IntcodeMachine& m = amplifiers.emplace_back();
				m.loadProgram(_input);
				m.haltWhenInputEmpty(true);
				m.setInput(phase[i]);
			}

			while (!amplifiers[4].hasHaltedFromOpCode()) {
				for (unsigned i = 0; i < 5; ++i) {
					auto& a = amplifiers[i];
					auto& prevAmp = amplifiers[i == 0 ? 4 : i - 1];
					auto inp = prevAmp.getOutput();
					a.setInput(inp);
					a.execute();
					if (i == 4) {
						if (a.getOutput() > max) {
							max = a.getOutput();
							bestPhase = std::vector<long>(phase);
						}
					}
				}
			}
		} while (std::next_permutation(phase.begin(), phase.end()));

		return max;
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {

		long part1 = doPart1(m_InputLines[0]);
		long part2 = doPart2(m_InputLines[0]);
		
		return { std::to_string(part1), std::to_string(part2)};
	}
}
