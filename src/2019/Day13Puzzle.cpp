#include <2019/Day13Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>

#include <unordered_set>

namespace TwentyNineteen {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Care Package", 2019, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	static void dumpBoard(core::Region<int>& _board) {
		for (unsigned y = 0; y < 24; ++y) {
			for (unsigned x = 0; x < 44; ++x) {
				switch (_board.getCell(x, y)) {
				case 1:
					std::cout << '#';
					break;
				case 2:
					std::cout << '=';
					break;
				case 3:
					std::cout << 'P';
					break;
				case 4:
					std::cout << '*';
					break;
				default:
					std::cout << ' ';
					break;
				}
			}
			std::cout << std::endl;
		}
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		std::unordered_set<core::Vector2i, core::vector2_hash_fxn> blockLocations1;
		std::unordered_set<core::Vector2i, core::vector2_hash_fxn> blockLocations2;

		unsigned part1 = 0;
		core::Vector2i ballLoc;
		core::Vector2i paddleLoc;
		{
			core::Region<int> board;
			IntcodeMachine m{};
			m.loadProgram(m_InputLines[0]);

			std::vector<IntcodeValue> results;
			while (true) {
				auto res = m.executeResult();
				if (res == IntcodeMachine::ExecutionResult::Halt) {
					break;
				}
				if (res == IntcodeMachine::ExecutionResult::Input) {
					std::cout << "WTF" << std::endl;
					break;
				}
				if (res == IntcodeMachine::ExecutionResult::Output) {
					results.push_back(m.getOutput());

					if (results.size() == 3) {
						if (results[2] == 2) {
							part1++;
						}
						results.clear();
					}
				}
			}
		}
		IntcodeValue score = 0;
		{
			IntcodeMachine m{};
			m.loadProgram(m_InputLines[0]);
			m.setValue(2, 0);
			core::Region<int> board;

			std::vector<IntcodeValue> results;

			while (true) {
				auto res = m.executeResult();
				if (res == IntcodeMachine::ExecutionResult::Halt) {
					break;
				}
				if (res == IntcodeMachine::ExecutionResult::Input) {
					if (ballLoc.x > paddleLoc.x) {
						m.setInput(1); // RIGHT
					}
					else if (ballLoc.x < paddleLoc.x) {
						m.setInput(-1); // LEFT
					} 
					else {
						m.setInput(0);
					}
				}
				if (res == IntcodeMachine::ExecutionResult::Output) {
					auto out = m.getOutput();
					results.push_back(out);

					if (results.size() == 3) {
						auto x = results[0];
						auto y = results[1];
						auto s = results[2];
						results.clear();
						
						if (x == -1 && y == 0) {
							score = s;
						} else {

							board.getCell(x, y) = s;
							if (s == 4) {
								ballLoc = { static_cast<int>(x), static_cast<int>(y) };
							} else if (s == 3) {
								paddleLoc = { static_cast<int>(x), static_cast<int>(y) };
							}
						}
					}
				}
			}
		}

		return { std::to_string(part1), std::to_string(score) };
	}
}
