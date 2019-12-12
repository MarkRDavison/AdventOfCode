#include <2019/Day11Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Orientation.hpp>
#include <unordered_set>

namespace TwentyNineteen {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Space Police", 2019, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {

		struct Panel {
			int colour{ 0 };
		};

		core::Region<Panel> hull;
		IntcodeMachine m1{};
		m1.loadProgram(m_InputLines[0]);
		std::vector<IntcodeValue> results;
		std::unordered_set<core::Vector2i, core::vector2_hash_fxn> visited;

		{
			core::Orientation orientation = core::Orientation::Up;
			core::Vector2i position{ 0,0 };

			while (true) {

				IntcodeMachine::ExecutionResult result = m1.executeResult();
				if (result == IntcodeMachine::ExecutionResult::Halt) {
					break;
				}
				if (result == IntcodeMachine::ExecutionResult::Input) {
					auto input = hull.getCell(position.x, position.y).colour;
					m1.setInput(input);
				}
				if (result == IntcodeMachine::ExecutionResult::Output) {
					results.push_back(m1.getOutput());

					if (results.size() == 2) {



						IntcodeValue o_0 = results[0];
						IntcodeValue o_1 = results[1];
						results.clear();

						auto& panel = hull.getCell(position.x, position.y);
						panel.colour = static_cast<int>(o_0);
						visited.insert(position);

						orientation = core::OrientationHelper::turn(orientation, o_1 == 0
							? core::Orientation::Left
							: core::Orientation::Right);

						position += core::OrientationHelper::toDirection(orientation);


					}
				}
			}

		}

		results.clear();
		IntcodeMachine m2{};
		m2.loadProgram(m_InputLines[0]);
		core::Region<Panel> hull2 = core::Region<Panel>();
		hull2.getCell(0,0).colour = 1;
		{
			core::Orientation orientation = core::Orientation::Up;
			core::Vector2i position{ 0,0 };

			while (true) {

				IntcodeMachine::ExecutionResult result = m2.executeResult();
				if (result == IntcodeMachine::ExecutionResult::Halt) {
					break;
				}
				if (result == IntcodeMachine::ExecutionResult::Input) {
					auto input = hull2.getCell(position.x, position.y).colour;
					m2.setInput(input);
				}
				if (result == IntcodeMachine::ExecutionResult::Output) {
					results.push_back(m2.getOutput());

					if (results.size() == 2) {



						IntcodeValue o_0 = results[0];
						IntcodeValue o_1 = results[1];
						results.clear();

						auto& panel = hull2.getCell(position.x, position.y);
						panel.colour = static_cast<int>(o_0);

						orientation = core::OrientationHelper::turn(orientation, o_1 == 0
							? core::Orientation::Left
							: core::Orientation::Right);

						position += core::OrientationHelper::toDirection(orientation);


					}
				}
			}

		}

		for (int y = 1; y > -7; --y) {
			for (int x = 00; x < 50; ++x) {
				std::cout << (hull2.getCell(x, y).colour == 0 ? ' ' : '#');
			}
			std::cout << std::endl;
		}

		return { std::to_string(visited.size()), "See output" };
	}
}
