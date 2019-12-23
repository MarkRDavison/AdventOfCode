#include <2019/Day23Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <array>
#include <set>

namespace TwentyNineteen {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Category Six", 2019, 23) {

	}
	Day23Puzzle::~Day23Puzzle() {

	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		std::array<IntcodeMachine, 50> network;
		std::array<std::vector<IntcodeValue>, 50> output;
		unsigned address = 0;
		for (IntcodeMachine& m : network) {
			m.loadProgram(m_InputLines[0]);
			m.setInput(address);
			address++;
		}

		bool part1Done = false;
		
		std::vector<IntcodeValue> nat;
		std::set<IntcodeValue> yValues;

		IntcodeValue part1 = 0;
		IntcodeValue part2 = 0;

		while (true) {
			address = 0;
			int idleCount = 0;
			for (IntcodeMachine& m : network) {
				auto status = m.executeResult();

				if  (status == IntcodeMachine::ExecutionResult::Input) {
					m.setInput(-1);
					status = m.executeResult();
				}
				if (status == IntcodeMachine::ExecutionResult::Output) {
					auto& outputBuffer = output[address];
					outputBuffer.push_back(m.getOutput());

					if (outputBuffer.size() == 3) {
						IntcodeValue target = outputBuffer[0];
						IntcodeValue x = outputBuffer[1];
						IntcodeValue y = outputBuffer[2];
						outputBuffer.clear();

						if (target == 255) {
							if (!part1Done) {
								part1Done = true;
								part1 = y;
							} 

							nat.clear();
							nat.push_back(x);
							nat.push_back(y);
							
						} else if (target < 50) {
							network[target].setInput(x);
							network[target].setInput(y);
						}
					}
				} else if (status == IntcodeMachine::ExecutionResult::Input) {
					idleCount++;
				}
				address++;
			}

			if (idleCount == 50 && !nat.empty()) {
				IntcodeMachine& m = network[0];
				m.setInput(nat[0]);
				m.setInput(nat[1]);
				if (yValues.count(nat[1]) > 0) {
					part2 = nat[1];
					return { std::to_string(part1), std::to_string(part2) };
				}
				yValues.insert(nat[1]);
				nat.clear();
			}
		}

	}
}
