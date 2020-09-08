#include <2016/Day10Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Balance Bots", 2016, 10) {

	}
	Day10Puzzle::~Day10Puzzle() {

	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		auto info = Day10Puzzle::initialiseRobotInfo(m_InputLines);
		Day10Puzzle::iterateProcess(info);
		const auto part1 = Day10Puzzle::getRobotNumberProcessingMicrochips(info, 17, 61);
		const auto part2 = info.output[0] * info.output[1] * info.output[2];
		return { std::to_string(part1), std::to_string(part2) };
	}
	Day10Puzzle::RobotInfo Day10Puzzle::initialiseRobotInfo(const std::vector<std::string>& _input) {
		Day10Puzzle::RobotInfo info;

		for (const auto& i : _input) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, " ");

			if (s[0] == "value") {
				const int value = std::stoi(s[1]);
				const int robotNumber = std::stoi(s[5]);

				auto& bot = info.robots[robotNumber];
				bot.id = robotNumber;
				bot.input.push_back(value);
			}
			else {
				const int robotNumber = std::stoi(s[1]);
				const int lowOutputNumber = std::stoi(s[6]);
				const int highOutputNumber = std::stoi(s[11]);
				const bool outputLowBot = (s[5] == "bot");
				const bool outputHighBot = (s[10] == "bot");

				auto& bot = info.robots[robotNumber];
				bot.id = robotNumber;
				bot.lowOutputNumber = lowOutputNumber;
				bot.highOutputNumber = highOutputNumber;
				bot.low = outputLowBot
					? Robot::OutputType::Robot
					: Robot::OutputType::Output;
				bot.high = outputHighBot
					? Robot::OutputType::Robot
					: Robot::OutputType::Output;
			}

		}

		return info;
	}

	void Day10Puzzle::iterateProcess(RobotInfo& _info) {
		bool running = true;
		while (running) {
			running = false;
			for (auto& [id, robot] : _info.robots) {
				if (robot.input.size() == 2) {
					running = true;
					const int min = std::min(robot.input[0], robot.input[1]);
					const int max = std::max(robot.input[0], robot.input[1]);
					robot.process1 = min;
					robot.process2 = max;
					robot.input.clear();
					if (robot.low == Robot::OutputType::Robot) {
						_info.robots[robot.lowOutputNumber].input.push_back(min);
					}
					else {
						_info.output[robot.lowOutputNumber] = min;
					}
					if (robot.high == Robot::OutputType::Robot) {
						_info.robots[robot.highOutputNumber].input.push_back(max);
					} else {
						_info.output[robot.highOutputNumber] = max;
					}

					break;
				}
			}
		}
	}
	int Day10Puzzle::getRobotNumberProcessingMicrochips(const RobotInfo& _info, int _first, int _second) {
		for (const auto& [id, robot] : _info.robots) {
			if ((robot.process1 == _first && robot.process2 == _second) ||
				(robot.process1 == _second && robot.process2 == _first)) {
				return id;
			}
		}
		return -1;
	}
}
